#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "TreapNode.h"
using namespace std;


//Data of the node of Linked List
struct data_node {
    node *user;
    TreapNode *friends;
    data_node *next;
    data_node(node *u) {
        user = u;
        friends = nullptr;
        next = nullptr;
    }
};

//Head and Tail of The Linked List
data_node *head;
data_node *tail;

//Insert at the end of the linked list
void insert_end(string new_data_userName, string new_data_Name, string new_data_email) ;


//inorder Traversal
void inorder(TreapNode *root);
//Print name and user name and email of the user
void PrintUser(node *Node);

//Function that get people may know
void potential_friends(data_node *user);

//function to make two users friends
void add_friend(data_node *user, data_node *frnd);

//function to unfriend two users
void remove_friend(data_node *user, data_node *frnd);

//searches for the user by username, used in log in, add and remove friends
data_node* get_user (string username);

int main()
{

    fstream input = fstream("all-users.in", ios::in);

    while (!input.eof()) {
        string s;
        getline(input, s);
        if(s.empty())
            continue;
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
        if(s.empty())
            continue;
        stringstream f(s);
        string a, b;
        getline(f, a, ',');
        getline(f, b, ',');
        b.erase(b.begin());

        data_node *tmp = head;
        data_node *tmp2 = head;

        bool flag1 = true, flag2 = true;
        while (tmp and flag1) {
            if (tmp->user->data_userName == a) {
                while (tmp2 and flag2) {
                    if (tmp2->user->data_userName == b) {
                        tmp->friends->insertNode(tmp->friends, tmp2->user);
                        tmp2->friends->insertNode(tmp2->friends, tmp->user);
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

            data_node *user = get_user(username);

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

                    } else if (choice2 == 3) {
                        string username2;
                        cout << "please Enter the Username: ";
                        cin >> username2;

                        data_node* frnd = get_user(username2);
                        if (frnd != NULL) {
                            add_friend(user, frnd);
                        }
                        else {
                            cout<< "Invalid Username \n";
                        }

                    } else if (choice2 == 4) {
                        string username2;
                        cout << "please Enter the Username: ";
                        cin >> username2;

                        data_node* frnd = get_user(username2);
                        if (frnd != NULL) {
                            remove_friend(user, frnd);
                        }
                        else {
                            cout<< "Invalid Username \n";
                        }

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
    cout << "Username:" << Node->data_userName << endl;
    cout << "Name:" << Node->data_Name << endl;
    cout << "Email:" << Node->data_email << endl;
    cout << "-------------------------------------------------------------\n";

}

void potential_friends(data_node *user){
    data_node *tmp = head;
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
        head = new data_node(new_node);
        tail = head;
        return;
    }
    tail->next = new data_node(new_node);
    tail = tail->next;
}

void add_friend(data_node *user, data_node *frnd) {
    if (user->friends->searchNode(user->friends, frnd->user->data_userName) == false){

        user->friends->insertNode(user->friends,frnd->user);
        frnd->friends->insertNode(frnd->friends,user->user);

        fstream relations;
        relations.open("all-users-relations.in", ios::app);
        relations << "\n" << user->user->data_userName << ", " << frnd->user->data_userName;
        relations.close();

        cout<<"You are now friends \n";
    }
    else {
        cout<<"You are already friends \n";
    }

}

void remove_friend(data_node *user, data_node *frnd) {
    if (user->friends->searchNode(user->friends, frnd->user->data_userName) == true){

        user->friends->remove(user->friends,frnd->user->data_userName);
        frnd->friends->remove(frnd->friends,user->user->data_userName);

        fstream relations, temp;
        relations.open("all-users-relations.in", ios::in);
        temp.open("temp.txt", ios::out);
        while (!relations.eof()) {
            string line;
            getline(relations, line);
            if (line != user->user->data_userName+", "+ frnd->user->data_userName
                && line != frnd->user->data_userName+", "+ user->user->data_userName) {
                temp << line << endl;
            }
        }
        relations.close();
        temp.close();

        relations.open("all-users-relations.in", ios::out);
        temp.open("temp.txt", ios::in);
        while (!temp.eof()) {
            string line;
            getline(temp, line);
            relations << line << endl;
        }
        relations.close();
        temp.close();
        remove("temp.txt");

        cout<< "Done \n";
    }
    else {
        cout<<"Done \n";
    }
}

data_node* get_user (string username) {
    data_node *curr = head;

    data_node *user = NULL;
    while (curr != NULL && !user) {

        if (curr->user->data_userName == username) {
            user = curr;
        }
        curr = curr->next;
    }
    return user;
}
