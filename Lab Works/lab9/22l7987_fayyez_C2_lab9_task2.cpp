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
    //////////////////TASK2//////////////////
    void breadth_firstOrderPrint() const {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                Node* node = q.front();
                q.pop();
                cout << node->data << " ";
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            cout << endl;
        }
    }
    int countNodes(Node* node) {
        if (!node) return 0;
        int countleft = countNodes(node->left);
        int countN = 1;
        int countright = countNodes(node->right);
        return countN + countleft + countright;
    }
    bool isFull(Node*node)
    {
        if(!node) return true;//base case
        if(!node->left&&!node->right) return true;//childless node
        else if(node->left!=nullptr&&node->right!=nullptr)
        {//if both children exist then both subtrees must be full at the same time
            return isFull(node->left)&&isFull(node->right);//recursively checking fullnes of the subtrees;
        }
        else return false;//only one child exists!!
    }
    // Wrappers //
    int countNodes() { return countNodes(root); }
    void insert(char * arr, int size ) { 
       root = insert(root, arr, 0, size);
    }
    bool isFull() { return isFull(root);}
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
    tree.insert(arr,7);
    cout << "Breadth-first order traversal:\n";
    tree.breadth_firstOrderPrint();
    if(tree.isFull()) cout<<"the given tree is full, mi'lord\n";
    else cout<<"the given tree is not full, mi'lord\n";
    cout << "\nNumber of nodes in the tree: " << tree.countNodes() << endl;

    return 0;
}
