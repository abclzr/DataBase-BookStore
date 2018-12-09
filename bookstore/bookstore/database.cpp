#include "database.h"
#include<fstream>
#include<string>

const int B = 100;

template<class T>
database<T>::database(std::string s)
{
	file.open(s);
	if (!file.is_open()) {
		file.open(s, ios::out);
		file.close();
		file.open(s);
	}
	trash.open(s + ".trash");
	if (!trash.is_open()) {
		trash.open(s + ".trash", ios::out);
		trash.close();
		trash.open(s + "trash");
	}

	file.read(reinterpret_cast<char *> (&num), sizeof(num));
	if (file.eof()) {
		num = 0;
		file.seekp(0);
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
		file.seekp(0);
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
			move(pos + sizeof(int) * 2 + sizeof(T) * i, pos + sizeof(int) * 2 + sizeof(T) * (size - 1), pos + sizeof(int) * 2 + sizeof(T) * (i + 1), pos + sizeof(int) * 2 + sizeof(T) * size, 0);
			file.seekp(pos + sizeof(int) * 2 + sizeof(T) * i);
			file.write(reinterpret_cast<char *> (&x), sizeof(x));
			set_size(size + 1);
			return;
		}
	}

	file.seekp(pos + sizeof(int) * 2 + sizeof(T) * size);
	file.write(reinterpret_cast<char *> (&x), sizeof(x));
	set_size(size + 1);
}

template<class T>
void database<T>::add(const T &x) {
	++num;
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
			if (size == 0) del(pos);
			return;
		}
	}
}

template<class T>
void database<T>::remove(const T &x) {
	int pos = get(x);
	rem(pos, x);
}

template<class T>
void database<T>::change(const T &x)
{
	int pos = find(x); int size = get_size(pos);
	static T a;
	file.seekg(pos + sizeof(int) * 2);
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (a == x) {
			file.seekp(pos + sizeof(int) * 2 + sizeof(T) * i);
			file.write(reinterpret_cast<char *> (&x), sizeof(x));
		}
	}
}

template<class T>
const T &database<T>::get_acc(const T &x) const {
	int pos = find(x); int size = get_size(pos);
	static T a;
	file.seekg(pos + sizeof(int) * 2);
	for (int i = 0; i < size; ++i) {
		file.read(reinterpret_cast<char *> (&a), sizeof(a));
		if (a == x) return a;
	}
	a.make_fail();
	return a;
}