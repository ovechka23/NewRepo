#include "Matrix.h"

int main()
{
	Matrix a(0,0);
	Matrix b(0,0);
	a.Add();
	b.Add();
	a.Print();
	b.Print();
	a = a*b;
	a.Print();
	system("pause");
	return 0;

}