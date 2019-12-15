// STL-Safe-Array.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include <iostream>
#include <string>
#include<fstream>
#include<map>
using namespace std;






// What the HashMap do : <Key, Value> pair, key is the power, and coeeficient is the value
// In this pseudoMap, index is the power, and its value is the coeeficient
//A map with identity function, use index as the key, no actual hash function is used
//Dynamic Array implementation

ofstream output;

class HashMap {
private:
	int size = 0;

public:
	//int* map;
	map<int, int>*hashmap;
	HashMap() {
		size = 10;//default siez
		hashmap = new map<int, int>();

		for (int i = 0; i < size; i++) {
			(*hashmap)[i] = 0; //all initialized to 0
		}

	}

	int getSize() {
		return size;
	}
	void subtractInsert(int power, int coeeficient) {
		if (power > this->size)
		{
			if (power >this->size) {
				map<int, int>*oldMap = hashmap;
				int oldSize = size;
				size = power + 1;
				hashmap = new map<int,int>();
				for (int i = 0; i < size; i++) {
					(*hashmap)[i] = 0;
				}
				for (int i = 0; i < oldSize; i++) {
					(*hashmap)[i] = (*oldMap)[i];
				}
				(*hashmap)[power] = -coeeficient;
				delete oldMap;
			}
		}
		else {
			(*hashmap)[power] = (*hashmap)[power] - coeeficient;
		}

	}

	void addInsert(int power, int coeeficient) {
		//cout << this->size << endl;
		if (power >= this->size)
		{
			//cout << "call" << endl;   1


			map<int, int>*oldMap = hashmap;
			int oldSize = size;
			size = power + 1;
			hashmap = new map<int, int>();
			for (int i = 0; i < size; i++) {
				(*hashmap)[i] = 0;
			}
			for (int i = 0; i < oldSize; i++) {
				(*hashmap)[i] = (*oldMap)[i];
			}
			//first, we need to copy the old content to the new map

			(*hashmap)[power] = coeeficient;
			delete oldMap;

		}
		else {
			(*hashmap)[power] = (*hashmap)[power] + coeeficient;
		}

	}

	void multiplyInsert(map<int,int>* otherMap, int othersize) {
		//cout << "dddddddd" << endl;
		//print();
		map<int,int>* oldMap = this->hashmap;
		int oldSize = size;
		this->hashmap = new map<int,int>();//10 as default size
		for (int i = 0; i < 10; i++) {
			(*hashmap)[i] = 0;
		}
		size = 10;
		//print();
		for (int i = 0; i < othersize; i++) {
			//i: power
			//otherMap[i] coeeficient
			for (int j = 0; j < oldSize; j++) {
				//cout << i << j << endl;
				this->addInsert(i + j, (*oldMap)[j] *(*otherMap)[i]);

			}
		}
		delete oldMap;

	}


	void print() {
		bool allZero = true;
		for (int i = 0; i < size; i++) {
			if ((*hashmap)[i] != 0) {
				allZero = false;
				break;
			}
		}
		if (allZero) {
			cout << "0" << endl;
			output << "0" << endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			if ((*hashmap)[i] == 0) {
				continue;
			}

			if (i == 0) {
				cout << (*hashmap)[i];
				output << (*hashmap)[i];
				//continue;
			}
			else {
				if ((*hashmap)[i] > 0) {
					if ((*hashmap)[i] == 1) {
						cout << "+X^" << i;
						output << "+X^" << i;
						continue;
					}
					cout << "+" << (*hashmap)[i] << "X^" << i;
					output << "+" << (*hashmap)[i] << "X^" << i;
				}
				else {
					cout << (*hashmap)[i] << "X^" << i;
					output << (*hashmap)[i] << "X^" << i;
				}

			}


		}
		cout << endl;
		output << endl;
	}


	//map is just a dynamic array
	~HashMap() {
		delete hashmap;
	}


};




class Polynomial {
private:
	string formula;
	HashMap *hashMap;
public:
	Polynomial() {
		hashMap = new HashMap();
	}

	Polynomial(string s) {
		this->formula = s;
		hashMap = new HashMap();
		construction();
		hashMap->print();

	}


