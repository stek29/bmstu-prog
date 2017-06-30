#include <functional>
#include "tree.h"

void tnode_t::append(tnode_t *leaf)  {
    if (leaf->element->key > element->key) {
        if (this->right != nullptr)
            this->right->append(leaf);
        else
            this->right = leaf;
    } else {
        if (this->left != nullptr)
            this->left->append(leaf);
        else
            this->left = leaf;
    }
};

void tnode_t::traverse(std::function<void(tnode_t*)> func, traverse_order order) {
    switch (order) {
        case traverse_order::normal:
            if (this->left != nullptr) this->left->traverse(func, order);
            func(this);
            if (this->right != nullptr) this->right->traverse(func, order);
            break;
        case traverse_order::reverse:
            if (this->right != nullptr) this->right->traverse(func, order);
            func(this);
            if (this->left != nullptr) this->left->traverse(func, order);
            break;
        case traverse_order::in_depth:
            if (this->right != nullptr) this->right->traverse(func, order);
            if (this->left != nullptr) this->left->traverse(func, order);
            func(this);
            break;
    }
}


void Tree::walk(std::function<void(tree_element_t&)> func, bool reverse) {
    if (head != nullptr) {
        traverse_order order = reverse ? traverse_order::reverse : traverse_order::normal;
        head->traverse([&func](tnode_t *node){func(node->value);}, order);
    }
}

tnode_t* Tree::create_node(const tree_element_t &element) {
    tnode_t *node = new tnode_t();
    node->element = element;
    return node;
}

void Tree::free_node(tnode_t *node) {
    delete node;
}

void Tree::insert(const tree_element_t &element) {
    tnode_t *leaf = create_node(element);
    if (head != nullptr) {
        head->append(leaf);
    } else {
        head = leaf;
    }
}

Tree::~Tree() {
    if (head != nullptr) {
        head->traverse(free_node, traverse_order::in_depth);
    }
}