#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

#include "sent.h"
#include "tree.h"

int main(void) {
    list<Sentence*> Lst;
    char st[MAX_WORD_CNT * (MAX_WORD_LEN+1)];
    cout << "Вводите предложения (до 'end'): " << endl;

    cin.getline(st, MAX_WORD_CNT * (MAX_WORD_LEN+1));
    while (cin && strcmp(st, "end") != 0) {
        Lst.push_back(new Sentence(st));
        cin.getline(st, 50);
    }

    cout << "\nВведенные приложения (в списке): " << endl;
    for (const auto &sent: Lst)
        sent->print();

    vector<Sentence*> Mas;
    Mas.reserve(Lst.size());
    for (const auto &sent: Lst)
        Mas.push_back(sent);

    cout << "\nСформированный из предложении массив: " << endl;
    for (const auto &sent: Mas)
        sent->print();

    cout << "Процент слов длиннее 5 букв: ";
    int totalWords, longWords;
    totalWords = longWords = 0;
    for(const auto &sent: Mas) {
        totalWords += sent->count();
        longWords += sent->longCount();
    }
    cout << longWords * 100. / totalWords << '%' << endl;


    Tree tree;
    for (int i = 0; i < Mas.size(); i++)
        tree.insert({i, Mas[i]});

    cout << "Сформировано дерево: " << endl;
    tree.walk([](tree_element_t& el) {
        el.v->print(cout << el.key << ": ");
    });

    cout << "Вводите слова для поиска (до 'end')";
    cin.getline(st, MAX_WORD_LEN);
    while (cin && strcmp(st, "end") != 0) {
        tree.walk([&st](tree_element_t& el) {
            int pos = el.v->wordPosition(st);
            if (pos != -1) {
                cout << "Слово №" << pos << " в предложении №" << el.key << endl;
            };
        });
        cout << "Вводите слова для поиска (до 'end'): ";
        cin.getline(st, MAX_WORD_LEN);
    }

    // Удаляем предложения
    tree.walk([](tree_element_t &el) { delete el.v; });

    return 0;
}