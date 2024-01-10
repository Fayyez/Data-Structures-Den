#include<iostream>
#include<cstring>
#include<windows.h>
#include<vector>

using namespace std;

// ------------------ PART B:
class StudentData
{
    string firstName;
    string lastName;
    int batch;
    string department;
    float cgpa;

public:

    // constructors
    StudentData()// default constructor
    {
        firstName = lastName = department = "";
        batch = cgpa = 0;
    }
    StudentData(string fname, string lname, int b, string dep, float grade)// parameteruzed constructor
    {
        firstName = fname;
        lastName = lname;
        batch = b;
        department = dep;
        cgpa = grade;
    }

    // getters
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }   
    int getBatch() const { return batch; }
    string getDepartment() const { return department; }
    float getCGPA() const { return cgpa; }

    // setters
    void setFirstName(string fname) { firstName = fname; }
    void setLastName(string lname) { lastName = lname; }
    void setBatch(int b) { batch = b; }
    void setDepartment(string dep) { department = dep; }
    void setCGPA(float grade) { cgpa = grade; }

    // printing
    void print()
    {
        cout<<"Name: "<<firstName<<" "<<lastName<<endl;
        cout<<"Batch: "<<batch<<endl;
        cout<<"Department: "<<department<<endl;
        cout<<"CGPA: "<<cgpa<<endl;
    }

};

// ------------------ PART A:
// Tree class
template<class K,class V>
class SpecialBST {
    // Node structure
    struct Node 
    {
        K key;
        V value;
        Node* left;
        Node* right;
        // constructor
        Node(K k, V v): key(k), value(v), left(nullptr), right(nullptr) {}
    };
    Node* root;
public:
    // default constructor
    SpecialBST() { root=nullptr; }
    // Rotations (left and right) ----- in O(1)
    Node* leftRotation(Node* parent)
    {
        // rotation not possible
        if(!parent) return parent;
        if(parent->right==nullptr) return parent;
        // rotation
        Node* temp = parent->right;// new parent
        parent->right=temp->left;
        temp->left=parent;
        return temp;
    }
    Node* rightRotation(Node* parent)
    {
        // rotation not possible
        if(!parent) return parent;
        if(parent->left == nullptr) return parent;
        // rotation
        Node* temp = parent->left;
        parent->left=temp->right;
        temp->right=parent;
        return temp;
    }
    
