#include "database.h"
#include<fstream>
#include<string>

const int B = 100;

template<class T>
database<T>::database(std::string s)
{
	ofstream of, ot;
	of.open(s, in | out);
	of.close();
	ot.open(s + ".trash", in | out);
	ot.close();
	file.open(s);
	trash.open(s + ".trash");

	file.read(reinterpret_cast<char *> (&num), sizeof(num));
	if (file.eof()) {
		num = 0;
		file.write(reinterpret_cast<char *> (&num), sizeof(num));
		head = 0; tail = 12;
		file.write(reinterpret_cast<char *> (&head), sizeof(head));
		file.write(reinterpret_cast<char *> (&tail), sizeof(tail));
	}
	else {
		file.read(reinterpret_cast<char *> (&head), sizeof(head));
		file.read(reinterpret_cast<char *> (&tail), sizeof(tail));
	}

	trash.read(reinterpret_cast<char *> (&top), sizeof(top));
	if (trash.eof()) {
		top = 0;
		file.write(reinterpret_cast<char *> (&top), sizeof(top));
	}
}

template<class T>
database<T>::~database()
{
	file.seekp(0);
	file.write(reinterpret_cast<char *> (&num), sizeof(num));
	file.write(reinterpret_cast<char *> (&head), sizeof(head));
	file.write(reinterpret_cast<char *> (&tail), sizeof(tail));

	trash.seekp(0);
	file.write(reinterpret_cast<char *> (&top), sizeof(top));
}

template<class T>
int database<T>::getnew() {
	if (top == 0) {
		int t = tail;
		tail += sizeof(int) * 2 + sizeof(T) * B;
		file.seekp(t);
		int blank = 0;
		file.write(reinterpret_cast<char *> (&blank), sizeof(blank));
		file.write(reinterpret_cast<char *> (&blakn), sizeof(blank));
		return t;
	}
	else {
		trash.seekg(top);
		int t;
		trash.read(reinterpret_cast<char *> (&t), sizeof(t));
		--top;
		return t;
	}
}

template<class T>
int database<T>::get(const T &x) {
	int tmp = head, pre = head, nxt;
	T fr;
	while (tmp != 0) {
		file.seekg(tmp);
		file.read(reinterpret_cast<char *> (&nxt), sizeof(nxt));
		file.seekg(2 * sizeof(int), tmp));
		file.read(reinterpret_cast<char *> (&fr), sizeof(fr));
		if (x < fr) return pre;
		else {
			pre = tmp;
			tmp = nxt;
		}
	}

	if (tmp == 0) return pre;
}

template<class T>
void database<T>::move(int l1, int r1, int l2, int r2) {
	int t1 = r1 - sizeof(T), t2 = r2 - sizeof(T);
	T x;
	while (t1 >= l1 && t2 >= l2) {
		file.seekg(t1);
		file.read(reinterpret_cast<char *> (&x), sizeof(x));		
		file.seekp(t2);
		file.write(reinterpret_cast<char *> (&x), sizeof(x));
		t1 -= sizeof(T); t2 -= sizeof(T);
	}
}

template<class T>
void add(T x) {
	++num;
	int pos = get(x);
	int nxt, size;
	file.seekg(pos);
	file.read(reinterpret_cast<char *> (&nxt), sizeof(nxt));
	file.read(reinterpret_cast<char *> (&size), sizeof(size));

	if (size == B) {
		int newpos = getnew();

	}
	else {
		T a;
		for (int i = 0; i < size; ++i) {
			file.read(reinterpret_cast<char *> (&a), sizeof(a));
			if (x < a) {
				move(pos + sizeof(int) * 2 + i * sizeof(T), pos + sizeof(int) * 2 + (size - 1) * sizeof(T), pos + sizeof(int) * 2 + (i + 1) * sizeof(T), pos + sizeof(int) * 2 + size * sizeof(T));
				file.seekp(pos + sizeof(int) * 2 + i * sizeof(T));
				file.write(reinterpret_cast<char *> (&x), sizeof(x));
			}
		}
		++size;
		file.seekp(pos + sizeof(int));
		file.write(reinterpret_cast<char *> (&size), sizeof(size));
	}
}
