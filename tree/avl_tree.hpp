#pragma once

#include <iostream>
#include <algorithm>

class TreeNode{
    int v, h;

    inline int __lheight() const {
        if(lchild)  return lchild->h;
        return 0;
    }
    inline int __rheight() const {
        if(rchild)  return rchild->h;
        return 0;
    }
public:
    TreeNode *parent, *lchild, *rchild;

    TreeNode():
    h(1), parent(nullptr), lchild(nullptr), rchild(nullptr){}
    TreeNode(int v):v(v){TreeNode();}
    TreeNode(int v, int h, TreeNode *t):
    v(v), h(h), parent(t), lchild(nullptr), rchild(nullptr){}
    TreeNode(const TreeNode &)=delete;
    TreeNode &operator = (const TreeNode &)=delete;

    inline int get() const {return v;}
    inline int height() const {return h;}
    inline int balance() const {return __lheight()-__rheight();}
    void stat(int &v, int &h, int &lh, int &rh){
        v = this->v;
        h = this->h;
        lh = __lheight();
        rh = __rheight();
    }
    void __updateHeight(){
        h = std::max(__lheight(),__rheight())+1;
    }
};

class AVLTree{
    TreeNode *root;

    TreeNode *__copyTree(const TreeNode *d, TreeNode *p){
        if(!d)   return nullptr;
        TreeNode *node = new TreeNode(d->get(), d->height(), p);
        if(d->lchild)    p->lchild = __copyTree(d->lchild, node);
        if(d->rchild)    p->rchild = __copyTree(d->rchild, node);
        return node;
    }

    void __deleteTree(TreeNode *d){
        if(!d)  return;
        __deleteTree(d->lchild);
        __deleteTree(d->rchild);
        delete d;
    }

    TreeNode *__find(int v, TreeNode *d){
        if(!d)  return d;
        if(d->get() < v){
            if(d->rchild)   return __find(v, d->rchild);
            return d;
        }
        if(d->lchild)   return __find(v, d->lchild);
        return d;
    }

    void __leftRotate(TreeNode *d){
        TreeNode *p = d->rchild;
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

    void __rightRotate(TreeNode *d){
        TreeNode *p = d->lchild;
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

    void __update(TreeNode *d, int val){
        if(!d)   return;
        d->__updateHeight();
        int diff = d->balance();
        TreeNode *rotate = d->get()<val?d->rchild:d->lchild;
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
        __update(d->parent, val);
    }

    void __printStat(TreeNode *d){
        if(!d)  return;
        int lh = 0, rh = 0;
        if(d->lchild)   lh = d->lchild->height();
        if(d->rchild)   rh = d->rchild->height();
        std::cout << "=========================" << std::endl;
        std::cout << "value:            " << d->get() << std::endl;
        std::cout << "height:           " << d->height() << std::endl;
        std::cout << "|- left height:   " << lh << std::endl;
        std::cout << "|- right height:  " << rh << std::endl;
        std::cout << "=========================" << std::endl;
    }

    void __inorder(TreeNode *d){
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

    TreeNode *find(int val){
        return __find(val, root);
    }

    void insert(int val){
        if(!root){
            root = new TreeNode(val);
            return;
        }
        TreeNode *d = __find(val, root);
        TreeNode *node = new TreeNode(val, 1, d);
        if(d->get() < val)
            d->rchild = node;
        else
            d->lchild = node;
        __update(d, val);
    }

    void printStat(){
        __inorder(root);
    }
};