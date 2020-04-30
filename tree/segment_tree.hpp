#pragma once

#include "basic_tree.hpp"

class SegmentTree: public BasicTree{
    class _Seg_Node{
        int v, _l, _r, _pending;

    public:
        _Seg_Node *parent, *lchild, *rchild;

        _Seg_Node(int v, int l, int r):
        v(v), _l(l), _r(r), _pending(0), lchild(nullptr), rchild(nullptr){}
        _Seg_Node(const _Seg_Node &node){
            lchild = rchild = nullptr;
            v = node.v;
            _l = node._l;
            _r = node._r;
            _pending = node._pending;
        }
        ~_Seg_Node()=default;
        _Seg_Node &operator = (const _Seg_Node &)=delete;

        void _setValue(int v){this->v = v;}
        void _setPend(int v){this->_pending += v;}
        void _clearPend(){this->_pending = 0;}
        int getLeft() const {return _l;}
        int getRight() const {return _r;}
        int getPend() const {return _pending;}
        int get() const {return v;}
    };

    int length;
    _Seg_Node *root;

    void __update(_Seg_Node *d, int diff){
        d->_setValue((d->getRight()-d->getLeft()+1)*diff+d->get());
    }

    void __pushup(_Seg_Node *d){
        if(!d || (d->getRight() == d->getLeft()))  return;
        int val = 0;
        if(d->lchild)   val += d->lchild->get();
        if(d->rchild)   val += d->rchild->get();
        d->_setValue(val);
    }

    void __pushdown(_Seg_Node *d){
        if(!d || d->getPend() == 0)   return;
        int diff = d->getPend();
        if(d->lchild){
            d->lchild->_setPend(diff);
            __update(d->lchild, diff);
        }
        if(d->rchild){
            d->rchild->_setPend(diff);
            __update(d->rchild, diff);
        }
        d->_clearPend();
    }

    _Seg_Node *__buildTree(int *arr, int l, int r){
        if(l > r)   return nullptr;
        _Seg_Node *node = new _Seg_Node(0, l, r);
        if(r == l)
            node->_setValue(arr[l]);
        else {
            int mid = (l+r)>>1, val = 0;
            node->lchild = __buildTree(arr, l, mid);
            node->rchild = __buildTree(arr, mid+1, r);
            __pushup(node);
        }
        return node;
    }

    int __query(_Seg_Node *d, int l, int r){
        if(!d)  return 0;
        if(l == d->getLeft() && r == d->getRight())
            return d->get();
        int val = 0;
        __pushdown(d);
        if(r <= d->lchild->getRight())
            return __query(d->lchild, l, r);
        if(l >= d->rchild->getLeft())
            return __query(d->rchild, l, r);
        return  __query(d->lchild, l, d->lchild->getRight())+__query(d->rchild, d->rchild->getLeft(), r);
    }

    void __modify(_Seg_Node *d, int l, int r, int diff){
        if(!d)  return;
        int mid = (d->getRight()+d->getLeft())>>1;
        if(l == d->getLeft() && r == d->getRight()){
            d->_setPend(diff);
            __update(d, diff);
            return;
        }
        if(d->getLeft() == d->getRight())   return;
        __pushdown(d);
        if(r <= mid)   __modify(d->lchild, l, r, diff);
        else if(l > mid)    __modify(d->rchild, l, r, diff);
        else{
            __modify(d->lchild, l, mid, diff);
            __modify(d->rchild, mid+1, r, diff);
        }
        __pushup(d);
    }
public:
    SegmentTree():BasicTree(), length(0), root(nullptr){}
    SegmentTree(int *arr, int n){buildTree(arr, n);}
    SegmentTree(const SegmentTree &tree){
        length = tree.length;
        root = __copyTree(tree.root);
    }
    ~SegmentTree(){__deleteTree(root);}

    void buildTree(int *arr, int n){length = n;root = __buildTree(arr, 0, n-1);}
    int query(int l, int r){
        if(l > r)   l ^= r ^= l ^= r;
        if(l < 0 || r >= length)    return 0;
        return __query(root, l, r);
    }
    void modify(int l, int r, int diff){
        if(!diff)   return;
        if(l > r)   l ^= r ^= l ^= r;
        if(l < 0 || r >= length)    return;
        __modify(root, l, r, diff);
    }
};