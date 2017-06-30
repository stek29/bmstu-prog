/*
 * lab4
 * Из исходной строки удалить слова, содержащие более трех гласных букв
 * четырех наиболее часто встречающихся их сочетания.
 * Пользуясь указателями напечатать их адреса.
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <list>

const size_t MOST_COMMON_PAIRS_LEN = 4;
const size_t MIN_VOWEL_COMBO_LEN = 4;

const std::string vowels("aeiou");
static inline bool is_vowel (char ltr) {
    return vowels.find(ltr) != std::string::npos;
};

// Для добавления символа в автосортирующуюся строку
void ordered_insert (unsigned char chr, std::string &str) {
    size_t i = 0;
    // c_str() кончается '\0'
    while (chr < str.c_str()[i]) i++;
    str.insert(i, 1, chr);
};

typedef std::map<std::string, size_t> combination_map;
typedef std::list<std::pair<std::string, size_t> > pair_list;

// комбинация : количество слов с нею
// не обрабатывает комбинации длинной меньше min_combination_l
combination_map get_combinations(const std::string &line, size_t min_combination_l);

// список самых частых комбинаций с длинной max_len
pair_list get_most_common_pairs(const combination_map &combinations, const size_t max_len);

// возвращает строку, из которой удалены комбинации, имеющиеся в pair_list
std::string filter_common_pairs(const std::string &line, const pair_list &pairs);

int main(void) {
    std::string line;

    std::cout << "Введите строку:" << std::endl;
    std::getline(std::cin, line);

    combination_map combinations = get_combinations(line, MIN_VOWEL_COMBO_LEN);
    pair_list most_common_pairs = get_most_common_pairs(combinations, MOST_COMMON_PAIRS_LEN);
    std::cout << filter_common_pairs(line, most_common_pairs) << std::endl;

    return EXIT_SUCCESS;
};

combination_map get_combinations(const std::string &line, size_t min_combination_l) {
    std::string combination;
    combination_map combinations;
    for (auto it = line.cbegin(); it != line.cend(); ++it) {
        if (*it == ' ') {
            if (combination.size() >= min_combination_l)
                combinations[combination]++;
            combination.erase();
        } else {
            char lowered = (unsigned char ) std::tolower(*it);
            if (is_vowel(lowered)) ordered_insert((unsigned char ) lowered, combination);
        }
    }
    // Если строка не кончалась пробелом, то нужно сохранить последнюю комбинацию
    if (combination.size() >= min_combination_l)
        combinations[combination]++;
    return combinations;
};

pair_list get_most_common_pairs(const combination_map &combinations, const size_t max_len) {
    auto it = combinations.cbegin();
    pair_list most_common_pairs;
    // Вставляем первую комбинацию, убедившись, что она существует
    if (it != combinations.cend()) {
        most_common_pairs.push_back(*it);
        it++;
    }
    while (it != combinations.cend()) {
        if (most_common_pairs.size() < max_len || it->second >= most_common_pairs.back().second) {
            auto lst_it = most_common_pairs.begin();
            bool inserted = false;
            while (!inserted && lst_it != most_common_pairs.end()) {
                if (it->second >= lst_it->second) {
                    most_common_pairs.insert(lst_it, *it);
                    inserted = true;
                }
                lst_it++;
            }
            if (!inserted) most_common_pairs.push_back(*it);
            // Если длина списка достигла max_len, то удаляем последний элемент
            if (most_common_pairs.size() > max_len)
                most_common_pairs.pop_back();
        }
        it++;
    }
    return most_common_pairs;
};

std::string filter_common_pairs(const std::string &line, const pair_list &pairs) {
    std::string result;
    std::string combination;
    // ws -- начало слова
    auto it = line.cbegin(), ws = it;
    for (; it != line.cend(); ++it) {
        if (*it == ' ') {
            // Если строка содержит повторяющиеся пробелы
            if (combination.size() > 0) {
                bool found = false;
                for (auto pit = pairs.cbegin(); !found && pit != pairs.cend(); pit++)
                    if (pit->first == combination)
                        found = true;
                if (!found) result += std::string(ws, it+1);
                else std::cout << "Удалено слово: " << (void *) &*it << '\n';
                combination.erase();
                ws = it + 1;
            }
        } else {
            char lowered = (char ) std::tolower(*it);
            if (is_vowel(lowered)) ordered_insert((unsigned char ) lowered, combination);
        }
    }
    // Если строка не кончалась пробелом, то нужно сохранить последнюю комбинацию
    if (combination.size() > 0) {
        bool found = false;
        for (auto pit = pairs.cbegin(); !found && pit != pairs.cend(); pit++)
            if (pit->first == combination)
                found = true;
        if (!found) result += std::string(ws, it);
        else std::cout << "Удалено слово: " << (void *) &*it << '\n';
    }
    return result;
};