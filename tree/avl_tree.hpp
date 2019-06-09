#pragma once

#include <iostream>
#include <algorithm>


class AVLTree{
    class _AVL_Node{
        int v, h;

        inline int __lheight() const {
            if(lchild)  return lchild->h;
            return 0;
        }
        inline int __rheight() const {
            if(rchild)  return rchild->h;
            return 0;
        }
        friend void __setValue(_AVL_Node *, int );
    public:
        _AVL_Node *parent, *lchild, *rchild;

        _AVL_Node():
        h(1), parent(nullptr), lchild(nullptr), rchild(nullptr){}
        _AVL_Node(int v):v(v){_AVL_Node();}
        _AVL_Node(int v, int h, _AVL_Node *t):
        v(v), h(h), parent(t), lchild(nullptr), rchild(nullptr){}
        _AVL_Node(const _AVL_Node &)=delete;
        _AVL_Node &operator = (const _AVL_Node &)=delete;

        inline int get() const {return v;}
        inline int height() const {return h;}
        inline int balance() const {return __lheight()-__rheight();}

        void __updateHeight(){
            h = std::max(__lheight(),__rheight())+1;
        }
    };

    _AVL_Node *root;

    _AVL_Node *__copyTree(const _AVL_Node *d, _AVL_Node *p){
        if(!d)   return nullptr;
        _AVL_Node *node = new _AVL_Node(d->get(), d->height(), p);
        if(d->lchild)    p->lchild = __copyTree(d->lchild, node);
        if(d->rchild)    p->rchild = __copyTree(d->rchild, node);
        return node;
    }

    void __deleteTree(_AVL_Node *d){
        if(!d)  return;
        __deleteTree(d->lchild);
        __deleteTree(d->rchild);
        delete d;
    }

    _AVL_Node *__find(int v, _AVL_Node *d){
        if(!d)  return d;
        if(d->get() <= v && d->rchild)  return __find(v, d->rchild);
        if(d->get() > v && d->lchild)   return __find(v, d->lchild);
        return d;
    }

    _AVL_Node *__locate(int v, _AVL_Node *d){
        if(!d)  return nullptr;
        if(d->get() == v)   return d;
        if(d->get() <= v)    return __locate(v, d->rchild);
        return __locate(v, d->lchild);
    }

    _AVL_Node *__maxLeaf(_AVL_Node *d){
        if(!d)  return nullptr;
        if(d->rchild)   return __maxLeaf(d->rchild);
        return d;
    }

    void __leftRotate(_AVL_Node *d){
        _AVL_Node *p = d->rchild;
        if(p->lchild)
            p->lchild->parent = d;
        d->rchild = p->lchild;
        p->parent = d->parent;
        if(d->parent == nullptr)
            root = p;
        else if(d->parent->lchild == d)
            d->parent->lchild = p;
        else
            d->parent->rchild = p;
        p->lchild = d;
        d->parent = p;
        d->__updateHeight();
        p->__updateHeight();
    }

    void __rightRotate(_AVL_Node *d){
        _AVL_Node *p = d->lchild;
        if(p->rchild)
            p->rchild->parent = d;
        d->lchild = p->rchild;
        p->parent = d->parent;
        if(d->parent == nullptr)
            root = p;
        else if(d->parent->lchild == d)
            d->parent->lchild = p;
        else
            d->parent->rchild = p;
        p->rchild = d;
        d->parent = p;
        d->__updateHeight();
        p->__updateHeight();
    }

    void __update(_AVL_Node *d, int val, bool deletion=false){
        if(!d)   return;
        d->__updateHeight();
        int diff = d->balance();
        _AVL_Node *rotate = nullptr;
        if(deletion){
            int lh = 0, rh = 0;
            if(d->lchild)   lh = d->lchild->height();
            if(d->rchild)   rh = d->rchild->height();
            rotate = lh>=rh?d->lchild:d->rchild;
        }
        else    rotate = d->get()>val?d->lchild:d->rchild;
        if(rotate){
            int subdiff = rotate->balance();
            if(diff > 1){
                if(subdiff < 0){
                    __leftRotate(rotate);
                    __rightRotate(d);
                } else   __rightRotate(d);
            }
            else if(diff < -1){
                if(subdiff < 0) __leftRotate(d);
                else{
                    __rightRotate(rotate);
                    __leftRotate(d);
                }
            }
        }
        __update(d->parent, val);
    }

    friend void __setValue(_AVL_Node *d, int v){d->v = v;}

    void __remove(_AVL_Node *d, int val){
        _AVL_Node *node = __locate(val, d), *child = nullptr, *parent = nullptr;
        if(!node)   return;
        parent = node->parent;
        if(!node->lchild || !node->rchild){
            child = node->lchild?node->lchild:node->rchild;
            if(parent){
                if(parent->lchild == node)    parent->lchild = child;
                else    parent->rchild = child;
            }
            if(child)   child->parent = parent;
            delete node;
            node = child;
        } else {
            child = __maxLeaf(node->lchild);
            __setValue(node, child->get());
            __remove(node->lchild, child->get());
        }
        if(parent)  __update(parent, 0, true);
    }

    void __printStat(_AVL_Node *d){
        if(!d)  return;
        int lh = 0, rh = 0;
        if(d->lchild)   lh = d->lchild->height();
        if(d->rchild)   rh = d->rchild->height();
        std::cout << "=========================" << std::endl;
        std::cout << "value:            " << d->get() << std::endl;
        if(d->lchild)
            std::cout << "|- left child:    " << d->lchild->get() << std::endl;
        else
            std::cout << "|- left child:    null" << std::endl;
        if(d->rchild)
            std::cout << "|- right child:   " << d->rchild->get() << std::endl;
        else
            std::cout << "|- right child:   null" << std::endl;
        std::cout << "height:           " << d->height() << std::endl;
        std::cout << "|- left height:   " << lh << std::endl;
        std::cout << "|- right height:  " << rh << std::endl;
        std::cout << "=========================" << std::endl;
    }

    void __inorder(_AVL_Node *d){
        if(!d)  return;
        __inorder(d->lchild);
        __printStat(d);
        __inorder(d->rchild);
    }
public:
    AVLTree():root(nullptr){}
    AVLTree(const AVLTree &tree){root = __copyTree(tree.root, nullptr);}
    ~AVLTree(){
        __deleteTree(root);
    }

    void insert(int val){
        if(!root){
            root = new _AVL_Node(val);
            return;
        }
        _AVL_Node *d = __find(val, root);
        _AVL_Node *node = new _AVL_Node(val, 1, d);
        if(d->get() > val)
            d->lchild = node;
        else
            d->rchild = node;
        __update(d, val);
    }

    void remove(int val){
        __remove(root, val);
    }

    void printStat(){
        __inorder(root);
    }
};