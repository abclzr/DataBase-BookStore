#pragma once

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

template<class T>
class database
{
public:
	static const int B = 200;
	int head, tail, num, top;
	fstream file, trash;

	//deliver a file name to the constructing function, if the file doesn't exist, make a new one.
	database(std::string);
	~database();

	//return whether the element exits in the database
	bool exist(const T&);
	
	//return the tot number of the elements;
	int get_num();

	//return the position of next block;
	int get_next(int);

	//return the size of the block;
	int get_size(int);

	//set the next positon;
	void set_next(int, int);

	//set the size of the block;
	void set_size(int, int);

	//find the position of the block that fits x;
	int get(const T &);

	int get_(const T &);

	//find the position of the fits x in the file;
	int get_pos_in_block(int, const T &);

	//return the position of a new block;
	int getnew();

	//move a slice of the block;
	void move(int, int, int, int, int);

	//insert an element in one block;
	void insert(int, const T &);

	//add x into the block-shape links;
	void add(const T &);

	//find the previous position of the block;
	int get_pre(int);

	//remove a block;
	void del(int);

	//delete an element in a block;
	void rem(int, const T &);

	//delete an element
	void remove(const T &);

	void change(const T &);

	//find the element
	const T &get_acc(const T &);

	//print all
	void make_print();

	//print the specific books
	void make_print(const T &);
};

template<class T>
inline bool database<T>::exist(const T &x)
{
	int pos = get(x);
	if (pos != 0) {
		pos = get_pos_in_block(pos, x);
		if (pos != -1) return true;
	}
	return false;
}

template<class T>
database<T>::database(std::string s)
{
	file.open(s, ios::binary | ios::in | ios::out);
	if (!file.is_open()) {
		file.open(s, ios::binary | ios::out);
		num = 0;
		file.write(reinterpret_cast<char *> (&num), sizeof(num));
		head = 0; tail = 12;
		file.write(reinterpret_cast<char *> (&head), sizeof(head));
		file.write(reinterpret_cast<char *> (&tail), sizeof(tail));
		file.close();
		file.open(s, ios::binary | ios::in | ios::out);
	}

	trash.open(s + ".trash", ios::binary | ios::in | ios::out);
	if (!trash.is_open()) {
		trash.open(s + ".trash", ios::binary | ios::out);
		top = 0;
		trash.seekp(0);
		trash.write(reinterpret_cast<char *> (&top), sizeof(top));
		trash.close();
		trash.open(s + "trash", ios::binary | ios::in | ios::out);
	}

	file.read(reinterpret_cast<char *> (&num), sizeof(num));
	file.read(reinterpret_cast<char *> (&head), sizeof(head));
	file.read(reinterpret_cast<char *> (&tail), sizeof(tail));

	trash.read(reinterpret_cast<char *> (&top), sizeof(top));
}

template<class T>
database<T>::~database()
{
	file.seekp(0);
	file.write(reinterpret_cast<char *> (&num), sizeof(num));
	file.write(reinterpret_cast<char *> (&head), sizeof(head));
	file.write(reinterpret_cast<char *> (&tail), sizeof(tail));

	trash.seekp(0);
	trash.write(reinterpret_cast<char *> (&top), sizeof(top));

	file.close();
	trash.close();
}

template<class T>
int database<T>::get_num()
{
	return num;
}

template<class T>
int database<T>::get_next(int pos) {
	int nxt;
	file.seekg(pos);
	file.read(reinterpret_cast<char *> (&nxt), sizeof(nxt));
	return nxt;
}

template<class T>
int database<T>::get_size(int pos) {
	int size;
	file.seekg(pos + sizeof(int));
	file.read(reinterpret_cast<char *> (&size), sizeof(size));
	return size;
}

template<class T>
void database<T>::set_next(int pos, int nxt) {
	file.seekp(pos);
	file.write(reinterpret_cast<char *> (&nxt), sizeof(nxt));
}

