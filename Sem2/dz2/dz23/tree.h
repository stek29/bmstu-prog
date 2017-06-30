#pragma once
#include <functional>
#include "sent.h"

typedef int tree_key_t;
typedef Sentence* tree_value_t;

struct tree_element_t {
    tree_key_t key;
    tree_value_t v;
};

enum class traverse_order {
    normal,
    reverse,
    in_depth
};

struct tnode_t {
    tnode_t(const tree_element_t &el)
            : element(el) {
    }
    tree_element_t element;
    tnode_t *left = nullptr;
    tnode_t *right = nullptr;

    void append(tnode_t *leaf);
    void traverse(std::function<void(tnode_t*)>, traverse_order order = traverse_order::normal);
};

class Tree {
public:
    ~Tree();
    void insert(const tree_element_t &element);
    void walk(std::function<void(tree_element_t&)> func, bool reverse = false);
private:
    static tnode_t *create_node(const tree_element_t &element);
    static void free_node(tnode_t *node);

    tnode_t *head = nullptr;
};
