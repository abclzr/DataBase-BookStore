#include "booksys.h"



booksys::booksys() : _ISBN("ISBN_file"), _name("name_file"), _author("author_file"), _keyword("keyword_file")
{
	cur.quantity = -1;
}


booksys::~booksys()
{
}

void booksys::delete_all(const book_base &x) {
	_ISBN.remove(x);
	_name.remove(x);
	_author.remove(x);
	//_keyword.remove(x);
}

void booksys::add_all(const book_base &x)
{
	_ISBN.add(x);
	_name.add(x);
	_author.add(x);
	//_keyword.add(x);
}

void booksys::select(const string &ISBN_str)
{
	book_ISBN x; x.set_ISBN(ISBN_str);
	changes = _ISBN.get_acc(x);
	cur = changes;
	if (changes.quantity != -1) delete_all(cur);
	else changes.quantity = 0;
}

void booksys::set_ISBN(const string &str)
{
	changes.set_ISBN(str);
}

void booksys::set_name(const string &str)
{
	changes.set_name(str);
}

void booksys::set_author(const string &str)
{
	changes.set_author(str);
}

void booksys::set_keyword(const string &str)
{
	changes.set_keyword(str);
}

void booksys::set_price(const string &str)
{
	changes.set_price(str);
}

void booksys::push()
{
	add_all(changes);
}

void booksys::importt(int, double)
{

}

void booksys::show_all()
{
	_ISBN.make_print();
}

void booksys::show_finance_all()
{
}

void booksys::show_finance(int)
{
}

void booksys::show_ISBN(const string &str)
{

}

void booksys::show_name(const string &)
{
}

void booksys::show_author(const string &)
{
}

void booksys::show_keyword(const string &)
{
}

void booksys::buy(const string &, int)
{
}

booksys::book_ISBN::book_ISBN() : booksys::book_base()
{
}

booksys::book_ISBN::book_ISBN(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_ISBN::operator<(const book_ISBN & a) const
{
	for (int i = 0; i < 20; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_ISBN::operator==(const book_ISBN & a) const
{
	for (int i = 0; i < 20; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_ISBN::operator=(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, 20);
	memcpy((void *) name, a.name, 40);
	memcpy((void *) author, a.author, 40);
	memcpy((void *) keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

booksys::book_name::book_name() : booksys::book_base()
{
}

booksys::book_name::book_name(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_name::operator<(const book_name & a) const
{
	for (int i = 0; i < 40; ++i) {
		if (name[i] < a.name[i]) return true;
		else if (name[i] > a.name[i]) return false;
	}
	for (int i = 0; i < 20; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_name::operator==(const book_name & a) const
{
	for (int i = 0; i < 40; ++i) if (name[i] != a.name[i]) return false;
	for (int i = 0; i < 20; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_name::operator=(const book_base &a)
{
	memcpy((void *) ISBN, a.ISBN, 20);
	memcpy((void *) name, a.name, 40);
	memcpy((void *) author, a.author, 40);
	memcpy((void *) keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

booksys::book_author::book_author() : booksys::book_base()
{
}

booksys::book_author::book_author(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_author::operator<(const book_author &a) const
{
	for (int i = 0; i < 40; ++i) {
		if (author[i] < a.author[i]) return true;
		else if (author[i] > a.author[i]) return false;
	}
	for (int i = 0; i < 20; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_author::operator==(const book_author & a) const
{
	for (int i = 0; i < 40; ++i) if (author[i] != a.author[i]) return false;
	for (int i = 0; i < 20; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_author::operator=(const book_base &a)
{ 
	memcpy((void *) ISBN, a.ISBN, 20);
	memcpy((void *) name, a.name, 40);
	memcpy((void *) author, a.author, 40);
	memcpy((void *) keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

booksys::book_keyword::book_keyword() : booksys::book_base()
{
}

booksys::book_keyword::book_keyword(const book_base &a)
{
	(*this) = a;
}

bool booksys::book_keyword::operator<(const book_keyword & a) const
{
	for (int i = 0; i < 40; ++i) {
		if (keyword[i] < a.keyword[i]) return true;
		else if (keyword[i] > a.keyword[i]) return false;
	}
	for (int i = 0; i < 20; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_keyword::operator==(const book_keyword & a) const
{
	for (int i = 0; i < 40; ++i) if (keyword[i] != a.keyword[i]) return false;
	for (int i = 0; i < 20; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_keyword::operator=(const book_base &a)
{
	memcpy((void *)ISBN, a.ISBN, 20);
	memcpy((void *)name, a.name, 40);
	memcpy((void *)author, a.author, 40);
	memcpy((void *)keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

booksys::book_base::book_base()
{
	memset(ISBN, 0, sizeof(ISBN));
	memset(name, 0, sizeof(name));
	memset(author, 0, sizeof(author));
	memset(keyword, 0, sizeof(keyword));
	quantity = 0;
	price = 0;
}

booksys::book_base::book_base(const book_base &a)
{
	memcpy((void *)ISBN, a.ISBN, 20);
	memcpy((void *)name, a.name, 40);
	memcpy((void *)author, a.author, 40);
	memcpy((void *)keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

bool booksys::book_base::operator<(const book_base &a) const
{
	for (int i = 0; i < 20; ++i) {
		if (ISBN[i] < a.ISBN[i]) return true;
		else if (ISBN[i] > a.ISBN[i]) return false;
	}
	return false;
}

bool booksys::book_base::operator==(const book_base &a) const
{
	for (int i = 0; i < 20; ++i) if (ISBN[i] != a.ISBN[i]) return false;
	return true;
}

void booksys::book_base::operator=(const book_base &a)
{
	memcpy(ISBN, a.ISBN, 20);
	memcpy(name, a.name, 40);
	memcpy(author, a.author, 40);
	memcpy(keyword, a.keyword, 40);
	quantity = a.quantity;
	price = a.price;
}

void booksys::book_base::make_fail()
{
	quantity = -1;
}

void booksys::book_base::set_ISBN(const string &a)
{
	for (int i = 0; i < a.size(); ++i) ISBN[i] = a[i];
	for (int i = a.size(); i < 20; ++i) ISBN[i] = 0;
}

void booksys::book_base::set_name(const string &a)
{
	for (int i = 0; i < a.size(); ++i) name[i] = a[i];
	for (int i = a.size(); i < 40; ++i) name[i] = 0;
}

void booksys::book_base::set_author(const string &a)
{
	for (int i = 0; i < a.size(); ++i) author[i] = a[i];
	for (int i = a.size(); i < 40; ++i) author[i] = 0;
}

void booksys::book_base::set_keyword(const string &a)
{
	for (int i = 0; i < a.size(); ++i) keyword[i] = a[i];
	for (int i = a.size(); i < 40; ++i) keyword[i] = 0;
}

void booksys::book_base::set_price(const string &str)
{
	istringstream ss(str);
	ss >> price;
}

void booksys::book_base::print()
{
	printf("%s\t%s\t%s\t%s\t%lf\t%d±¾\n", ISBN, name, author, keyword, price, quantity);
}

