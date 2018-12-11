#include "booksys.h"



booksys::booksys() : _ISBN("ISBN_file"), _name("name_file"), _author("author_file"), _keyword("keyword_file")
{
	cur.quantity = -1;
}


booksys::~booksys()
{
}

void booksys::select(const string &ISBN_str)
{
	book_ISBN a();
}

void booksys::set_ISBN(const string &)
{
}

void booksys::set_name(const string &)
{
}

void booksys::set_author(const string &)
{
}

void booksys::set_keyword(const string &)
{
}

void booksys::set_price(const string &)
{
}

void booksys::importt(int, double)
{
}

void booksys::show_all()
{
}

void booksys::show_finance_all()
{
}

void booksys::show_finance(int)
{
}

void booksys::show_ISBN(const string &)
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

bool booksys::book_author::operator<(const book_author & a) const
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

booksys::book_base::book_base(const string &a = "")
{
	for (int i = 0; i < a.size(); ++i) ISBN[i] = a[i];
	for (int i = a.size(); i < 20; ++i) ISBN[i] = 0;
	memset(name, 0, sizeof(name));
	memset(author, 0, sizeof(author));
	memset(keyword, 0, sizeof(keyword));
	quantity = 0;
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

void booksys::book_base::copy(const book_base &a)
{
	memcpy(ISBN, a.ISBN, 20);
	memcpy(name, a.name, 40);
	memcpy(author, a.author, 40);
	memcpy(keyword, a.keyword, 40);
	quantity = a.quantity;
}
