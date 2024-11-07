#include <iostream>
#include "Stack.h"
using namespace std;
int main()
{
	TStack<int> s(10);
	s.Push(3);
	s.Push(4);
	s.Push(2);
	TCalc c;
	c.SetInfix("2^3");
	c.ToPostfix();
	cout << c.CalcPostfix() << endl;
	
}