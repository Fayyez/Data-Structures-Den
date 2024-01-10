//#include<iostream>
//using namespace std;
//
//int** AllocateMemory(int& row, int& col) {
//	int** ptr = new int* [row];
//	for (int i = 0; i < col; i++) {
//		ptr[i] = new int[col];
//	}
//	return ptr;
//}
//void InputMatrix(int**matrix, const int&row, const int&col) {
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < col; j++)
//		{
//			cout << "enter matrix(" << i << "," << j << ") : ";
//			cin >> matrix[i][j];
//		}
//	}
//}
//void displayMatrix(int** matrix, const int& row, const int& col) {
//
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < col; j++)
//		{
//			cout << "matrix(" << i << "," << j << ") = "<<matrix[i][j]<<" ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//void displayArr(int* arr, const int& size) {
//	for (int j = 0; j < size; j++)
//	{
//		cout << arr[j] << " ";
//	}
//	cout << endl;
//}
//int* maxCol(int**matrix,const int row,const int col) {
//	int* tempPtr = new int[col];
//
//	for (int i = 0; i < col; i++) {//traverse column-wise
//		int max = matrix[0][i];
//		for (int j = 1; j < row; j++) {
//			if (matrix[j][i] > max) {//assign highest value of each column
//				max = matrix[j][i];
//			}
//		}
//		tempPtr[i] = max;
//	}
//	return tempPtr;
//}
//void DeallocateMemory(int** matrix, const int& rows) {
//	for (int i = 0; i < rows; i++) {
//		delete[]matrix[i];
//	}
//	delete[]matrix;
//	matrix = NULL;
//}
//void deallocate(int * arr) {
//	delete[]arr;
//	arr = NULL;
//}
//int main() {
//	int row = 0, col = 0, ** ptr = NULL, *arr=NULL;
//	cout << "enter rows : ";
//	cin >> row;
//	cout << "enter col : ";
//	cin >> col;
//	ptr = AllocateMemory(row, col);
//	InputMatrix(ptr, row, col);
//	cout << "matrix :\n";
//	displayMatrix(ptr, row, col);
//	arr = maxCol(ptr, row, col);
//	cout << "max Col array = ";
//	displayArr(arr, col);
//	DeallocateMemory(ptr, row);
//	deallocate(arr);
//
//	return 0;
//}