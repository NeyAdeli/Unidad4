
#include <iostream>
#include <string>
using namespace std;
 

struct Node
{
    int data;
    Node *left, *right;
 
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};
 
struct Btree
{
    Btree *prev;
    string str;
 
    Btree(Btree *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};
 

void showbtree(Btree *p)
{
    if (p == nullptr) {
        return;
    }
 
    showbtree(p->prev);
    cout << p->str;
}
 
void printTree(Node* root, Btree *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    string prev_str = "    ";
    Btree *btree = new Btree(prev, prev_str);
 
    printTree(root->right, btree, true);
 
    if (!prev) {
        btree->str = "---";
    }
    else if (isLeft)
    {
        btree->str = "---";
        prev_str = "   |";
    }
    else {
        btree->str = "---";
        prev->str = prev_str;
    }
 
    showbtree(btree);
    cout << " " << root->data << endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    btree->str = "   |";
 
    printTree(root->left, btree, false);
}
 
int main()
{

    Node* root = new Node(15);
    root->left = new Node(5);
    root->right = new Node(10);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->right->left = new Node(13);
    root->right->right = new Node(1);
    root->left->left->left = new Node(12);
    root->left->left->right = new Node(9);
    root->left->right->left = new Node(3);
    root->left->right->right = new Node(11);
    root->right->left->left = new Node(4);
    root->right->left->right = new Node(6);
    root->right->right->left = new Node(14);
    root->right->right->right = new Node(8);
 

    printTree(root, nullptr, false);
 
    return 0;
}
