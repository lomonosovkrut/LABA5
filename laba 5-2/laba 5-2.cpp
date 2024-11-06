#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void generateAdjacencyMatrix(int n, int** G) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i != j) {
                G[i][j] = rand() % 2; // Генерация случайного ребра
                G[j][i] = G[i][j];    // Симметричное значение для неориентированного графа
            }
            else {
                G[i][j] = 0; // Нет петель
            }
        }
    }
}

void printAdjacencyMatrix(int n, int** G) {
    setlocale(LC_ALL, "RUS");
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

int** createIncidenceMatrix(int n, int** G, int* edgeCount) {
    *edgeCount = 0;

    // Сначала подсчитываем количество рёбер
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                (*edgeCount)++;
            }
        }
    }

    // Создаем матрицу инцидентности
    int** incidenceMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        incidenceMatrix[i] = (int*)calloc(*edgeCount, sizeof(int));
    }

    // Заполняем матрицу инцидентности
    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1;  // Инцидентность для первой вершины
                incidenceMatrix[j][edgeIndex] = 1;  // Инцидентность для второй вершины
                edgeIndex++;
            }
        }
    }

    return incidenceMatrix;
}

void printIncidenceMatrix(int n, int** incidenceMatrix, int edgeCount) {
    setlocale(LC_ALL, "RUS");
    printf("Матрица инцидентности графа G:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incidenceMatrix[i][j]);
        }
        printf("\n");
    }
}

void findVertexTypes(int n, int** G) {
    setlocale(LC_ALL, "RUS");
    int* degrees = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        degrees[i] = 0; // Инициализация степеней вершин
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degrees[i] += G[i][j]; // Подсчет степени вершины
        }
    }

    for (int i = 0; i < n; i++) {
        if (degrees[i] == 0) {
            printf("Вершина %d - изолированная\n", i);
        }
        if (degrees[i] == 1) {
            printf("Вершина %d - концевая\n", i);
        }
    }

    int max_degree = 0;
    for (int i = 0; i < n; i++) {
        if (degrees[i] > max_degree) {
            max_degree = degrees[i]; // Находим максимальную степень
        }
    }

    for (int i = 0; i < n; i++) {
        if (degrees[i] == max_degree) {
            printf("Вершина %d - доминирующая\n", i);
        }
    }

    free(degrees);
}

int main(void) {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int n;

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    // Создание матрицы смежности
    int** G = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
    }

    // Генерация матрицы смежности
    generateAdjacencyMatrix(n, G);
    printAdjacencyMatrix(n, G);

    // Создание матрицы инцидентности
    int edgeCount;
    int** incidenceMatrix = createIncidenceMatrix(n, G, &edgeCount);
    printIncidenceMatrix(n, incidenceMatrix, edgeCount);

    // Нахождение изолированных, концевых и доминирующих вершин
    findVertexTypes(n, G);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(G[i]);
        free(incidenceMatrix[i]);
    }
    free(G);
    free(incidenceMatrix);

    return 0;
}