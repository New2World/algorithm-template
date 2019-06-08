#pragma once

#include <iostream>
#include <string>

class RBTree{
    enum class __color{red, black};
    class _RB_Node{
        int val;
        __color color;
    public:
        _RB_Node *parent, *lchild, *rchild;
        _RB_Node(int v, __color c, _RB_Node *p=nullptr):val(v), color(c), parent(p), lchild(nullptr), rchild(nullptr){}

        int get() const {return val;}
        __color getColor() const {return color;}
        void setColor(__color c){color = c;}
    };

    _RB_Node *root;

    _RB_Node *__copyTree(_RB_Node *src){
        if(!src)    return nullptr;
        _RB_Node *dest = new _RB_Node(src->get(), src->getColor());
        dest->lchild = __copyTree(src->lchild);
        if(dest->lchild)
            dest->lchild->parent = dest;
        dest->rchild = __copyTree(src->rchild);
        if(dest->rchild)
            dest->rchild->parent = dest;
        return dest;
    }
    void __deleteTree(_RB_Node *node){
        if(!node)   return;
        __deleteTree(node->lchild);
        __deleteTree(node->rchild);
        delete node;
    }
    void __leftRotate(_RB_Node *node){
        _RB_Node *ptr = node->rchild;
        if(ptr->lchild) ptr->lchild->parent = node;
        node->rchild = ptr->lchild;
        ptr->parent = node->parent;
        if(node->parent == nullptr)
            root = ptr;
        else if(node->parent->lchild == node)
            node->parent->lchild = ptr;
        else
            node->parent->rchild = ptr;
        ptr->lchild = node;
        node->parent = ptr;
    }
    void __rightRotate(_RB_Node *node){
        _RB_Node *ptr = node->lchild;
        if(ptr->rchild) ptr->rchild->parent = node;
        node->lchild = ptr->rchild;
        ptr->parent = node->parent;
        if(node->parent == nullptr)
            root = ptr;
        else if(node->parent->lchild == node)
            node->parent->lchild = ptr;
        else
            node->parent->rchild = ptr;
        ptr->rchild = node;
        node->parent = ptr;
    }

    void __insert(_RB_Node *current){
        _RB_Node *parent = current->parent;
        if(!parent){                                            // case 1: parent is nullptr
            current->setColor(__color::black);
            return;
        }
        _RB_Node *grand = parent->parent;
        if(parent->getColor() == __color::black)    return;     // case 2: parent is black
        _RB_Node *uncle = nullptr;
        if(grand)   uncle = grand->lchild == parent ? grand->rchild : grand->lchild;
        if(uncle && uncle->getColor() == __color::red){         // case 3: parent and uncle are red
            parent->setColor(__color::black);
            uncle->setColor(__color::black);
            grand->setColor(__color::red);
            __insert(grand);
        } else{                                                 // case 4: parent is red, uncle is black
            if(current == parent->rchild && parent == grand->lchild){
                __leftRotate(parent);
                current = current->lchild;
            }
            else if(current == parent->lchild && parent == grand->rchild){
                __rightRotate(parent);
                current = current->rchild;
            }
            parent = current->parent, grand = parent->parent;
            if(parent == grand->lchild)
                __rightRotate(grand);
            else
                __leftRotate(grand);
            parent->setColor(__color::black);
            grand->setColor(__color::red);
        }
    }

    _RB_Node *__find(_RB_Node *d, int val){
        if(!d)  return nullptr;
        if(d->get() <= val && d->rchild)    // <
            return __find(d->rchild, val);
        else if(d->get() > val && d->lchild)    // >=
            return __find(d->lchild, val);
        return d;
    }

    void __printStat(_RB_Node *d){
        if(!d)  return;
        int lh = 0, rh = 0;
        std::cout << "=========================" << std::endl;
        std::cout << "value: " << d->get() << std::endl;
        if(d->getColor() == __color::red)
            std::cout << "color: red" << std::endl;
        else
            std::cout << "color: black" << std::endl;
        std::cout << "=========================" << std::endl;
    }

    void __inorder(_RB_Node *d){
        if(!d)  return;
        __inorder(d->lchild);
        __printStat(d);
        __inorder(d->rchild);
    }
public:
    RBTree():root(nullptr){}
    RBTree(const RBTree& tree){root = __copyTree(tree.root);}
    ~RBTree(){__deleteTree(root);};

    void insert(int val){
        if(!root){                                              // case 1: parent is nullptr
            root = new _RB_Node(val, __color::black);
            return;
        }
        _RB_Node *parent = __find(root, val);
        _RB_Node *newNode = new _RB_Node(val, __color::red, parent);
        if(parent->get() <= val) parent->rchild = newNode;  // <
        else    parent->lchild = newNode;
        __insert(newNode);
    }
    void erase(int){
        // TODO
    }
    void printStat(){
        __inorder(root);
    }
};