#include<iostream>
#include<Windows.h>
using namespace std;
template<typename T>
class SortedSet {
	struct Node {
		T data;
		Node* next;
		Node(T value = 0) :data(value), next(nullptr) {}
	};
	Node* head;
	Node* tail;
public:
	//////////// Q no.1: ////////////
	SortedSet() {// default constructor (1), O(1)
		head = tail = nullptr;
	}
	void insert(T const data) {//insertion (2), O(n)
		Node* newNode = new Node(data);
		if (newNode == nullptr) {
			cout << "node not created!\n";
			return;
		}
		if (head == nullptr) head = tail = newNode;//if the list is empty
		else {//for non-empty lists
			Node* current = head;
			Node* previous = head;
			while (current != nullptr && current->data < data) {
				previous = current;
				current = current->next;
			}
			if (current != nullptr && current->data == data) {
				cout << data << " is value is already present in the list. There can be no duplicates my master!\n";
				delete newNode;
				newNode = nullptr;
				return;
			}
			newNode->next = current;
			previous->next = newNode;
			if (current == nullptr) tail = newNode;//if newNode is added at the end, tail is updated
		}
	}
	void Delete(int const index) {//deletion (3), O(n)
		Node* current = head;
		if (current == nullptr) {//for empty list
			cout << "I regret to inform you that the list is already empty my master!!\n";
			return;
		}
		Node* previous=nullptr;
		int i = 0;
		while( i < index && current!=nullptr) {//traverse till index is found or link has ended
			previous = current;
			current = current->next;
			i++;
		}
		if (i < index || current == nullptr) {
			cout << "The index [" << index << "] is out of bounds my Lord!!\n";
			return;
		}
		if (current == head) {//when deleting first node
			head = current->next;
			if (current == tail) tail = nullptr;//if there is only one element
		}
		else {
			previous->next = current->next;
			if (current == tail) tail = previous;//when deleting last element
		}
		delete current;
	}
	void print() {//printing (4), O(n)
		Node* current = head;
		while (current != nullptr) {
			cout << current->data << "->";
			current = current->next;
		}
		cout << "NULL\n";
	}
	void takeUnion(SortedSet<T> const& objList) {// union by deep-copying unique objList members in calling list (5), O(n)
		Node* current = head, * objCurrent = objList.head, * previous = head;
		while (current != nullptr && objCurrent != nullptr) {//if data to add is greater, move on to next node
			if (objCurrent->data > current->data) {
				previous = current;
				current = current->next;
			}
			else {
				if (objCurrent->data != current->data) {//data is to be added to the calling list
					Node* toAdd = new Node(objCurrent->data);//make a deep copy
					if (current == head) {//if node is to be added as firt node
						toAdd->next = current;
						head = toAdd;
						previous = head;
						current = previous->next;
					}
					else {//when node is to be added in the middle/end
						toAdd->next = current;
						previous->next = toAdd;
						previous = toAdd;
						if (current == nullptr) tail = toAdd;//if new node is added at the end then update tail
					}
				}
				//when objcurrent->data == current->data will automatically be skipped
				objCurrent = objCurrent->next;
			}
		}
		//for remaining nodes:
		while (objCurrent != nullptr) {//if obj list still has remaining nodes
			Node* newNode = new Node(objCurrent->data);
			previous->next = newNode;
			tail = previous = newNode;
			objCurrent = objCurrent->next;
		}
	}
	//////////// Q no.2: ////////////
	void rotateAntiClockwise() {// rotates list clockwise, O(n)
		auto k = 0;
		while (cout << "Enter times of rotating : " && !(cin >> k)) { cin.clear(); cin.ignore(); }
		Node* current = head;
		//bool valid = false;
		int i = 1;
		while ( i < abs(k) && current != nullptr) {
			current = current->next;//current is the new tail
			i++;
		}
		if (current != nullptr && i == abs(k)) {
			tail->next = head;
			head = current->next;
			tail = current;
			current->next = nullptr;
		}
		else {
			cout << "number isout of scope, MY graceful LORD ;-;\n";
			rotateAntiClockwise();
		}

	}
	//////////// Q no.3: ////////////
	void reverseSet() {
		Node* current = head, * temp = nullptr, * previous = nullptr;
		while (current != nullptr) {
			temp = current->next;
			current->next = previous;
			previous = current;
			current = temp;
		}
		temp = head;
		head = tail;
		tail = head;
	}
	////////// destructor //////////
	~SortedSet() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
};
int main() {

	system("color 8f");
	SortedSet<int> set1, set2;
	//////////////
	set1.insert(-1);
	set1.insert(1);
	set1.insert(1);
	set1.insert(4);
	////////////// Qno.1:
	set2.insert(0);
	set2.insert(1);
	set2.insert(3);
	cout << "set1 = ";
	set1.print();
	cout << "set2 = ";
	set2.print();
	set1.takeUnion(set2);
	cout << "set1 + set2 = ";
	set1.print();
	set1.insert(5);
	set1.Delete(6);
	set1.Delete(0);
	cout << "after deleting 1st index; set1 = ";
	set1.print();
	/////////////// Qno.2:
	set1.rotateAntiClockwise();
	cout << "after rotation; set1 = ";
	set1.print();
	/////////////// Qno.3:
	set2.reverseSet();
	cout << "reversed set2 = ";
	set2.print();

	return 0;
}