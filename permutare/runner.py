# Generates tests/<subtask>_test<id>.in/.ok and tests.zip, checking every test against its subtask.
import os
import subprocess
import sys
import tempfile
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
TESTS = os.path.join(HERE, "tests")

# Generator arguments for each test, one list per subtask.
SUBTASKS = [
    # Subtask 1 (40p): n is even and p = 2 1 4 3 ... n n-1
    [
        "2 -p",
        "10 -p",
        "1000 -p",
        "99998 -p",
        "200000 -p",
    ],
    # Subtask 2 (30p): every cycle has length at most 3
    [
        "1 1",
        "7 -c 3 2 1 1",
        "200000 1",
        "200000 -c 3 1x199997",
        "200000 -c 2x99000 1x2000",
        "200000 -c 3x66666 2",
        "200000 -c 3x40000 2x30000 1x20000",
        "123457 -c 3x20000 2x30000 1x3457",
    ],
    # Subtask 3 (30p): no extra restrictions
    [
        "5 5",
        "200000 -c 4 1x199996",
        "199999 4",
        "200000 7",
        "200000 1000",
        "200000 -c 100000",
        "200000 -c",
        "200000 200000",
    ],
]


def compile(sources, out_dir):
    for source in sources:
        subprocess.run(["g++", "-O2", "-std=c++20", os.path.join(HERE, source + ".cpp"),
                        "-o", os.path.join(out_dir, source)], check=True)


def cycle_lengths(p):
    seen = [False] * len(p)
    lengths = []
    for i in range(1, len(p)):
        length, j = 0, i
        while not seen[j]:
            seen[j] = True
            j = p[j]
            length += 1
        if length:
            lengths.append(length)
    return lengths


def check_subtask(subtask, text):
    n, *values = map(int, text.split())
    p = [0] + values
    if not 1 <= n <= 200000 or sorted(values) != list(range(1, n + 1)):
        return False
    if subtask == 1:
        return n % 2 == 0 and all(p[i] == (i + 1 if i % 2 else i - 1) for i in range(1, n + 1))
    if subtask == 2:
        return max(cycle_lengths(p)) <= 3
    return True


def main():
    os.makedirs(TESTS, exist_ok=True)
    with tempfile.TemporaryDirectory() as bin_dir:
        compile(["model-radu", "checker"], bin_dir)
        model, checker = (os.path.join(bin_dir, name) for name in ("model-radu", "checker"))

        files = []
        for subtask, tests in enumerate(SUBTASKS, start=1):
            for test, args in enumerate(tests, start=1):
                name = os.path.join(TESTS, f"{subtask}_test{test}")
                text = subprocess.run([sys.executable, os.path.join(HERE, "generator.py"), *args.split()],
                                      check=True, capture_output=True, text=True).stdout
                if not check_subtask(subtask, text):
                    sys.exit(f"{name}.in breaks the restrictions of subtask {subtask}")
                with open(name + ".in", "w") as f:
                    f.write(text)

                answer = subprocess.run([model], input=text, check=True, capture_output=True, text=True).stdout
                with open(name + ".ok", "w") as f:
                    f.write(answer)
                # The checker makes sure the model's swaps are legal and sort the permutation.
                verdict = subprocess.run([checker, name + ".in", name + ".ok", name + ".ok"],
                                         capture_output=True, text=True)
                if float(verdict.stdout) != 1:
                    sys.exit(f"the model fails {name}.in: {verdict.stderr.strip()}")

                files += [name + ".in", name + ".ok"]
                print(f"{subtask}_test{test}: {args} -> {answer.split()[0]} seconds")

    with zipfile.ZipFile(os.path.join(HERE, "tests.zip"), "w", zipfile.ZIP_DEFLATED) as archive:
        for file in files:
            archive.write(file, os.path.basename(file))


main()
