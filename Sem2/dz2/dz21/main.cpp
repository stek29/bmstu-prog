/* dz21
 * Дана последовательность строк.
 * Каждая строка состоит из слов, разделенных пробелами.
 * Написать программу, обеспечивающую ввод строк и их корректировку.
 * Корректировка заключается в удалении или замене слов.
 * Если слово стоит на четном месте и
 *  начинается на букву «е» - оно удаляется;
 * если слово стоит на четном месте и
 *  начинается на букву «с», оно  замещается на слово,
 *  введенное с клавиатуры.
 * Вывести на печать исходную и скорректированную последовательности строк.
 * Реализовать как с использованием библиотечных функций работы со строками,
 *  так и с помощью собственной их реализации.
 * Оценить время выполнения программы разными реализациями.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>

#define TEST_CUSTOM
#ifndef TEST_CUSTOM
#include <cstring>
#define strcpy_ strcpy
#define strtok_ strtok
#define strcat_ strcat
#else
char *strcpy_(char *dst, const char *src) {
    char* retval = dst;
    while (*src != '\0') *dst++ = *src++;
    *dst = *src; // '\0'
    return retval;
}

char *strcat_(char *dst, const char *src) {
    char *retval = dst;
    while (*dst != '\0') dst++;
    strcpy_(dst, src);
    return retval;
}

char *strchr_(char * str, char character) {
    while(*str != '\0' && *str != character) str++;
    if (*str == character) return str;
    else return nullptr;
}

size_t strcspn_(char *string, const char *chars) {
    char c, *s;
    const char *p;

    for (s = string, c = *s; c != 0; s++, c = *s) {
        for (p = chars; *p != 0; p++) {
            if (c == *p) {
                return s - string;
            }
        }
    }

    return s - string;
}

char *strtok_(char *s, char *delim)  {
    static char *lasts;
    int ch;

    if (s == nullptr)
        s = lasts;

    do {
        if ((ch = *s++) == '\0')
            return nullptr;
    } while (strchr_(delim, ch));
    --s;

    lasts = s + strcspn_(s, delim);
    if (*lasts != '\0')
        *lasts++ = '\0';

    return s;
}

#endif

using namespace std;
int main(void) {
    int n, i, j;
    cout << "Введите число строк: ";
    cin >> n;
    char st[n][256];
    cout << "Введите строки:" << endl;
    for (i = 0; i < n; i++)
        (cin >> ws).getline(st[i], 256);

    cout << "Введенные строки: " << endl;
    for (i = 0; i < n; i++)
        cout << st[i] << '\n';
    cout << flush;

    char divider[] = " ",
            *words[n][128],
            *p,
            result[n][256];
    int cnt[n];

    for (i = 0; i < n; i++) {
        cnt[i] = 0;
        p = strtok_(st[i], divider);

        while (p != nullptr) {
            r
        }
    }

    for (i = 0; i < n; i++) {
        bool even = true;
        result[i][0] = '\0';
        for (j = 0; j < cnt[i]; j++) {
            if (!even) {
                switch (*words[i][j]) {
                    case 'e':
                        words[i][j] = nullptr;
                        break;
                    case 'c':
                        char word[256];
                        cout << "Введите замену для слова " << words[i][j] << " в строке " << i << ": ";
                        cin >> word;
                        words[i][j] = word;
                        break;
                    default:
                        break;
                }
            }
            if (words[i][j] != nullptr) {
                strcat_(result[i], words[i][j]);
                strcat_(result[i], " ");
            }
            even = !even;
        }
        cout << endl;
    }

    cout << "Исправленные строки:" << endl;
    for (i = 0; i < n; i++)
        cout << result[i] << '\n';
    cout << flush;

    return EXIT_SUCCESS;
}