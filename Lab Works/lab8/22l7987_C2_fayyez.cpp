//#include<iostream>
//using namespace std;
//
//template<class T>
//class List {
//    struct Node {
//        T data;
//        Node* next;
//        Node(T d) : data(d), next(nullptr) {}
//    };
//
//    int count;
//    Node* head;
//
//    Node* reverseRecursive(Node* node) {
//        if (node == nullptr || node->next == nullptr) {
//            return node;
//        }
//
//        Node* restReversed = reverseRecursive(node->next);
//        node->next->next = node;
//        node->next = nullptr;
//
//        return restReversed;
//    }
//
//    bool isEqualRecursive(Node* n1, Node* n2) {
//        if (n1 == nullptr && n2 == nullptr) return true;
//        if (n1 == nullptr || n2 == nullptr || n1->data != n2->data) return false;
//        return isEqualRecursive(n1->next, n2->next);
//    }
//
//    Node* deepCopyRecursive(Node* node) {
//        if (node == nullptr) return nullptr;
//        Node* newNode = new Node(node->data);
//        newNode->next = deepCopyRecursive(node->next);
//        return newNode;
//    }
//
//public:
//    List() : count(0), head(nullptr) {}
//
//    ~List() {
//        while (head) {
//            Node* temp = head;
//            head = head->next;
//            delete temp;
//        }
//    }
//
//    void insertAtEnd(T val) {
//        Node* newNode = new Node(val);
//        if (head == nullptr) {
//            head = newNode;
//        }
//        else {
//            Node* current = head;
//            while (current->next != nullptr) {
//                current = current->next;
//            }
//            current->next = newNode;
//        }
//        count++;
//    }
//
//    void print() {
//        Node* c = head;
//        while (c) {
//            cout << c->data << "->";
//            c = c->next;
//        }
//        cout << "NULL" << endl;
//    }
//
//    void reverse() {
//        head = reverseRecursive(head);
//    }
//
//    bool isEqual(const List& obj) {
//        return isEqualRecursive(this->head, obj.head);
//    }
//
//    void deepCopy(const List& obj) {
//        while (count != 0) {
//            deleteAtEnd();
//        }
//        head = deepCopyRecursive(obj.head);
//    }
//
//    void deleteAtEnd() {
//        if (count == 0 || head == nullptr) {
//            cout << "List is empty!" << endl;
//            return;
//        }
//        else if (head->next == nullptr) {
//            delete head;
//            head = nullptr;
//        }
//        else {
//            Node* current = head;
//            Node* prev = nullptr;
//            while (current->next != nullptr) {
//                prev = current;
//                current = current->next;
//            }
//            delete current;
//            prev->next = nullptr;
//        }
//        count--;
//    }
//};
//
//int stringCompare(const char* string1, const char* string2) {
//    if (*string1 == '\0' && *string2 == '\0') {
//        return 0;
//    }
//    else if (*string1 == *string2) {
//        return stringCompare(string1 + 1, string2 + 1);
//    }
//    else if (*string1 > *string2) {
//        return 1;
//    }
//    else {
//        return -1;
//    }
//}
//
//int product(int a, int b) {
//    if (b == 0) return 0;
//    else if (b > 0) {
//        return product(a, b - 1) + a;
//    }
//    else {
//        return -product(a, -b);
//    }
//}
//
//int main() {
//    if (!stringCompare("ab", "abC")) cout << "Strings are the same" << endl;
//    else cout << "Strings are not the same" << endl;
//
//    if (!stringCompare("abc", "ab")) cout << "Strings are the same" << endl;
//    else cout << "Strings are not the same" << endl;
//
//    if (!stringCompare("abc", "abc")) cout << "Strings are the same" << endl;
//    else cout << "Strings are not the same" << endl;
//
//    cout << "15 X -9 = " << product(15, -9) << endl;
//
//    List<int> l1;
//    l1.insertAtEnd(10);
//    l1.insertAtEnd(9);
//    l1.insertAtEnd(7);
//    l1.insertAtEnd(5);
//
//    List<int> l2;
//    l2.deepCopy(l1);
//
//    if (l1.isEqual(l2)) cout << "Lists are equal." << endl;
//    else cout << "Lists are not equal." << endl;
//
//    l1.reverse();
//    cout << "Reversed!!" << endl;
//
//    if (l1.isEqual(l2)) cout << "Lists are equal." << endl;
//    else cout << "Lists are not equal." << endl;
//
//    return 0;
//}
