//#include<iostream>
//using namespace std;
//
//template<class T>
//class List {
//
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
//	bool search(T const value) {
//		Node*current = head;
//		while (current != nullptr) {
//			if (current->data == value) {
//				return true;
//			}
//			current = current->next;
//		}
//		return false;
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
//	void Delete(List<T> & deletedList, T const value) {
//		Node* current = head;
//		Node* previous = nullptr;
//		if (head == nullptr) return;
//		while (current != nullptr) {
//			if (current->data == value) {//current is the node to delete
//				break;
//			}
//			previous = current;
//			current = current->next;
//		}
//		if (current == head) {
//			head = current->next;
//		}
//		else {
//			previous->next = current->next;
//		}
//		deletedList.insertAtEnd(current->data);
//		delete current;
//		// List was already empty
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
//	~List() {// destructor
//		while (head != nullptr) {
//			Node* temp = head;
//			head = head->next;
//			delete temp;
//		}
//	}
//};
//
//int main() {
//	system("color 8f");
//	srand((unsigned)time(NULL));
//	List<int> list1, deleted;
//	for (int i = 0; i < 10; i++) {
//		int randomNo = rand()%10+1;
//		if (list1.search(randomNo)) {//if number is found
//			i--;
//		}
//		else {
//			list1.insertAtEnd(randomNo);
//		}
//	}
//	cout << "Original list = ";
//	list1.print();
//	for (int i = 0; i < 4; i++) {
//		int randomNo = rand() % 10 + 1;
//		if (list1.search(randomNo)) {
//			list1.Delete(deleted, randomNo);
//		}
//		else i--;
//	}
//
//	cout << "After deleting 4 random nodes = ";
//	list1.print();
//
//	cout << "Deleted Nodes are = ";
//	deleted.print();
//
//	return 0;
//}