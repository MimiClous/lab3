#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Ошибка");
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


    int matrix[n][m];


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fscanf(f, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка чтения элемента матрицы.\n");
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    long long product = 1;
    int has_positive = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j < n - 1 && matrix[i][j] > 0) {
                product *= matrix[i][j];
                has_positive = 1;
            }
        }
    }

    if (has_positive) {
        printf("Произведение положительных элементов: %lld\n", product);
    } else {
        printf("Положительных элементов выше побочной диагонали нет.\n");
    }


    int min_val = matrix[0][1];
    int min_i = 0;

    for (int i = 1; i < n; i++) {
        if (matrix[i][1] < min_val) {
            min_val = matrix[i][1];
            min_i = i;
        }
    }


    int temp = matrix[min_i][1];
    matrix[min_i][1] = matrix[3][2];
    matrix[3][2] = temp;



    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
