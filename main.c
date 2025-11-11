#include <stdio.h>
#include <stdlib.h> 


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Ошибка\n");
        return 1;
    }


    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    int n, m;
    if (fscanf(f, "%d %d", &n, &m) != 2) {
        printf("Ошибка чтения размеров матрицы.\n");
        fclose(f);
        return 1;
    }

    if (n != m || n < 4) {
        printf("Ошибка: матрица должна быть квадратной и иметь размер не менее 4x4.\n");
        fclose(f);
        return 1;
    }


    int *matrix = (int *)malloc(n * m * sizeof(int));
    if (matrix == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fscanf(f, "%d", &matrix[i * m + j]) != 1) {
                printf("Ошибка чтения элемента матрицы.\n");
                fclose(f);
                free(matrix);
                return 1;
            }
        }
    }
    fclose(f);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i * m + j]);
        }
        printf("\n");
    }

    long long res = 1;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j < n - 1 && matrix[i * m+ j] > 0) {
                res *= matrix[i * m + j];
            }
        }
    }

    if (res != 1) {
        printf("Произведение положительных элементов: %lld\n", res);
    } else {
        printf("Положительных элементов выше побочной диагонали нет.\n");
    }


    int min_val = matrix[0 * m + 1];
    int min_i = 0;

    for (int i = 1; i < n; i++) {
        if (matrix[i * m + 1] < min_val) {
            min_val = matrix[i * m + 1];
            min_i = i;
        }
    }


    int temp = matrix[min_i * m + 1];
    matrix[min_i * m + 1] = matrix[3 * m + 2];
    matrix[3 * m + 2] = temp;



    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i * m + j]);
        }
        printf("\n");
    }


    free(matrix);
    return 0;
}
