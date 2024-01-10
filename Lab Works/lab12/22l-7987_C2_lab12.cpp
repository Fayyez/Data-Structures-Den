#include<iostream>
using namespace std;


template<typename h>
struct Hashitem {
    int key;
    h value;
    int status;// 0=empty, 1=deleted, 2=occupied.
    Hashitem(h value = 0, int key = 0, int status = 0) {
        this->value = value;
        status =0;
        this->key = key;
    } 
};

class hashmap {
    Hashitem<int>* arr;
    int capacity;
    int count;// current size
    virtual int getNextIndex(int key, int i) {// for probing (linear in this case)
        return hashfunction(key+i);
    }
public:
    hashmap() {
        capacity=0; count =0;
        arr = nullptr;
    }
    hashmap(int c) {
        capacity = c; count = 0;
        arr = new Hashitem<int> [capacity];
    }
    int hashfunction(int key) {
        return key%capacity;
    }
    void insert(Hashitem<int> i, int& iterations) {
        if(count<capacity) {//if there is an empty slot in the hash array
            int index = hashfunction(i.key);
            if(arr[index].status == 0 || arr[index].status == 1) {
                //if index is empty or deleted thne insert 
                arr[index] = i;
                arr[index].status = 2;
            }
            else {//if index was occupied, status == 2
                for(int j = 0; j < capacity; j++) {
                    iterations++;
                    int index= getNextIndex(i.key, j);
                    if(arr[index].status != 2) {
                        //if index is empty or deleted thne insert 
                        arr[index] = i;
                        arr[index].status = 2;
                        break;
                    }
                }
            }
            count++;
        }
        else {
            cout << "hash map is full\n";
        }
    }
    bool deleleteitem(Hashitem<int> i, int& iterations) {
        if(count>0) {
            int index = hashfunction(i.key);
            if(arr[index].status == 2 && arr[index].value == i.value) {//if index is occupied
                arr[index].status = 1;//marked as deleted
                cout<<"hashitem: "<<arr[index].value<<" deleted\n";
                count--;
                return true;
            }
            else {
                for(int j = 0; j < capacity; j++) {//run the loop capacity times
                    iterations++;
                    int index= getNextIndex(i.key, j);
                    if(arr[index].status == 2 && arr[index].value == i.value) {//if occupied, then marked deleted
                        arr[index].status = 1;
                        cout<<"hashitem: "<<arr[index].value<<" deleted\n";
                        count--;
                        return true;
                    }
                    if(arr[index].status == 0) {//if index is empty
                        cout<<"hashitem not present\n";
                        return false;
                    }
                }
            }
        }
        else cout<<"hashmap is empty\n";
        return false;
    }
    bool search(int i, int & iterations) {
        if(count>0) {
            int index = hashfunction(i);
            if(arr[index].status == 2 && arr[index].key == i) {
                //if index is occupied & matched
                cout<<"hashitem: "<<arr[index].key <<" found\n";
                return true;
            }
            else {
                for(int j = 0; j < capacity; j++) {//run the loop capacity times
                    iterations++;
                    int index= getNextIndex(i, j);
                    if(arr[index].status == 2 && arr[index].key == i) {//if occupied, then marked deleted
                        cout<<"hashitem: "<<arr[index].key <<" found\n";
                        return true;
                    }
                    if(arr[index].status == 0) {//if index is empty
                        cout<<"hashitem not present\n";
                        return false;
                    }
                }
            }
        }
        else cout<<"hashmap is empty\n";
        return false;
    }
    ~hashmap() { delete[]arr; }
};

int main() {
    hashmap hash(12);
    int arr[12] = { 2,4,6,8,10,12,14,16,18,48,24 };
    int iterations = 1;
    cout<<"insertion:\n";
    for(int i = 0; i < 12; i++) {//inserting hashitems here
        Hashitem<int> item(arr[i], arr[i], 0);
        hash.insert(item, iterations);
        cout<<"inserted: "<<arr[i]<<" in "<< iterations <<" iterations."<<endl;
        iterations=1;
    }
    cout<<"searching:\n";
    if(hash.search(48, iterations))
        cout<<"searched for 48 in "<< iterations <<" iterations."<<endl;
    else cout<<"48 not found";
    iterations=1;
    cout<<"deleting:\n";
    if(hash.deleleteitem(Hashitem<int>(48,48,0), iterations))
        cout<<"deleted 48 in "<< iterations <<" iterations."<<endl;
    else cout<<"48 not found";
    iterations =1;
    if(hash.deleleteitem(Hashitem<int>(4,4,0), iterations))
        cout<<"deleted 4 in "<< iterations <<" iterations."<<endl;
    else cout<<"4 not found";
    iterations = 1;

    return 0;
}