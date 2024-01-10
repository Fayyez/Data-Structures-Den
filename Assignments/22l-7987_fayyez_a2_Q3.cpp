#include <iostream>
#include <string>
using namespace std;
template <class T>
class Undostack
{ // with circular array based implementation. lessgo
    int maxSize;
    T *arr;
    int current, count;

public:
    // Constructor//
    Undostack(int s)
    {
        maxSize = s; // is always 100
        arr = new T[maxSize];
        count = 0;
        current = 0; // stays at the empty index to be filled
    }
    // Destructor
    ~Undostack()
    {
        delete[] arr;
        arr = nullptr;
    }

    // Method
    int getSize() { return count; }
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == maxSize; }
    bool isHalve() { return count < maxSize / 2; }
    auto top()
    { // returns the last pushed element
        if (isEmpty())
        {
            cout << "M'Lord! the stack is empty......\n";
            return INT_MIN;
        }
        else
        {
            return arr[current]; // return the current element
        }
    }
    bool push(T const element) // will overwrite an index, if arldy filled
    {                          // returns true if element is added successfully
        if (isEmpty())
        {
            current = 0;
            arr[current] = element;
        }
        else
        {
            current++;
            if (current >= maxSize)
            {
                current = 0; // to bring back ccurrent from last to first index
            }
            arr[current] = element; // add element to the arr[]
        }
        if (count < maxSize) // count can go upto 100 at max
            count++;
        return true; // is always pushed in the stack :)
    }
    bool pop()
    {
        if (isEmpty())
        { // for empty arr[] display error
            cout << "Stack is already empty mi'lord, so popping is out of my mortal capabilities. Mercy!\n";
            return false; // didnt pop anything
        }
        else
        {
            // for non-empty array:
            // if moving to right, pop to left
            current--;
            // re-position to last index, if reached start
            if (current < 0)
                current = maxSize - 1;
        }
        count--;
        return true; // has popped smthly
    }
};
int main()
{
    system("color f0");
    Undostack<int> stack(4);
    int toBePushed = 0;

    for (int i = 0; i < 6; i++)
    {
        cout << "enter value: ";
        cin >> toBePushed;
        stack.push(toBePushed);
        cout << "top value: " << stack.top() << endl;
        cout << "stack size: " << stack.getSize() << endl;
    }

    system("pause");
    system("CLS");

    for (int i = 0; i < 4; i++)
    {
        if(stack.pop() && stack.top()!=INT_MIN) {
            cout << "after popping, top: " << stack.top();
            cout << "\nsize: " << stack.getSize() << endl;
        }
    }

    system("pause");
    return 0;
}