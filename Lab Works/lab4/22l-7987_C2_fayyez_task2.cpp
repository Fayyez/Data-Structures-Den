#include <iostream>
using namespace std;
template<class T>
class Set {
    struct Node {
        int el;
        Node* next;
        Node(T const& value) {
            el = value;
            next = nullptr;
        }
    };
    Node* head, * tail;
    int count;

public:
    bool isMember(int x) {
        Node* current = head;
        while (current != nullptr) {
            if (current->el == x) return true;
            current = current->next;
        }
        return false;
    }
    void addElementInOrder(int x) {
        if (isMember(x)) {
            cout << "Element " << x << " is already present in the list.\n";
        }
        else {
            Node* newNode = new Node(x);
            if (head == nullptr) head = tail = newNode;//if list is empty
            else {
                tail->next = newNode;
                tail = newNode;
            }
            count++;
        }
    }
    Set() {
        head = tail = nullptr;
        count = 0;
    }
    Set(const Set& obj) {//copy constructor
        Node* current = obj.head;
        while (current != nullptr) {
            addElementInOrder(current->el);
            current = current->next;
        }
    }
    bool operator ==(const Set& obj) {
        if (obj.count != count) return false;
        Node* current = obj.head;
        while (current != nullptr) {
            if (!isMember(current->el)) return false;
            current = current->next;
        }
        return true;
    }
    void eraseElement(int x) {
        Node* current = head, * previous = nullptr;
        if (count == 0 || !isMember(x)) {
            cout << "Element "<<x<<" is not present in the list!\n";
            return;
        }
        //if list is NOT empty & element is present!!!!!
        while (current != nullptr && current->el != x) {
            previous = current;
            current = current->next;
        }
        //current is at the node to be deleted
        if (current == head) {//for first element
            head = head->next;
            if (current == tail) tail = nullptr;
        }
        else {//if in middle
            previous->next = current->next;
            if (current == tail) {//if last element is being deleted
                tail = previous;
            }
        }
        count--;
        delete current;
    }
    void printSet() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->el << "->";
            current = current->next;
        }
        cout << "NULL\n";
    }
    Set operator + (const Set& obj) {
        Set<int> third(*this);
        cout << "third is = ";
        third.printSet();
        Node* current = obj.head;
        while (current != nullptr) {
            third.addElementInOrder(current->el);
            current = current->next;
        }
        return third;
    }
    int getSize() {
        return count;
    }
    bool isEmpty() {
        return count == 0;
    }
    //////// destructor ////////
    ~Set() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Set<int> s;
    s.addElementInOrder(3);
    s.addElementInOrder(4);
    s.addElementInOrder(3);
    s.addElementInOrder(1);
    s.addElementInOrder(2);
    s.eraseElement(3);
    cout << " 3 is present =" << s.isMember(3); /* answer is False */
    s.printSet(); /* answer is 4->1-2*/
    Set<int> t;
    t.addElementInOrder(9);
    t.addElementInOrder(4);
    t.addElementInOrder(2);
    t.printSet(); /* answer is 9->4-2*/
    bool flag = s == t;
    cout << " Are set t and s equivalent = " << flag; /* answer is False */
    Set<int> q = s + t;
    q.printSet(); /* answer is 4->1->2->9*/
    return 0;
}

