#include<iostream>
#include<queue>
using namespace std;
class bst {
    struct Node {
        int data;
        Node*left;
        Node*right;
        Node(int d): data(d), left(nullptr), right(nullptr) {}
    };
    Node*root;
public:
    //default constructor//
    bst() {root=nullptr;}
    //copy constructor//
    bst(bst&obj)
    {
        if(obj.root) copyNode(root,obj.root);
        else root=nullptr;
    }
    void copyNode(Node*&node,Node* og)
    {
        if(og!=nullptr&&node==nullptr)
        {
            node=new Node(og->data);//copy that node
            copyNode(node->left,og->left);//copy left subtree
            copyNode(node->right,og->right);//copy right subtree
        }
    }
    ///////////Methods///////////
    Node* search(int key, Node*& node) {
        if(node)
        {
            if(node->data==key) return node;
            else if(node->data>key) return search(key,node->left);
            else return search(key,node->right);
        }
        else return nullptr;
    }
    void insert(int element,Node*&node)
    {
        if(!search(element,root))//if element is not alrdy present in the tree
        {
            Node*newnode=new Node(element);
            if(!node) {node=newnode;}//if node is null
            else if(node->data>element) insert(element,node->left);
            else insert(element,node->right);
        }
        else cout<<"Element is alrdy present in the tree.\n";
    }
    void inorderPrint(Node*node)
    {
        if(!node) return;//base case
        inorderPrint(node->left);
        cout<<node->data<<" ";
        inorderPrint(node->right);
    }
    void levelorderPrint () const {//top down priting
        if (root == NULL) return;//if empty
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                Node* node = q.front();
                q.pop();
                cout << node->data << " ";
                if (node->left != NULL) q.push(node->left);
                if (node->right != NULL) q.push(node->right);
            }
            cout << endl;
        }
    }
    int countNodes(Node*node) {
        if(!node) return 0;
        int countleft=countNodes(node->left);
        int countN=1;
        int countright=countNodes(node->right);
        return countN+countleft+countright;
    }
    int countLeaf(Node*node) {
        if (node == NULL) { return 0; }
        if (node->left == NULL && node->right == NULL) {
            return 1;//for no child node
        }
        return countLeaf(node->left) + countLeaf(node->right);
    }
    ///////////////////Wrappers/////////////////////
    int countLeaf() {return countLeaf(root);}
    int countNodes() {return countNodes(root);}
    Node* search(int key) {
        Node*temp=search(key,root);
        if (temp!=nullptr) cout<<"key found, Where node = "<<temp->data<<endl;
        else cout<<"key not found.\n";
        return temp;
    }
    void insert(int key) {insert(key,root);}
    void inorderPrint() {inorderPrint(root);}
    //////////Destructor///////
    void destroyPostOrder(Node*node)
    {
        if(node->left) destroyPostOrder(node->left);
        if(node->right) destroyPostOrder(node->right);
        delete node;
    }
    ~bst() {destroyPostOrder(root);}
};
int main() {
    bst tree1;
    int arr[10]={5,3,7,9,2,1,4,6,8,10};
    for(int i=0;i<10;i++)
    {
        tree1.insert(arr[i]);
    }
    cout<<"OG tree (in order) = ";
    tree1.inorderPrint(); cout<<endl;
    bst tree2(tree1);
    cout<<"copied tree1 (in order) = ";
    tree2.inorderPrint();
    cout<<"\nLevel order print:\n";
    tree2.levelorderPrint();
    cout<<endl;
    int key=5;
    cout<<"enter key to search: ";
    cin>>key;
    tree1.search(key);
    cout<<"Number of leaves in tree = "<<tree1.countLeaf()<<endl;
    cout<<"Number of nodes in tree = "<<tree1.countNodes()<<endl;

    return 0;
}