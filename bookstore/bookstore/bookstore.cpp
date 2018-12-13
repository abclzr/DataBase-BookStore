#include<map>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;

#include "usersys.h"
#include "booksys.h"

void error() { puts("Invalid"); }

int to_int(string &s) {
	istringstream ss(s);
	int x;
	ss >> x;
	return x;
}

double to_double(string &s) {
	istringstream ss(s);
	double x;
	ss >> x;
	return x;
}

int get_command_num(string s) {
	if (s == "exit") return -1;
	if (s == "su") return 0;
	if (s == "logout") return 1;
	if (s == "useradd") return 2;
	if (s == "register") return 3;
	if (s == "delete") return 4;
	if (s == "passwd") return 5;
	if (s == "select") return 6;
	if (s == "modify") return 7;
	if (s == "import") return 8;
	if (s == "show") return 9;
	if (s == "buy") return 10;
	if (s == "load") return 11;
	if (s == "report") return 12;
	if (s == "log") return 13;
	return 14;
}

booksys book;
usersys user;
ifstream in;

bool run(string &cmd) {
	vector<string> c;
	int p = cmd.find(" ");
	while (p != string::npos) {
		c.push_back(cmd.substr(0, p));
		cmd = cmd.substr(p + 1, cmd.size() - p - 1);
	}
	c.push_back(cmd);

	int op = get_command_num(c[0]);
	switch (op) {
	case -1://exit
		return false;
		break;
	case 0://login
		if (c.size() < 2 || c.size() > 3) error();
		else {
			if (c.size() == 2) user.login(c[1]);
			else user.login(c[1], c[2]);
		}
		break;
	case 1://logout
		if (c.size() > 1 || user.level() < 1) error();
		else user.logout();
		break;
	case 2://useradd
		if (c.size() != 5 || user.level < 3) error();
		else user.useradd(c[1], c[2], c[3], c[4]);
		break;
	case 3://register
		if (c.size() != 4) error();
		else user.registerr(c[1], c[2], c[3]);
		break;
	case 4://delete
		if (c.size() != 2 || user.level() < 7) error();
		else user.deletee(c[1]);
		break;
	case 5://passwd
		if (c.size() < 3 || c.size() > 4 || user.level() < 1) error();
		else {
			if (c.size() == 3) user.passwd(c[1], c[2]);
			else user.passwd(c[1], c[2], c[3]);
		}
		break;
	case 6://select
		if (c.size() != 2 || user.level() < 3) error();
		else book.select(c[1]);
		break;
	case 7://modify
		if (c.size() < 2 || user.level() < 3) error();
		else {
			book.pull();
			for (int i = 1; i < c.size(); ++i) {
				string s = c[i];
				if (s[0] != '-') { error(); break; }
				int findequ = s.find("=");
				if (findequ == string::npos) { error(); break; }
				string id = s.substr(1, findequ - 1);
				string changed = s.substr(findequ + 1, s.size() - findequ - 1);

				if (id == "ISBN") book.set_ISBN(changed);
				else if (id == "name") book.set_name(changed.substr(1, changed.size() - 2));
				else if (id == "author") book.set_author(changed.substr(1, changed.size() - 2));
				else if (id == "keyword") book.set_keyword(changed.substr(1, changed.size() - 2));
				else if (id == "price") book.set_price(changed);
				else {
					error();
					break;
				}
			}
			book.push();
		}
		break;
	case 8:
		if (c.size() != 3 || user.level() < 3) error();
		else book.importt(to_int(c[1]), to_double(c[2]));
		break;
	case 9://show
		if (c.size() == 1) {
			if (user.level() < 1) { error(); break; }
			book.show_all();
		}
		else {
			if (c[1] == "finance") {
				if (c.size() == 2) book.show_finance_all();
				else {
					if (c.size() != 3) error();
					else book.show_finance(to_int(c[2]));
				}
			}
			else {
				if (c.size() != 2) { error(); break; }
				string s = c[1];
				if (s[0] != '-') { error(); break; }
				int p = s.find("=");
				if (p == string::npos) { error(); break; }
				string id = s.substr(1, p - 1);
				string changed = s.substr(p + 1, s.size() - p - 1);

				if (id == "ISBN") book.show_ISBN(changed);
				else if (id == "name") book.show_name(changed.substr(1, changed.size() - 2));
				else if (id == "author") book.show_author(changed.substr(1, changed.size() - 2));
				else if (id == "keyword") book.show_keyword(changed.substr(1, changed.size() - 2));
				else {
					error();
					break;
				}
			}
		}
		break;
	case 10://buy
		if (c.size() != 3 || user.level() < 1) error();
		else book.buy(c[1], to_int(c[2]));
		break;
	case 11://load
		in.open(c[1]);
		break;
	case 12://report
		break;
	case 13://log
		break;
	case 14:
		error();
		break;
	}
	return true;
}

int main() {
	string cmd;
	in.open("command.txt");

	while (true) {
		if (in.is_open()) getline(in, cmd);
		else getline(cin, cmd);

		if (!run(cmd)) {
			return 0;
		}

		if (in.is_open() && in.eof()) in.close();
	}

	return 0;
}