#include "booksys.h"



booksys::booksys() : _ISBN("ISBN_file"), _name("name_file"), _author("author_file"), _keyword("keyword_file"), finance("finance_file")
{
	cur.quantity = -1;
}


booksys::~booksys()
{
}

bool booksys::exist_ISBN(const string &str)
{
	book_ISBN x(str);
	return _ISBN.exist(x);
}

bool booksys::select_empty()
{
	return cur.quantity == -1;
}

void booksys::delete_all(const book_base &x) {
	_ISBN.remove(x);
	_name.remove(x);
	_author.remove(x);
	//_keyword.remove(x);
	book_keyword a = x;
	string str = x.keyword;
	int p;
	while ((p = str.find("|")) != string::npos) {
		a.set_keyword(str.substr(0, p));
		_keyword.remove(a);
		str = str.substr(p + 1, str.size() - p - 1);
	}
	a.set_keyword(str);
	_keyword.remove(a);
}

void booksys::add_all(const book_base &x)
{
	_ISBN.add(x);
	_name.add(x);
	_author.add(x);
	//_keyword.add(x);
	book_keyword a = x;
	string str = x.keyword;
	int p;
	while ((p = str.find("|")) != string::npos) {
		a.set_keyword(str.substr(0, p));
		_keyword.add(a);
		str = str.substr(p + 1, str.size() - p - 1);
	}
	a.set_keyword(str);
	_keyword.add(a);
}

void booksys::select(const string &ISBN_str)
{
	book_ISBN x(ISBN_str);
	cur = _ISBN.get_acc(x);
	if (cur.quantity == -1) {
		cur = x;
		cur.quantity = -2;
	}
}

void booksys::pull() {
	if (cur.quantity != -2) delete_all(cur);
	else cur.quantity = 0;
}

void booksys::set_ISBN(const string &str)
{
	cur.set_ISBN(str);
}

void booksys::set_name(const string &str)
{
	cur.set_name(str);
}

void booksys::set_author(const string &str)
{
	cur.set_author(str);
}

void booksys::set_keyword(const string &str)
{
	cur.set_keyword(str);
	cur.set_true_key(str);
}

void booksys::set_price(const string &str)
{
	cur.set_price(str);
}

void booksys::push()
{
	add_all(cur);
}

void booksys::importt(int num, double price)
{
	pull();
	cur.quantity += num;
	push();

	finance.lose(price);
}

void booksys::show_all()
{
	_ISBN.make_print();
}

void booksys::show_finance_all()
{
	finance.show();
}

void booksys::show_finance(int times)
{
	finance.show(times);
}

void booksys::show_ISBN(const string &str)
{
	book_ISBN x(str);
	_ISBN.make_print(x);
}

void booksys::show_name(const string &str)
{
	book_name x(str);
	x.ignoreISBN = true;
	_name.make_print(x);
}

void booksys::show_author(const string &str)
{
	book_author x(str);
	x.ignoreISBN = true;
	_author.make_print(x);
}

void booksys::show_keyword(const string &str)
{
	book_keyword x(str);
	x.ignoreISBN = true;
	_keyword.make_print(x);
}

void booksys::buy(const string &str, int num)
{
	book_ISBN x(str);
	book_base a = _ISBN.get_acc(x);
	if (a.quantity == -1) { puts("Invalid"); return; }
	if (a.quantity < num) { puts("Invalid"); return; }
	delete_all(a);
	a.quantity -= num;
	add_all(a);

	finance.gain(num * a.price);
}

booksys::book_ISBN::book_ISBN() : book_base()
{
}

booksys::book_ISBN::book_ISBN(const string &a) : book_base()
{
	for (int i = 0; i < a.size(); ++i) ISBN[i] = a[i];
}

