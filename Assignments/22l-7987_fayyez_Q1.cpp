#include<iostream>
using namespace std;

class IntervalHeap {
    int count;
    int maxcount;
    int ** heap;
    int currentIndex;
    int leftHeapSize, rightHeapSize;
    //index 0 is a min heap and index 1 is a maxheap
public:
    // constructor & destructor
    IntervalHeap(int s=15) {
        currentIndex = leftHeapSize = rightHeapSize = count = 0;
        maxcount = s;
        heap = new int*[2];
        heap[0] = new int[maxcount];
        heap[1] = new int[maxcount];
    }
    ~IntervalHeap() {
        delete [] heap[0];
        delete [] heap[1];
        delete [] heap;
    }
    // ---------  methods !!! ----------
    void MaxheapifyDown(int index) {
        int maxChild = 2*index + 1;//assume mas=xChild is the left child
        if (maxChild < count -1) {//if within scope of heap[]
            int otherChild = maxChild + 1;
            // get the largest child
            if (otherChild < count -1  && heap[1][otherChild] > heap[1][maxChild]) {
                maxChild = otherChild;
            }
            // if the child is bigger than the parent
            if (heap[1][maxChild] > heap[1][index]) {
                swap(heap[1][index], heap[1][maxChild]);
                MaxheapifyDown(maxChild);
            }
        }
    }
    void MinheapifyDown(int index) {
        int minChild = 2*index + 1;//assume mas=xChild is the left child
        if (minChild < count -1) {//if within scope of heap[]
            int otherChild = minChild + 1;
            // get the smallest child
            if (otherChild < count -1  && heap[0][otherChild] < heap[0][minChild]) {
                minChild = otherChild;
            }
            // if the child is smaller than the parent
            if (heap[0][minChild] < heap[0][index]) {
                swap(heap[0][index], heap[0][minChild]);
                MinheapifyDown(minChild);
            }
        }
    }
    void MaxheapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (parent >= 0 && heap[1][index] > heap[1][parent]) {
            swap(heap[1][index], heap[1][parent]);
            MaxheapifyUp(parent);
        }
    }
    void MinheapifyUP(int index) {
        int parent = (index - 1) / 2;
        if (parent >= 0 && heap[0][index] < heap[0][parent]) {
            swap(heap[0][index], heap[0][parent]);
            MinheapifyUP(parent);
        }
    }
    void insert(int value) {

        // if to be inserted into the left heap and val is greater tha max val in right heap
        if(currentIndex==0 && value > heap[1][0] && count > 0) {
            cout<<"value to be insert is greater than max value! so not allowed.\n ************insert the lower bound of interval first*************";
            return;
        }
        if(currentIndex==1 && value < heap[0][0] && count > 0) {
            cout<<"value to be insert is smaller than min value! so not allowed.\n ************insert the upper bound of interval now*************";
            return;
        }
        if (count < maxcount) {
            heap[currentIndex][count] = value;
            if(currentIndex==0) {
                MinheapifyUP(count);
                leftHeapSize++;
            } else {
                MaxheapifyUp(count);
                rightHeapSize++;
            }
            if(currentIndex) count++;
            currentIndex = (currentIndex + 1) % 2;
        }
    }
    bool deleteNode() {//deletes the top node of the heap
        if(count<=0) return false;
        // deletetop values from both heaps
        heap[0][0] = heap[0][leftHeapSize-1];
        heap[1][0] = heap[1][rightHeapSize-1];
        count--;
        leftHeapSize--;
        rightHeapSize--;
        // heapify up for left and right heaps
        MinheapifyUP(leftHeapSize);
        MaxheapifyUp(rightHeapSize);
        return true;
    }
    bool updateInterval(int newMinValue, int newMaxVAlue) {
        //swap values and the heapify withut chanigng the size of the heaps
        if(count>=maxcount) return false;
        heap[0][0] = newMinValue;
        heap[1][0] = newMaxVAlue;
        MinheapifyDown(0);
        MaxheapifyDown(0);
        return true;
    }
    void InOrderPrinting(int index) {
        if(index>=count) return;
        InOrderPrinting(2*index+1);
        cout << heap[0][index] << " - " << heap[1][index] << " : "
        << heap[1][index] - heap[0][index] << "\n";
        InOrderPrinting(2*index+2);
    }
    void print() {
        //print the heap iteratively
        for(int i=0;i<count;i++) {
            cout << heap[0][i] << " - " << heap[1][i] << " : "
            << heap[1][i] - heap[0][i] << "\n";
        }
    }
};

int main() {
    IntervalHeap heap; // created a heap with default size of 15
    system("color 0A");
    // create menu for thhe 4 operations on the heaps; insert, delete, update, exit
    int choice = 0;
    while(choice!=5) {
        cout<<"MENU OPTIONS:\n";
        cout << "1> Insert\n2> Delete\n3> Update\n4> Print\n5> Exit\n";
        cin >> choice;
        switch(choice) {
            case 1: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                break;
            }
            case 2: {
                if(heap.deleteNode()) cout << "Deleted successfully\n";
                else cout << "Heap is empty\n";
                break;
            }
            case 3: {
                int newMinValue, newMaxValue;
                cout << "Enter new min value: ";
                cin >> newMinValue;
                cout << "Enter new max value: ";
                cin >> newMaxValue;
                if(heap.updateInterval(newMinValue, newMaxValue)) cout << "Updated successfully\n";
                else cout << "Heap is full\n";
                break;
            }
            case 4: {
                cout << "Interval HEAP:\n";
                heap.print();
                break;
            }
            case 5: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice\n";
                break;
            }
        }
        system("pause");
        system("cls");
    }
}