#ifndef _MATRIX_H
#define _MYATRIX_H

#include <iostream>
#include <math.h>
using namespace std;

class Matrix
{
protected:
	double** m;
	int i, j;
	void Get_mem(int _i, int _j);
public:
	Matrix(int _i, int _j);
	Matrix(const Matrix& m1);
	~Matrix();
	static inline void Error(const char* str);
	friend Matrix operator+(Matrix m1, Matrix m2);
	friend Matrix operator-(Matrix m1, Matrix m2);
	friend Matrix operator*(Matrix m1, Matrix m2);
	friend Matrix operator/(Matrix m1, Matrix m2);
	friend Matrix operator+(Matrix& m1, double a);
	friend Matrix operator-(Matrix m1, double a);
	friend Matrix operator*(Matrix m1, double a);
	friend Matrix operator/(Matrix m1, double a);
	friend Matrix operator+(double a, Matrix m1);
	friend Matrix operator-(double a, Matrix m1);
	friend Matrix operator*(double a, Matrix m1);
	friend Matrix operator/(double a, Matrix m1);
	double* operator[](const int k);
	Matrix const& operator=(Matrix const& m1);
	void Add();

	void Print() const;

};
#endif