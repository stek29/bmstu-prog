/* lab3
 * Программирование функций
 * Простое число называется числом Мерсена, если оно может быть
 *  представлено в виде 2^p-1, где p – тоже простое число.
 *
 * Написать программу, определяющую количество чисел Мерсена <= некоторого n
 * (n вводится с клавиатуры). Вывести на печать числа Месена и их количество
 * в указанном диапазоне.
 */

#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>

std::set <unsigned int> non_primes_lt_N(unsigned int N) {
    std::set <unsigned int> non_primes;
    unsigned int i, sqrt_log_N = (unsigned int) sqrtf(log2f(N + 1));
    for (i = 2; i <= sqrt_log_N; i++) {
        if (!non_primes.count(i))
            for (unsigned int j = i + i; j < N; j += i)
                non_primes.insert(j);
    }
    return non_primes;
};

int main(void) {
    unsigned int N;
    std::cout << "Введите n: ";
    std::cin >> N;

    auto non_primes = non_primes_lt_N(N);

    std::cout << "Числа Мерсена: " << std::endl;
    unsigned int k = 0;
    for (unsigned int i = 4; i <= N + 1; i*=2)
        if (!non_primes.count(i - 1)) {
            std::cout << i - 1 << std::endl;
            k++;
        }

    std::cout << "Всего чисел в диапазоне: " << k << std::endl;

    return EXIT_SUCCESS;
}