#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
int data;
Node *left_child;
Node *right_child;

Node(int key) {
data = key;
left_child = nullptr;
right_child = nullptr;
}
};


Node* search(Node* root, int val)
{
    Node* current = root;
    while(current!= nullptr)
    {
        if(current->data == val)
        {
            return current;
        }
        else if(val > current->data)
        {
            current = current->right_child;
        }
        else
        {
            current = current->left_child;
        }
    }
    return nullptr;
}


int main()
{

    return 0;
}