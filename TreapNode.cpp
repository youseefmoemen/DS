#include "TreapNode.h"

TreapNode::TreapNode(string data_userName, node *u){
        this->data_userName = data_userName;
    this->priority = rand() % 100;
    this->left = this->right = NULL;
    this->user = u;
}

void TreapNode::Left_Rot(TreapNode *&root)
{
    TreapNode *Right = root->right;
    TreapNode *X = root->right->left;
    Right->left = root;
    root->right = X;
    root = Right;
}


void TreapNode::Right_Rot(TreapNode *&root)
{
    TreapNode *Left = root->left;
    TreapNode *Y = root->left->right;
    Left->right = root;
    root->left = Y;
    root = Left;
}

void TreapNode::insertNode(TreapNode *&root, node* frnd) 
{
    if (root == nullptr)
    {
        root = new TreapNode(frnd->data_userName, frnd);
        return;
    }
    if (frnd->data_userName < root->data_userName)
    {
        insertNode(root->left, frnd);
        if (root->left != NULL && root->left->priority > root->priority)
            root->Right_Rot(root);
    }
    else if(frnd->data_userName > root->data_userName)
    {
        insertNode(root->right, frnd);
        if (root->right != NULL && root->right->priority > root->priority)
            root->Left_Rot(root);
    }
}

bool TreapNode::searchNode(TreapNode *root, string key)
{
    if (root == NULL)
    {
        cout << "not found" << endl;
        return false;
    }

    if (root->data_userName == key)
    {
        cout << "found" << endl;
        cout << key << endl;
        return true;
    }

    if (key < root->data_userName)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}
