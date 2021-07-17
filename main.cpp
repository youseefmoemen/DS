#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "TreapNode.h"
#include "TreapNode.cpp"
using namespace std;


//Data of the node of Linked List
struct data {
    node *user;
    TreapNode *friends;
    data *next;
    data(node *u) {
        user = u;
        friends = nullptr;
        next = nullptr;
    }
};

//Head and Tail of The Linked List
data *head;
data *tail;

void displayTreap(TreapNode *root, int space = 0, int height = 10);

//Insert at the end of the linked list
void insert_end(string new_data_userName, string new_data_Name, string new_data_email) ;

//Print the data of the linked list
void print_data() ;

//inorder Traversal
void inorder(TreapNode *root);
//Print name and user name and email of the user
void PrintUser(node *Node);

//Function that get people may know
void potential_friends(data *user);

int main()
{

    fstream input = fstream("all-users.in", ios::in);

    while (!input.eof()) {
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
    while (!input2.eof()) {
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
        while (tmp and flag1) {
            if (tmp->user->data_userName == a) {
                while (tmp2 and flag2) {
                    if (tmp2->user->data_userName == b) {
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

    short choice=1;

    while (choice) {
        cout << "1- Log in\n"
             << "2- Exit\n";
        cin >> choice;
        if (choice == 1) {
            string username;
            cout << "Enter Username:";
            cin >> username;

            data *curr = head;

            data *user = NULL;
            while (curr != NULL && !user) {

                if (curr->user->data_userName == username) {
                    user = curr;
                }

                curr = curr->next;

            }

            if (user == NULL) {
                cout << "Invalid Username\n";
            } else {

                short choice2=1;
                while (choice2) {
                    cout << "1- List all friends\n"
                         << "2- Search by username\n"
                         << "3- Add friend\n"
                         << "4- Remove friend\n"
                         << "5- People you may know\n"
                         << "6- logout\n";
                    cin >> choice2;

                    if (choice2 == 1) {
                        cout << "Friends:-\n";
                        inorder(user->friends);

                    } else if (choice2 == 2) {
                        string username2;
                        cout << "please Enter the Username: ";
                        cin >> username2;

                        node *Friend = user->friends->Find(user->friends, username2);
                        if(Friend!=NULL)
                            PrintUser(Friend);
                        else
                            cout<<"Not Found\n";

                    } else if (choice2 == 5) {

                        cout << "people you may know:-\n\n";
                        potential_friends(user);
                        cout << "-------------------------------------------------------------\n";

                    } else if (choice2 == 6){
                        break;
                    }
                    else{
                        cout<<"Choice invalid\n";
                    }

                }
            }


        } else if (choice == 2) {
            return 0;
        } else {
            cout << "please Enter right number:\n";
            cin >> choice;
        }


    }


    return 0;
}


void PrintUser(node *Node)
{

    cout << "Data:-" << endl;
    cout << "Username:" << Node->data_Name << endl;
    cout << "Name:" << Node->data_Name << endl;
    cout << "Email:" << Node->data_email << endl;
    cout << "-------------------------------------------------------------\n";

}

void potential_friends(data *user){
    data *tmp = head;
    int count = 0;
    while (tmp)
    {
        if(tmp != user and !user->friends->searchNode(user->friends, tmp->user->data_userName)){
            cout << count+1 << ": " << tmp->user->data_userName << ", " << tmp->user->data_Name << endl;
            count++;
        }
        if (count == 5)
        {
            return;
        }
        tmp = tmp->next;
    }
}

void inorder(TreapNode *root)
{

    if (root == NULL) {
        cout << "-------------------------------------------------------------\n";
        return;
    }
    inorder(root->left);
    cout << "userName:" << root->data_userName
         << "\nName:" << root->user->data_Name << "\n";
    inorder(root->right);

}
void insert_end(string new_data_userName, string new_data_Name, string new_data_email) {
    node *new_node = new node();
    new_node->data_userName = new_data_userName;
    new_node->data_Name = new_data_Name;
    new_node->data_email = new_data_email;

    if (head == NULL) {
        head = new data(new_node);
        tail = head;
        return;
    }
    tail->next = new data(new_node);
    tail = tail->next;
}

void displayTreap(TreapNode *root, int space, int height)
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

void print_data() {
    data *tmp = head;
    while (tmp) {
        cout << tmp->user->data_userName << " " << tmp->user->data_Name << " " << tmp->user->data_email << "\nTRP:\n";
        displayTreap(tmp->friends);

        cout << "\n-------------------------------------------------------------\n";
        tmp = tmp->next;
    }

}
