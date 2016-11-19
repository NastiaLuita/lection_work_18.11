// LectionWork.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Exception
{
public:
	Exception() {}
	virtual void print() {}
};

class IndexOutOfRange : public Exception
{
public:
	IndexOutOfRange(int index, int maxIndex) : index(index), maxIndex(maxIndex) {}
	void print() 
	{
		cout << "Index out of Range! Bad index: " << index << " (max index: " << maxIndex << ")" << endl;
	}
private:
	int index, maxIndex;
};

class ListIsEmpty : public Exception
{
public:
	ListIsEmpty() {}
	void print()
	{
		cout << "List is Empty!" << endl;
	}
};

template <class T>
class ArrayList
{
public:
	ArrayList(const initializer_list<T> mas) :arity(mas.size()), maxArity(mas.size())
	{
		arr = new T [maxArity];
		int i = 0;
		for (initializer_list<T>::iterator it = mas.begin(); it != mas.end(); ++it)
		{
			arr[i] = *it;
			i++;
		}
	}
	friend ostream & operator <<(ostream& os, ArrayList& a)
	{
		for (int i = 0; i < a.arity; i++)
			os << a.arr[i] << " ";
		return os;
	}
	T operator[] (int index)
	{
		if (index >= arity)	throw IndexOutOfRange(index, arity - 1);
		else return arr[index];
	}
	void push(T elem)
	{
		if (maxArity == arity) {
			maxArity = 2 * maxArity;
			T *newMas = new T [maxArity];
			for (int i = 0; i < arity; i++) 
				newMas[i] = arr[i];
			delete[] arr;
			arr = newMas;
		}
		arr[arity] = elem;
		arity++;
	}
	T pop()
	{
		if (arity == 0)	throw ListIsEmpty();
		else
		{
			arity--;
			return arr[arity];
		}
	}
	void insert(T elem)
	{
		if (maxArity == arity) 
			maxArity = 2 * maxArity;
		T *newMas = new T[maxArity];
		for (int i = 0; i < arity; i++)
			newMas[i + 1] = arr[i];
		delete[] arr;
		arr = newMas;
		arr[0] = elem;
		arity++;
	}
	T shift()
	{
		if (arity == 0)	throw ListIsEmpty();
		else
		{
			T *newMas = new T[maxArity], elemToReturn = arr[0];
			for (int i = 0; i < arity; i++)
				newMas[i] = arr[i + 1];
			delete[] arr;
			arr = newMas;
			arity--;
			return elemToReturn;
		}
	}
private:
	int arity, maxArity;
	T *arr;
};


int main()
{
	try
	{
		ArrayList<int> a{ 1, 2, 3, 4};
		cout << a << endl;
		a.push(5); 
		cout << "After push: " << a << endl;
		a.insert(0);
		cout << "After insert: " << a << endl;
		cout << "Shift: " << a.shift() << "; after shift: " << a << endl;
		cout << "Pop: " << a.pop() << "; after pop: " << a << endl;
	}
	catch (Exception & e)
	{
		e.print();
	}
	system("pause");
    return 0;
}