import random
import sys

USAGE = """Usage:
  python generator.py <N> <M> <D> [-p S [-e]] [-f | -k K] [-l]
    M random edges with 0 <= st <= dr <= D, interval lengths log-uniform in [0, D]
    -p S   the first N - 1 edges form a path 1 -> N that can be walked starting at time S
           (bounce on its first edge until time S, then take one path edge per step)
    -e     path edges are open only at the moment they are needed
    -f     every random edge is open on [0, D]
    -k K   the ends of the random intervals are taken from only K distinct values
    -l     every random edge is a self-loop with probability 1/4
The same arguments always produce the same test."""

args = sys.argv[1:]
if len(args) < 3:
    print(USAGE)
    sys.exit(1)

random.seed(" ".join(args))
n, m, d = map(int, args[:3])
flags = args[3:]


def flag(name):
    return name in flags


def value(name):
    return int(flags[flags.index(name) + 1])


if n < 2 or m < 1 or d < 0:
    print("Need N >= 2, M >= 1 and D >= 0")
    sys.exit(1)


def log_uniform(limit):
    # Short lengths are as likely as long ones, so both sparse and dense times show up.
    return int((limit + 1) ** random.random()) - 1


def random_interval():
    if flag("-f"):
        return 0, d
    if flag("-k"):
        return tuple(sorted(random.choices(ends, k=2)))
    length = log_uniform(d)
    st = random.randint(0, d - length)
    return st, st + length


if flag("-k"):
    ends = random.sample(range(d + 1), min(value("-k"), d + 1))

edges = []
if flag("-p"):
    # Bouncing on the first edge keeps us on node 1 at even times only.
    s = value("-p") // 2 * 2
    if m < n - 1 or s + n - 2 > d:
        print("Need M >= N - 1 and S + N - 2 <= D")
        sys.exit(1)
    middle = list(range(2, n))
    random.shuffle(middle)
    path = [1] + middle + [n]
    for j in range(n - 1):
        t = s + j
        st, dr = (0 if j == 0 else t), t
        if not flag("-e"):
            st, dr = max(0, st - log_uniform(d)), min(d, dr + log_uniform(d))
        edges.append((path[j], path[j + 1], st, dr))

while len(edges) < m:
    u, v = random.sample(range(1, n + 1), 2)
    if flag("-l") and random.random() < 0.25:
        v = u
    edges.append((u, v, *random_interval()))

random.shuffle(edges)
print(n, m)
for u, v, st, dr in edges:
    if random.random() < 0.5:
        u, v = v, u
    print(u, v, st, dr)