template<class T>
void database<T>::set_size(int pos, int size) {
	file.seekp(pos + sizeof(int));
	file.write(reinterpret_cast<char *> (&size), sizeof(size));
}

template<class T>
int database<T>::getnew() {
	if (true) {
		int t = tail;
		tail += sizeof(int) * 2 + sizeof(T) * B;
		file.seekp(t);
		int blank = 0;
		file.write(reinterpret_cast<char *> (&blank), sizeof(blank));
		file.write(reinterpret_cast<char *> (&blank), sizeof(blank));
		return t;
	}
	else {
		trash.seekg(top * sizeof(int));
		int t;
		trash.read(reinterpret_cast<char *> (&t), sizeof(t));
		file.seekp(t);
		int blank = 0;
		file.write(reinterpret_cast<char *> (&blank), sizeof(blank));
		file.write(reinterpret_cast<char *> (&blank), sizeof(blank));
		--top;
		return t;
	}
}

template<class T>
int database<T>::get(const T &x) {
	int tmp = head, pre = head, nxt;
	T fr;
	while (tmp != 0) {
		nxt = get_next(tmp);
		file.seekg(tmp + sizeof(int) * 2);
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
int database<T>::get_(const T &x)
{
	int tmp = head, pre = head, nxt;
	T fr;
	while (tmp != 0) {
		nxt = get_next(tmp);
		file.seekg(tmp + sizeof(int) * 2);
		file.read(reinterpret_cast<char *> (&fr), sizeof(fr));
		if (x < fr || x == fr) return pre;
		else {
			pre = tmp;
			tmp = nxt;
		}
	}

	if (tmp == 0) return pre;
}

template<class T>
int database<T>::get_pos_in_block(int pos, const T &x)
{
	if (pos == -1) pos = get(x);
	int size = get_size(pos);
	T a;
	file.seekg(pos + sizeof(int) * 2);
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (x == a) return i;
	}
	return -1;
}

template<class T>
void database<T>::move(int l1, int r1, int l2, int r2, int flag) {
	int t1, t2; T x;
	if (flag == 0) {
		int t1 = r1 - sizeof(T), t2 = r2 - sizeof(T);
		while (t1 >= l1 && t2 >= l2) {
			file.seekg(t1);
			file.read(reinterpret_cast<char *> (&x), sizeof(x));
			file.seekp(t2);
			file.write(reinterpret_cast<char *> (&x), sizeof(x));
			t1 -= sizeof(T); t2 -= sizeof(T);
		}
	}
	else {
		t1 = l1; t2 = l2;
		while (t1 < r1 && t2 < r2) {
			file.seekg(t2);
			file.read(reinterpret_cast<char *> (&x), sizeof(x));
			file.seekp(t1);
			file.write(reinterpret_cast<char *> (&x), sizeof(x));
			t1 += sizeof(T); t2 += sizeof(T);
		}
	}
}

template<class T>
void database<T>::insert(int pos, const T &x) {
	int size = get_size(pos);
	T a;
	file.seekg(pos + 2 * sizeof(int));
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (x < a) {
			move(pos + sizeof(int) * 2 + sizeof(T) * i, pos + sizeof(int) * 2 + sizeof(T) * size, pos + sizeof(int) * 2 + sizeof(T) * (i + 1), pos + sizeof(int) * 2 + sizeof(T) * (size + 1), 0);
			file.seekp(pos + sizeof(int) * 2 + sizeof(T) * i);
			file.write(reinterpret_cast<const char *> (&x), sizeof(x));
			set_size(pos, size + 1);
			return;
		}
	}

	file.seekp(pos + sizeof(int) * 2 + sizeof(T) * size);
	file.write(reinterpret_cast<const char *> (&x), sizeof(x));
	set_size(pos, size + 1);
}

