# Cerință

Se dă o permutare $p_1, p_2, \ldots, p_n$. Într-o secundă se pot efectua oricâte interschimbări, cu condiția ca fiecare poziție să participe la cel mult una dintre ele. Interschimbarea $(i, j)$ schimbă între ele valorile de pe pozițiile $i$ și $j$. Să se sorteze permutarea într-un număr minim de secunde.

# Date de intrare

Pe prima linie se găsește un număr natural $n$. Pe a doua linie se găsesc $n$ numere naturale, $p_1, p_2, \ldots, p_n$.

# Date de ieșire

Pe prima linie se va găsi un număr natural $k$, numărul minim de secunde. Urmează cele $k$ secunde, în ordine. Pentru fiecare secundă se va afișa o linie cu numărul $m$ de interschimbări efectuate în acea secundă, urmată de $m$ linii, fiecare conținând două poziții $i$ și $j$.

# Restricții și precizări

* $1 \leq n \leq 200 \ 000$;
* $p$ este o permutare a numerelor $1, 2, \ldots, n$;
* Dacă există mai multe soluții, se poate afișa oricare.

| # | Punctaj | Restricții |
|---|---------|------------|
| 1 | 40 | $n$ este par și $p = 2, 1, 4, 3, \ldots, n, n - 1$ |
| 2 | 30 | Fiecare ciclu$^\dagger$ al permutării are lungimea cel mult $3$ |
| 3 | 30 | Fără restricții suplimentare |

$^\dagger$ Un ciclu al permutării este un șir de poziții distincte $i_1, i_2, \ldots, i_k$ cu proprietatea că $p_{i_1} = i_2$, $p_{i_2} = i_3$, $\ldots$, $p_{i_{k-1}} = i_k$ și $p_{i_k} = i_1$. Numărul $k$ este lungimea ciclului. Fiecare poziție face parte din exact un ciclu; de exemplu, permutarea $2, 3, 1, 5, 4$ are ciclurile $(1, 2, 3)$ și $(4, 5)$, iar o poziție $i$ cu $p_i = i$ formează singură un ciclu de lungime $1$.

# Exemplul 1

`stdin`
```
5
2 3 1 5 4
```

`stdout`
```
2
2
2 3
4 5
1
1 2
```

## Explicație

După prima secundă permutarea devine $2, 1, 3, 4, 5$, iar după a doua devine $1, 2, 3, 4, 5$.

# Exemplul 2

`stdin`
```
3
1 2 3
```

`stdout`
```
0
```

## Explicație

Permutarea este deja sortată.
