#pragma once

#include <iostream>
#include <initializer_list>
#include <functional>

namespace My {
    template <typename T>
    struct Node {
        Node()
                : val()
                , next(nullptr)
        { };

        Node(T el)
                : val(el)
                , next(nullptr)
        { };

        Node(const Node<T>& rhs)
                : val(rhs.val)
                , next(rhs.next)
        { };

        T val;
        Node<T>* next;
    };

    template<typename T>
    class Stack {
        using TNode = Node<T>;

    public:
        Stack() : head(nullptr) {}

        Stack(std::initializer_list<T> args) : head(nullptr) {
            for (auto el : args)
                add(el);
        }

        void add(const T &el) {
            auto ptr = create(el);
            ptr->next = head;
            head = ptr;
        }

        bool remove(const T &el) {
            TNode* del_me = nullptr;
            if (!empty()) {
                if (head->val == el) {
                    del_me = head;
                    head = head->next;
                } else {
                    for (auto q = head; q!= nullptr && q->next != nullptr; q = q->next) {
                        if (q->next->val == el) {
                            del_me = q->next;
                            q->next = q->next->next;
                        }
                    }
                }
            }

            if (del_me != nullptr) delete del_me;
            return del_me != nullptr;
        }

        T pop() {
            // would throw if empty
            auto result = first();

            auto del_me = head;
            head = head->next;
            delete del_me;

            return result;
        }

        T first() const {
            if (empty()) throw std::out_of_range("Stack is empty");
            else return head->val;
        }

        bool empty() const { return head == nullptr; };

        void foreach(std::function<void(T)> func) const {
            for (auto p = head; p != nullptr; p = p->next) {
                func(p->val);
            }
        }

        ~Stack() {
            while (!empty()) {
                auto p = head;
                head = head->next;
                delete p;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
            stack.foreach([&os](T el) { os << el << ' '; });
            return os;
        }

    protected:
        static TNode *create(const T &el) {
            return new TNode(el);
        }

        TNode *head;

    };

    template <typename T>
    class SortableStack: public Stack<T> {
    public:
        using Stack<T>::empty;
        using Stack<T>::Stack;

        void sort();

    private:
        using Stack<T>::head;

    };

    template <typename T>
    void SortableStack<T>::sort() {
        bool sorted = empty() || head->next == nullptr;
        while (!sorted) {
            sorted = true;
            auto prev = head; auto q = head;
            for (; q != nullptr && q->next != nullptr; q = q->next) {
                if (q->val > q->next->val) {
                    if (q == head) {
                        head = q->next;
                        q->next = head->next;
                        head->next = q;
                    } else {
                        prev->next = q->next;
                        q->next = prev->next->next;
                        prev->next->next = q;
                    }
                    sorted = false;
                }
                prev = q;
            }
        }
    }
}