booksys::book_ISBN::book_ISBN(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_ISBN::operator<(const book_ISBN & a) const
{
	for (int i = 0; i < N1; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_ISBN::operator==(const book_ISBN & a) const
{
	for (int i = 0; i < N1; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_ISBN::operator=(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, N1);
	memcpy((void *) name, a.name, N2);
	memcpy((void *) author, a.author, N2);
	memcpy((void *) keyword, a.keyword, N2);
	memcpy((void *) true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = false;
}

booksys::book_name::book_name() : book_base()
{
}

booksys::book_name::book_name(const string &a) : book_base()
{
	for (int i = 0; i < a.size(); ++i) name[i] = a[i];
}

booksys::book_name::book_name(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_name::operator<(const book_name & a) const
{
	for (int i = 0; i < N2; ++i) {
		if (name[i] < a.name[i]) return true;
		else if (name[i] > a.name[i]) return false;
	}
	if (ignoreISBN || a.ignoreISBN) return false;

	for (int i = 0; i < N1; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_name::operator==(const book_name &a) const
{
	for (int i = 0; i < N2; ++i) if (name[i] != a.name[i]) return false;
	if (ignoreISBN || a.ignoreISBN) return true;

	for (int i = 0; i < N1; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_name::operator=(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, N1);
	memcpy((void *) name, a.name, N2);
	memcpy((void *) author, a.author, N2);
	memcpy((void *) keyword, a.keyword, N2);
	memcpy((void *) true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = a.ignoreISBN;
}

booksys::book_author::book_author() : book_base()
{
}

booksys::book_author::book_author(const string &a) : book_base()
{
	for (int i = 0; i < a.size(); ++i) author[i] = a[i];
}

booksys::book_author::book_author(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_author::operator<(const book_author &a) const
{
	for (int i = 0; i < N2; ++i) {
		if (author[i] < a.author[i]) return true;
		else if (author[i] > a.author[i]) return false;
	}
	if (ignoreISBN || a.ignoreISBN) return false;

	for (int i = 0; i < N1; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_author::operator==(const book_author & a) const
{
	for (int i = 0; i < N2; ++i) if (author[i] != a.author[i]) return false;
	if (ignoreISBN || a.ignoreISBN) return true;

	for (int i = 0; i < N1; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_author::operator=(const book_base &a)
{ 
	memcpy((void *) ISBN, a.ISBN, N1);
	memcpy((void *) name, a.name, N2);
	memcpy((void *) author, a.author, N2);
	memcpy((void *) keyword, a.keyword, N2);
	memcpy((void *) true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = a.ignoreISBN;
}

booksys::book_keyword::book_keyword() : book_base()
{
}

booksys::book_keyword::book_keyword(const string &a) : book_base()
{
	for (int i = 0; i < a.size(); ++i) keyword[i] = a[i];
}

booksys::book_keyword::book_keyword(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_keyword::operator<(const book_keyword &a) const
{
	for (int i = 0; i < N2; ++i) {
		if (keyword[i] < a.keyword[i]) return true;
		else if (keyword[i] > a.keyword[i]) return false;
	}
	if (ignoreISBN || a.ignoreISBN) return false;

	for (int i = 0; i < N1; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_keyword::operator==(const book_keyword &a) const
{
	for (int i = 0; i < N2; ++i) if (keyword[i] != a.keyword[i]) return false;
	if (ignoreISBN || a.ignoreISBN) return true;

	for (int i = 0; i < N1; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_keyword::operator=(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, N1);
	memcpy((void *) name, a.name, N2);
	memcpy((void *) author, a.author, N2);
	memcpy((void *) keyword, a.keyword, N2);
	memcpy((void *) true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = a.ignoreISBN;
}

booksys::book_base::book_base()
{
	memset(ISBN, 0, sizeof(ISBN));
	memset(name, 0, sizeof(name));
	memset(author, 0, sizeof(author));
	memset(keyword, 0, sizeof(keyword));
	memset(true_key, 0, sizeof(true_key));
	quantity = 0;
	price = 0;
	ignoreISBN = false;
}

booksys::book_base::book_base(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, N1);
	memcpy((void *) name, a.name, N2);
	memcpy((void *) author, a.author, N2);
	memcpy((void *) keyword, a.keyword, N2);
	memcpy((void *) true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = a.ignoreISBN;
}

bool booksys::book_base::operator<(const book_base &a) const
{
	for (int i = 0; i < N1; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_base::operator==(const book_base &a) const
{
	for (int i = 0; i < N1; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_base::operator=(const book_base &a)
{
	memcpy(ISBN, a.ISBN, N1);
	memcpy(name, a.name, N2);
	memcpy(author, a.author, N2);
	memcpy(keyword, a.keyword, N2);
	memcpy(true_key, a.true_key, N2);
	quantity = a.quantity;
	price = a.price;
	ignoreISBN = a.ignoreISBN;
}

void booksys::book_base::make_fail()
{
	quantity = -1;
}

void booksys::book_base::set_ISBN(const string &a)
{
	for (int i = 0; i < a.size(); ++i) ISBN[i] = a[i];
	for (int i = a.size(); i < N1; ++i) ISBN[i] = 0;
}

void booksys::book_base::set_name(const string &a)
{
	for (int i = 0; i < a.size(); ++i) name[i] = a[i];
	for (int i = a.size(); i < N2; ++i) name[i] = 0;
}

void booksys::book_base::set_author(const string &a)
{
	for (int i = 0; i < a.size(); ++i) author[i] = a[i];
	for (int i = a.size(); i < N2; ++i) author[i] = 0;
}

void booksys::book_base::set_keyword(const string &a)
{
	for (int i = 0; i < a.size(); ++i) keyword[i] = a[i];
	for (int i = a.size(); i < N2; ++i) keyword[i] = 0;
}

void booksys::book_base::set_true_key(const string &a)
{
	for (int i = 0; i < a.size(); ++i) true_key[i] = a[i];
	for (int i = a.size(); i < N2; ++i) true_key[i] = 0;
}

void booksys::book_base::set_price(const string &str)
{
	istringstream ss(str);
	ss >> price;
}

void booksys::book_base::print()
{
	printf("%s\t%s\t%s\t%s\t%.2lf\t%d±¾\n", ISBN, name, author, true_key, price, quantity);
}

