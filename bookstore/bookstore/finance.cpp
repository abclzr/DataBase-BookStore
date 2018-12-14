#include "finance.h"



finance_base::finance_base(const string &str)
{
	file.open(str, ios::binary | ios::in | ios::out);
	if (!file.is_open()) {
		file.open(str, ios::binary | ios::out);
		top = 0;
		x = y = 0;
		file.write(reinterpret_cast<char *> (&top), sizeof(top));
		file.write(reinterpret_cast<char *> (&x), sizeof(x));
		file.write(reinterpret_cast<char *> (&y), sizeof(y));
		file.close();
		file.open(str, ios::binary | ios::in | ios::out);
	}
	else {
		file.read(reinterpret_cast<char *> (&top), sizeof(top));
		file.read(reinterpret_cast<char *> (&x), sizeof(x));
		file.read(reinterpret_cast<char *> (&y), sizeof(y));
	}
}


finance_base::~finance_base()
{
	file.seekp(0);
	file.write(reinterpret_cast<char *> (&top), sizeof(top));
	file.write(reinterpret_cast<char *> (&x), sizeof(x));
	file.write(reinterpret_cast<char *> (&y), sizeof(y));
	file.close();
}

void finance_base::gain(double num)
{
	x += num;
	file.seekp(sizeof(int) + sizeof(double) * (top + 1) * 2);
	file.write(reinterpret_cast<char *> (&x), sizeof(x));
	file.write(reinterpret_cast<char *> (&y), sizeof(y));
	++top;
}

void finance_base::lose(double num)
{
	y += num;
	file.seekp(sizeof(int) + sizeof(double) * (top + 1) * 2);
	file.write(reinterpret_cast<char *> (&x), sizeof(x));
	file.write(reinterpret_cast<char *> (&y), sizeof(y));
	++top;
}

void finance_base::show()
{
	printf("+ %.2lf - %.2lf\n", x, y);
	/*
	file.seekg(sizeof(int) + sizeof(double) * 2);
	double xx, yy;
	for (int i = 1; i <= top; ++i) {
		file.read(reinterpret_cast<char *> (&xx), sizeof(xx));
		file.read(reinterpret_cast<char *> (&yy), sizeof(yy));
		printf("+ %.2lf - %.2lf\n", xx, yy);
	}
	*/
}

void finance_base::show(int times)
{
	if (times > top) { puts("Invalid"); return; }
	if (times == top) { show(); return; }
	file.seekg(sizeof(int) + sizeof(double) * 2 + sizeof(double) * 2 * (top - times - 1));
	double xx, yy;
	file.read(reinterpret_cast<char *> (&xx), sizeof(xx));
	file.read(reinterpret_cast<char *> (&yy), sizeof(yy));
	printf("+ %.2lf - %.2lf\n", x - xx, y - yy);
}
