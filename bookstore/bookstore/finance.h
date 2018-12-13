#pragma once

#include<string>
#include<fstream>
using namespace std;

class finance_base
{
public:
	finance_base(const string &);
	~finance_base();

	void gain(double);
	void lose(double);
	void show();
	void show(int);

	fstream file;
	int top;
	double x, y;
};

