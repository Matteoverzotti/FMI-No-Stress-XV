# Generates tests/<subtask>_test<id>.in/.ok and tests.zip, checking every test against its subtask.
import os
import subprocess
import sys
import tempfile
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
TESTS = os.path.join(HERE, "tests")

# The brute is O(max(dr) * m), so it double-checks the model only below this.
BRUTE_LIMIT = 10 ** 6

# Generator arguments for each test, one list per subtask.
SUBTASKS = [
    # Subtask 1 (60p): dr_i <= 100
    [
        "2 1 0",
        "5 4 3 -p 0 -e",
        "4 10 100 -p 30",
        "2 100 100",
        "10 30 100 -p 0",
        "30 100 100 -k 5",
        "50 100 100 -p 0",
        "50 100 100 -p 40 -k 8",
        "50 100 100 -p 50 -e",
        "50 100 100 -f",
        "3 50 100 -l",
        "20 100 100 -p 10 -l",
    ],
    # Subtask 2 (40p): no extra restrictions
    [
        "2 1 1000000000 -f",
        "2 100 1000000000 -f",
        "50 49 1000000000 -p 999999950 -e",
        "50 100 1000000 -p 500000",
        "10 100 1000000000 -p 0",
        "50 100 1000000000 -p 0",
        "50 100 1000000000 -p 500000000",
        "50 100 1000000000 -p 999999000 -k 20",
        "50 100 1000000000 -p 123456789 -k 200",
        "50 100 1000000000 -f",
        "50 100 1000000 -p 700000 -l",
        "5 100 1000000000 -p 2 -k 10 -l",
        "50 100 1000000000 -p 300000000 -l",
    ],
]


def compile(sources, out_dir):
    for source in sources:
        subprocess.run(["g++", "-O2", "-std=c++20", os.path.join(HERE, source + ".cpp"),
                        "-o", os.path.join(out_dir, source)], check=True)


def check_subtask(subtask, text):
    n, m, *values = map(int, text.split())
    edges = [values[i:i + 4] for i in range(0, len(values), 4)]
    if not (2 <= n <= 50 and 1 <= m <= 100 and len(edges) == m and len(edges[-1]) == 4):
        return False
    if not all(1 <= u <= n and 1 <= v <= n and 0 <= st <= dr <= 10 ** 9 for u, v, st, dr in edges):
        return False
    if subtask == 1:
        return all(dr <= 100 for *_, dr in edges)
    return True


def run(binary, text):
    return subprocess.run([binary], input=text, check=True, capture_output=True, text=True).stdout


def main():
    os.makedirs(TESTS, exist_ok=True)
    with tempfile.TemporaryDirectory() as bin_dir:
        compile(["model-radu", "brute"], bin_dir)
        model, brute = (os.path.join(bin_dir, name) for name in ("model-radu", "brute"))

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

                answer = run(model, text)
                with open(name + ".ok", "w") as f:
                    f.write(answer)
                if max(int(line.split()[3]) for line in text.splitlines()[1:]) <= BRUTE_LIMIT \
                        and run(brute, text) != answer:
                    sys.exit(f"the model and the brute disagree on {name}.in")

                files += [name + ".in", name + ".ok"]
                print(f"{subtask}_test{test}: {args} -> {answer.strip()}")

    with zipfile.ZipFile(os.path.join(HERE, "tests.zip"), "w", zipfile.ZIP_DEFLATED) as archive:
        for file in files:
            archive.write(file, os.path.basename(file))


main()
