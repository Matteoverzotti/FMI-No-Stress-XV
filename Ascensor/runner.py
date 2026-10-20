import subprocess

def compile(files):
    for file in files:
        command = f"g++ -O2 -Wall -fsanitize=address,undefined,signed-integer-overflow -std=c++20 {file}.cpp -o {file}"
        subprocess.run(command, shell=True, check=True)

def remove_files(files):
    for file in files:
        command = f"rm {file}"
        subprocess.run(command, shell=True, check=True)

def zip_files(files, zip_name="tests.zip"):
    file_list = " ".join(files)
    command = f"zip {zip_name} {file_list}"
    subprocess.run(command, shell=True, check=True)

def generate_tests(generator, solution):
    # Subtask 1: s_i < t_i
    # Subtask 2: 1 <= N, M <= 2e5
    args = [
        [
            [2, 5, True],
            [10, 200, True],
            [10000, 20000, True],
            [93810, 138292, True],
            [200000, 200000, True],
        ],
        [
            [2, 10, False],
            [38, 294, False],
            [3942, 28392, False],
            [200000, 3, False],
            [200000, 200000, False],
        ]
    ]
    
    files = []
    for subtask_id in range(len(args)):
        for test_id in range(len(args[subtask_id])):
            n, m, ascending = args[subtask_id][test_id]
            file = f"subtask{subtask_id}-test{test_id}"
            gen_command = f"python3 {generator}.py {n} {m} {ascending} > {file}.in"
            subprocess.run(gen_command, shell=True, check=True)
            sol_command = f"./{solution} < {file}.in > {file}.ok"
            subprocess.run(sol_command, shell=True, check=True)
            files.append(file + ".in")
            files.append(file + ".ok")

            print(f"Generated {file}.in and {file}.ok with N={n}, M={m} ascending={ascending}")

    return files

def main():
    files = ["matteo"]
    compile(files)
        
    test_files = generate_tests("generator", "matteo")
    # for file in test_files:
    #     files.append(file)
    #
    zip_files(test_files)

    remove_files(files)

main()
