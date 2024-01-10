//#include<iostream>
//#include<cstring>
//using namespace std;
//
//template<class T>
//class Queue {
//public:
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
//	void display() {
//		Node* c = front;
//		while (c != nullptr) {
//			cout << c->data << endl;
//			c = c->next;
//		}
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
//class Operator {
//	int id;
//	bool available;
//public:
//	Operator(int i = 0, bool flag = 0) {
//		id = i;
//		available = flag;
//	}
//	bool isAvailable() { return available; }
//	int getId() { return id; }
//	void Switch() { available = !available; };
//};
//class CallCenter {
//	int numberOfOperators;
//	Operator* ops;
//	Queue<int> calls;
//public:
//	CallCenter(int const n) {
//		numberOfOperators = n;
//		ops = new Operator[numberOfOperators];
//		for (int i = 0; i < numberOfOperators; i++) {
//			Operator temp(i+1, 1);
//			ops[i] = temp;
//		}
//	}
//	void addCall(int data) {
//		calls.enqueue(data);
//	}
//	void assignCall() {
//		for (int i = 0; i < numberOfOperators; i++) {
//			if (calls.isEmpty()) {
//				cout << "there are no calls to assign sir!\n";
//				return;
//			}
//			else {
//				if (ops[i].isAvailable()) {
//					cout << "caller id: "<<calls.Front()<<" assigned, id = " << ops[i].getId() << endl;
//					ops[i].Switch();
//					calls.dequeue();
//					return;
//				}
//			}
//		}
//		cout << "all operators are occupied, plz wait!!\n";
//	}
//	void process() {
//		for (int i = 0; i < numberOfOperators; i++) {
//			if (!ops[i].isAvailable()) {
//				ops[i].Switch();//end call and label operator as free
//				cout << "call ended!!\n";
//				return;
//			}
//		}
//		cout << "all operators are alrdy free!!\n";
//	}
//	void display() {
//		cout << "all remaining calls:\n";
//		calls.display();
//		cout << "operators:\n";
//		for (int i = 0; i < numberOfOperators; i++) {
//			cout << "operattor id:" << ops[i].getId() << "  status: ";
//			if (ops[i].isAvailable()) cout << "available";
//			else cout << "occupied";
//			cout << endl;
//		}
//	}
//};
//int main() {
//	CallCenter callCenter(2); // Assuming 2 operators are available
//	callCenter.addCall(101);
//	callCenter.addCall(102);
//	callCenter.addCall(103);
//	callCenter.display();
//	callCenter.assignCall();
//	callCenter.assignCall();
//	callCenter.display();
//	callCenter.process();
//	callCenter.display();
//	return 0;
//}
