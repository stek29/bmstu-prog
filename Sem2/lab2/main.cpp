/* lab2
 *  Работа с массивами С++
 * В целочисленной матрице D(N,M), где N<M в каждой строке
 *  найти наибольшее значение и заменить его суммой элементов
 *  строки, предшествующих этому наибольшему значению.
 * Если наибольший элемент является первым в строке,
 *  то преобразование не производится.
 *
 * Распечатать:
 *  а) исходную и преобразованную матрицы;
 *  б) индексы и значения тех элементов, которые оказались
 *   наибольшими в строках;
 *  в) вывести однократно все значения матрицы,
 *   проводя обход «змейкой» одновременно с двух сторон:
 *   элементы [1,1], [N,M], [1,2], [N,M-1]...
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>

// для заполнения случайными числами (не с клавиатуры)
#define RANDOM_FILL 1

// "сахар" для вывода с фиксированной шириной
#define PRINT(x) std::setw(5) << x

// элемент матрицы
typedef int element;

// индекс максимального элемента массива
size_t arr_max(element array[], size_t length);

// Вывод матрицы -- "нормальный" и "змейкой"
void print_matrix(element **matrix, size_t N, size_t M);
void print_snake(element **matrix, size_t N, size_t M);

int main(void) {
    size_t N, M;
    element **matrix;

    std::cout << "Введите N и M: ";
    std::cin >> N >> M;

    if (N >= M) std::cerr << "[WARN] N >= M" << std::endl;

#if !RANDOM_FILL
    std::cout << "Введите матрицу:" << std::endl;
#else
    srand((unsigned int) time(NULL));
#endif /* RANDOM_FILL */

    matrix = new element*[N];
    for (size_t i = 0; i < N; i++) {
        matrix[i] = new element[M];
        for (size_t j = 0; j < M; j++) {
#if RANDOM_FILL
            matrix[i][j] = rand() % 100;
#else
            std::cin >> matrix[i][j];
#endif /* RANDOM_FILL */
        }
    }

    std::cout << "Исходная матрица: " << std::endl;
    print_matrix(matrix, N, M);

    for (size_t i = 0; i < N; i++) {
        size_t max_el = arr_max(matrix[i], M);
        std::cout << "D[" << i << "][" << max_el << "] = " << PRINT(matrix[i][max_el]) << std::endl;
        if (max_el > 0) {
            matrix[i][max_el] = 0;
            for (size_t j = 0; j < max_el; j++)
                matrix[i][max_el] += matrix[i][j];
        }
    }

    std::cout << "Преобразованная матрица: " << std::endl;
    print_matrix(matrix, N, M);

    std::cout << "Вывод \"змейкой\": " << std::endl;
    print_snake(matrix, N, M);

    for (size_t i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;

    return EXIT_SUCCESS;
}

size_t arr_max(element array[], size_t length) {
    size_t max_ind = 0;

    for (size_t i = 1; i < length; i++)
        if (array[i] > array[max_ind])
            max_ind = i;
    return max_ind;
}

void print_matrix(element **matrix, size_t N, size_t M) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++)
            std::cout << PRINT(matrix[i][j]);
        std::cout << std::endl;
    }
}

void print_snake(element **matrix, size_t N, size_t M) {
    size_t i, j = 0;
    // N/2 + N%2 <=> N/2 с округлением в бОльшую сторону
    for (i = 0; i < N/2 + N%2; i++) {
        // Если i == N/2, то идет обработка среднего ряда, и вывести нужно только половину
        for (j = 0; j < ((i == N/2) ? M/2 : M); j++) {
            // при нечетных i нужно выводить ряд (i) с начала, а ряд (N - 1 - i) -- с конца
            // для четных -- наоборот
            std::cout << PRINT(matrix[        i][i % 2 ? M - 1 - j :         j]);
            std::cout << PRINT(matrix[N - 1 - i][i % 2 ?         j : M - 1 - j]);
        }
    }
    if (N % 2 && M % 2) std::cout << PRINT(matrix[i - 1][j]);
    std::cout << std::endl;
}
