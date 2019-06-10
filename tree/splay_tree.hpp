#pragma once

class SplayTree{
    class _Sp_Node{
        int v;
    public:
        _Sp_Node *parent, *lchild, *rchild;

        _Sp_Node(int v, _Sp_Node *p=nullptr):
        v(v), parent(p), lchild(nullptr), rchild(nullptr){}
        _Sp_Node(const _Sp_Node &d)=delete;
        ~_Sp_Node()=default;
        _Sp_Node &operator = (const _Sp_Node &)=delete;

        int get() const {return v;}
    };

    _Sp_Node *root;

    _Sp_Node *__copyTree(const _Sp_Node *d){
        if(!d)   return nullptr;
        _Sp_Node *node = new _Sp_Node(d->get());
        if(d->lchild){
            node->lchild = __copyTree(d->lchild);
            node->lchild->parent = node;
        }
        if(d->rchild){
            node->rchild = __copyTree(d->rchild);
            node->rchild->parent = node;
        }
        return node;
    }

    void __deleteTree(_Sp_Node *d){
        if(!d)  return;
        __deleteTree(d->lchild);
        __deleteTree(d->rchild);
        delete d;
    }

    void __leftRotate(_Sp_Node *d){
        _Sp_Node *p = d->rchild;
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
    }

    void __rightRotate(_Sp_Node *d){
        _Sp_Node *p = d->lchild;
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
    }

    _Sp_Node *__find(_Sp_Node *d, int v){
        if(!d)  return d;
        if(d->get() <= v && d->rchild)  return __find(d->rchild, v);
        if(d->get() > v && d->lchild)   return __find(d->lchild, v);
        return d;
    }

    _Sp_Node *__locate(_Sp_Node *d, int v){
        if(!d)  return nullptr;
        if(d->get() == v)   return d;
        if(d->get() <= v)    return __locate(d->rchild, v);
        return __locate(d->lchild, v);
    }

    _Sp_Node *__maxLeaf(_Sp_Node *d){
        if(!d)  return nullptr;
        if(d->rchild)   return __maxLeaf(d->rchild);
        return d;
    }

    void __splay(_Sp_Node *d){
        if(!d)  return;
        _Sp_Node *parent = nullptr, *grand = nullptr;
        while(d != root){
            parent = d->parent;
            if(parent == root){
                if(d == parent->lchild) __rightRotate(parent);
                else    __leftRotate(parent);
                break;
            }
            grand = parent->parent;
            if(d == parent->lchild && parent == grand->lchild){
                __rightRotate(grand);
                __rightRotate(parent);
            } else if(d == parent->rchild && parent == grand->rchild){
                __leftRotate(grand);
                __leftRotate(parent);
            } else if(d == parent->lchild && parent == grand->rchild){
                __rightRotate(parent);
                __leftRotate(d->parent);
            } else {
                __leftRotate(parent);
                __rightRotate(d->parent);
            }
        }
    }

    void __remove(_Sp_Node *d, int v){
        if(!d)  return;
        _Sp_Node *node = __locate(d, v);
        if(!node)   return;
        __splay(node);
        _Sp_Node *ll = node->lchild, *rr = node->rchild;
        delete node;
        node = nullptr;
        if(ll){
            ll->parent = nullptr;
            node = __maxLeaf(ll);
            __splay(node);
            root = node;
        }
        if(rr){
            if(ll)  node->rchild = rr;
            else    root = rr;
            rr->parent = node;
        }
    }

    static void __printStat(_Sp_Node *d){
        if(!d)  return;
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
        std::cout << "=========================" << std::endl;
    }

    void __inorder(_Sp_Node *d, void (*fn)(_Sp_Node *)){
        if(!d)  return;
        __inorder(d->lchild, fn);
        fn(d);
        __inorder(d->rchild, fn);
    }
public:

    SplayTree():root(nullptr){}
    SplayTree(const SplayTree &tree){root = __copyTree(tree.root);}
    ~SplayTree(){__deleteTree(root);}

    void insert(int val){
        if(!root){
            root = new _Sp_Node(val);
            return;
        }
        _Sp_Node *parent = __find(root, val);
        _Sp_Node *node = new _Sp_Node(val, parent);
        if(parent->get() > val)
            parent->lchild = node;
        else
            parent->rchild = node;
        __splay(node);
    }

    void remove(int val){
        __remove(root, val);
    }

    void printStat(){
        __inorder(root, SplayTree::__printStat);
    }
};