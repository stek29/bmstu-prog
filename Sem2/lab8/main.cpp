/* lab8
 * Моделировать стек, в качестве элементов которого
 * могут использоваться целые и вещественные числа.
 * Операции:
 *  - добавление элемента
 *  - удаление элемента
 *  - печать элементов стека
 * Создать класс - потомок, который содержит
 * процедуру сортировки элементов стека.
 * Тестировать полученную модель.
 * Примечание: сначала реализовать и отладить структуру
 * данных как класс, после чего преобразовать в класс шаблон.
 * В отчете представить структуру использованных классов
 * и обосновать выбранную структуру представления данных.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "mystack.h"
#include "mynumber.h"

using namespace My;
using namespace std;

Number read_num() {
    cout << "Enter type (D=double, I(or other)=int) and Value: " << endl;
    auto type = NumberType::Int;

    char ch_type;
    cin >> ch_type;
    if (ch_type == 'D') type = NumberType::Double;

    Number result(type);
    cin >> result;
    return result;
}

int main(void) {
    SortableStack<Number> stack({3, 2.2, 0, 1.3, 4});

    char cmd;
    for(cout << endl << "Enter cmd" << endl, cin >> ws >> cmd;
        cmd != 'q';
        cout << endl << "Enter cmd" << endl, (cin >> ws >> cmd) || (cmd = 'q')
    ) {
        switch(cmd) {
            case 'a':
                stack.add(read_num());
                break;

            case 'r':
                stack.remove(read_num());
                break;

            case 'f':
                cout << stack.first() << endl;
                break;

            case 'e':
                cout << stack.empty() << endl;
                break;

            case 'p':
                cout << stack.pop() << endl;
                break;

            case 's':
                stack.sort();
                break;

            case 'P':
                cout << stack << endl;
                break;

            case 'q':
                break;

            default:
                cout << "Invalid cmd" << endl;
        }
    }

    return EXIT_SUCCESS;
}