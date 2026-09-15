#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));    
    int m, f_s;
    printf("размер массива m:\n");
    scanf("%d", &m);
    int **matrix = malloc(m * sizeof(int*));
    
    printf("matrix:\n");
    for(int i = 0; i < m; ++i){
        matrix[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = rand()%10;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // printf("sums colms enter 0, sums rows enter 1:\n");
    // scanf("%d", &f_s);
    int sum = 0;
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < m-i-1; ++j) {
            sum += matrix[i][j];
            // if (f_s == 0) sum += matrix[j][i];
            // else sum += matrix[i][j];
            // printf("%d ", matrix[i][j]);
        }
        // printf("\n");
    }
    printf("%d ", sum);
    printf("\n");
        

    for(int i = 0; i < m; ++i){
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}
