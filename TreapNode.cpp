#include <climits>
#ifndef TREAPNODE_H
#define TREAPNODE_H

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
        if (root->left != NULL && root->left->priority < root->priority)
            Right_Rot(root);
    }

    else if(frnd->data_userName > root->data_userName)
    {
        insertNode(root->right, frnd);
        if (root->right != NULL && root->right->priority < root->priority)
           Left_Rot(root);
    }
    else //duplcation
        return;
}

//Search in the Treap
bool TreapNode::searchNode(TreapNode *root, string key) //Deleting the cout(s) just useless and use conditions at callings
{
    if (root == NULL)
    {
        return false;
    }

    else if (root->data_userName == key)
    {
        return true;
    }

    else if (key < root->data_userName)
        return searchNode(root->left, key);

    else
        return searchNode(root->right, key);
}
node *TreapNode::Find(TreapNode *root, string key) {
    if (root == NULL)
    {
        return nullptr;
    }

    else if (root->data_userName == key)
    {
        return root->user;
    }

    else if (key < root->data_userName)
        return Find(root->left, key);

    else
        return Find(root->right, key);

}


void TreapNode::remove(TreapNode* &root, string key)
{
    if (root == NULL)
        return;


    if (key < root->data_userName)
        remove(root->left, key);


    else if (key > root->data_userName)
        remove(root->right, key);


    else
        {

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = nullptr;
        }

        else if (root->left!=NULL && root->right!=NULL)
        {

            if (root->left->priority < root->right->priority)
            {
                Right_Rot(root);
                remove(root->left, key);
            }
            else {
                Left_Rot(root);
                remove(root->right, key);
            }

        }

        else {
            TreapNode* child = (root->left)? root->left: root->right;
            TreapNode* curr = root;
            root = child;
            delete curr;
        }
    }
}


#endif
