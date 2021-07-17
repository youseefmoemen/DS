

#include "node.h"
#include <iostream>
using namespace std;
class TreapNode
{
public:
    string data_userName;
    int priority;
    node *user;
    TreapNode *left, *right;
    TreapNode(string, node *);
    void Left_Rot(TreapNode *&);
    void Right_Rot(TreapNode *&);
    void insertNode(TreapNode *&, node*);
    bool searchNode(TreapNode *, string);
    node* Find(TreapNode*,string);
    void remove(TreapNode* &root, string key);
    


    };

