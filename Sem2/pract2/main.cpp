/* pract2
 * Разработать программу, которая реализует операции над векторами.
 * Реализовать следующие операции:
 *  - поэлементный ввод координат векторов
 *  - сумму векторов, разность векторов
 *  - произведение вектора на скаляр
 *  - проверку равенства векторов
 *  - вывод результатов операции на экран.
 * Необходимо разработать шаблон, реализующий вектор.
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "vector.h"

using elem = double;
using scalar = double;
using Vect = MyVector<elem, scalar>;
namespace { using namespace std; }

Vect *a, *b;

bool ask() {
    short ans; cin >> ans;
    return bool(ans);
}
void askToSave(const Vect &v) {
    cout << "Сохранить в вектор b [1/0]?" << endl;
    if (ask()) {
        if (b != nullptr) delete b;
        b = new Vect(v);
    }
}
static void in(void) {
    cout << "Введите 1 для поэлементного ввода вектора a\n";
    cout << "Или 0 для обмена векторов a и b местами\n";
    if (ask()) {
        if (a != nullptr) delete a;
        cout << "Введите размерность вектора a: " << endl;
        size_t len; cin >> len;
        cout << "Введите его координаты: " << endl;
        a = new Vect(len);
        cin >> *a;
    } else {
        auto tmp = a;
        a = b; b = tmp;
    }
};
static void add(void) {
    if (a == nullptr || b == nullptr) {
        cout << "Введите сначала вектора a и b, пожалуйста.\n";
        return;
    }
    cout << "Введите 1 для a+b и 0 для a-b: ";
    Vect res = *a;
    if (ask()) res += *b;
    else res -= *b;
    cout << "Результат: \n" << res << endl;
    askToSave(res);
};
static void mul(void) {
    if (a == nullptr) {
        cout << "Введите сначала вектор a, пожалуйста.\n";
        return;
    }
    scalar n;
    cout << "Введите скаляр для умножения вектора a:" << endl;
    cin >> n;
    cout << "Умножаю вектор a на '" << n << "':\n";
    auto res = Vect(n * *a);
    cout << res << endl;
    askToSave(res);
};
static void cmp(void) {
    if (a == nullptr || b == nullptr) {
        cout << "Введите сначала вектора a и b, пожалуйста.\n";
        return;
    }
    if (*a == *b) cout << "Вектора a и b равны\n";
    else       cout << "Вектора a и b не равны\n";
};

void(*commands[])(void) = {
        in, add, mul, cmp
};
const auto command_cnt = sizeof(commands)/sizeof(*commands);

inline ostream& printVect(ostream& to, Vect *p) {
    if (p == nullptr)
        return to << "[null]";
    else
        return to << *p;
};

void printMenu() {
    cout << "Доступные вектора: \n";
    printVect(cout << "a: ", a) << '\n';
    printVect(cout << "b: ", b) << '\n';

    cout << "Выберите команду: \n";
    cout << "0. Ввод векторов\n";
    cout << "1. Сумма/Разность векторов\n";
    cout << "2. Умножение векторов на скаляр\n";
    cout << "3. Проверка равенства векторов\n";
    cout << "4. Выход\n";
};

int main(void) {
    a = b = nullptr;
    cout << "Добро пожаловать в программу по работе с векторами.\n";
    for (;;) {
        printMenu();
        short command;
        cin >> command;
        if (command < command_cnt) {
            commands[command]();
        } else if (command == command_cnt) { // Последняя команда -- выход
            break;
        } else {
            cout << "Введена несуществующая команда. Попробуйте еще раз.\n";
        }
    }
    if (a != nullptr) delete a;
    if (b != nullptr) delete b;
    cout << "Прощайте!" << endl;
    return EXIT_SUCCESS;
}

//class TestStr {
//public:
//    TestStr(): str() {};
//    TestStr(std::string s): str(s) {};
//
//    using string_t = std::string;
//    operator string_t() const { return str; };
//
//    TestStr& operator+=(const TestStr &rhs) { str+=rhs.str; return *this; }
//
//    TestStr& operator-=(const TestStr &rhs) {
//        auto n = rhs.str.length();
//        for (auto i = str.find(rhs);
//             i != std::string::npos;
//             i = str.find(rhs))
//             str.erase(i, n);
//        return *this;
//    }
//
//    TestStr& operator*=(const TestStr &rhs) {
//        auto res = std::string();
//        for (auto ch_l : str)
//            for (auto ch_r : rhs.str)
//                (res += ch_l) += ch_r;
//        str = res;
//        return *this;
//    }
//
//    TestStr& operator*=(int rhs) {
//        auto res = str;
//        while (--rhs > 0)
//            str += res;
//        return *this;
//    }
//
//    TestStr& operator =(const TestStr &rhs) { str = rhs.str;  return *this; }
//
//    friend std::istream &operator>>(std::istream &is, TestStr &obj) {
//        is >> obj.str;
//        return is;
//    }
//
//    friend std::ostream &operator<<(std::ostream &os, const TestStr &obj) {
//        os << '\'' << obj.str << '\'';
//        return os;
//    }
//private:
//    std::string str;
//};

//int main(void) {
//    size_t siz;
//    std::cout << "Введите величины: " << std::endl;
//
//    std::cout << "Размерность вектора a: ";
//    std::cin >> siz;
//    Vect a(siz);
//    std::cout << "Вектор a: ";
//    std::cin >> a;
//
//    std::cout << "Размерность вектора b: ";
//    std::cin >> siz;
//    Vect b(siz);
//    std::cout << "Вектор b: ";
//    std::cin >> b;
//
//    scalar k;
//    std::cout << "Скаляр k: ";
//    std::cin >> k;
//
//    std::cout << "a: " << a << std::endl;
//    std::cout << "b: " << b << std::endl;
//    std::cout << "k: " << k << std::endl;
//
//    std::cout << "a + b: "
//              << a + b
//              << std::endl;
//
//    std::cout << "a - b: "
//              << a - b
//              << std::endl;
//
//    std::cout << "k * a: "
//              << k * a
//              << std::endl;
//
//    std::cout << "k * b: "
//              << k * b
//              << std::endl;
//
//    return EXIT_SUCCESS;
//}
/*
0
1
2
1.3 -4
0
0
0
1
3
0 1 3.3
1
1
1
2
-1.5
1
3
0
1
3
-0 -1.5 -4.95
3
4
 */