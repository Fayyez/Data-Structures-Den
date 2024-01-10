#include<iostream>
#include<queue>
using namespace std;

class bst {
    struct Node {
        char data;
        Node* left;
        Node* right;
        Node(char d) : data(d), left(nullptr), right(nullptr) {}
    };
    Node* root;

public:
    // Default constructor
    bst() { root = nullptr; }
    // Methods
    Node* insert(Node*node,char*arr, int i, int size) {
        if (i < size) {
            node = new Node(arr[i]);
            node->left = insert(node->left, arr, 2 * i + 1, size);
            node->right = insert(node->right, arr, 2 * i + 2, size);
        }
        return node;
    }
    int countNodes(Node* node) {
        if (!node) return 0;
        int countleft = countNodes(node->left);
        int countN = 1;
        int countright = countNodes(node->right);
        return countN + countleft + countright;
    }
    //////////////Task3//////////////////
    ////////DEPTH-FIRST SEARCHES :
    void inorderPrint(Node*node)//LNR
    {
        if(!node) return;//base case
        inorderPrint(node->left);
        cout<<node->data<<" ";
        inorderPrint(node->right);
    }
    void preorderPrint(Node*node)//NLR
    {
        if(!node) return;
        cout<<node->data<<" ";
        preorderPrint(node->left);
        preorderPrint(node->right);
    }
    void postorderPrint(Node*node)//NLR
    {
        if(!node) return;
        postorderPrint(node->left);
        postorderPrint(node->right);
        cout<<node->data<<" ";
    }
    // Wrappers //
    int countNodes() { return countNodes(root); }
    void insert(char * arr, int size ) { 
       root = insert(root, arr, 0, size);
    }
    void inorderPrint() { inorderPrint(root); }
    void preorderPrint() {preorderPrint(root);}
    void postorderPrint() {postorderPrint(root);}
    // Destructor //
    void destroyPostOrder(Node* node) {
        if (node->left) destroyPostOrder(node->left);
        if (node->right) destroyPostOrder(node->right);
        delete node;
    }
    ~bst() { destroyPostOrder(root); }
};

int main() {
    bst tree;
    char arr[7] = { 'A','B','C','D','E','F','G' };
    for (int i = 0; i < 7; i++) {
        tree.insert(arr,7);
    }
    cout<<"Depth-first Traversals:\n";
    cout << "In-order traversal: ";
    tree.inorderPrint();
    cout << endl;
    cout << "Pre-order traversal: ";
    tree.preorderPrint();
    cout << endl;
    cout << "Post-order traversal: ";
    tree.postorderPrint();
    cout << endl;

    return 0;
}
