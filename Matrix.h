#pragma once
#include"operations.h"
#include<iostream>
#include<vector>
class matrix :public  Operations
{
	int SizeRov;
	int SizeCol;
	double value;
	bool isNum;
	std::vector<std::vector<double>> array;

public:
	matrix();
	~matrix();
	matrix(const std::string& str);
	matrix(const Operations*);
	Operations* add(const Operations*); // =+
	Operations* increase(const Operations*); // =*
	Operations* subtraction(const Operations*); // =-
	Operations* div(const Operations*); // =/

	friend std::ostream& operator <<(std::ostream& out, const matrix& num);
};
