#include <stdio.h>
int m, n;
char matrix[105][105] = {{0}};
 
void dfs(int x, int y) {
    matrix[x][y] = '.'; //현재 위치를 .으로 바꿈
 
    for (int i = -1; i <= 1; i++){ 
        for (int j = -1; j <= 1; j++){
            int a = x + i;
            int b = y + j; //주변 8자리를 검사
 
            if (matrix[a][b] == 'W') { 
                dfs(a, b); 
            }
        }
    }
}
 
int main(void) {
    int number = 0; 
    scanf("%d %d\n", &m, &n);
 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%c", &matrix[i][j]);
        }
    }

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (matrix[i][j] == 'W'){ 
                dfs(i, j); 
                number++;
            }
        }
    }
    printf("%d\n", number);
    return 0;
}