#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#ifdef LAB7_RAND_FILL
#include <ctime>
#endif

#if defined(LAB7_USE_STL)
#include "stl.h"
#elif defined(LAB7_USE_QT) // LAB7_USE_STL
#include "qt.h"
#endif // LAB7_USE_QT

#ifdef LAB7_DBG
#define DBG_PRINT(str) std::cout << str << std::endl
#else
#define DBG_PRINT(str)
#endif


int main(int charc, char *charv[]) {
    int n;
    std::string ffname, gfname;
    if (charc != 3) {
        std::cout << "Введите имя файла F: " << std::flush;
        std::getline(std::cin, ffname);
        std::cout << "Введите имя файла G: " << std::flush;
        std::getline(std::cin, gfname);
    } else {
        ffname = charv[1];
        gfname = charv[2];
    }

    using std::ios;
    bool fEmpty = false;
    std::fstream fstream(ffname, ios::in | ios::out | ios::binary);
    if (!fstream) {
        fstream.open(ffname, ios::in | ios::out | ios::binary | ios::trunc);
        fEmpty = true;
    }

    if (!fstream) {
        std::cerr << "Ошибка при открытии файла F: \n" << strerror(errno) << std::endl;
        return 1;
    }

    if (fEmpty) {
#ifdef LAB7_RAND_FILL
        srand(static_cast<unsigned int>(time(nullptr)));
        std::cout << "Введите число чисел для генерации в файле F:" << std::endl;
        int len; std::cin >> len;
        while (len-- > 0) {
            n = random() % 10000;
            fstream.write(reinterpret_cast<char *>(&n), sizeof(n));
        }
#else // LAB7_RAND_FILL
        std::cout << "Введите числа для файла F (0 для конца)" << std::endl;

        std::cin >> n;
        while (n != 0) {
            fstream.write(reinterpret_cast<char *>(&n), sizeof(n));
            std::cin >> n;
        }
#endif // LAB7_RAND_FILL
    }

    DBG_PRINT("Содержимое файла F: ");

    NumberSorter NumSort;
    fstream.seekg(0);
    while (fstream.read(reinterpret_cast<char *>(&n), sizeof(n))) {
        NumSort.feed(n);
        DBG_PRINT(n);
    }

    if (!fstream.eof()) {
        std::cerr << "Ошибка при считывании файла F!" << std::endl;
        return 2;
    }

    DBG_PRINT("Числа отсортированы, выполняю запись в файл G...");

    std::fstream gstream(gfname, ios::in | ios::out | ios::binary | ios::trunc);
    if (!gstream) {
        std::cerr << "Ошибка при открытии файла G: \n" << strerror(errno) << std::endl;
        return 3;
    }

    auto gWriter = [&gstream](int num) mutable -> bool {
        if (gstream) gstream.write(reinterpret_cast<char *>(&num), sizeof(num));
        return bool(gstream);
    };
    if (!NumSort.exec(gWriter) || !gstream) {
        std::cerr << "Ошибка при заполнении файла G:" << std::endl;
        return 4;
    }

    DBG_PRINT("Содержимое файла G:");
    gstream.seekg(0);
    while (gstream.read(reinterpret_cast<char *>(&n), sizeof(n))) {
        DBG_PRINT(n << " -- " << digit_sum(n));
    }
    std::cout << std::flush;

    if (!gstream.eof()) {
        std::cerr << "Ошибка при считывании файла G!" << std::endl;
        return 5;
    }

    gstream.flush(); gstream.close();
    fstream.flush(); fstream.close();

    return EXIT_SUCCESS;
}
