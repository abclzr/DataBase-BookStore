#pragma once

#include<string>
using namespace std;

class booksys
{
public:
	booksys();
	~booksys();

	//select a book;
	void select(const string &);

	//set the attributes
	void set_ISBN(const string &);
	void set_name(const string &);
	void set_author(const string &);
	void set_keyword(const string &);
	void set_price(const string &);

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
		char ISBN[20], name[40], author[40], keyword[40];
		int quantity;
	};

	class book_ISBN : book_base {
		bool operator<(const book_ISBN &a) const;
		bool operator==(const book_ISBN &a) const;
	};

	class book_name : book_base {
		bool operator<(const book_name &a) const;
		bool operator==(const book_name &a) const;
	};

	class book_author : book_base {
		bool operator<(const book_author &a) const;
		bool operator==(const book_author &a) const;
	};

	class book_keyword : book_base {
		bool operator<(const book_keyword &a) const;
		bool operator==(const book_keyword &a) const;
	};
};

