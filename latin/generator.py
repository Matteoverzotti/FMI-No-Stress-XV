# s1: k = 1 - 5p
# s2: k = 2, n <= 16 - 15p 
# s3: k = 3, n <= 10 - 10p
# s4: k > 3 - 10p 
# s5: k = 2 - 60p

import numpy as np 
import sys 

def gen(subtsk, is_lim):
    n,k=None,None
    if subtsk==1:
        k=1
        if is_lim>0:
            n=10**5
        else:
            n=np.random.randint(1,10**5)
    elif subtsk==2:
        k=2 
        if is_lim>0:
            n=16
        else:
            n=np.random.randint(3,16)
    elif subtsk==3:
        k=3 
        if is_lim>0:
            n=10
        else:
            n=np.random.randint(4,10)
    elif subtsk==4:
        if is_lim>0:
            k=26
            n=10**5
        else:
            k=np.random.randint(4,27)
            n=np.random.randint(10**4,10**5)
    elif subtsk==5:
        k=2
        if is_lim>0:
            n=10**5
        else:
            n=np.random.randint(10**4,10**5)
    else:
        print("no such subtask")
        return 
    print(n,k)

def main():
    if len(sys.argv)<4:
        print("give <seed> <subtask> <is_limit_case>")
        exit(0)

    seed=int(sys.argv[1])
    subtsk=int(sys.argv[2])
    is_lim=int(sys.argv[3])
    
    np.random.seed(seed)
    gen(subtsk,is_lim)

if __name__=="__main__":
    main()