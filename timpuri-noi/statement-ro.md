# Cerință

Se dă un graf neorientat cu $n$ noduri și $m$ muchii. Muchia $i$ unește nodurile $u_i$ și $v_i$ și are asociat un interval $[st_i, dr_i]$: ea poate fi parcursă doar dacă numărul de muchii parcurse înainte este cuprins între $st_i$ și $dr_i$, inclusiv.

Un drum este un șir de muchii $e_1, e_2, \ldots, e_k$, cu $k \geq 1$, care pornește din nodul $1$, în care fiecare muchie continuă din nodul în care s-a terminat cea dinainte și în care muchia $e_j$ respectă $st_{e_j} \leq j - 1 \leq dr_{e_j}$. Nodurile și muchiile se pot repeta. Să se afle câte drumuri se termină în nodul $n$. Deoarece rezultatul poate fi foarte mare, se cere modulo $10^9 + 7$.

# Date de intrare

Pe prima linie se găsesc două numere naturale, $n$ și $m$. Pe fiecare dintre următoarele $m$ linii se găsesc patru numere naturale, $u_i$, $v_i$, $st_i$ și $dr_i$.

# Date de ieșire

Pe prima linie se va găsi un număr natural, numărul de drumuri care se termină în nodul $n$, modulo $10^9 + 7$.

# Restricții și precizări

* $2 \leq n \leq 50$;
* $1 \leq m \leq 100$;
* $1 \leq u_i, v_i \leq n$;
* $0 \leq st_i \leq dr_i \leq 10^9$;
* Între două noduri pot exista mai multe muchii și pot exista muchii cu $u_i = v_i$. Două drumuri sunt diferite dacă diferă șirurile lor de muchii.

| # | Punctaj | Restricții |
|---|---------|------------|
| 1 | 60 | $dr_i \leq 100$ |
| 2 | 40 | Fără restricții suplimentare |

# Exemplul 1

`stdin`
```
4 4
1 2 0 1
2 3 1 3
3 4 2 2
2 4 3 5
```

`stdout`
```
4
```

## Explicație

Cele $4$ drumuri care se termină în nodul $4$ trec, în ordine, prin nodurile: $1, 2, 3, 4$; $1, 2, 3, 2, 4$; $1, 2, 3, 4, 2, 4$; $1, 2, 3, 2, 4, 2, 4$. După $6$ muchii parcurse nu se mai poate folosi nicio muchie.

# Exemplul 2

`stdin`
```
2 2
1 2 0 2
1 2 1 1
```

`stdout`
```
3
```

## Explicație

Drumurile sunt $(1)$, $(1, 1, 1)$ și $(1, 2, 1)$, unde fiecare drum este dat prin indicii muchiilor parcurse. Primul drum ajunge în nodul $2$ și se oprește, iar celelalte două trec prin nodul $2$, se întorc în nodul $1$ și ajung din nou în nodul $2$.
