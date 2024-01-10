//#include<iostream>
//#include<string>
//#include<fstream>
//#include<SFML/Graphics.hpp>
//#include<SFML/System.hpp>
//#include<SFML/Audio.hpp>
//
//using namespace sf;
//using namespace std;
//
//template<class t>
//class Queue {
//	//Node structure
//	struct Node {
//		bool isAlive;
//		Node* next;
//		Node(bool flag) : next(nullptr), isAlive(flag) {}
//	};
//	//data members
//	Node* front;
//	Node* rear;
//	int count;
//	int count_alive;
//public:
//	////Constructor & Destructor////
//	Queue() {
//		front = rear = nullptr;
//		count = count_alive = 0;
//	}
//	~Queue() {
//		while (!this->isEmpty()) { dequeue(); }
//		front = rear = nullptr;
//	}
//
//	////METHODS////
//	bool isEmpty() { return count == 0; }
//	Node* top() { return front;  }
//	Node* last() { return rear; }
//	int getSize() { return count; }
//	bool getIsAlive() { return top()->isAliveisalive; }
//	int getCountAlive() { return count_alive; }
//	void setCountAlive(int n) { count_alive = n; }
//	void enqueue(bool flag) {
//		Node* newnode = new Node(flag);
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
//	int skipRandomNodes() {//return S random persons skipped
//		srand(time(0));
//		int nodesToSkip = rand() % count;
//		for (int i = 0; i < nodesToSkip; i++) {
//			bool temp = top()->isAlive;
//			dequeue();
//			enqueue(temp);
//		}
//		return nodesToSkip;
//	}
//	bool isExecuted(RenderWindow& window, int N, int k);
//	void print() {//in O(N)
//		cout << "queue = ";
//		for (int i = 0; i < count; i++) {
//			cout << top()->isAlive << " ";
//			bool temp = top()->isAlive;
//			dequeue();
//			enqueue(temp);
//		}
//		cout << endl;
//	}
//};
//void display(RenderWindow& window, Queue<int> & que, int N, int k, int S) {
//	//Prints the ring of persons to be killed sequentially
//	//Sound??
//	SoundBuffer buffer;
//	buffer.loadFromFile("final_sound.wav");
//	Sound scream;
//	scream.setBuffer(buffer);
//	//loading soldier pictures
//	Texture soldier_tex, dead_soldier_tex;
//	soldier_tex.loadFromFile("soldier.png");
//	dead_soldier_tex.loadFromFile("dead_soldier.png");
//	Sprite soldier, dead_soldier;
//	soldier.setTexture(soldier_tex);
//	dead_soldier.setTexture(dead_soldier_tex);
//	//loading font
//	Font font;
//	font.loadFromFile("font.ttf");
//	//Status
//	Text text;
//	text.setFont(font);
//	text.setString("Total Soldiers = " + to_string(N) + " |  Currently Alive = " +
//		to_string(que.getCountAlive()) + "  |  K = " + to_string(k) +
//		"\nStarted killing from S = " + to_string(S));
//	text.setCharacterSize(24);
//	text.setPosition(20, 20);
//	window.draw(text);
//	//display the soldier in a circular fashion in the center of window
//	float centerX = window.getSize().x / 2;
//	float centerY = window.getSize().y / 2;
//	float radius = 20*N;
//	float angleIncrement = 2 * 3.14159265359 / N;
//	for (int i = 0; i < N; i++) {
//		bool temp = que.top()->isAlive;
//		if (temp) {
//			soldier.setPosition(centerX + radius * cos(i * angleIncrement) - soldier_tex.getSize().x / 2,
//				centerY + radius * sin(i * angleIncrement) - soldier_tex.getSize().y / 2);
//			window.draw(soldier);
//		}
//		else {
//			dead_soldier.setPosition(centerX + radius * cos(i * angleIncrement) - dead_soldier_tex.getSize().x / 2,
//				centerY + radius * sin(i * angleIncrement) - dead_soldier_tex.getSize().y / 2);
//			window.draw(dead_soldier);
//		}
//		que.dequeue();
//		que.enqueue(temp);
//	}
//	scream.play();
//	while (scream.getStatus() == Sound::Playing);
//	window.display();
//	window.clear();
//}
//bool Queue<int>::isExecuted(RenderWindow& window, int N, int k) {//executes soldiers without disturbing the sequence
//
//	Node* temp = nullptr;
//	int counter = 1;
//	bool flag = false;//represents is execution happended
//	//sounf buffer
//	SoundBuffer buffer2;
//	buffer2.loadFromFile("coffin.wav");
//	Sound coffin;
//	coffin.setBuffer(buffer2);
//
//	int S = skipRandomNodes();//skips S random person in the que 
//	bool lastLeft = false;
//
//	while (window.isOpen()) {
//		while (count_alive > 1) {
//			for (int i = 0; i < count; i++) {//iterate throughout the queue
//				if (count_alive <= 1) {//identifiesif only one survivor is left
//					lastLeft = true; 
//				}
//				flag = false;
//				temp = top();
//				if (!temp->isAlive) {//for dead person
//					dequeue();
//					enqueue(0);
//					continue;
//				}
//				else if (!flag && counter % k == 0 && !lastLeft) {//if not killed, is kth node && is alive
//					counter = 1;
//					temp->isAlive = false;//kill
//					flag = true;//is killed
//					dequeue();
//					enqueue(0);
//					count_alive--;
//				}
//				else if (flag) {//if alrdy killed & isAlive
//					dequeue(); enqueue(1);
//				}
//				else {
//					counter++;
//					dequeue();
//					enqueue(1);
//				}
//			}
//			print();
//			display(window, *this, N, k, S);
//			//sf::sleep(seconds(4));//wait for 2 seconds before iterating again
//		}
//		coffin.play();
//		while (coffin.getStatus() == Sound::Playing);
//		sf::sleep(seconds(10));
//		return true;
//	}
//}
//int main() {
//
//	RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");
//	window.setFramerateLimit(90);
//
//	int n = 10, k=4;
//	while (n <= 1) {
//		cout << "Enter N (must be >1): ";
//		cin >> n;
//	}
//	while (k<=0) {
//		cout << "PLease enter k (must be >0): ";
//		cin >> k;
//	}
//	
//	Queue<int> que;
//	for (int i = 0; i < n; i++) {
//		que.enqueue(1);
//		que.setCountAlive(que.getSize());
//	}
//	que.isExecuted(window,n,k);
//
//	return 0;
//}