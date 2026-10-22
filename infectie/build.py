import numpy as np 
import sys 
import subprocess

cnt_tests=[5,5,5,10]

src="matei-100"
gen="generator"

def setup(src):
    comm=f"g++ -std=c++23 {src}.cpp -o {src}"
    subprocess.run(comm, shell=True, check=True)

def generate(src, gen):
    cnt=0
    curr_seed=0
    for sub_idx in range(len(cnt_tests)):
        for test_idx in range(cnt_tests[sub_idx]):
            file=""
            if cnt<10:
                file="0"+str(cnt)
            else:
                file=str(cnt)
            cnt+=1

            file=file+"-test"

            curr_seed+=1
            is_lim=0
            if test_idx==cnt_tests[sub_idx]-1:
                is_lim=1

            comm=f"python3 {gen}.py {curr_seed} {sub_idx+1} {is_lim} > {file}.in"
            subprocess.run(comm, shell=True, check=True)

            comm=f"./{src} < {file}.in > {file}.out"
            subprocess.run(comm, shell=True, check=True)

def zip_em():
    cnt=0
    all_tests=[]
    for sub_idx in range(len(cnt_tests)):
        for _ in range(cnt_tests[sub_idx]):
            file=""
            if cnt<10:
                file="0"+str(cnt)
            else:
                file=str(cnt)
            cnt+=1
            file=file+"-test"
            all_tests.append(file+".in")
            all_tests.append(file+".out")

    comm=f"zip teste.zip {" ".join(all_tests)}"
    subprocess.run(comm, shell=True, check=True)
    
def cleanup():
    subprocess.run(f"rm {src}", shell=True, check=True)
    cnt=0
    for sub_idx in range(len(cnt_tests)):
        for _ in range(cnt_tests[sub_idx]):
            file=""
            if cnt<10:
                file="0"+str(cnt)
            else:
                file=str(cnt)
            cnt+=1
            file=file+"-test"
            subprocess.run("rm "+file+".in", shell=True, check=True)
            subprocess.run("rm "+file+".out", shell=True, check=True)


def main():
    setup(src)
    generate(src,gen)
    zip_em()
    cleanup()

if __name__=="__main__":
    main()