#include<iostream>
#include<string>
using namespace std;

template<typename T>
class Matrix {
	T** ptr;
	int rows, cols;
public:
	Matrix(int rows=0, int col=0) {//parameterized constructor
		this->rows = rows;
		this->cols = col;
		ptr = new T * [rows];
		for (int i = 0; i < rows; i++) {
			ptr[i] = new T[col];
		}
	}
	Matrix(const Matrix<T>& obj) {//copy constructor
		this->rows = obj.rows;
		this->cols = obj.cols;
		ptr = new T * [rows];//allocation
		for (int i = 0; i < rows; i++) {
			ptr[i] = new int[cols];
		}
		for (int i = 0; i < rows; i++) {//copying matrix
			for (int j = 0; j < cols; j++) {
				ptr[i][j] = obj.ptr[i][j];
			}
		}
	}
	void insertElement(T const& element, int rowNo, int colNo) {
		if (colNo >= 0 && colNo < cols && rowNo >= 0 && rowNo < rows) {
			this->ptr[rowNo][colNo] = element;
		}
		else {
			cout << "rows and columns are out of scope. SORRY!!\n";
		}
	}
	Matrix<T> operator+ (Matrix const& obj) {
		if (rows != obj.rows || cols != obj.cols) {
			throw "ROWS AND COLUMNS DONT MATCH.";
		}
		Matrix<T> tempMatrix(obj.rows, obj.cols);
		for (int i = 0; i < tempMatrix.rows; i++) {
			for (int j = 0; j < tempMatrix.cols; j++) {
				tempMatrix.insertElement(ptr[i][j] + obj.ptr[i][j], i, j);
			}
		}
		return tempMatrix;
	}
	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
			{
				cout << "matrix(" << i << "," << j << ") = " << ptr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void transpose() {
		Matrix<T> tempMatrix(cols, rows);
		for (int i = 0; i < rows; i++) {//tempMatrix is now transpose of calling obj
			for (int j = 0; j < cols; j++) {
				tempMatrix.ptr[j][i] = ptr[i][j];
			}
		}
		//deleting callin obj
		for (int i = 0; i < rows; i++) {
			delete[]ptr[i];
		}
		delete[]ptr;
		//allocating temp to calling obj
		ptr = new T * [cols];
		for (int i = 0; i < cols; i++) {
			ptr[i] = new T[rows];
		}
		rows = tempMatrix.rows;
		cols = tempMatrix.cols;
		for (int i = 0; i < rows; i++) {//copying transposed values
			for (int j = 0; j < cols; j++) {
				ptr[i][j] = tempMatrix.ptr[i][j];
			}
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[]ptr[i];
		}
		delete[]ptr;
	}
};
int main() {
	Matrix<char> m1(2, 3);
	m1.insertElement('c', 0, 0);
	m1.insertElement('a', 0, 1);
	m1.insertElement(' ', 0, 2);
	m1.insertElement('h', 1, 0);
	m1.insertElement('-', 1, 1);
	m1.insertElement('i', 1, 2);
	m1.transpose();
	Matrix<int> m2(2, 3);
	m2.insertElement(-1, 0, 0);
	m2.insertElement(-1, 0, 1);
	m2.insertElement(-1, 0, 2);
	m2.insertElement(10, 1, 0);
	m2.insertElement(5, 1, 1);
	m2.insertElement(1, 1, 2);
	m2.transpose();
	Matrix<int> m3(m2);
	try {
		Matrix<int> m4(m2 + m3);
		m4.transpose();
		m4.print();
	}
	catch (string e) {
		cout << e << endl;
	}
	system("pause");
	return 0;
}