#include <iostream>

struct node {
    int key;
    unsigned char height;
    node* left;
    node* right;
    node(int k)
    {
        key = k;
        left = right = 0;
        height = 1;
    }
};

unsigned char height(node* p)
{
    return p ? p->height : 0;
}

int heightDifference(node* p)
{
    return height(p->right) - height(p->left);
}

void setheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    setheight(p);
    setheight(q);
    return q;
}

node* rotateleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    setheight(q);
    setheight(p);
    return p;
}

node* balance(node* p)
{
    setheight(p);
    if (heightDifference(p) == 2) {
        if (heightDifference(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (heightDifference(p) == -2) {
        if (heightDifference(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

node* insert(node* p, int k)
{
    if (!p)
        return new node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node* findmin(node* p)
{
    return p->left ? findmin(p->left) : p;
}

node* removemin(node* p)
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k)
{
    if (!p)
        return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r)
            return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

int main(int ac, char** av)
{
    node* n = new node(2);

    n = insert(n, 3);
    n = insert(n, 5);
    n = insert(n, -1);
    n = insert(n, -4);

    return 0;
}