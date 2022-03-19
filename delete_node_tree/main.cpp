//Comment it before submitting
struct Node {
  Node* left;
  Node* right;
  int value;
};


//#include "solution.h"
#include <cassert>

Node* findReplacement(Node* node)
{
    Node* temp = node;

    while (temp && temp->left != nullptr)
    {
        temp = temp->left;
    }

    return temp;
}

Node* remove(Node* root, int key) {
    if (root == nullptr)
    {
        return root;
    }

    if (key < root->value)
    {
        root->left = remove(root->left, key);
    }
    else if (key > root->value)
    {
        root->right = remove(root->right, key);
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            return nullptr;
        }
        else if(root->left == nullptr)
        {
            Node* temp = root->right;
            root = nullptr;
            return temp;
        }
        else if(root->right == nullptr)
        {
            Node* temp = root->left;
            root = nullptr;
            return temp;
        }
        else
        {
            Node* temp = findReplacement(root->right);
            root->value = temp->value;
            root->right = remove(root->right, temp->value);
        }
    }
    return root;
}

void test() {
    Node node1({nullptr, nullptr, 14});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}
