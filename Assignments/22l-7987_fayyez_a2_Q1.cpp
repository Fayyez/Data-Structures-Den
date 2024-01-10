#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
using namespace std;

/////////////////////
template<class T>
class Stack {
	struct Node {
		T data;
		Node* next;
		Node(T d) : data(d), next(nullptr) {}
	};
	Node* top;
	int count;
public:
	//default constructor//
	Stack() {
		top = nullptr;
		count = 0;
	}

	//METHODS//
	bool isEmpty() {// O(1)
		return count == 0;
	}
	bool push(const T& val) {// O(1)
		Node* newNode = new Node(val);
		if (newNode == nullptr) return false;//if new node is not allocated (in case of memory exhausted)
		if (isEmpty()) top = newNode;
		else {//if stack is not empty
			newNode->next = top;
			top = newNode;
		}
		count++;
		return true;
	}
	bool Top(T& val) {// O(1)
		if (isEmpty()) {
			//val=INT_MIN;//assign int_min as sentinel value
			cout << "stack is empty my lord!\n";
			return false;
		}
		else {
			val = top->data;
			return true;
		}
	}
	bool pop(T& val) {// O(1)
		if (!Top(val)) {//if stack is empty & update val
			cout << "stack is empty my lord!\n";
			return false;
		}
		else {//if stack is not empty
			Node* temp = top;
			top = top->next;
			temp->next = nullptr;//NO Dangling Ptrs!!
			delete temp;
			count--;
			return true;
		}
	}

	//destructor//
	~Stack() {// O(count)
		T placeholder;
		while (!isEmpty()) {
			pop(placeholder);
		}
		top = nullptr;
	}
};
/////////////////////
class XMLChecker {// encapulates all methods used to verify an xml code
	//composition
	Stack<string> tags;
	Stack<char> quotes;
	string* xmlCode;
	ifstream reader;
public:
	//Parameterized constructor//
	XMLChecker(string filename) {
		xmlCode = new string[100];
		reader.open(filename);
		int i = 0;
		string temp;
		if (reader.is_open()) {//if file is open
			while (!reader.eof()) {//read the entire xml file
				getline(reader, xmlCode[i]);
				cout << xmlCode[i] << endl;
				i++;
			}
			reader.close();
		}
		else {//if nothing was read
			cout << "file not found my lord!\n";
		}
	}

	//destructor//
	~XMLChecker() {
		delete[] xmlCode;
		xmlCode = nullptr;
	}

