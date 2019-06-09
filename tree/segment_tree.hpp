#pragma once

class SegmentTree{
    class _Seg_Node{
        int v, _min, _max, _pending;
        bool leaf;

    public:
        _Seg_Node *lchild, *rchild;

        _Seg_Node(int v, int l, int r):
        v(v), _min(l), _max(r), _pending(0), lchild(nullptr), rchild(nullptr), leaf(false){}
        _Seg_Node(const _Seg_Node &node)=delete;
        ~_Seg_Node()=default;
        _Seg_Node &operator = (const _Seg_Node &)=delete;

        void __setValue(int v){this->v = v;}
        void __setDiff(int v){this->_pending += v;}
        void __setLeaf(){this->leaf = true;}
        void __clearDiff(){this->_pending = 0;}
        int getMax() const {return _max;}
        int getMin() const {return _min;}
        int getDiff() const {return _pending;}
        int get() const {return v;}
        bool isLeaf() const {return leaf;}
    };

    int length;
    _Seg_Node *root;

    _Seg_Node *__copyTree(const _Seg_Node *d){
        if(!d)   return nullptr;
        _Seg_Node *node = new _Seg_Node(d->get(), d->getMin(), d->getMax());
        if(d->lchild)
            node->lchild = __copyTree(d->lchild);
        if(d->rchild)
            node->rchild = __copyTree(d->rchild);
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
        d->__setValue(val);
    }

    void __pushdown(_Seg_Node *d){
        if(!d)  return;
        if(d->getDiff() == 0)   return;
        if(d->lchild)   d->lchild->__setDiff(d->getDiff());
        if(d->rchild)   d->rchild->__setDiff(d->getDiff());
        d->__clearDiff();
    }

    _Seg_Node *__buildTree(int *arr, int l, int r){
        if(l > r)   return nullptr;
        _Seg_Node *node = new _Seg_Node(0, l, r);
        if(r == l){
            node->__setValue(arr[l]);
            node->__setLeaf();
        } else {
            int mid = (l+r)>>1, val = 0;
            node->lchild = __buildTree(arr, l, mid);
            node->rchild = __buildTree(arr, mid+1, r);
            if(node->lchild)
                val += node->lchild->get();
            if(node->rchild)
                val += node->rchild->get();
            node->__setValue(val);
        }
        return node;
    }

    void __modify(_Seg_Node *d, int l, int r){
        if(!d)  return;
        if(d->getDiff()){
            int val = (d->getMax()-d->getMin()+1)*d->getDiff()+d->get();
            d->__setValue(val);
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
        if(l == d->getMin() && r == d->getMax())    d->__setDiff(diff);
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
        __modifyLazy(root, l, r, diff);
    }
};