#include "matrix.h"
matrix::matrix()
{
	isNum = false;
}
matrix::~matrix() {}
matrix::matrix(const std::string& str)
{
	if (IsNumber(str))
	{
		isNum = true;
		value = std::stod(str);
		SizeRov = 0;
		SizeCol = 0;
		return;
	}
	isNum = false;
	value = 0;
	SizeRov = std::count(str.begin(), str.end(), '|');
	SizeCol = std::count(str.begin(), str.end(), ',') / SizeRov + 1;;
	array.resize(SizeRov);
	int numRov = 0;
	for (auto& string : StringSplit(str.substr(0, str.size() - 1), "|")) {
		if (SizeCol != std::count(string.begin(), string.end(), ',') + 1)
			throw std::exception("Row sizes do not match");
		for (auto& number : StringSplit(string, ",")) {
			if (!IsFloat(number))
				throw std::exception("One or more elements of the matrix is not a number!");
			array[numRov].push_back(std::stod(number));
		}
		numRov++;
	}
}

matrix::matrix(const Operations* calc)
{
	SizeRov = ((matrix*)calc)->SizeRov;
	SizeCol = ((matrix*)calc)->SizeCol;
	value = ((matrix*)calc)->value;
	isNum = ((matrix*)calc)->isNum;
	array = ((matrix*)calc)->array;
}
//+
Operations* matrix::add(const Operations* arr)
{
	try
	{
		if (isNum && ((matrix*)arr)->isNum)
		{
			value += ((matrix*)arr)->value;
			return this;
		}
		if (isNum && !((matrix*)arr)->isNum)
		{
			SizeRov = ((matrix*)arr)->SizeRov;
			SizeCol = ((matrix*)arr)->SizeCol;
			array = ((matrix*)arr)->array;
			isNum = false;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] = ((matrix*)arr)->array[i][j] + value;
			return this;
		}
		if (!isNum && ((matrix*)arr)->isNum)
		{
			value = ((matrix*)arr)->value;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] += value;
			return this;
		}
		if (SizeCol == ((matrix*)arr)->SizeCol and SizeRov == ((matrix*)arr)->SizeRov)
		{
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] += ((matrix*)arr)->array[i][j];
			return this;
		}
		throw std::exception("Matrix sizes do not match\n");

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

}
//*
Operations* matrix::increase(const Operations* arr)
{
	try
	{
		if (isNum && ((matrix*)arr)->isNum)
		{
			value *= ((matrix*)arr)->value;
			return this;
		}
		if (isNum && !((matrix*)arr)->isNum)
		{
			SizeRov = ((matrix*)arr)->SizeRov;
			SizeCol = ((matrix*)arr)->SizeCol;
			array = ((matrix*)arr)->array;
			isNum = false;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] = ((matrix*)arr)->array[i][j] * value;
			return this;
		}
		if (!isNum && ((matrix*)arr)->isNum)
		{
			value = ((matrix*)arr)->value;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] *= value;
			return this;
		}
		if (SizeCol == ((matrix*)arr)->SizeRov)
		{
			matrix m1;
			m1.SizeRov = SizeRov;
			m1.SizeCol = ((matrix*)arr)->SizeCol;
			m1.array = array;
			for (int i = 0; i < SizeRov; i++)
				m1.array[i].resize(SizeRov);
			for (int i = 0; i < m1.SizeRov; i++)
				for (int j = 0; j < m1.SizeCol; j++)
					m1.array[i][j] = 0;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < m1.SizeCol; j++)
					for (int k = 0; k < SizeCol; k++)
						m1.array[i][j] += array[i][k] * ((matrix*)arr)->array[k][j];
			SizeCol = ((matrix*)arr)->SizeCol;
			array = std::move(m1.array);
			return this;
		}
		throw std::exception("Matrix sizes do not match\n");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

}
//-
Operations* matrix::subtraction(const Operations* arr)
{
	try
	{
		if (isNum && ((matrix*)arr)->isNum)
		{
			value -= ((matrix*)arr)->value;
			return this;
		}
		if (isNum && !((matrix*)arr)->isNum)
		{
			throw std::exception("It is impossible to subtract a matrix from a number!\n");
			SizeRov = 0;
			value = 0;
			return this;
		}
		if (!isNum && ((matrix*)arr)->isNum)
		{
			value = ((matrix*)arr)->value;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] -= value;
			return this;
		}
		if (SizeCol == ((matrix*)arr)->SizeCol and SizeRov == ((matrix*)arr)->SizeRov)
		{
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] -= ((matrix*)arr)->array[i][j];
			return this;
		}
		throw std::exception("Matrix sizes do not match\n");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

}
//%
Operations* matrix::div(const Operations* arr)
{
	try
	{
		if (isNum && ((matrix*)arr)->isNum)
		{
			if (((matrix*)arr)->value == 0)
			{
				throw std::exception("Couldn't div by 0!\n");
				SizeRov = 0;
				return this;
			}
			value /= ((matrix*)arr)->value;
			return this;
		}
		if (isNum && !((matrix*)arr)->isNum)
		{
			throw std::exception("Error! Couldn't div num on matrix!\n");
			SizeRov = 0;
			return this;
		}
		if (!isNum && ((matrix*)arr)->isNum)
		{
			if (((matrix*)arr)->value == 0)
			{
				throw std::exception("Error! Couldn't div by 0!\n");
				SizeRov = 0;
				return this;
			}
			value = ((matrix*)arr)->value;
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] /= value;
			return this;
		}
		if (SizeCol == ((matrix*)arr)->SizeCol and SizeRov == ((matrix*)arr)->SizeRov)
		{
			for (int i = 0; i < ((matrix*)arr)->SizeCol; i++)
				for (int j = 0; j < ((matrix*)arr)->SizeRov; j++)
					if (((matrix*)arr)->array[i][j] == 0)
					{
						throw std::exception("Error! Couldn't div by 0!\n");
						SizeRov = 0;
						return this;
					}
			for (int i = 0; i < SizeRov; i++)
				for (int j = 0; j < SizeCol; j++)
					array[i][j] /= ((matrix*)arr)->array[i][j];
			return this;
		}
		throw std::exception("Matrix sizes do not match\n");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}


}
//**
Operations* matrix::exp(const Operations* arr)
{
	if (isNum && ((matrix*)arr)->isNum)
	{
		if (((matrix*)arr)->value < 0)
		{
			auto tmp = value;
			for (int i = 1; i <= -((matrix*)arr)->value - 1; i++)
				value *= tmp;
			value = 1 / value;
			return this;
		}
		if (((matrix*)arr)->value == 0)
		{
			value = 1;
			return this;
		}
		auto tmp = value;
		for (int i = 1; i <= ((matrix*)arr)->value - 1; i++)
			value *= tmp;
		return this;
	}
	
	if (isNum && !((matrix*)arr)->isNum)
	{
		throw std::exception("Error! Wrong operation! It is impossible to raise the number to this power!");
		SizeRov = 0;
		value = 0;
		return this;
	}
	if (!isNum && ((matrix*)arr)->isNum)
	{
		if (SizeCol != SizeRov)
		{
			throw std::exception("Error! Wrong operation! It is impossible not to raise a square matrix to a power!");
			SizeRov = 0;
			value = 0;
			return this;
		}
		if (((matrix*)arr)->value <= -1)
		{
			throw std::exception("Error! Wrong operation! It is impossible to raise the matrix to this power!");
			SizeRov = 0;
			value = 0;
			return this;
		}
		if (((matrix*)arr)->value == 0)
		{
			for (int i = 0; i < SizeCol; i++) {
				for (int j = 0; j < SizeCol; j++) {
					if (i == j) {
						array[i][j] = 1;
					}
					else {
						array[i][j] = 0;
					}
				}
			}
			return this;
		}
		if (((matrix*)arr)->value == 1)
			return this;
		matrix m1;
		m1.SizeRov = SizeRov;
		m1.SizeCol = SizeCol;
		m1.array = array;
		for (int i = 0; i < m1.SizeRov; i++)
			for (int j = 0; j < m1.SizeCol; j++)
				m1.array[i][j] = 0;
		for (int i = 0; i < SizeRov; i++)
			for (int j = 0; j < SizeCol; j++)
				for (int k = 0; k < SizeCol; k++)
					m1.array[i][j] += array[i][k] * array[k][j];

		if (((matrix*)arr)->value > 2)
		{
			matrix m2;
			m2.SizeRov = SizeRov;
			m2.SizeCol = SizeCol;
			m2.array = array;
			for (int i = 0; i < m1.SizeRov; i++)
				for (int j = 0; j < m1.SizeCol; j++)
					m2.array[i][j] = m1.array[i][j];
			for (int i = 3; i <= ((matrix*)arr)->value; i++)
			{
				for (int i = 0; i < SizeRov; i++)
					for (int j = 0; j < m1.SizeCol; j++)
						for (int k = 0; k < SizeCol; k++)
							m2.array[i][j] += m1.array[i][k] * array[k][j];
			}
			array = std::move(m2.array);

		}
		else
			array = std::move(m1.array);
		return this;
	}
	if (!isNum && !((matrix*)arr)->isNum)
	{
		throw std::exception("Error! Wrong operation! It is impossible to raise the matrix to this power!");
		SizeRov = 0;
		value = 0;
		return this;
	}
	throw std::exception("Matrix sizes do not match");
}

std::ostream& operator<<(std::ostream& out, const matrix& matrix) {
	if (matrix.value && matrix.SizeRov == 0)
		out << matrix.value;
	for (int i = 0; i < matrix.SizeRov; i++) {
		out << "[ ";
		for (int j = 0; j < matrix.SizeCol; j++)
			out << matrix.array[i][j] << ' ';
		out << "]\n";
	}
	return out;
}