	//Methods//
	bool getHeader() {//return true if correct prolog syntaxt is present
		bool found = false, present = false;
		string dummy = "xyz";
		for (int i = 0; i < xmlCode->size(); i++) {//traverse all lines; i+1=line number
			for (int j = 0; j < xmlCode[i].size() && xmlCode[i].size() >= 3; j++) {//traverse column-wise
				//>=3 => header must have <?, followed by non-whitespace character
				if (!found && xmlCode[i][j] == '<' && xmlCode[i][++j] == '?') {
					//if header/prolog found
					j++;
					cout << "Prolog found at line : " << i + 1 << endl;
					if (i != 0) cout << "Error: prolog is not at the beginning of the code my lord!\n";
					//check for prolog' syntax accuracy
					if (xmlCode[i][j] != ' ' && xmlCode[i][j] != '>') {
						tags.push("?");//push prolog opening in stack
						found = true;
						present = true;
					}
					else cout << "Error: the prolog is un-named dear lord!\n";
				}
				if (found) {//if prolog is opened, check for closing tag
					if (xmlCode[i][j] == '<') {//another opening tag found
						cout << "new tag opened without closing prolog at line : " << i + 1 << endl;
					}
					else if (xmlCode[i][j] == '>' && xmlCode[i][j - 1] == '?') {//tag is properly closed
						tags.pop(dummy);
						found = false;
					}
				}
			}
		}
		if (!present) cout << "Warning: the xml code has no named prolog my lord!\n";
		if (!tags.isEmpty()) cout << "my lord, code has unbalanced prolog!\n";
		return present;
	}
	string readWordTillEnd(int& i, int& j) {
		string word = "";//initiate word will null terminator
		int tempI = i;
		bool gotTheWord = false;
		for (; i < xmlCode->size(); i++) {
			for (; j < xmlCode[i].size(); j++) {//traverse till a > is found
				if (xmlCode[i][j] == ' ') continue;
				else if (xmlCode[i][j] == '>') {//if > found
					gotTheWord = true;
					break;
				}
				else {//add to word
					word += xmlCode[i][j];
				}
			}
			if (gotTheWord) break;
		}
		if (!gotTheWord) {//if script ended without closing a tag
			cout << "line: " << tempI + 1 << "; you forgot to close the tag with \'>\' my lordship!\n";
		}
		return word;
	}
	string readWordTillWs(int& i, int& j) {
		string word = "\0";//initiate word will null terminator
		int tempI = i;
		bool gotTheWord = false;
		for (; i < xmlCode->size(); i++) {
			for (; j < xmlCode[i].size(); j++) {//traverse till a > is found
				if (xmlCode[i][j] == '>' || xmlCode[i][j] == ' ') {//if > found
					gotTheWord = true;
					break;
				}
				else {//add to word
					word += xmlCode[i][j];
				}
			}
			if (gotTheWord) break;
		}
		return word;
	}
	bool dealWithAttributes(int& i, int& j) {//return false if > is not found
		bool flag = false, closed = false;
		int tempI = i;
		char dummy;
		for (; i < xmlCode->size(); i++) {
			for (; j < xmlCode[i].size(); j++) {//traverse till a > is found
				if (xmlCode[i][j] == '>') {
					closed = true;
					break;
				}
				else if (xmlCode[i][j] == ' ') continue;
				else if (xmlCode[i][j] == '=' && flag) {//= occured twice without closing first attribute
					cout << "line: " << i + 1 << "; attributes are invalid m'lord!\n";
				}
				else if (xmlCode[i][j] == '=') {
					flag = true;
				}
				else if (xmlCode[i][j] == '\'' || xmlCode[i][j] == '\"' && flag) {//if a quote is found after = operator
					char temp = '\0';
					if (!quotes.isEmpty()) {//check top of non-empty stack
						quotes.Top(temp);
						if (temp == xmlCode[i][j]) {
							quotes.pop(temp);
							flag = false;
						}
						else quotes.push(xmlCode[i][j]);
					}
					else quotes.push(xmlCode[i][j]);
				}
			}
			if (closed)  break;
		}
		if (!quotes.isEmpty()) {
			cout << "line: " << tempI + 1 << "; invalid quotations found in the tag, my grace!\n";
			while (!quotes.isEmpty()) {//empty the quotes stack for use by next tag
				quotes.pop(dummy);
			}
		}
		return closed;//does not end with >   
	}
	bool dealWithComments(int& i, int& j) {
		bool opened = true, dash1 = false, dash2 = false, closed = false, flag = false;
		char temp = '\0';
		int tempI = i;
		j++;
		for (; i < xmlCode->size(); i++) {
			for (; j < xmlCode[i].size(); j++) {
				if (xmlCode[i][j] == '>') {
					flag = true;
					break;
				}
				else if (opened) {//push whatever comes after !
					quotes.push(xmlCode[i][j]);
					dash1 = true;//dash 1 is pushed
					opened = false;
				}
				else if (dash1) {
					quotes.push(xmlCode[i][j]);
					dash1 = false;
				}
				else if (xmlCode[i][j] == '-' && !dash2) {
					quotes.Top(temp);
					if (xmlCode[i][j] == temp) {
						quotes.pop(temp);
					}
					else quotes.push(xmlCode[i][j]);
					dash2 = true;
				}
				else if (dash2) {
					quotes.Top(temp);
					if (xmlCode[i][j] == temp) {
						quotes.pop(temp);
						if (temp == '-') closed = true;
					}
					else quotes.push(xmlCode[i][j]);
				}
			}
            if(flag) break;
		}
		if (!quotes.isEmpty()) {
			cout << "line: " << tempI + 1 << "; comment has incorrect syntax!\n";
			while (!quotes.isEmpty()) {//empty quotes for attributes
				quotes.pop(temp);
			}
		}
		return closed;
	}
	void generateReport() {//reports all the errors; unlcosed tags, mismatched tags and unbalanced quotes
		cout << "Errors:\n";
		for (int i = 0; i < xmlCode->size(); i++) {//traverse line by line; i+1=line number
			for (int j = 0; j < xmlCode[i].size(); j++) {//traverse column by column;

				if (xmlCode[i][j] == '<') {//if a tag is opened
					j++;
					if (xmlCode[i][j] == ' ' || xmlCode[i][j] == '>') {//if tag is unnamed (not allowed)
						cout << "line: " << i + 1 << "; invalid or unnamed start tag name thy lordship!\n";
						if (xmlCode[i][j] == ' ') {
							int tempI = i;
							if (!dealWithAttributes(i, j)) {//check quotations and check for >
								cout << "line: " << tempI + 1 << "; \'>\' is missing your highness!\n";
							}
						}
					}
					else if (xmlCode[i][j] == '/') {//if closing tag is opened
						j++;
						string topElement = "\0";
						tags.Top(topElement);
						int tempI = i;
						string closingTag = readWordTillEnd(i, j);
						if (closingTag != topElement) {//if closing corresponds to last opened tag
							cout << "line: " << tempI + 1 << "; " << "<" << topElement << "> and </" << closingTag << "> is a mismatch! (has no corresponding opening tag)\n";
						}
						tags.pop(topElement);
					}
					else if (xmlCode[i][j] == '!') {//if comment or prolog, then skip till '>'
						dealWithComments(i, j);//move control till comment/prolog is closed
						//will also report if comment/prolog is not properly closed
					}
					else if (xmlCode[i][j] == '?') {//dea with prolog attributes
						dealWithAttributes(i, j);
					}
					else if (xmlCode[i][j] == '!') {//in case of a comment opened
						dealWithComments(i, j);
					}
					else {
						string tagName = readWordTillWs(i, j);
						tags.push(tagName);//push the tag name into the stack
						dealWithAttributes(i, j);//for attributes 
					}
				}
			}
		}
        if(tags.isEmpty()) cout<<"tags are balanced my master!\n";
        else {
            string dummy = "\0";
            cout<<"these tags are not closed:\n";
            while(!tags.isEmpty()) {
                tags.Top(dummy);
                cout << dummy << endl;
                tags.pop(dummy);
            }
        }
	}
};
int main() {
	
	XMLChecker x1("xmlCode.txt");
	x1.getHeader();
	x1.generateReport();
	system("pause");
	return 0;
    
}