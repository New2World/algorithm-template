#pragma once

class SegmentTree{
    class _Seg_Node{
        int v, _min, _max, _pending;
        bool leaf;

        friend void __setValue(_Seg_Node *, int);
        friend void __setDiff(_Seg_Node *, int);
        friend void __setLeaf(_Seg_Node *);
        friend void __clearDiff(_Seg_Node *);
    public:
        _Seg_Node *parent, *lchild, *rchild;

        _Seg_Node(int l, int r):
        v(0), _min(l), _max(r), _pending(0), parent(nullptr), lchild(nullptr), rchild(nullptr), leaf(false){}
        _Seg_Node(const _Seg_Node &node):
        v(node.v), _max(node._max), _min(node._min), _pending(node._pending), parent(nullptr), lchild(nullptr), rchild(nullptr), leaf(node.leaf){}

        int getMax() const {return _max;}
        int getMin() const {return _min;}
        int getDiff() const {return _pending;}
        int get() const {return v;}
        bool isLeaf() const {return leaf;}
    };

    friend void __setValue(_Seg_Node *d, int v){if(d)   d->v = v;}
    friend void __setDiff(_Seg_Node *d, int v){if(d)    d->_pending += v;}
    friend void __setLeaf(_Seg_Node *d){if(d)   d->leaf = true;}
    friend void __clearDiff(_Seg_Node *d){if(d) d->_pending = 0;}

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

    void __update(_Seg_Node *d){
        if(!d || (d->getMin() == d->getMax()))  return;
        int val = 0;
        if(d->lchild)   val += d->lchild->get();
        if(d->rchild)   val += d->rchild->get();
        __setValue(d, val);
    }

    void __pushdown(_Seg_Node *d){
        if(!d)  return;
        if(d->getDiff() == 0)   return;
        if(d->lchild)   __setDiff(d->lchild, d->getDiff());
        if(d->rchild)   __setDiff(d->rchild, d->getDiff());
        __clearDiff(d);
    }

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

    void __modify(_Seg_Node *d, int l, int r){
        if(!d)  return;
        if(d->getDiff()){
            int val = (d->getMax()-d->getMin()+1)*d->getDiff()+d->get();
            __setValue(d, val);
        }
        __pushdown(d);
        if(d->lchild)   __modify(d->lchild, l, d->lchild->getMax());
        if(d->rchild)   __modify(d->rchild, d->rchild->getMin(), r);
        __update(d);
    }

    int __query(_Seg_Node *d, int l, int r){
        if(!d)  return 0;
        if(l == d->getMin() && r == d->getMax()){
            __modify(d, l, r);
            return d->get();
        }
        if(d->lchild && r <= d->lchild->getMax())
            return __query(d->lchild, l, r);
        if(d->rchild && l >= d->rchild->getMin())
            return __query(d->rchild, l, r);
        return  __query(d->lchild, l, d->lchild->getMax())+ \
                __query(d->rchild, d->rchild->getMin(), r);
    }

    void __modifyLazy(_Seg_Node *d, int l, int r, int diff){
        if(!d)  return;
        int mid = (d->getMin()+d->getMax())>>1;
        if(l == d->getMin() && r == d->getMax())    __setDiff(d, diff);
        else if(r <= mid)   __modifyLazy(d->lchild, l, r, diff);
        else if(l > mid)    __modifyLazy(d->rchild, l, r, diff);
        else{
            __modifyLazy(d->lchild, l, mid, diff);
            __modifyLazy(d->rchild, mid+1, r, diff);
        }
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
    void modify(int l, int r, int diff){
        if(!diff)   return;
        if(l > r)   l ^= r ^= l ^= r;
        if(l < 0 || r >= length)    return;
        __modifyLazy(root, l, r, diff);
    }
};