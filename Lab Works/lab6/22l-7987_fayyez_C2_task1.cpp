#include <iostream>
#include <stdexcept>
#include<string>
using namespace std;
template <class T>
class Stack {
private:

    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;  int count;     

public:
    Stack() {
        topNode = nullptr;
        count = 0;
    }

    int size() {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool top(T& value) const {
        if (isEmpty()) {
            return false;
        }
        value = topNode->data;
        return true;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    void push(const T& element) {
        Node* newNode = new Node(element);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

bool isBalanced(string exp) {
    int i = 0;
    Stack<char> s;
    char valToCheck = ' ';
    for (; i < exp.size(); i++) {
        if (!s.isEmpty()) {
            s.top(valToCheck);
            if (valToCheck == '{' && exp[i]=='}' ||
                valToCheck == '(' && exp[i] == ')' ||
                valToCheck == '[' && exp[i] == ']') {
                s.pop();
            }
            else s.push(exp[i]);
        }
        else s.push(exp[i]);
    }
    if (s.isEmpty()) return true;
    return false;
}

void move(Stack<int>& og, Stack<int>& target) {
    int element = 0;
    og.top(element);
    og.pop();
    target.push(element);

}

void solveTower(int n, Stack<int>& og, Stack<int>& centre, Stack<int>& destination) {
    if (n==1) {
        move(og, destination);
        return;
    }
    else {
        solveTower(n - 1, og, destination, centre);
        move(og, destination);
        solveTower(n - 1, centre, og, destination);
    }
}

int main() {
    /////////////////Q1/////////////////
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "Stack size: " << stack.size() << endl;

    int topElement;
    if (stack.top(topElement)) {
        cout << "Top element: " << topElement << endl;
    }
    else {
        cout << "Stack is empty." << endl;
    }
    stack.pop();
    cout << "Stack size after pop: " << stack.size() << endl;

    /////////////////Q2////////////////////
    string exp1 = "{[{}{}]}[()]";
    if (isBalanced(exp1)) cout << "string " << exp1 << " is balanced\n";
    else cout << "is not balanced";
    
    ///////////////////Q3///////////////////
    Stack<int> og, centre, destination;
    for (int i = 5; i > 0; i--) {
        og.push(i);
    }
    solveTower(5, og, centre, destination);
    cout << "checking destination stack : ";
    int temp = 0;
    while (!destination.isEmpty()) {
        destination.top(temp);
        cout << temp << " ";
        destination.pop();
    }

    return 0;
}
