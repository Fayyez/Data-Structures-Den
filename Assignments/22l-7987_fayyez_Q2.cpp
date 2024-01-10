#include <iostream>
#include<string>
#include<fstream>
using namespace std;

template <class v>
struct HashItem
{
    int key;
    v value;
    short status;
    // 0 means empty, 1 means deleted, 2 means occupied
    HashItem(int k = 0, v val = v(), short s = 0)
    {
        key = k;
        value = val;
        status = s;
    }
};

template<class v>
class HashMap {
    HashItem<v>* hashArray;
    int maxsize;
    int count;
public:
    virtual int getNextCandidateIndex(int key, int i) {
        return (hashFunction(key + i));//linear probing for next index
    }
    int hashFunction(int key) {//hash function
        return key % maxsize;
    }
    HashMap() {//default constructor
        maxsize = 10;
        count = 0;
        hashArray = new HashItem<v>[maxsize];
    }
    HashMap(int s) {//parameterized constructor
        if (s < 1) {
            cout << "Invalid size\n";
            return;
        }
        maxsize = s;
        count = 0;
        hashArray = new HashItem<v>[maxsize];
    }
    // getters ---------------------
    int getMaxSize() {
        return maxsize;
    }
    int getCount() {
        return count;
    }
    int getLoadFactor() {
        return (count * 100) / maxsize;
    }
    // Methods ---------------------
    void printHash() {
        cout << "Hashmap:- (key : value)\n";
        for (int i = 0; i < count; i++) {
            cout << hashArray[i].key << " :" << hashArray[i].value << endl;
        }
    }
    void doubleTHeCapacity() {
        HashItem<v>* temp = hashArray;
        hashArray = new HashItem<v>[maxsize * 2];
        maxsize *= 2;
        count = 0;
        for (int i = 0; i < maxsize / 2; i++) {
            if (temp[i].status == 2) {
                insert(temp[i].key, temp[i].value);
            }
        }
        cout << maxsize * 2 << endl;
        if (temp != nullptr)
            delete[] temp;
        temp = nullptr;
    }
    void insert(int const key, v val) {
        if (getLoadFactor() >= 75) {
            cout << "Load factor is greater than 75%, so size is doubled\n";
            doubleTHeCapacity();
        }
        if (count == maxsize) {
            cout << "Hashmap is full\n";
            return;
        }
        int i = 0;
        int index = hashFunction(key);
        while (hashArray[index].status == 2) {
            if (hashArray[index].key == key) {
                cout << "Key already exists\n";
                return;
            }
            i++;
            index = getNextCandidateIndex(key, i);
        }
        hashArray[index].key = key;
        hashArray[index].value = val;
        hashArray[index].status = 2;// set status to occupied
        count++;
    }
    bool deleteKey(int const key) {
        if (count == 0) {
            cout << "Hashmap is empty\n";
            return false;
        }
        int i = 0;
        int index = hashFunction(key);
        while (hashArray[index].status != 0) {
            if (hashArray[index].key == key && hashArray[index].status == 2) {
                hashArray[index].status = 1;// set status to deleted
                count--;
                return true;
            }
            i++;
            index = getNextCandidateIndex(key, i);
        }
        cout << "Key not found\n";
        return false;
    }
    v* getVal(int key) {
        if (count == 0) {
            cout << "Hashmap is empty\n";
            return NULL;
        }
        int i = 0;
        int index = hashFunction(key);
        while (hashArray[index].status != 0) {// braek the search for first empty node
            if (hashArray[index].key == key && hashArray[index].status == 2) {
                return &hashArray[index].value;
            }
            i++;
            index = getNextCandidateIndex(key, i);
        }
        cout << "Key not found\n";
        return nullptr;

    }
    // destructor
    ~HashMap() {
        delete[] hashArray;
        cout << "Hashmap deleted\n";
    }
};

// other classes:

template <class v>
class QHashMap : public HashMap<string> {
    // overriding the get next wala virtual function
public:
    //constructor
    QHashMap(int s) : HashMap<string>(s) {}
    int getNextCandidateIndex(int key, int i) {
        return (hashFunction(key + i * i));//quadratic probing for next index
    }
};
template <class v>
class DHashMap : public HashMap<string> {
    // overriding the get next wala virtual function
public:
    //constructor
    DHashMap(int s) : HashMap<string>(s) {}
    int getNextCandidateIndex(int key, int i) {
        int first_val = hashFunction(key);
        int second_val = (7 - hashFunction(key));
        return hashFunction(first_val + i * second_val);//double hashing for next index
    }
};

// Create a global function populateHash which is passed a filename as parameter and a HashMap object
// by pointer void populateHash(string filename, HashMap<string> *hash). The
// function reads <id, name> pairs and populates the hash with those pairs. The key is id.

template<class v>
void populateHash(string filename, HashMap<v>& hash) {
    ifstream reader("students.txt");
    string id, name, temp;
    for (int i = 0; i < 18; i++) {
        reader >> id >> name >> temp;
        hash.insert(stoi(id), name);
    }
    reader.close();
}

int main()
{
    system("color 8f");
    cout << "Hello\n";
    cout << endl << endl;
    string filename = "students.txt";
    HashMap<string> normalHash(10);
    populateHash(filename, normalHash);
    cout << "key 9 in normal hash : " << *normalHash.getVal(9) << endl;
    normalHash.deleteKey(9);
    if (normalHash.getVal(9) == nullptr) {
        cout << "key 9 deleted from normal hash\n";
    }

    cout << endl << endl;
    QHashMap<string> quadraticHash(10);
    populateHash(filename, quadraticHash);
    cout << "key 98 in quadratic hash : " << *quadraticHash.getVal(98) << endl;
    quadraticHash.deleteKey(98);
    if (quadraticHash.getVal(98) == nullptr) {
        cout << "key 98 deleted from quadratic hash\n";
    }

    cout << endl << endl;
    DHashMap<string> doubleHash(10);
    populateHash(filename, doubleHash);
    cout << "key 101 in double hash : " << *doubleHash.getVal(101) << endl;
    doubleHash.deleteKey(101);
    if (doubleHash.getVal(101) == nullptr) {
        cout << "key 101 deleted from double hash\n";
    }

    cout << endl << endl;
    return 0;

}

