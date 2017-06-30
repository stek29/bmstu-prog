/* lab6
 *  Динамические структуры данных. Деревья.
 * Реализовать программу сортировки чисел по
 * их десятичной записи с использованием дерева.
 * Обеспечить вывод элементов по возрастанию и убыванию.
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "tree.h"

int main(void) {
    Tree tree;

    std::cout << "Введите числа (end для окончания ввода)" << std::endl;

    std::string input;
    std::getline(std::cin, input);
    while (input != "end") {
        tree.insert(std::atoi(input.c_str()));
        std::getline(std::cin, input);
    }

    auto print = [](int num) {std::cout << num << '\n';};
    std::cout << "Отсортированные числа: " << std::endl;
    tree.walk(print);
    std::cout << std::endl;

    std::cout << "В обратном поряде: " << std::endl;
    tree.walk(print, true);
    std::cout << std::endl;

    return EXIT_SUCCESS;
};