    // Methods
    bool insert(Node*& node, K key, V val) // ---- in O(logn)
    {
        if(!node)// base case
        {
            node = new Node(key,val);
            return true;
        }
        else// when node is not empty
        {
            if(node->key > key) 
            {//insert at left and rotate to right
                bool flag = insert(node->left,key,val);
                node = rightRotation(node);
                return flag;
            }
            else if(node->key < key) 
            {
                bool flag = insert(node->right,key,val);
                node = leftRotation(node);
                return flag;
            }
            cout << "Duplicate keys are not allowed, mi'lord!\n";
            return false;// duplicate case
        }
        return false;
    }
    V* search(Node*& node, K key) // ---- in O(logn)
    {
        if(!node) { cout<<"key not found, mi'Lord\n"; return nullptr; }// key not found
        else
        {
            if(key < node->key) 
            {// if key is smaller
                V* temp = search(node->left, key);
                node = rightRotation(node);
                return temp;
            }
            else if(key > node->key) 
            {// if key is larger
                V* temp = search(node->right, key);  
                node = leftRotation(node);
                return temp;
            }
            else if(key== node->key) return &(node->value);//if key matched
        }
        return nullptr;
    }
    void getValuesInOrder(Node* node, vector<V>& v) // ---- in O(n)
    {
        if(node)
        {
            getValuesInOrder(node->left);
            v.push_back(node->value);
            getValuesInOrder(node->right);
        }
    }
    int getHeight(Node* node) // ---- in O(logn)
    {
        if(!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
    void getLevelOrderValues(Node* node,vector<V>& v, int i) // ---- in O(logn)
    {
        if(!node) return;
        if(i==1) v.push_back(node->value);
        else if(i>1) 
        {
            getLevelOrderValues(node->left, v, i-1);
            getLevelOrderValues(node->right, v, i-1);
        }
    }
    vector<V> levelOrderTraversal() 
    {
        int height = getHeight();
        vector<V> v;
        for(int i=1;i<=height;i++) getLevelOrderValues(root, v, i);
        return v;
    }
    Node* getPredecessorNode(Node* node) // get the largest value in left subtree
    {
        while(node->right) node = node->right;
        return node;
    }
    bool del(Node*& node,K key) // ---- in O(logn)
    {
        if(!node) return false;// base case
        else
        {
            if(key<node->key)// move to left subtree
            {
                bool temp = del(node->left, key);
                node = rightRotation(node);
                return temp;
            }
            else if(key > node->key)
            {
                bool temp = del(node->right, key);
                node = leftRotation(node);
                return temp;
            }
            else // key is found
            {
                Node* temp = node;// temp is the node to be deleted
                // one child or no child cases
                if(!node->left || !node->right)
                {
                    if(!node->left) node = node->right;
                    else if(!node->right) node = node->left;
                    delete temp;
                }
                else // two child case
                {
                    // get largest node key in left subtree
                    Node* placeholder = this->getPredecessorNode(node->left);
                    // copy the ubtree node in node itself
                    node->key = placeholder->key;
                    node->value = placeholder->value;
                    return del(node->left, placeholder->key);
                }
            }
        }
        return false;
    }
    void getNodesInOrder(Node* node, vector<pair<K, V>>& v) // ---- in O(n)
    {
        if(node)
        {
            getNodesInOrder(node->left, v);
            v.push_back(make_pair(node->key, node->value));
            getNodesInOrder(node->right, v);
        }
    }
    V getRoot() { return root->value;} // return the value in root // ---- in O(1)
    // Recursive Method Wrappers
    bool insert(K key, V val) { return insert(root,key,val); }
    V* search(K key) { return search(root,key); }
    vector<V> getValuesInOrder() 
    {
        vector<V> v;
        getValuesInOrder(root, v); 
        return v;
    }
    int getHeight() { return getHeight(root); }
    bool del(K key) { return del(root,key); }
    vector<pair<K, V>> getNodesInOrder()
    {
        vector<pair<K, V>> v;
        getNodesInOrder(root, v);
        return v;
    }
    // Destructor (in post-order)
    void destroy(Node* node) 
    {
        if(node)
        {// if node exists
            destroy(node->left);// first kill left child
            destroy(node->right);// then kill right child
            delete node;// then kill parent node itself
        }
    }
    ~SpecialBST() { destroy(root); }
};

// FOR TESTING
void printV(vector<int> v) 
{
    for(auto i : v) cout << i;
    cout<<endl;
}

// ------------------ PART B:
class StudentList {
    // key = (int) roll number, value = student data
    // because roll number is the only unique attribute of a student
    SpecialBST<int, StudentData> student_list;
public:
    // Methods
    bool insertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
    {
        StudentData s(firstName, lastName, batch, department, cgpa); // create a student
        bool studentInserted = student_list.insert(rollNumber, s); // insert the student in the list
        if(studentInserted) 
            cout<<"Student inserted successfully.\n";
        else cout<<"Roll number already taken! try again with a different roll number please.\n";

        return studentInserted;
    }
    bool insert()
    {
        string firstName, lastName, department;
        int cgpa, batch, rollNumber;
        // taking user input :D
        cout<<"Enter Roll No: ";
        cin>>rollNumber;
        cout<<"Enter First Name: ";
        cin>>firstName;
        cout<<"Enter Last Name: ";
        cin>>lastName;
        cout<<"Enter Batch: ";
        cin>>batch;
        cout<<"Enter Department: ";
        cin>>department;
        cout<<"Enter CGPA: ";
        cin>>cgpa;
        return insertNewStudent(rollNumber, firstName, lastName, batch, department, cgpa);
    }
    bool deleteStudent(int rollNumber) 
    { // delete the student with the corresponding roll number
        bool studentDeleted = student_list.del(rollNumber);
        if(studentDeleted) 
            cout<<"Student deleted successfully.\n";
        else cout<<"Mi'Lord, the Roll no. is not part of the list\n";

        return studentDeleted;
    }
    StudentData* search(int rollNumber) 
    { // search the student with the corresponding roll number
        return student_list.search(rollNumber);
    }
    bool updateStudent(int oldRollNo, int newRollNo, string newFirstName, string newLastName,
    int newBatch, string newDep, float newCgpa)
    {
        StudentData* temp = student_list.search(oldRollNo);
        StudentData* newRollNoNode = student_list.search(newRollNo);
        if(!temp || newRollNoNode) // if student is not present and newRollno is alrdy taken
        {
            cout<<"no student with rollno = "<<oldRollNo<<" found in the database or new roll no. already taken, mi'lord!\n";
            return false;
        }
        else // if student is present in the list
        {
            if(oldRollNo==newRollNo) // if student roll number is supposed to remain the same
            {
                temp->setFirstName(newFirstName);// update the student data
                temp->setLastName(newLastName);
                temp->setBatch(newBatch);
                temp->setDepartment(newDep);
                temp->setCGPA(newCgpa);
                cout<<"Student updated successfully.\n";
                return true;
            }
            else // if student roll number is supposed to change
            {
                string temFirstName = temp->getFirstName();
                string temLastName = temp->getLastName();
                int temBatch = temp->getBatch();
                string temDep = temp->getDepartment();
                float temCgpa = temp->getCGPA();
                deleteStudent(oldRollNo);// delete the student with old roll number
                return insertNewStudent(newRollNo, temFirstName, temLastName, temBatch, temDep, temCgpa);
            }
        }
    }
    void printAllStudent() 
    { // print the student with the corresponding roll number
        vector<pair<int, StudentData>> students = student_list.getNodesInOrder();
        cout<<"Students Information:\n\n";
        for(auto i: students)
        {
            cout<<"Roll No: "<<i.first<<endl;
            i.second.print();
            cout<<endl;
        }
    }
    StudentData getTop() { return student_list.getRoot(); }
    vector<StudentData> getStudentsLevelOrder()
    {
        vector<StudentData> v;
        v = student_list.levelOrderTraversal();
        return v;
    }
};

// ------------------ PART C:
int main() 
{
    StudentList students;
    char choice = '\0';
    while(choice!='E' && choice!='e')
    { // main driver menu for user

        system("cls");
        system("color 0A");

        cout<<
        "=================================================\n" <<
        "\t<PRESS I> to insert\n" <<
        "\t<PRESS D> to delete\n" <<
        "\t<PRESS S> to search\n" <<
        "\t<PRESS U> to update\n" <<
        "\t<PRESS P> to print\n" <<
        "\t<PRESS E> to exit\n" <<
        "=================================================\n\n";

        cout<<"Enter here: ";
        cin>> choice;

        if(choice=='I' || choice == 'i')
        {
            students.insert();
        }
        else if(choice == 'D' || choice == 'd')
        {
            int rollnoToDelete = INT_MIN;
            cout<<"Enter Roll to delete my master: ";
            cin >> rollnoToDelete;
            students.deleteStudent(rollnoToDelete);
        }
        else if(choice == 'S' || choice == 's')
        {
            int rollNotToSearch = INT_MIN;
            cout<<"Enter Roll to search my master: ";
            cin >> rollNotToSearch;
            StudentData* temp = students.search(rollNotToSearch);
            if(!temp) cout<<"Student not found, mi'lord!\n";
            else 
            {
                cout<<"Student found!!!\nDetails:\n";
                temp->print();
            }
        }
        else if(choice == 'U' || choice == 'u')
        {
            int oldRollNo = INT_MIN, newRollNo = INT_MIN;
            string newFirstName, newLastName, newDep;
            int newBatch;
            float newCgpa;
            cout<<"Enter Roll to update: ";
            cin >> oldRollNo;
            cout<<"Enter new Roll: ";
            cin >> newRollNo;
            cout<<"Enter new First Name: ";
            cin >> newFirstName;
            cout<<"Enter new Last Name: ";
            cin >> newLastName;
            cout<<"Enter new Batch: ";
            cin >> newBatch;
            cout<<"Enter new Department: ";
            cin >> newDep;
            cout<<"Enter new CGPA: ";
            cin >> newCgpa;
            students.updateStudent(oldRollNo, newRollNo, newFirstName, newLastName, newBatch, newDep, newCgpa);
        }
        else if(choice == 'P' || choice == 'p')
        {
            students.printAllStudent();
        }
        else if(choice == 'E' || choice == 'e')
        {
            cout<<"Thank you for using our system, mi'lord!\n";
            break;
        }
        else
        {
            cout<<"Invalid choice, mi'lord!\n";
        }
        cin.clear();
        cin.ignore(1000,'\n');
        system("pause");
    }
    return 0;
}   