 //#include<iostream>
 //using namespace std;

 //template<class T>
 //class List {

 //	struct Node {
 //		T data;
 //		Node* next;
 //		Node(T const& value) {
 //			data = value;
 //			next = nullptr;
 //		}
 //	};
 //	Node* head;
 //public:
 //	List() {//constructor
 //		head = nullptr;
 //	}
 //	void insertAtEnd(T const value) {
 //		Node* newNode = new Node(value);
 //		if (head == nullptr) {//if list is uninitialized
 //			head = newNode;
 //		}
 //		else {//if list already has elements
 //			Node* current = head;
 //			while (current->next != nullptr) {
 //				//move to next node until the last link is reached
 //				current = current->next;
 //			}
 //			current->next = newNode;
 //		}
 //	}
 //    bool deleteAtEnd() {
 //		if (head != nullptr) {
 //			//if list is not empty
 //			if (head->next == nullptr) {//list has only one element
 //				delete head;
 //				head = nullptr;
 //			}
 //			else {//if list has multiple elements
 //				Node* previous = nullptr, *current = head;
 //				while (current->next != nullptr) {
 //					previous = current;
 //					current = current->next;
 //				}
 //				delete current;
 //				current = nullptr;
 //				previous->next = nullptr;//previous == 2nd last link
 //			}
 //			return true; // Deletion successful
 //		}
 //		return false; // List was already empty
 //	}
 //	void print() const {
 //		Node* current = head;
 //		while (current != nullptr) {
 //			cout << current->data << "->";
 //			current = current->next;
 //		}
 //		cout << "NULL";
 //		cout << endl;
 //	}
 //	int size() const {
 //		int count = 0;
 //		Node* current = head;
 //		while (current != nullptr) {
 //			count++;
 //			current = current->next;
 //		}
 //		return count;
 //	}
 //	~List() {// destructor
 //		while (head != nullptr) {
 //			Node* temp = head;
 //			head = head->next;
 //			delete temp;
 //		}
 //	}
 //};

 //int main() {
 //	List<int> list1;
 //	for(int i = 0; i < 10; i++) {
 //		list1.insertAtEnd(i + 1);
 //	}
 //	list1.print();

 //	cout << "Linked List elements (forward) : ";
 //	list1.print();
	//
 //	return 0;
 //}