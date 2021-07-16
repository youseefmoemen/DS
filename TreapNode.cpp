#include "TreapNode.h"
#include <climits>

TreapNode::TreapNode(string data_userName, node *u){
    this->data_userName = data_userName;
    this->priority = rand() % INT_MAX;
    this->left = this->right = NULL;
    this->user = u;
}

//Left Rotation
void TreapNode::Left_Rot(TreapNode *&root)
{
    TreapNode *Right = root->right;
    TreapNode *X = root->right->left;
    Right->left = root;
    root->right = X;
    root = Right;
}

//Right Rotation
void TreapNode::Right_Rot(TreapNode *&root)
{
    TreapNode *Left = root->left;
    TreapNode *Y = root->left->right;

    Left->right = root;

    root->left = Y;

    root = Left;
}
//insert node in the Treap
void TreapNode::insertNode(TreapNode *&root, node* frnd)
{
    if (root == nullptr)
    {
        root = new TreapNode(frnd->data_userName, frnd);
        return;
    }
    else if (frnd->data_userName < root->data_userName)
    {
        insertNode(root->left, frnd);
        if (root->left != NULL && root->left->priority > root->priority)
            Right_Rot(root);
    }
    else if(frnd->data_userName > root->data_userName)
    {
        insertNode(root->right, frnd);
        if (root->right != NULL && root->right->priority > root->priority)
           Left_Rot(root);
    }
    else //duplcation
        return;
}

//Search in the Treap
bool TreapNode::searchNode(TreapNode *root, string key)
{
    if (root == NULL)
    {
        cout << "not found" << endl;
        return false;
    }

    else if (root->data_userName == key)
    {
        cout << "found" << endl;
        cout << key << endl;
        return true;
    }

    else if (key < root->data_userName)
        return searchNode(root->left, key);

    else
        return searchNode(root->right, key);
}

