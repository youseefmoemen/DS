#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

class node
{
public:
    string data_userName;
    string data_Name;
    string data_email;
    node *next;
};


class TreapNode
{
public:
    string data_userName;
    int priority;
    node *user;
    TreapNode *left, *right;
    TreapNode(string data_userName, node *u)
    {
        this->data_userName = data_userName;
        this->priority = rand() % 100;
        this->left = this->right = NULL;
        this->user = u;
    }
};

struct data
{
    node* user;
    TreapNode* friends;
    data* next;
    data(node *u){
        user = u;
        friends = nullptr;
        next = nullptr;
    }
};

data *head;
data *tail;

void Left_Rot(TreapNode *&root)
{
    TreapNode *Right = root->right;
    TreapNode *X = root->right->left;
    Right->left = root;
    root->right = X;
    root = Right;
}

void Right_Rot(TreapNode *&root)
{
    TreapNode *Left = root->left;
    TreapNode *Y = root->left->right;
    Left->right = root;
    root->left = Y;
    root = Left;
}

void insertNode(TreapNode *&root, node* frnd) //redo
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
            Right_Rot(root);
    }
    else if(frnd->data_userName > root->data_userName)
    {
        insertNode(root->right, frnd);
        if (root->right != NULL && root->right->priority > root->priority)
            Left_Rot(root);
    }
}

bool searchNode(TreapNode *root, string key)
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

void displayTreap(TreapNode *root, int space = 0, int height = 10)
{
    if (root == NULL)
        return;
    space += height;
    displayTreap(root->left, space);
    cout << endl;
    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->data_userName << "(" << root->priority << ")\n";
    cout << endl;
    displayTreap(root->right, space);
}

void insert_end(string new_data_userName, string new_data_Name, string new_data_email)
{
    node *new_node = new node();
    new_node->data_userName = new_data_userName;
    new_node->data_Name = new_data_Name;
    new_node->data_email = new_data_email;

    if (head == NULL)
    {
        head = new data(new_node);
        tail = head;
        return;
    }
    tail->next = new data(new_node);
    tail = tail->next;
}

void delete_duplicates(node *head)
{
    node *curr = head;
    node *ptr2;
    node *ptr3;
    while (curr->next != NULL && curr != NULL)
    {
        ptr2 = curr;
        while (ptr2->next != NULL)
        {
            if (curr->data_userName == ptr2->next->data_userName)
            {
                ptr3 = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete (ptr3);
            }
            else
                ptr2 = ptr2->next;
        }
        curr = curr->next;
    }
}

void printBST(TreapNode *t)
{
    if (t == nullptr)
    {
        return;
    }
    cout << t->data_userName << endl;
    printBST(t->left);
    printBST(t->right);
}
void printt(TreapNode* t){
    if(t == nullptr){
        return;
    }
    cout << t->data_userName << " " ;
    printt(t->left);
    printt(t->right);
}

void print_data(){
    data* tmp = head;
    while (tmp)
    {
        cout << tmp->user->data_userName << " " << tmp->user->data_Name << " " << tmp->user->data_email  << "\nTRP:\n";
        printt(tmp->friends);
        cout << "\n-------------------------------------------------------------\n";
        tmp = tmp->next;
    }
    
}

int main()
{

    fstream input = fstream("all-users.in", ios::in);
    while (!input.eof())
    {
        string s;
        getline(input, s);
        stringstream f(s);
        string a, b, c;
        getline(f, a, ',');
        getline(f, b, ',');
        getline(f, c, ',');
        insert_end(a, b, c);
    }
    fstream input2 = fstream("all-users-relations.in", ios::in);
    while (!input2.eof())
    {
        string s;
        getline(input2, s);
        stringstream f(s);
        string a, b;
        getline(f, a, ',');
        getline(f, b, ',');
        b.erase(b.begin()); //for White space
        data *tmp = head;
        data *tmp2 = head;
        bool flag1 = true, flag2 = true; 
        while (tmp and flag1)
        {
            if (tmp->user->data_userName == a)
            {
                while (tmp2 and flag2)
                {
                    if(tmp2->user->data_userName == b){
                        insertNode(tmp->friends, tmp2->user);
                        flag2 = false;
                    }
                    tmp2 = tmp2->next;
                }
                flag1 = false;
            }
            tmp = tmp->next;
        }
    }
    print_data();
    return 0;
}
