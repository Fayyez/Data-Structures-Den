//#include<iostream>
//#include<string>
////#include<typeinfo>
//using namespace std;
//
//int getNthdigit(int n, int num) {
//	for (int i = 0; i < n; i++) num /= 10;
//	return num % 10;
//}
////char getNthChar(int n, string word) {
////	if (word.length() - 1 - n >= 0) {
////		return word[word.length() - 1 - n];
////	}
////	else return '\0';
////}
//template<class t>
//class Queue {
//	//Node structure
//	struct Node {
//		t data;
//		Node* next;
//		Node(t d): data(d), next(nullptr) {}
//	};
//	//data members
//	Node* front;
//	Node* rear;
//	int count;
//public:
//	////Constructor & Destructor////
//	Queue() {
//		front = rear = nullptr;
//		count = 0;
//	}
//	~Queue() {
//		while (!this->isEmpty()) { dequeue(); }
//		front = rear = nullptr;
//	}
//
//	////basic Queue operations////
//	bool isEmpty() { return count == 0; }
//	bool top(t& dummy) {
//		if (isEmpty()) return false;
//		else dummy = front->data;
//		return true;
//	}
//	bool last(t& dummy) {
//		if (isEmpty()) return false;
//		else dummy = rear->data;
//		return true;
//	}
//	int getSize() { return count; }
//	void enqueue(t element) {
//		Node* newnode = new Node(element);
//		if (isEmpty()) rear = front = newnode;//if queue is empty
//		else rear = rear->next = newnode;//if queue is non-empty -> add at rear
//		count++;
//	}
//	bool dequeue() {//return false if no node was deleted
//		if (isEmpty()) return false;//if queue is empty
//		else {//if ueue is non-empty
//			Node* temp = front;
//			front = front->next;
//			delete temp;
//		}
//		count--;
//		return true;//a node was deleted
//	}
//	void reverse() {//reverses a queue using recursion in O(n)
//		if (isEmpty()) return;
//		t frontElement;
//		top(frontElement);
//		dequeue();
//		reverse();//recursive call
//		enqueue(frontElement);
//		
//	}
//
//	////Specialized Mrthods For Sorting////
//	int getLargest() {//works for <int> queues only & return the largest element of queue
//		int largestData = INT_MIN, topNodeData = INT_MIN;
//		for (int i = 0; i < count; i++) {
//			if (top(topNodeData) && topNodeData>largestData) {
//				largestData = topNodeData;
//			}
//			dequeue();//re-enter the element in the queue
//			enqueue(topNodeData);
//		}
//		return largestData;
//	}
//	int getLengthOfLargestString() {
//		string largestString = "";
//		string topElement = "placeholder";
//		top(topElement);//get the top element
//		for (int i = 0; i < count; i++) {
//			if (top(topElement) && topElement.length() > largestString.length()) {
//				largestString = topElement;
//			}
//			//re-enter the element in the queue
//			dequeue(); enqueue(topElement);
//		}
//		return (int)largestString.length();
//	}
//	int getNumberOfDigits() {
//		//assuming all enteries in the queue contain the same number of digits
//		int temp = getLargest(), noOfdigits = 1;
//		if(temp<0) temp = abs(temp);//convert to a positve number
//		while (temp/10) {
//			temp /= 10;
//			noOfdigits++;
//		}
//		return noOfdigits;
//	}
//	string getType() { return typeid(t).name(); }//returns the type of the template in run-time
//	void insertBack(Queue<t>*& arrOfQueuesToInsert, int size) {
//		for (int i = 0; i < size; i++) {//inser in-order all element of queue array
//			t ElementToInsert;
//			while (!arrOfQueuesToInsert[i].isEmpty()) {
//				arrOfQueuesToInsert[i].top(ElementToInsert);
//				arrOfQueuesToInsert[i].dequeue();
//				this->enqueue(ElementToInsert);
//			}
//		}
//	}
//	void sortNumbers() { 
//
//		int numberOfDigits = getNumberOfDigits();//holds the number of digits in each key
//
//		for (int i = 0; i < numberOfDigits; i++) {//iterate the sorting algo times the number of digits
//
//			int topElement = 0;
//			Queue<int>* positiveNumbers = new Queue[10];//will store all the positive numbers
//			Queue<int>* negativeNumbers = new Queue[10];//will store all the negative numbers
//
//			while (!isEmpty()) {//sort into +ve & -ve queues based digitwise
//				top(topElement);//get the top element
//				if (topElement >= 0) {//if top element is a whole number
//					int indexToStore = getNthdigit(i, topElement);//get the it digit of top element
//					positiveNumbers[indexToStore].enqueue(topElement);
//				}
//				else {//if top element is a negative number 
//					int indexToStore = getNthdigit(i, topElement) + 9;
//					negativeNumbers[indexToStore].enqueue(topElement);
//				}
//				this->dequeue();//remove that element
//			}
//			this->insertBack(negativeNumbers, 10);
//			this->insertBack(positiveNumbers, 10);
//			//NO MEMORY LEAKS!!
//			delete[] positiveNumbers;
//			delete[] negativeNumbers;
//			positiveNumbers = negativeNumbers = nullptr;
//		}
//	}
//	void sortChar() {
//		Queue<char>* alphabetsArr = new Queue[26];//index zero for '\0'
//		t topElement;
//		while (!this->isEmpty()) {//iterate through the queue
//			top(topElement);//get front element
//			int indexToInsert = toupper(topElement[topElement.length() - 1]) - 65;
//			alphabetsArr[indexToInsert].enqueue(topElement);//sort alphabet-wise
//			this->dequeue();
//		}
//		insertBack(alphabetsArr, 26);//insert back yooo!!!
//		delete[] alphabetsArr;
//	}
//	void sortString() {
//		//no. of iteration = number of chars in string
//		int numberOfIteraations = this->getLengthOfLargestString();
//		for (int i = 0; i < numberOfIteraations; i++) {
//			Queue<string>* alphabetsArr = new Queue[26];//index zero for '\0'
//			string topElement;
//			while (!this->isEmpty()) {
//				top(topElement);
//				int indexToInsert = toupper(topElement[topElement.length() - 1 - i]) - 65;
//				alphabetsArr[indexToInsert].enqueue(topElement);
//				this->dequeue();
//			}
//		    insertBack(alphabetsArr, 26);//insert back babyy!!!
//			delete[] alphabetsArr;
//		}
//	}
//
//	////main sorting wrapper////
//	////WORKS FOR int, string & char////
//	void sort(int) { sortNumbers(); }
//	void sort(char) { sortChar(); }
//	void sort(string) { sortString(); }
//	void sortAscending() {
//		//wrapper that calls the relevant sorting method based on type of template in runtime
//		sort(t());
//	}
//	void sortDescending() {
//		this->sortAscending();
//		this->reverse();
//	}
//};
//
//int main() {
//
//	system("color 8f");
//	//Queue<string> que;
//	Queue<string> stringque;
//	Queue<int> intque;
//	Queue<char> charque;
//	//values to insert
//	string st_arr[10] = { "for","FoR","Uyo","UIN","heN","Hen","Cen","Abc","BaC","aAZ"};
//	int int_arr[10] = { 465,-285,1757,-284656, 9274,0,-1,756,166,866 };
//	char char_arr[10] = { 'Z','z','A','y','R','i','O','r','w','b' };
//
//	cout << "INT Queue = ";
//	for (int i = 0; i < 10; i++) {//insert into respective queues
//		stringque.enqueue(st_arr[i]);
//		charque.enqueue(char_arr[i]);
//		intque.enqueue(int_arr[i]);
//		cout << int_arr[i] << " ";
//	}
//	cout << endl;
//	cout << "String Queue = ";
//	for (int i = 0; i < 10; i++, cout << st_arr[i] << " ");
//	cout << endl;
//	stringque.sortAscending();
//	intque.sortDescending();
//	string temp = "\0";
//	int tempInt = 0;
//	cout << "\n*********After sorting in ascending order********\n\nINT Queue (descending):\n";
//	while (!intque.isEmpty()) {
//		intque.top(tempInt);
//		cout << "top = " << tempInt << endl;
//		intque.dequeue();
//	}
//	cout << "\nString Queue (ascending):\n";
//	while (!stringque.isEmpty()) {
//		stringque.top(temp);
//		cout << "top = " << temp << endl;
//		stringque.dequeue();
//	}
//	cout << endl;
//	system("pause");
//	return 0;
//}