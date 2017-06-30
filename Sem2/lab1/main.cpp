/* lab1
 *  Основные управляющие операторы C++
 * Числа Фибоначчи считаются следующим образом: а1=а2=1,
 *  аn=an-1+an-2. Определить первое число последовательности
 *  Фибоначчи, значение которого превышает А.
 */

#include <cstdlib>
#include <iostream>

int fib1, fib2, A;

int main(void) {
    std::cout << "Введите A: ";
    std::cin >> A;

    fib1 = fib2 = 1;

    while (fib2 < A) {
        fib2 += fib1;
        fib1 = fib2 - fib1;
    }

    std::cout << fib2 << std::endl;

    return EXIT_SUCCESS;
}
