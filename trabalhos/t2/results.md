Pthreads:

| Tamanho  | Repetições | 1 Thread | 2 Threads | 4 Threads |
| -------- | ---------- | -------- | --------- | --------- |
| 1000000  | 1000       | 2721892  | 1386003   | 772170    |
| 1000000  | 2000       | 5408812  | 2825345   | 1543960   |
| 5000000  | 1000       | 13598542 | 7034924   | 4775388   |
| 5000000  | 2000       | 27349511 | 14037434  | 9531410   |
| 10000000 | 1000       | 27357584 | 14082316  | 9717152   |
| 10000000 | 2000       | 54406983 | 28181426  | 19440930  |

| Tamanho  | Repetições | 2 Threads(Speedup) | 4 Threads(Speedup) |
| -------- | ---------- | ------------------ | ------------------ |
| 1000000  | 1000       | 1.96               | 3.52               |
| 1000000  | 2000       | 1.91               | 3.50               |
| 5000000  | 1000       | 1.93               | 2.84               |
| 5000000  | 2000       | 1.94               | 2.86               |
| 10000000 | 1000       | 1.94               | 2.81               |
| 10000000 | 2000       | 1.93               | 2.79               |

OpenMP:
