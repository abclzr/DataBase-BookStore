#pragma once

#include<string>
#include<fstream>
#include "database.h"
using namespace std;

class usersys
{
public:
	static const int N1 = 30;
	static const int N2 = 20;

	usersys();
	~usersys();

	//return the level of the current user;
	int level();

	//login;
	void login(const string &);

	void login(const string &, const string &);

	//logout;
	void logout();

	//add a new user;
	void useradd(const string &, const string &, const string &, const string &);

	//register
	void registerr(const string &, const string &, const string &);

	//delete
	void deletee(const string &);

	//change password
	void passwd(const string &, const string &);

	void passwd(const string &, const string &, const string &);

	bool the_same(const char*, int, const string &);

	class user {
	public:
		user();
		user(const string &);
		user(const string &, const string &, int, const string &);
		user(const string &, const string &, const string &, const string &);

		char user_id[N1], passwd[N1], name[N2], level;
		bool operator<(const user &) const;
		bool operator==(const user &) const;

		void set_user_id(const string &);
		void set_passwd(const string &);
		void set_name(const string &);
		void set_level(const string &);
		void set_level(int);
		void make_fail();
		void print();
	};

	database<user> u;

	user cur;
};

