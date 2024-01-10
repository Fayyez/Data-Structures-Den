#include<iostream>
using namespace std;
template<class T>
class Stack {//with circular array based implementation
	int maxSize;
	T* arr;
	bool direction;//tell which direction to pop/push towards
	// 1 = push to right, pop to left
	// 0 = pop to right, push to left
	int start, current, count;
public:
	//Constructor//
	Stack() {
		maxSize = 1;
		arr = new T[maxSize];
		start = current = -1;
		direction = 1;
		count = 0;
	}
	//Destructor
	~Stack() {
		delete[]arr;
		arr = nullptr;
	}
	//Methods
	bool isEmpty() { return count == 0; }
	bool isFull() { return count == maxSize; }
	bool isHalve() { return count < maxSize / 2; }
	auto top() {//returns the last pushed element
		if (isEmpty()) {
			cout << "M'Lord! the stack is empty......\n";
			return INT_MIN;
		}
		else return arr[current];//return the current element
	}
	void flip() {//reverses the entire stack in O(1)
		direction = !direction;
		swap(current, start);//and ho gaya flip lmao!
	}
	void resize(int oldMax) {//resizes the arr[] to the new maxSize
		int* temp = new int[maxSize];
		int i = start, tempCount = count;
		for (int j = 0; j < count; j++) {
			temp[j] = arr[i];
			if (direction) {
				i++;
				if (i >= oldMax) i = 0;
			}
			else {
				i--;
				if (i < 0) i = oldMax - 1;
			}
		}
		delete[]arr;
		this->arr = temp;
		this->count = tempCount;
		this->start = 0;
		this->current = count - 1;
		this->direction = 1;
		//for newly initialized arr[], directionis always to right
	}
	void doubleTheSize() {
		maxSize = maxSize * 2;
		resize(maxSize / 2);
	}
	void halvenTheSize() {
		maxSize /= 2;
		resize(maxSize * 2);
	}
	bool push(T const element) {//returns true is element is added successfully
		if (isFull()) doubleTheSize();//if arr[] is filled -> double the size()
		if (isEmpty()) {//for empty stack:
			direction = true;//start filling to right from the start
			start = current = 0;
		}
		else if (direction) {//to be pushed to the right
			current++;
			if (current >= maxSize) {//if arr[] not filled but at last index
				current = 0;//to bring back ccurrent from last to first index
			}
		}
		else {//arr[] is non-empty && is in negative direction
			current--;
			if (current < 0) {//if arr[] not filled but at -1
				current = maxSize - 1;
			}
		}
		arr[current] = element;//add element to the arr[]
		count++;
		return true;
		//an element is always pushed as array resizes itself accordingly
	}
	bool pop() {
		if (isEmpty()) {//for empty arr[] display error
			cout << "Array is already empty mi'lord, so popping is out of my mortal capabilities. Mercy!\n";
			return false;
		}
		//for non-empty array:
		else if (direction) {//if moving to right, pop to left
			current--;
			//re-position to last index, if reached 
			if (current < 0) current = maxSize - 1;
		}
		else {//if moving to the left, pop to right
			current++;
			//reposition if
			if (current >= maxSize) current = 0;
		}
		count--;
		//if arr[]] is less than halve, after popping -> halven the size of the array
		//if(isHalve()) halvenTheSize();
		return true;
	}
	void display() {
		cout << "direction = " << direction << endl;
		cout << "count = " << count << endl;
		cout << "maxSize = " << maxSize << endl;
		cout << "stack = ";
		int i = start;
		for (int j = 0; j < count; j++) {
			cout << arr[i] << " ";
			if (direction) {
				i++;
				if (i >= maxSize) i = 0;
			}
			else {
				i--;
				if (i < 0) i = maxSize - 1;
			}
		}
		cout << endl;
	}
};

int main() {
	Stack<int> stack;
	system("color 8f");
	while (1) {
		system("CLS");
		int option = -1;
		cout << "Make your choice:\n" <<
			"enter (0) to push()\n" <<
			"enter (1) to pop()\n" <<
			"enter (2) to display()\n"
			"enter (3) to flip\n\n" <<
			"here: ";
		cin >> option;
		if (option == 0) {
			int element = 0;
			cout << "enter element to enter: ";
			cin >> element;
			stack.push(element);
		}
		else if (option == 1) {
			if (stack.pop()) cout << "popped successfully!\n";
			if (stack.isHalve()) stack.halvenTheSize();
		}
		else if (option == 3) {
			stack.flip();
			cout << "stack flipped successfully!\n";
		}
		else if (option == 2) {
		}
		else cout << "my lord chose an incorrect option!!!\n";
		stack.display();
		system("pause");
		option = -1;
	}
	return 0;
}