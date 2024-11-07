#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;
const int MAXS = 10000;
template <class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;
public:
	TStack(int _MaxSize = 10); //конструктор инициализации
	~TStack(); //деструктор
	TStack(const TStack& s); //конструктор копирования
	int GetSize() { return MaxSize; } // размер стека
	int GetStartIndex() { return Num; } // индекс Num
	TStack& operator=(const TStack<T> s); //оператор присваивания
	bool operator==(const TStack& s) const; //сравнение равно
	bool operator!=(const TStack& s) const; //сравнение не равно
	T Pop(); //извлечение элемента из стека
	void Push(T val); //добавление элемента в стек
	bool Empty() const; // проверка на пустоту Num = -1
	bool Full() const; // проверка на полноту Nun = MaxSize-1
	T Top() const; //посмотреть на вершинку стека
	void Clear(); //очистка стека Clear
	bool Check(string str);
	friend istream& operator>>(istream& in, TStack& s) //ввод элемента
	{
		if (this->isFull())
			throw - 1;
		Num++;
		in >> s.pMem[Num];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TStack& s) //âûâîä ýëåìåíòà
	{
		if (this->isEmpty())
			throw - 1;
		out << s.pMem[Num];
		return out;
	}
};
template <class T>
TStack<T>::TStack(int _MaxSize)
{
	if (_MaxSize < 0 || _MaxSize > MAXS)
		throw - 1;
	MaxSize = _MaxSize;
	Num = -1;
	pMem = new T[MaxSize];
}
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
	if (s.MaxSize < 0 || s.MaxSize > MAXS || s.Num < -1 || s.Num >= s.MaxSize)
		throw - 1;
	MaxSize = s.MaxSize;
	Num = s.Num;
	pMem = new T[MaxSize];
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
}
template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T> s)
{
	if (this == &s)
		return *this;
	if (MaxSize != s.MaxSize)
	{
		MaxSize = s.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = s.Num;
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
	return *this;
}
template <class T>
bool TStack<T>::operator==(const TStack& s) const
{
	if (this == &s)
		return true;
	if (MaxSize != s.MaxSize)
		return false;
	if (Num != s.Num)
		return false;
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != s.pMem[i])
			return false;
	}
	return true;
}
template <class T> // сравнение
bool TStack<T>::operator!=(const TStack& s) const
{
	return !(*this == s);
}
template <class T>
bool TStack<T>::Empty() const
{
	if (Num == -1)
		return true;
	return false;
}
template <class T>
bool TStack<T>::Full() const
{
	if (Num == MaxSize - 1)
		return true;
	return false;
}
template <class T>
T TStack<T>::Pop()
{
	if (this->Empty())
		throw - 1;
	T tmp = pMem[Num];
	Num--;
	return tmp;
}
template <class T>
void TStack<T>::Push(T val)
{
	if (this->Full())
		throw - 1;
	Num++;
	pMem[Num] = val;
}
template <class T>
T TStack<T>::Top() const
{
	if (this->Empty())
		throw - 1;
	return pMem[Num];
}
template <class T>
void TStack<T>::Clear() {
	Num = -1;
}
template <class T>
bool TStack<T>::Check(string str)
{
	TStack<char> s;
	bool res = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			s.Push('(');
		if (str[i] == ')')
		{
			if (s.Empty())
				return false;
			s.Pop();
		}
	}
	if (!s.Empty())
		return false;
	return true;
}
class TCalc
{
	string infix;
	string postfix;
	TStack<double> StNum;
	TStack<char> StChar;
public:
	TCalc();//конструктор может быть пустым
	void SetInfix(string _infix) {
		infix = _infix;
	}
	void SetPostfix(string _postfix) {
		postfix = _postfix;
	}
	string GetInfix() {
		return infix;
	}
	string GetPostfix() {
		return postfix;
	}
	void ToPostfix(); //преобразовать из infix в postfix
	double CalcPostfix();

	int Prior(char op); //у ( приотритет меньше, чем у любой другой операции
	//(((1+2)*3)^4-5)/6 ((( кладется в стек, дальше + и ) выталкивает (+, дальше заносится *, ) выталкивает (*, ^ и -: у ^ выше приоритет, выполняется, далее - и тд
};
TCalc::TCalc() {
	StNum = TStack<double>(MAXS);
	StChar = TStack<char>(MAXS);
}
int TCalc::Prior(char op) {
	if (op == '+' || op == '-')return 1;
	if (op == '*' || op == '/')return 2;
	if (op == '(')return 0;
	if (op == '^')return 3;
}
double TCalc::CalcPostfix() {
	StNum.Clear();
	StChar.Clear();
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] >= '0' && postfix[i] <= '9')
			StNum.Push(postfix[i] - '0');
		if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
		{
			double Num2 = StNum.Pop();
			double Num1 = StNum.Pop();
			if (postfix[i] == '+')
				StNum.Push(Num1 + Num2);
			if (postfix[i] == '-')
				StNum.Push(Num1 - Num2);
			if (postfix[i] == '*')
				StNum.Push(Num1 * Num2);
			if (postfix[i] == '/')
			{
				if (Num2 == 0)
					throw - 1;
				StNum.Push(Num1 / Num2);
			}
			if (postfix[i] == '^') {
				StNum.Push(pow(Num1, Num2));
			}
		}
	}
	int a = StNum.Pop();
	return a;
}
void TCalc::ToPostfix() {
	postfix = "";
	StChar.Clear();
	string s = "(" + infix + ")";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			StChar.Push(s[i]);
		else if (s[i] - '0' <= 9 && s[i] - '0' >= 0)
			postfix += s[i];
		else if (s[i] == ')')
		{
			char a = StChar.Pop();
			while (a != '(')
			{
				postfix += a;
				a = StChar.Pop();
			}
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
		{
			while (Prior(StChar.Top()) >= Prior(s[i]))
				postfix += StChar.Pop();
			StChar.Push(s[i]);
		}
	}
}