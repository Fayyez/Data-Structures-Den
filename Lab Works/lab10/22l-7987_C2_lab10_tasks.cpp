#include<iostream>
using namespace std;

class avl
{
    struct Node 
    {
        int data;
        Node* left;
        Node* right;
        Node(int data, Node* left = nullptr, Node* right = nullptr)
        {
            this->data = data;
            this->left = left;
            this->right = right;
        }
    };
    Node* root;
    int h;
public:
    avl()
    {
        root = nullptr;
        h = 0;
    }
    // copy constructor
    Node* copy(Node* other)
    {
        if (other == nullptr)// if other is empty
            return nullptr;
        Node* newNode = new Node(other->data);
        newNode->left = copy(other->left);
        newNode->right = copy(other->right);
        return newNode;
    }
    avl(const avl& other)
    {
        root = copy(other.root);
    }
    int height(Node* node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    
    }
    bool isBalanced(Node* node, int & balanceFactor)
    {
        balanceFactor = height(node->left) - height(node->right);
        if(abs(balanceFactor) > 1)
            return false;
        return true;
    }
    void rotateRight(Node*& node)
    {
        if(!node || !node->left)
            return;
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }
    void rotateLeft(Node*&node)
    {
        if(!node || !node->right)
            return;
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }
    Node* insert(Node* node,int data)
    {
        // normal insertion
        if(!node){
        {
            node = new Node(data);
            return node;
        }
        }
        else 
        {
            if(data < node->data)
            {
                node->left = insert(node->left, data);
            }
            else
            {
                node->right = insert(node->right, data);
            }
            // comes back here after insertion
            // check if balanced
            int bf=0;
            if(isBalanced(node, bf))
                return node;
            else {// if not balanced
                if(bf > 1)// left heavy
                {
                    if(data < node->left->data)// left left case
                    {
                        rotateRight(node);
                    }
                    else // left right case
                    {
                        rotateLeft(node->left);
                        rotateRight(node);
                    }
                }
                else // right heavy
                {
                    if(data > node->right->data)// right right case
                    {
                        rotateLeft(node);
                    }
                    else // right left case
                    {
                        rotateRight(node->right);
                        rotateLeft(node);
                    }
                }
                return node;
            }
        }
        return node;
    }
    void insert(int data)
    { root = insert(root, data); 
       h = height(root);//re evaluteheight after each insertion
    }
    bool search(Node* node, int data)
    {
        if(!node) return false;
        if(node->data == data) return true;
        else if(node->data > data) return search(node->left, data);
        else return search(node->right, data);
    }
    bool search(int data)
    {
        return search(root, data);
    }
    void printInOrder(Node* node)
    {
        if(!node) return;
        printInOrder(node->left);
        cout<<node->data<<" ";
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
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(5);
    cout << "Inorder traversal of the AVL tree is: ";
    tree.printInOrder();
    cout << endl;
    int key_to_search = 20;
    if (tree.search(key_to_search))
    cout << key_to_search << " found in the AVL tree. "<< endl;
    else
    cout << key_to_search <<" not found in the AVL tree." << endl;

    return 0;
    }