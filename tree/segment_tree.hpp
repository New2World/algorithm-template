#pragma once

#include <iostream>

class SegmentTree{
    class _Seg_Node{
        int v, _min, _max;
        bool leaf;

        friend void __setValue(_Seg_Node *, int);
        friend void __setLeaf(_Seg_Node *);
    public:
        _Seg_Node *parent, *lchild, *rchild;

        _Seg_Node(int l, int r):
        v(0), _min(l), _max(r), parent(nullptr), lchild(nullptr), rchild(nullptr), leaf(false){}
        _Seg_Node(const _Seg_Node &node){
            v = node.v;
            _max = node._max;
            _min = node._min;
            leaf = node.leaf;
        }

        int getMax() const {return _max;}
        int getMin() const {return _min;}
        int get() const {return v;}
        bool isLeaf() const {return leaf;}
    };

    friend void __setValue(_Seg_Node *d, int v){if(d)   d->v = v;}
    friend void __setLeaf(_Seg_Node *d){if(d)   d->leaf = true;}

    int length;
    _Seg_Node *root;

    _Seg_Node *__copyTree(const _Seg_Node *d, _Seg_Node *p){
        if(!d)   return nullptr;
        _Seg_Node *node = new _Seg_Node(*d);
        node->parent = p;
        if(d->lchild)    p->lchild = __copyTree(d->lchild, node);
        if(d->rchild)    p->rchild = __copyTree(d->rchild, node);
        return node;
    }

    void __deleteTree(_Seg_Node *d){
        if(!d)  return;
        __deleteTree(d->lchild);
        __deleteTree(d->rchild);
        delete d;
    }

    // void __update(_Seg_Node *d){
    //     if(!d)  return;
    //     int _sum = 0;
    //     if(d->lchild)   _sum += d->lchild->get();
    //     if(d->rchild)   _sum += d->rchild->get();
    //     __setValue(d, _sum);
    //     __update(d->parent);
    // }

    _Seg_Node *__buildTree(int *arr, int l, int r){
        if(l > r)   return nullptr;
        _Seg_Node *node = new _Seg_Node(l, r);
        if(r == l){
            __setValue(node, arr[l]);
            __setLeaf(node);
        } else {
            int mid = (l+r)>>1, val = 0;
            node->lchild = __buildTree(arr, l, mid);
            node->rchild = __buildTree(arr, mid+1, r);
            if(node->lchild){
                node->lchild->parent = node;
                val += node->lchild->get();
            }
            if(node->rchild){
                node->rchild->parent = node;
                val += node->rchild->get();
            }
            __setValue(node, val);
        }
        return node;
    }

    int __query(_Seg_Node *d, int l, int r){
        if(!d)  return 0;
        if(l == d->getMin() && r == d->getMax())  return d->get();
        if(d->lchild && r <= d->lchild->getMax())
            return __query(d->lchild, l, r);
        if(d->rchild && l >= d->rchild->getMin())
            return __query(d->rchild, l, r);
        return  __query(d->lchild, l, d->lchild->getMax())+ \
                __query(d->rchild, d->rchild->getMin(), r);
    }
public:
    SegmentTree():length(0), root(nullptr){}
    SegmentTree(int *arr, int n){buildTree(arr, n);}
    SegmentTree(const SegmentTree &tree){length = tree.length;root = __copyTree(tree.root, nullptr);}

    void buildTree(int *arr, int n){length = n;root = __buildTree(arr, 0, n-1);}
    int query(int l, int r){
        if(l > r)   l ^= r ^= l ^= r;
        if(l < 0 || r >= length)    return 0;
        return __query(root, l, r);
    }
};