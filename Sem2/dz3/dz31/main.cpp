/* dz31
 * Разработать и реализовать диаграмму классов для описанных объектов
 *  предметной области, используя механизмы наследования и композиции.
 * Проверить ее на тестовом примере, с демонстрацией всех возможностей
 *  разработанных классов на конкретных данных. Подготовить документацию.
 *
 * Даны:
 *  - объект вещественное число, умеющий печатать свое значение
 *   и отвечать на запрос о значении своего числового поля, количестве
 *   цифр целой и дробной частей этого поля.
 *  - объект массив вещественных чисел, умеющий выводить на печать
 *   значение своих элементов, возвращать значение любого элемента
 *   по его индексу, возвращать среднее количество цифр целых и дробных
 *   частей его элементов, а также определять элемент с минимальным и
 *   максимальным количеством цифр его целой и дробной частей.
 */

#include <cstdlib>
#include <iostream>
#include "number.h"
#include "numberarray.h"

void test(NumberArray &a, int i) {
    std::cout << "Создан массив:\n";
    a.dump(std::cout);

    std::cout << "Получим элемент по индексу " << i << " для тестирования.\n";

    std::cout << "Печать своего значения: " << a[i] << std::endl;

    std::cout << "Значение числового поля: ";
    std::cout << a[i].v() << std::endl;

    std::cout << "Количество цифр целой и дробной частей: \n";
    std::cout << a[i].getDigitCnt(Part::Integer) << ' ' << a[i].getDigitCnt(Part::Fractional) << '\n';

    std::cout << "Вывод на печать своих элементов: \n" << a;

    std::cout << "Среднее количество цифр частей элементов\n";
    std::cout << "\tЦелых: " << a.meta(Part::Integer).average << '\n';
    std::cout << "\tДробных: " << a.meta(Part::Integer).average << '\n';

    std::cout << "элемент с X количеством цифр его Y частей\n";
    std::cout << "\tMAX Целой " << a[a.meta(Part::Integer).maxIdx] << " ("
              << a.meta(Part::Integer).max << " цифр)\n";
    std::cout << "\tMIN Целой " << a[a.meta(Part::Integer).minIdx] << " ("
              << a.meta(Part::Integer).min << " цифр)\n";
    std::cout << "\tMAX Дробной " << a[a.meta(Part::Fractional).maxIdx] << " ("
              << a.meta(Part::Fractional).max << " цифр)\n";
    std::cout << "\tMIN Дробной " << a[a.meta(Part::Fractional).minIdx] << " ("
              << a.meta(Part::Fractional).min << " цифр)\n";

    std::cout << "Тестирование завершено." << std::endl;
}

int main(void) {
    NumberArray a1({"13", "1493.2", "243.21", "1242.53", "0", "1.014"});
    test(a1, 1);
    NumberArray a2({"13.43", "1421343.2198", "-14243.21", "95401242.53", "0", "109.014"});
    test(a2, 3);

    return EXIT_SUCCESS;
}