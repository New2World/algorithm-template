#pragma once

class BasicTree{
protected:
    template <class _Tree_Node>
    _Tree_Node *__copyTree(const _Tree_Node *d){
        if(!d)   return nullptr;
        _Tree_Node *node = new _Tree_Node(*d);
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

    template <class _Tree_Node>
    void __deleteTree(_Tree_Node *d){
        if(!d)  return;
        __deleteTree(d->lchild);
        __deleteTree(d->rchild);
        delete d;
    }

public:
    template <class _Tree_Node>
    void inorder(_Tree_Node *d, void (*fn)(_Tree_Node *)){
        if(!d)  return;
        inorder(d->lchild, fn);
        fn(d);
        inorder(d->rchild, fn);
    }

    template <class _Tree_Node>
    void preorder(_Tree_Node *d, void (*fn)(_Tree_Node *)){
        if(!d)  return;
        fn(d);
        preorder(d->lchild, fn);
        preorder(d->rchild, fn);
    }

    template <class _Tree_Node>
    void postorder(_Tree_Node *d, void (*fn)(_Tree_Node *)){
        if(!d)  return;
        postorder(d->lchild, fn);
        postorder(d->rchild, fn);
        fn(d);
    }
};