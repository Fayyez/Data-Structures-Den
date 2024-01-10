//#include<iostream>
//#include<cstring>
//using namespace std;
//
//class Msg {
//	string text;
//	bool type; //1 for input and 0 for output;
//public:
//	Msg(string data="", bool type=0) {
//		this->type = type;
//		text = data;
//	}
//	Msg(Msg const& m) {
//		text = m.text;
//		type = m.type;
//	}
//	void print() {
//		cout << "TEXT = \"" << text << "\"\n";
//		if (type)
//			cout << "DEVICE TYPE = Input\n";
//		else cout << "DEVICE TYPE = output\n";
//	}
//};
//template<class T>
//class Queue {
//	struct Node {
//		T data;
//		Node* next;
//		Node(T data) {
//			this->data = data;
//			next = nullptr;
//		}
//	};
//	Node* front;
//	Node* rear;
//	int count;
//public:
//	Queue() {
//		front = rear = nullptr;
//		count = 0;
//	}
//	int size() {
//		return count;
//	}
//	bool isEmpty() {
//		return count == 0;
//	}
//	T Front() {
//		return front->data;
//	}
//	T Rear() {
//		return rear->data;
//	}
//	void enqueue(T const& e) {//enter new element
//		Node* newNode = new Node(e);
//		if (isEmpty()) {//if q is empty
//			front = rear = newNode;
//		}
//		else {
//			rear->next = newNode;
//			rear = newNode;
//		}
//		count++;
//	}
//	T dequeue() {//delete element
//		if (!isEmpty()) {
//			Node* temp = front;
//			front = front->next;
//			T toReturn = temp->data;
//			delete temp;
//			count--;
//			return toReturn;
//		}
//		else {
//			throw "Queue is Already empty!!!";
//		}
//	}
//	~Queue() {//destructor
//		while (front != nullptr) {
//			Node* temp = front;
//			front = front->next;
//			delete temp;
//		}
//		rear = nullptr;
//	}
//};
//int main() {
//
//	Queue<Msg> q;
//	Msg m1("Message coming from keyboard", 1);
//	Msg m2("File data to printed on printer", 0);
//	q.enqueue(m1);
//	q.enqueue(m2);
//	cout << "front element :\n";
//	q.Front().print();
//	cout << "rear element :\n";
//	q.Rear().print();
//	try {
//		q.dequeue();
//	}
//	catch (string e) {
//		cout << e;
//	}
//	cout << "after deletion :\n";
//	cout << "Queue size: " << q.size() << endl;
//	return 0;
//}
