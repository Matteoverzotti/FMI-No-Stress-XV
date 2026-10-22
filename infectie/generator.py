# s1: n = 1, m <= 1e5
# s2: n = 2, m <= 1e5
# s3: n,m <= 500
# s4: full

import numpy as np 
import sys

def gen(subtsk: int, lim: int):
    n,m=None,None
    if subtsk==1:
        n=1
        if lim>0: 
            m=10**5
        else:
            m=np.random.randint(1,10**5)
    elif subtsk==2:
        n=2
        if lim>0: 
            m=10**5
        else:
            m=np.random.randint(1,10**5)
    elif subtsk==3:
        if lim>0:
            n=m=500
        else:
            n=np.random.randint(300,500)
            m=np.random.randint(300,500)
    elif subtsk==4:
        if lim>0:
            n=m=10**9
        else:
            n=np.random.randint(10**7,10**9)
            m=np.random.randint(10**7,10**9)
    else:
        print("no such subtask")
        return 
    print(n,m)

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
    
    
