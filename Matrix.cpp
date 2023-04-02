#include "Matrix.h"
//using namespace std;

void Matrix::Get_mem(int _i, int _j)
{
	m = new double* [_i];
	for (int k = 0; k < _i; k++)
		m[k] = new double[_j];
}

Matrix::Matrix(int _i, int _j)
{
	if (_i == 0 && _j == 0)
	{
		cout << "vvedite razmer matritsy: ";
		cin >> i >> j;
	}
	else
	{
		i = _i;
		j = _j;
	}
	if (i <= 0 || j <= 0)
	{
		printf("bad size");
		system("pause");
		exit(1);
	}
	Get_mem(i, j);
}

Matrix::Matrix(const Matrix& m1)
{
	i = m1.i;
	j = m1.j;
	Get_mem(i, j);
	for (int k = 0; k < i; k++)
		for (int l = 0; l < j; l++)
			m[k][l] = m1.m[k][l];
}

Matrix::~Matrix()
{
	for (int k = 0; k < i; k++)
	{
		delete[] m[k];
	}
	delete[] m;
}

inline void Error(const char* str)
{
	cout << endl << str << endl;
	system("pause");
	exit(1);
}

//-------------------------------------------------------------------------------------------------------------------------

Matrix operator+(Matrix m1, Matrix m2)
{
	Matrix m3(m1.i, m1.j);
	if (m1.i == m2.i && m1.j == m2.j)
	{
		for (int i = 0; i < m1.i; i++)
			for (int j = 0; j < m1.j; j++)
				m3[i][j] = m1[i][j] + m2[i][j];
	}
	else cout << "неверный размер матриц, попробуйте ввести снова" << endl;
	return m3;
}

Matrix operator-(Matrix m1, Matrix m2)
{
	Matrix m3(m1.i, m1.j);
	if (m1.i == m2.i && m1.j == m2.j)
	{
		for (int i = 0; i < m1.i; i++)
			for (int j = 0; j < m1.j; j++)
				m3[i][j] = m1[i][j] - m2[i][j];
	}
	else cout << "неверный размер матриц, попробуйте ввести снова" << endl;
	return m3;
}

Matrix operator*(Matrix m1, Matrix m2)
{
	Matrix m3(m1.i, m1.i);
	for (int i = 0; i < m1.i; i++)
		for (int j = 0; j < m1.i; j++)
			m3[i][j] = 0;
	if (m1.i == m2.j && m1.j == m2.i)
	{
		for (int i = 0; i < m1.i; i++)
			for (int j = 0; j < m1.i; j++)
				for (int k = 0; k < m1.j; k++)
				m3[i][j] += m1[i][k] * m2[k][j];
	}
	else Error("nevern razmer matrits");
	return m3;
}

Matrix operator/(Matrix m1, Matrix m2)
{
	Matrix m3(m1.i, m1.j);
	if (m1.i == m2.i && m1.j == m2.j)
	{
		for (int i = 0; i < m1.i; i++)
			for (int j = 0; j < m1.j; j++)
				m3[i][j] = m1[i][j] / m2[i][j];
	}
	else Error("неверный размер матриц");
	return m3;
}

//-------------------------------------------------------------------------------------------------------------------------

Matrix operator+(Matrix& m1, double a)
{
	Matrix m3(m1.i, m1.j);
	for (int i = 0; i < m1.i; i++)	
		for (int j = 0; j < m1.j; j++)
			m3.m[i][j] = m1.m[i][j] + a;
	return m3;
}

Matrix operator-(Matrix m1, double a)
{
	Matrix m3(m1.i, m1.j);
	for (int i = 0; i < m1.i; i++)
		for (int j = 0; j < m1.j; j++)
			m3.m[i][j] = m1.m[i][j] - a;
	return m3;
}

Matrix operator*(Matrix m1, double a)
{
	Matrix m3(m1.i, m1.j);
	for (int i = 0; i < m1.i; i++)
		for (int j = 0; j < m1.j; j++)
			m3.m[i][j] = m1.m[i][j] * a;
	return m3;
}

Matrix operator/(Matrix m1, double a)
{
	Matrix m3(m1.i, m1.j);
	for (int i = 0; i < m1.i; i++)
		for (int j = 0; j < m1.j; j++)
			m3.m[i][j] = m1.m[i][j] / a;
	return m3;
}

//-------------------------------------------------------------------------------------------------------------------------

Matrix operator+(double a, Matrix m1)
{
	return m1+a;
}

Matrix operator-(double a, Matrix m1)
{
	Error("nelzya vychitat` matritsu iz chicla");
	return m1;
}

Matrix operator*(double a, Matrix m1)
{
	return m1*a;
}
Matrix operator/(double a, Matrix m1)
{
	Error("nelzya delit` chiclo na matritsy");
	return m1;
}

double* Matrix::operator[](const int k)
{
	return  m[k];
}

Matrix const& Matrix::operator=(Matrix const& m1)
{
	if (m) delete m;
	i = m1.i;
	j = m1.j;
	Get_mem(i,j);
	for (int k = 0; k < i; k++)
		for (int l = 0; l < j; l++)
			m[k][l] = m1.m[k][l];
	return *this;
}

void Matrix::Print() const
{
	for (int k = 0; k < i; k++)
	{
		for (int l = 0; l < j; l++)
			cout << m[k][l] << " ";
		cout << endl;
	}
	cout << endl;
}

void Matrix::Add()
{
	cout << "vvedite znacheniya: " << endl;
	for (int k = 0; k < i; k++)
		for (int l = 0; l < j; l++)
			cin >> m[k][l];
}
