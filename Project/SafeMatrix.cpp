// SafeMatrix.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
using namespace std;


template <class T>
class SA {
private:
	int low, high;
	T* p;
public:


//Default contructor
	SA() { low = 0; high = -1; p = NULL; }

//2 param constructor
	SA(int l, int h) {
		if ((h - l + 1) <= 0)
		{
			cout << "constructor error in bounds definition" << endl;
			exit(1);
		}
		low = l;
		high = h;
		p = new T[h - l + 1];
	}



//1 param constructor
	SA(int i) {
		low = 0; high = i - 1;
		p = new T[i];
	}


	SA(const SA & s) {
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i<size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
	}

	//Destructor
	~SA() {
		//cout << "sa destructor" << endl;
		delete[] p;
	}


	T& operator[](int i) {
		if (i<low || i>high)
		{
			cout << "index " << i << " out of range" << endl;
			exit(1);
		}
		return p[i - low];
	}




	SA & operator=(const SA & s) {
		if (this == &s)return *this;
		delete[] p;
		int size = s.high - s.low + 1;
		p = new int[size];
		for (int i = 0; i<size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
		return *this;
	}

	// overloads << so we can directly print SAs

	friend ostream& operator<<(ostream& os, SA s) {
		int size = s.high - s.low + 1;
		for (int i = 0; i<size; i++)
			cout << s.p[i] << endl;
		return os;
	};
};


template <class T>
class Matrix {
	private:
		int colLow;
		int colHigh;
		int rowLow;
		int rowHigh;
		SA<SA<T>*>*matrix;

	public:
		//default constructor
		Matrix() 
		{
			matrix = NULL;
			colLow = 0; colHigh = -1;
			rowLow = 0; rowHigh = 1;
		}
		//2 param constructor by number
		Matrix(int row,int col) 
		{
			if (col <= 0 || row <= 0) {
				cout << "Invelid Argument" << endl;
				exit(1);
			}
			colLow = 0; colHigh = col - 1;
			rowLow = 0; rowHigh = row - 1;
			matrix = new SA< SA<T>*>(row);
			for (int i = 0; i < row; i++) {
				(*matrix)[i] = new SA<T>(col);
			}
		}

		int getRow() {
		
			return  rowHigh - rowLow + 1;
		}

		int getCol() {
		
			return colHigh - colLow + 1;
		}
		
		//4 param constructor
		Matrix(int lowrow, int highrow,int lowcol,int highcol) {

			if (((highcol - lowcol + 1) <= 0)|| ((highrow - lowrow + 1) <= 0))
			{
				cout << "constructor error in bounds definition" << endl;
				exit(1);
			}
			colLow = lowcol; colHigh = highcol;
			rowLow = lowrow; rowHigh = highrow;
			int row = rowHigh - rowLow + 1;
			int col = colHigh - colLow + 1;
			matrix = new SA< SA<T>*>(row);
			for (int i = 0; i < row; i++) {
				(*matrix)[i] = new SA<T>(col);
			}
		}




		SA<T>& operator[](int row){

			int correctrow = rowHigh - rowLow + 1;
			if (row < 0 || row >= correctrow) {
				cout << "Row index outboubd" << endl;
				exit(1);
			}

			return *((*matrix)[row]); //return the reference (Address of that particular SA)
		}

		Matrix<T>* operator*(Matrix &s) {

			if (this->getCol() != s.getRow()) {
				cout << "Uncompatiable Matrix" << endl;
				exit(1);
			}
			//cout << "compatiable" << endl;
			
			int row = this->getRow();
			int col = s.getCol();
			//cout << row << " " << col << endl;
			Matrix<T> *resultMatrix=new  Matrix<T>(row,col);
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {	
					int times = s.getRow();
					T result = 0;
					for (int k = 0; k < times; k++) {
						result = result + ((*this)[i][k]*s[k][j]);
					}
					//cout << result<<endl;
					(*resultMatrix)[i][j] = result;

				}
			}
			//cout << *resultMatrix;
			//cout << "before return" << endl;
			return resultMatrix;
		}



		//Destructor
		~Matrix() 
		{
			int col = colHigh - colLow + 1;
			int row = rowHigh - rowLow + 1;
			//cout << "destructor " << row << " " << col << endl;
			//1. delete the content in each row first
			//2. delete the whole matrix
			for (int i = 0; i < row; i++) {
				delete (*matrix)[i];
			}
			delete matrix;
			
		}

		


		friend ostream& operator<<(ostream& os, Matrix &s) {
			int col = s.colHigh - s.colLow + 1;
			int row = s.rowHigh - s.rowLow + 1;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					//cout << s.((*(*matrix)[i])[j]) << " ";
					os << (*((*s.matrix)[i]))[j] << " ";
				}
				os << endl;
			}
			os << endl;
			return os;
		};

	

};


int main() {
	//a test for SA in new
	//SA<int> *a=new SA<int>(10);
	//(*a)[1] = 13;
	//cout << (*a)[1] << endl;
	//delete a;
	

	Matrix<int> m(3,3);
	m[0][0] = 9; m[0][1] = 8; m[0][2] = 7;
	m[1][0] = 6; m[1][1] = 5; m[1][2] = 4;
	m[2][0] = 3; m[2][1] = 2; m[2][2] = 1;


	Matrix<int> n(3, 4);
	n[0][0] = 1; n[0][1] = 2; n[0][2] = 3; n[0][3] = 4;
	n[1][0] = 5; n[1][1] = 6; n[1][2] = 7; n[1][3] = 8;
	n[2][0] = 9; n[2][1] = 10; n[2][2] = 11; n[2][3] = 12;




	cout << "The matrix m is" << endl;
	cout << m;
	cout << "The matrix n is" << endl;
	cout << n;
	cout << "The result of m*n is" << endl;
	
	Matrix<int>* result= m * n;
	cout << (*result);
	return 0;
}
