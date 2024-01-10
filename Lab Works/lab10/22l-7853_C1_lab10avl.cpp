#include<iostream>
using namespace std;

class avl
{
    struct Node 
    {
        int data;
        Node* left;
        Node* right;
        int height;
        Node(int data, Node* left = nullptr, Node* right = nullptr)
        {
            this->data = data;
            this->left = left;
            this->right = right;
            this->height = 1;
        }
    };
    Node* root;
public:
    avl()
    {
        root = nullptr;
    }
    // copy constructor
    Node* copy(Node* other)
    {
        if (other == nullptr)// if other is empty
            return nullptr;
        Node* newNode = new Node(other->data);
        newNode->left = copy(other->left);
        newNode->right = copy(other->right);
        newNode->height = other->height;
        return newNode;
    }
    avl(const avl& other)
    {
        root = copy(other.root);
    }
    int getHeight(Node* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    int getBalanceFactor(Node* node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    Node* rotateRight(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
        return newRoot;
    }
    Node* rotateLeft(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
        return newRoot;
    }
    Node* insert(Node* node, int data)
    {
        if (node == nullptr)
        {
            node = new Node(data);
            return node;
        }
        if (data < node->data)
        {
            node->left = insert(node->left, data);
        }
        else if (data > node->data)
        {
            node->right = insert(node->right, data);
        }
        else
        {
            return node;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) // Left heavy
        {
            if (data < node->left->data) // Left Left case
            {
                return rotateRight(node);
            }
            else // Left Right case
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        else if (balanceFactor < -1) // Right heavy
        {
            if (data > node->right->data) // Right Right case
            {
                return rotateLeft(node);
            }
            else // Right Left case
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }
    void insert(int data)
    {
        root = insert(root, data);
    }
    bool search(Node* node, int data)
    {
        if (node == nullptr)
            return false;
        if (node->data == data)
            return true;
        else if (data < node->data)
            return search(node->left, data);
        else
            return search(node->right, data);
    }
    bool search(int data)
    {
        return search(root, data);
    }
    void printInOrder(Node* node)
    {
        if (node == nullptr)
            return;
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
    void printInOrder()
    {
        printInOrder(root);
    }
};
int main()
{
    avl tree;
    int keys[] = { 10, 20, 30, 15, 5 };
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++)
    {
        tree.insert(keys[i]);
    }
    cout << "Inorder traversal of the AVL tree is: ";
    tree.printInOrder();
    cout << endl;
    int key_to_search = 20;
    if (tree.search(key_to_search))
    {
        cout << key_to_search << " found in the AVL tree." << endl;
    }
    else
    {
        cout << key_to_search << " not found in the AVL tree." << endl;
    }
    return 0;
} 


