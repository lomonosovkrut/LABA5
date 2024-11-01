
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


#define MAX_VERTICES 10 // Увеличим максимальное количество вершин для большей гибкости
#define MAX_EDGES 20    // Увеличим максимальное количество рёбер

// Функция для создания матрицы инцидентности на основе матрицы смежности
void create_incidence_matrix(int graph[MAX_VERTICES][MAX_VERTICES], int incidence_matrix[MAX_VERTICES][MAX_EDGES], int* edges) {
    int edge_index = 0;

    // Инициализация матрицы инцидентности
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_EDGES; j++) {
            incidence_matrix[i][j] = 0;
        }
    }

    // Заполнение матрицы инцидентности на основе матрицы смежности
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = i + 1; j < MAX_VERTICES; j++) {
            if (graph[i][j] == 1) { // Если есть ребро
                incidence_matrix[i][edge_index] = 1; // Инцидентность для первой вершины
                incidence_matrix[j][edge_index] = 1; // Инцидентность для второй вершины
                edge_index++;
            }
        }
    }

    *edges = edge_index; // Обновляем количество рёбер
}

// Функция для нахождения изолированных, концевых и доминирующих вершин
void find_special_vertices(int incidence_matrix[MAX_VERTICES][MAX_EDGES], int vertices, int edges) {
    setlocale(LC_ALL, "RUS");
    int max_incident_count = 0;
    int dominant_vertex = -1;

    // Сначала находим максимальное количество инцидентных рёбер
    for (int i = 0; i < vertices; i++) {
        int incident_count = 0;
        for (int j = 0; j < edges; j++) {
            if (incidence_matrix[i][j] == 1) {
                incident_count++;
            }
        }

        if (incident_count > max_incident_count) {
            max_incident_count = incident_count;
            dominant_vertex = i; // Запоминаем вершину с максимальным количеством рёбер
        }
    }

    // Теперь определяем типы вершин
    for (int i = 0; i < vertices; i++) {
        int incident_count = 0;
        for (int j = 0; j < edges; j++) {
            if (incidence_matrix[i][j] == 1) {
                incident_count++;
            }
        }

        if (incident_count == 0) {
            printf("Вершина %d является изолированной.\n", i);
        }
        else if (incident_count == 1) {
            printf("Вершина %d является концевой.\n", i);
        }
        else if (i == dominant_vertex && incident_count == max_incident_count) {
            printf("Вершина %d является доминирующей.\n", i);
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int num_vertices;
    printf("Введите количество вершин (максимум %d): ", MAX_VERTICES);
    scanf("%d", &num_vertices);

    // Проверка на допустимое количество вершин
    if (num_vertices < 1 || num_vertices > MAX_VERTICES) {
        printf("Ошибка: количество вершин должно быть от 1 до %d.\n", MAX_VERTICES);
        return 1;
    }

    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 }; // Инициализация графа нулями
    int incidence_matrix[MAX_VERTICES][MAX_EDGES];
    int edges = 0;

    // Генерация случайных рёбер
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            if (rand() % 2 && edges < MAX_EDGES) { // С вероятностью 50% добавляем ребро, если не превышен лимит
                graph[i][j] = 1;
                graph[j][i] = 1; // Для неориентированного графа
                edges++;
            }
        }
    }

    // Создание матрицы инцидентности на основе матрицы смежности
    create_incidence_matrix(graph, incidence_matrix, &edges);

    // Вывод матрицы смежности
    printf("Матрица смежности:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    // Вывод матрицы инцидентности
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < edges; j++) {
            printf("%d ", incidence_matrix[i][j]);
        }
        printf("\n");
    }

    // Нахождение специальных вершин
    find_special_vertices(incidence_matrix, num_vertices, edges);

    return 0;
}
