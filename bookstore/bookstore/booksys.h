#pragma once

#include<string>
#include<cstring>
#include<sstream>
#include "database.h"
#include "finance.h"

using namespace std;

class booksys
{
public:
	static const int N1 = 20;
	static const int N2 = 40;

	booksys();
	~booksys();

	//return whether has selected a book
	bool select_empty();

	//select a book;
	void select(const string &);

	//pull the selected book from the file
	void pull();

	//set the attributes
	void set_ISBN(const string &);
	void set_name(const string &);
	void set_author(const string &);
	void set_keyword(const string &);
	void set_price(const string &);

	//push the changes into the file
	void push();

	//import a book
	void importt(int, double);

	//show;
	void show_all();
	void show_finance_all();
	void show_finance(int);
	void show_ISBN(const string &);
	void show_name(const string &);
	void show_author(const string &);
	void show_keyword(const string &);

	//buy k books;
	void buy(const string &, int);

	class book_base {
	public:
		char ISBN[N1], name[N2], author[N2], keyword[N2];
		int quantity; double price;
		bool ignoreISBN;
		book_base();
		book_base(const book_base &);
		bool operator<(const book_base &) const;
		bool operator==(const book_base &) const;
		void operator=(const book_base &);
		void make_fail();
		void set_ISBN(const string &);
		void set_name(const string &);
		void set_author(const string &);
		void set_keyword(const string &);
		void set_price(const string &);
		void print();
	};

	class book_ISBN : public book_base {
	public:
		book_ISBN();
		book_ISBN(const string &);
		book_ISBN(const book_base &);
		bool operator<(const book_ISBN &) const;
		bool operator==(const book_ISBN &) const;
		void operator=(const book_base &);
	};

	class book_name : public book_base {
	public:
		book_name();
		book_name(const string &);
		book_name(const book_base &);
		bool operator<(const book_name &) const;
		bool operator==(const book_name &) const;
		void operator=(const book_base &);
	};

	class book_author : public book_base {
	public:
		book_author();
		book_author(const string &);
		book_author(const book_base &);
		bool operator<(const book_author &) const;
		bool operator==(const book_author &) const;
		void operator=(const book_base &);
	};

	class book_keyword : public book_base {
	public:
		book_keyword();
		book_keyword(const string &);
		book_keyword(const book_base &);
		bool operator<(const book_keyword &) const;
		bool operator==(const book_keyword &) const;
		void operator=(const book_base &);
	};

	//delete the book in all files
	void delete_all(const book_base &);
	
	//add the book in all files
	void add_all(const book_base &);

private:
	database<book_ISBN> _ISBN;
	database<book_name> _name;
	database<book_author> _author;
	database<book_author> _keyword;

	book_base cur;

	finance_base finance;
};

