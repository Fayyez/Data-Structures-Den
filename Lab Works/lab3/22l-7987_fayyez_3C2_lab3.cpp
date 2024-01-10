#include<iostream>
#include<cstring>
#include<set>
using namespace std;

template<class T>

class List {

	struct Node {
		T data;
		Node* next;
		Node(T const& value) {
			data = value;
			next = nullptr;
		}
	};
	Node* head;
public:
	List() {//constructor
		head = nullptr;
	}
	void insertAtStart(T value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
	}
	void insertAtEnd(T value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {//if list is uninitialized
			head = newNode;
		}
		else {//if list already has elements
			Node* current = head;
			while (current->next != nullptr) {
				//move to next node untill last link is reached
				current = current->next;
			}
			current->next = newNode;
		}
	}
	void deleteAtStart() {

		if (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		//else list is alrdy empty so nw :)
	}
	void deleteAtend() {
		if (head != nullptr) {
			//if list is not empty
			if (head->next == nullptr) {//list has only one element
				delete head;
				head = nullptr;
			}
			else {//if list has multiple elements
				Node* previous, *current = head;
				while (current->next != nullptr) {
					previous = current;
					current = current.next;
				}
				delete current;
				current = nullptr;
				previous->next = nullptr;//previous == 2nd last link
			}
		}
	}
	void printForward() const {
		Node* current = head;
		while (current->next != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << current->data << " ";
		cout << endl;
	}
	void printReverse() const {
		if (head != nullptr) {//if not empty

			Node* current = head;
			int size = 1;
			T * arr = new T[size];
			arr[0] = current->data;
			while (current->next != nullptr) {
				//traverse till last link is reached
				current = current->next;
				T* temp = new T[size + 1];
				for (int i = 0; i < size; i++) {
					temp[i] = arr[i];
				}
				temp[size] = current->data;
				size++;
				delete[]arr;
				arr = temp;
			}
			for (int i = size - 1; i >= 0; i--) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
		else cout << " empty list\n";
	}
	int size() const {
		int count = 0;
		Node* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}
	T returnMiddle() const {
		if (head == nullptr) return INT_MIN;//return sentinel value for empty list
		int mid = (this->size() / 2) +1;//always taking upper bound
		Node* current = head;
		for (int i = 1; i < mid; i++) {
			current = current->next;
		}
		return current->data;
	}
	bool isEmpty() {
		if (head == nullptr) return true;
		else return false;
	}
	int findMax() {
		if (head == nullptr) return INT_MIN;
		else {
			int max = head->data;
			Node* current = head;
			while (current != nullptr) {
				if (current->data > max) {
					max = current->data;
				}
				current = current->next;
			}
			return max;
		}
	}
	void insertAfter(T val, T key) {
		bool found = false;
		Node* current = head;
		Node* newNode = new Node(val);
		while (current != nullptr) {
			if (current->data == key) {
				found = true;
				break;
			}
			current = current->next;
		}
		if (found) {
			Node* temp = current->next;
			current->next = newNode;
			newNode->next = temp;
		}
		else insertAtEnd(val);
	}
	void insertBefore(T val, T key) {
		bool found = false;
		Node* current = head;
		Node* previous = head;
		Node* newNode = new Node(val);
		while (current != nullptr) {
			if (current->data == key) {
				found = true;
				break;
			}
			previous = current;
			current = current->next;
		}
		if (current == head && found) {
			newNode->next = head;
			head = newNode;
		}
		else if (found) {
			newNode->next = current;
			previous->next = newNode;
		}
		else insertAtEnd(val);
	}
	bool presentInSet(int val, set<int> mySet) {
	}
	void deleteDuplicates() {
		std::set<int> mySet;
		Node* current = head;
		Node* previous = nullptr;

		while (current != nullptr) {
			if (mySet.find(current->data) == mySet.end()) {
				// If the data is NOT in the set (i.e., it's a new data)
				mySet.insert(current->data);
				previous = current;
				current = current->next;
			}
			else {
				// If the data IS in the set (i.e., it's a duplicate), delete the current node
				Node* temp = current;
				current = current->next;

				if (previous != nullptr) {
					previous->next = current;
				}
				else {
					// If the duplicate is at the beginning of the list, update the root
					head = current;
				}

				delete temp;
				temp = nullptr;
			}
		}
	}

	~List() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
};
int main() {
	List<int> myList;
	myList.insertAtStart(3);
	myList.insertAtStart(8);
	myList.insertAtStart(1);
	myList.insertAtStart(12);
	myList.insertAtEnd(5);
	myList.insertAtEnd(3);
	myList.insertAtEnd(3);


	cout << "Linked List elements (forward) : ";
	myList.printForward();
	cout << "Linked List elements (reverse) : ";
	myList.printReverse();
	int max = myList.findMax();
	if (max != INT_MIN) {
		cout << "Maximum value in the linked list: " << max << endl;
	}
	else {
		cout << "Linked list is empty." << endl;
	}

	myList.insertAfter(1, 10); // Insert 10 after the first occurrence of 1
	myList.insertBefore(12, 20); // Insert 20 before the first occurrence of 12

	cout << "Linked List elements after inserting (before and after) : ";
	myList.printForward();

	myList.deleteDuplicates();
	cout << "list after deleting duplicates : ";
	myList.printForward();
	system("pause");
	return 0;
}