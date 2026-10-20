import sys
import numpy as np

if len(sys.argv) < 4:
    print("Usage: python generator.py <N> <M> <ascending>")
    sys.exit(1)


n, m = map(int, sys.argv[1:3])
ascending_arg = sys.argv[3]
ascending = ascending_arg == "True"

print(n, m)

v = np.random.randint(0, n, (2, m))

equal = v[0] == v[1]
v[0, equal] -= 1

was_zero = v[0] == -1
v[0, was_zero] += 1
v[1, was_zero] += 1

if ascending:
    swap = v[0] > v[1]
    v[:, swap] = v[::-1, swap]


np.savetxt(sys.stdout, v, fmt="%d", delimiter=" ")
