#pragma once

#include<string>
#include<fstream>
#include "database.h"
using namespace std;

class usersys
{
public:
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
		user(const string &, const string &, int, const string &);
		user(const string &, const string &, const string &, const string &);

		char user_id[30], passwd[30], name[20], level;
		bool operator<(const user &) const;
		bool operator==(const user &) const;

		void set_user_id(const string &);
		void set_passwd(const string &);
		void set_name(const string &);
		void set_level(const string &);
		void set_level(int);
		void make_fail();
	};

	database<user> u;

	user cur;
};