template<class T>
void database<T>::add(const T &x) {
	++num;
	if (head == 0) {
		head = getnew();
		set_next(head, 0);
		set_size(head, 1);
		file.seekp(head + sizeof(int) * 2);
		file.write(reinterpret_cast<const char *> (&x), sizeof(x));
		return;
	}
	int pos = get(x);
	int nxt = get_next(pos), size = get_size(pos);

	if (size == B) {
		int newpos = getnew();
		move(pos + sizeof(int) * 2 + sizeof(T) * B / 2, pos + sizeof(int) * 2 + sizeof(T) * B, newpos + sizeof(int) * 2, newpos + sizeof(int) * 2 + sizeof(T) * B / 2, 0);
		size /= 2;
		set_next(newpos, nxt);
		set_size(newpos, size);
		set_next(pos, newpos);
		set_size(pos, size);
		T a;
		file.seekg(newpos + sizeof(int) * 2);
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (x < a) {
			insert(pos, x);
		}
		else {
			insert(newpos, x);
		}
	}
	else {
		insert(pos, x);
	}
	//cout << "next(head) = " << get_next(head) << endl;
}

template<class T>
int database<T>::get_pre(int pos) {
	int tmp = head, t;
	while ((t = get_next(tmp)) != pos) {
		tmp = t;
	}
	return tmp;
}

template<class T>
void database<T>::del(int pos) {
	if (pos == head) {
		head = get_next(pos);
		trash.seekp((++top) * sizeof(int));
		trash.write(reinterpret_cast<char *> (&pos), sizeof(pos));
	}
	else {
		int pre = get_pre(pos);
		set_next(pre, get_next(pos));
		trash.seekp((++top) * sizeof(int));
		trash.write(reinterpret_cast<char *> (&pos), sizeof(pos));
	}
}

template<class T>
void database<T>::rem(int pos, const T &x) {
	int size = get_size(pos);
	T a;
	file.seekg(pos + 2 * sizeof(int));
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (a == x) {
			move(pos + sizeof(int) * 2 + sizeof(T) * i, pos + sizeof(int) * 2 + sizeof(T) * (size - 1), pos + sizeof(int) * 2 + sizeof(T) * (i + 1), pos + sizeof(int) * 2 + sizeof(T) * size, 1);
			set_size(pos, --size);
			--num;
			if (size == 0) del(pos);
			return;
		}
	}
	puts("Invalid");
}

template<class T>
void database<T>::remove(const T &x) {
	int pos = get(x);
	rem(pos, x);
}

template<class T>
void database<T>::change(const T &x)
{
	int pos = get(x); int size = get_size(pos);
	static T a;
	file.seekg(pos + sizeof(int) * 2);
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (a == x) {
			file.seekp(pos + sizeof(int) * 2 + sizeof(T) * i);
			file.write(reinterpret_cast<const char *> (&x), sizeof(x));
		}
	}
}

template<class T>
const T &database<T>::get_acc(const T &x)
{
	int pos = get(x); int size = get_size(pos);
	static T a;
	file.seekg(pos + sizeof(int) * 2);
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (a == x) return a;
	}
	a.make_fail();
	return a;
}

template<class T>
void database<T>::make_print()
{
	int pos = head, nxt, size;
	T x;
	while (pos) {
		nxt = get_next(pos);
		size = get_size(pos);
		file.seekg(pos + sizeof(int) * 2);
		for (int i = 0; i < size; ++i) {
			file.read(reinterpret_cast<char *> (&x), sizeof(x));
			x.print();
		}
		pos = nxt;
	}
}

template<class T>
void database<T>::make_print(const T &x)
{
	int pos = get_(x);
	int tmp = get_pos_in_block(pos, x), size;
	T a;
	if (tmp == -1) pos = get_next(pos);
	while (pos) {
		size = get_size(pos);
		tmp = get_pos_in_block(pos, x);
		file.seekg(pos + sizeof(int) * 2 + sizeof(T) * tmp);
		for (int i = tmp; i < size; ++i) {
			file.read(reinterpret_cast<char *> (&a), sizeof(a));
			if (a == x) a.print();
			else return;
		}
		pos = get_next(pos);
	}
}
