import random
import sys

USAGE = """Usage:
  python generator.py <N> <K>                every cycle has length as close to K as possible
  python generator.py <N> -c <L1> <L2> ...   cycles of lengths L1, L2, ..., the rest is random
                                             (LxC stands for C cycles of length L)
  python generator.py <N> -p                 the permutation 2 1 4 3 ... N N-1 (N even)"""

if len(sys.argv) < 3:
    print(USAGE)
    sys.exit(1)

n = int(sys.argv[1])
if n < 1:
    print("N must be positive")
    sys.exit(1)


def split(cycles):
    # Lengths differ by at most one and add up to n.
    q, r = divmod(n, cycles)
    return [q + 1] * r + [q] * (cycles - r)


def badness(k, lengths):
    # Ties go to the split whose longest cycle is on the same side of 2 as k,
    # so the answer (0, 1 or 2 seconds) stays what k suggests.
    return max(abs(length - k) for length in lengths), (max(lengths) <= 2) != (k <= 2)


def parse_lengths(args):
    lengths = []
    for arg in args:
        length, _, count = arg.partition("x")
        lengths += [int(length)] * int(count or 1)
    return lengths


if sys.argv[2] == "-p":
    if n % 2:
        print("N must be even")
        sys.exit(1)
    print(n)
    print(*(i + 1 if i % 2 else i - 1 for i in range(1, n + 1)))
    sys.exit(0)

if sys.argv[2] == "-c":
    lengths = parse_lengths(sys.argv[3:])
    if any(length < 1 for length in lengths) or sum(lengths) > n:
        print("Cycle lengths must be positive and add up to at most N")
        sys.exit(1)
else:
    k = int(sys.argv[2])
    if k < 1:
        print("K must be positive")
        sys.exit(1)
    candidates = [c for c in (n // k, n // k + 1) if 1 <= c <= n]
    lengths = min((split(c) for c in candidates), key=lambda lengths: badness(k, lengths))
    random.shuffle(lengths)

positions = list(range(1, n + 1))
random.shuffle(positions)

p = [0] * (n + 1)
start = 0
for length in lengths:
    cycle = positions[start:start + length]
    for i in range(length):
        p[cycle[i]] = cycle[(i + 1) % length]
    start += length

# Positions outside the requested cycles get a uniformly random permutation among themselves.
rest = positions[start:]
images = rest[:]
random.shuffle(images)
for i, image in zip(rest, images):
    p[i] = image

print(n)
print(*p[1:])
