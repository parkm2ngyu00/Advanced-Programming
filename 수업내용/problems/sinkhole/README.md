# 싱크홀 (Sinkhole)

크기가 M * N인 격자모양의 구역에서 지하철 공사를 하고 있었습니다.

There is a subway construction in a grid-shaped area with m * n.

각 격자 g의 상하, 좌우 그리고 대각선 네 군데 등 8 개의 격자를 인접한 격자라고 부릅니다.

The 8 grids, including the upper and lower, left and right, and four diagonal lattice of each grid, are called adjacent lattice.

최근 비가 많이 내리면서 일부 격자에 지반이 함몰되는 현상 (싱크홀)이 발생하였습니다.

Recently, as it rained a lot, sinkholes have occured in some grids.

싱크홀은 하나의 격자 크기로 발생하였으나, 편의 상 하나의 격자에 대해해 인접한 격자에도 싱크홀이 발생했을 경우 모두 하나의 싱크홀로 간주합니다.

A sinkhole occured in one grid size, but it is considered as one sinkhole if sinkholes occured at the adjacent lattices of the sinkhole. 

지도 정보가 주어졌을 때 위에서 정의한 싱크홀의 개수를 세는 프로그램을 작성하세요.

When given map information, write a program that counts the number of sinkholes defined above.

# 입력 (Input)

입력 첫 줄에는 가로 M (M<=60)과 세로 N (N<=60)가 주어집니다.

The firts line of input is given horizontal M (M <= 60) and vertical N (N <= 60).

다음 줄부터 M * N 지도 정보가 주어집니다.

From the next line, m * n map information is given.

싱크홀은 W로 표시하며, 그 외 격자는 . 으로 표시합니다.

The sinkhole is marked as 'W', and the other lattices are presented as '.'.

# 출력 (Output)

싱크홀의 개수를 출력합니다.

Print the number of sinkholes.

예제 입력 (Sample Input)

```
8 12
W........WW.
.WWW.....WWW
....WW....WW
............
..W.........
.WWW........
...WW.......
............
```

예제 출력 (Sample Output)

```
3
```