	void construction() {
		char symbol;
		int i = 0;
		while (i < formula.size())
		{

			if (formula[i] == '(' || formula[i] == ')') {
				continue;
			} // skip any parentesie

			if (i == 0 && formula[i] != '+'&&formula[i] != '-')
			{

				if (formula[i] == 'x')
				{
					int coeeficient = 1;
					int power = 0;
					if (formula[i + 1] != '^')
					{

						power = 1;
						this->hashMap->addInsert(power, coeeficient);
						i++;
						continue;
					}

					else {
						int coeeficient = 1;
						int power = 0;
						i++;
						i++;
						while (isdigit(formula[i])) {
							power = power * 10 + (formula[i] - 48);
							i++;
						}
						this->hashMap->addInsert(power, coeeficient);
						continue;
					}

				}

				//staring with a number without + and -
				else {
					int coeeficient = 0;
					int power = 0;
					while (isdigit(formula[i]))
					{
						coeeficient = coeeficient * 10 + (formula[i] - 48);
						i++;
					}
					if (formula[i] != 'x') {
						power = 0;
						this->hashMap->addInsert(power, coeeficient);
						continue;
					}
					else
					{
						if (formula[i + 1] != '^') {
							power = 1;
							//Node* newNode = new Node(coeeficient, power, '+');
							this->hashMap->addInsert(power, coeeficient);
							continue;
						}
						i++;
						i++;
						while (isdigit(formula[i])) {
							power = power * 10 + (formula[i] - 48);
							i++;
						}
						this->hashMap->addInsert(power, coeeficient);

						continue;
					}
				}
				continue;
			}//the case for i=0, only for the beginning



			if (formula[i] == '+' || formula[i] == '-')
			{

				symbol = formula[i];
				i++;
				int coeeficient = 0;
				int power = 0;

				while (isdigit(formula[i])) {
					coeeficient = coeeficient * 10 + (formula[i] - 48);
					i++;
				}
				if (coeeficient == 0) {
					coeeficient = 1;
				}

				if (formula[i] != 'x') {
					power = 0;
					if (symbol == '+') {
						this->hashMap->addInsert(power, coeeficient);
					}
					else {
						this->hashMap->addInsert(power, -coeeficient);
					}
					continue;
				}
				else
				{
					if (formula[i + 1] != '^') {
						power = 1;
						if (symbol == '+') {
							this->hashMap->addInsert(power, coeeficient);
						}
						else {
							this->hashMap->addInsert(power, -coeeficient);
						}

						continue;
					}
					i++;
					i++;
					while (isdigit(formula[i])) {
						power = power * 10 + (formula[i] - 48);
						i++;
					}

					if (symbol == '+') {
						this->hashMap->addInsert(power, coeeficient);
					}
					else {
						this->hashMap->addInsert(power, -coeeficient);
					}
					continue;
				}
				continue;
			}
			i++;
		}

	}

	HashMap* getMap() {
		return this->hashMap;

	}

	void print() {
		//print function
		this->hashMap->print();
	}

	Polynomial* operator+(Polynomial* other) {
		Polynomial* result = new Polynomial();

		int size1 = this->getMap()->getSize();
		for (int i = 0; i < size1; i++) {
			map<int, int>*h = this->getMap()->hashmap;
			result->getMap()->addInsert(i,(*h)[i]);

		}
		int size2 = other->getMap()->getSize();
		for (int i = 0; i < size2; i++) {
			map<int, int>*h = other->getMap()->hashmap;
			result->getMap()->addInsert(i, (*h)[i]);

		}


		result->print();
		return result;

	}


	Polynomial* operator-(Polynomial* other) {
		Polynomial* result = new Polynomial();

		int size1 = this->getMap()->getSize();
		for (int i = 0; i < size1; i++) {
			map<int, int>*h = this->getMap()->hashmap;
			result->getMap()->addInsert(i, (*h)[i]);

		}

		int size2 = other->getMap()->getSize();
		for (int i = 0; i < size2; i++) {
			map<int, int>*h = other->getMap()->hashmap;
			result->getMap()->subtractInsert(i, (*h)[i]);

		}
		result->print();
		return result;

	}

	/*
	void setList(LinkedList* copy) {
	LinkedList* old = this->list;
	this->list = copy;
	delete old;

	}
	*/

	Polynomial* operator*(Polynomial* other)
	{
		Polynomial* result = new Polynomial();

		int size1 = this->getMap()->getSize();
		for (int i = 0; i < size1; i++) {
			map<int, int>*h = this->getMap()->hashmap;
			result->getMap()->addInsert(i, (*h)[i]);

		}
		map<int, int>*o = other->getMap()->hashmap;
		result->getMap()->multiplyInsert(o, other->getMap()->getSize());
		result->print();
		return result;
	}



	~Polynomial() {
		delete this->hashMap; // call the destructor of the list
	}

};




int main()
{
	cout << "Testing the map" << endl;
	HashMap map;
	map.addInsert(1, 4);
	map.addInsert(1, 3);
	map.addInsert(0, 13);
	map.addInsert(2, 10);
	map.addInsert(13, 10);
	map.print();

	cout << "In mathematics, a polynomial is an expression consisting of variables (also called indeterminates) and coefficients, that involves only the operations of addition, subtraction, multiplication, and non-negative integer exponents of variables." << endl;

	ifstream input;
	input.open("input.txt");
	output.open("ouput.txt");
	string line1;
	string line2;
	input >> line1;
	input >> line2;
	cout << line1 << endl;
	cout << line2 << endl;
	cout << "p1 is" << endl;
	output << "p1 is" << endl;
	Polynomial *p1 = new Polynomial(line1);
	cout << "p2 is" << endl;
	output << "p2 is" << endl;
	Polynomial *p2 = new Polynomial(line2);
	cout << "p1+p2 is" << endl;
	output << "p1+p2 is" << endl;
	(*p1) + p2;
	cout << "p1-p2 is" << endl;
	output << "p1-p2 is" << endl;
	(*p1) - p2;
	cout << "p1*p2 is" << endl;
	output << "p1*p2 is" << endl;
	(*p1) * p2;
	cout << endl;	cout << endl;



	output.close();
	return 0;
}

