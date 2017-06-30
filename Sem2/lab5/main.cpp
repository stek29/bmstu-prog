/* lab5
 *  Динамические структуры данных. Списки.
 * С клавиатуры вводятся строки, содержащие наименование товара и цену.
 *  Количество данных заранее неизвестно. Организовать из вводимых данных
 *  тип запись и сформировать из этих записей список, упорядоченный по алфавиту.
 * В программе предусмотреть возможность добавить в список новый элемент
 *  и удалить элемент, введенный с клавиатуры.
 * Переупорядочить элементы списка по возрастанию цен товаров.
 * Вывести на печать списки и проверить функции добавления и удаления элементов.
 */

// EXIT_SUCCESS
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#define HELP_TEXT "Введите команду.\n"\
         " q -- сортировка по стоимости и выход \n"\
         " a -- добавление значения \n"\
         " d -- удаление значения \n"\
         " p -- вывод списка"

typedef struct node_t {
    string name;
    float price;
    node_t* next;

    void operator=(node_t node) {
        this->name = node.name;
        this->price = node.price;
    }

    bool read() {
        cin >> this->price;
        return (this->price >= 0) && getline(cin >> ws, this->name);
    }
} node_t;

typedef struct list_t {
    node_t* head = nullptr;

    void insert_sorted(node_t node) {
        node_t* ptr;

        if (this->head == nullptr || this->head->name.compare(node.name) > 0) {
            ptr = new node_t;
            *ptr = node;
            ptr->next = this->head;
            this->head = ptr;
        } else {
            for(ptr = this->head; ptr->next != nullptr; ptr = ptr->next)
                if (ptr->next->name.compare(node.name) > 0)
                    break;
            node_t* insert_me = new node_t;
            *insert_me = node;
            insert_me->next = ptr->next;
            ptr->next = insert_me;
        }
    }

    bool delete_by_name(string name) {
        bool found = false;

        if (this->head != nullptr) {
            node_t* ptr;
            if (this->head->name == name) {
                ptr = this->head->next;
                delete this->head;
                this->head = ptr;
                found = true;
            } else {
                for(ptr = this->head; ptr->next != nullptr; ptr = ptr->next)
                    if (ptr->next->name == name)
                        break;
                if (ptr->next != nullptr) {
                    node_t* tmp_ptr = ptr->next;
                    ptr->next = ptr->next->next;
                    delete tmp_ptr;
                    found = true;
                }
            }
        }
        return found;
    }

    void free() {
        node_t* ptr = this->head;
        while (ptr != nullptr) {
            this->head = ptr->next;
            delete ptr;
            ptr = this->head;
        }
    }

    void print() {
        for (node_t* ptr = this->head; ptr != nullptr; ptr = ptr->next)
            cout << setw(5) << ptr->price << ": " << ptr->name << '\n';
        cout << flush;
    }

    void sort_by_price() {
        if (head != nullptr && head->next != nullptr) {
            node_t *curr, *prev;
            for (bool hadSwapped = true; hadSwapped; ) {
                hadSwapped = false;
                prev = head;
                for(curr = head; curr != nullptr && curr->next != nullptr; curr = curr->next) {
                    if (curr->price > curr->next->price) {
                        if (curr == head) {
                            head = curr->next;
                            curr->next = curr->next->next;
                            head->next = curr;
                        } else {
                            prev->next = curr->next;
                            curr->next = curr->next->next;
                            prev->next->next = curr;
                        }
                        hadSwapped = true;
                    }
                    prev = curr;
                }
            }
        }
    }
} list_t;

int main(void) {
    list_t list;
    node_t tmp_node;

    cout << "Введите товары (цена и наименование) \n (введите отрицательную цену для окончания ввода)" << endl;

    while (tmp_node.read())
        list.insert_sorted(tmp_node);


    cout << HELP_TEXT << endl;

    char choice = 'q';
    for (cin >> choice; choice != 'q'; cin >> choice) {
        switch (choice) {
            case 'a':
                cout << "Введите товар: " << endl;
                if (tmp_node.read()) list.insert_sorted(tmp_node);
                break;
            case 'd':
                cout << "Введите наименование товара: " << endl;
                if (getline(cin >> ws, tmp_node.name)) {
                    if (!list.delete_by_name(tmp_node.name))
                        cout << "Товар не найден";
                    else
                        cout << "Товар удален";
                    cout << endl;
                }
                break;
            case 'p':
                list.print();
                break;
            default:
                cout << "Неправильная команда." << endl;
        }
        cout << HELP_TEXT << endl;
    }


    cout << "Список после сортировки по цене: " << endl;
    list.sort_by_price();
    list.print();
    list.free();

    return EXIT_SUCCESS;
}