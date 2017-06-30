#ifndef LABS_NUMBERTREE_H
#define LABS_NUMBERTREE_H

#include <functional>

enum class traverse_order {
    normal,
    reverse,
    in_depth
};

struct tnode_t {
    int value;
    tnode_t *left = nullptr;
    tnode_t *right = nullptr;

    void append(tnode_t *leaf);
    void traverse(std::function<void(tnode_t*)>, traverse_order order = traverse_order::normal);
};

class Tree {
public:
    ~Tree();
    void insert(int val);
    void walk(std::function<void(int)> func, bool reverse = false);
private:
    static tnode_t *create_node(int val);
    static void free_node(tnode_t *node);

    tnode_t *head = nullptr;
};

#endif //LABS_NUMBERTREE_H
