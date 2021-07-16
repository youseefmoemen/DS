#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "TreapNode.h"
using namespace std;


//Data of the node of Linked List
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
//Head and Tail of The Linked List
data *head;
data *tail;

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

//inorder Traversal
void inorder(TreapNode *root){
    displayTreap(root->left);
    cout << root->data_userName << '(' << root->priority << ")\n";
    displayTreap(root->right);

}

//Insert at the end of the linked list
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

//Print the data of the linked list
void print_data(){
    data* tmp = head;
    while (tmp)
    {
        cout << tmp->user->data_userName << " " << tmp->user->data_Name << " " << tmp->user->data_email  << "\nTRP:\n";
        displayTreap(tmp->friends);

        cout << "\n-------------------------------------------------------------\n";
        tmp = tmp->next;
    }

}


int main() {

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

    //put the Friends in the Treap
    while (!input2.eof())
    {
        string s;
        getline(input2, s);
        stringstream f(s);
        string a, b;
        getline(f, a, ',');
        getline(f, b, ',');
        b.erase(b.begin());
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
                        tmp->friends->insertNode(tmp->friends, tmp2->user);
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