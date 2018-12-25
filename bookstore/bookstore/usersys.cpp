#include "usersys.h"

usersys::usersys() : u("user_file"), u_o("user_log")
{
	if (u.get_num() == 0)
		u.add(user("root", "sjtu", 7, "yyu"));
	ifstream in("current_user", ios::binary | ios::in);
	if (in.is_open()) in.read(reinterpret_cast<char *> (&cur), sizeof(cur));
	else cur = user("root", "sjtu", 7, "yyu");
}

usersys::~usersys()
{
	ofstream of("current_user", ios::binary | ios::out);
	of.write(reinterpret_cast<char *> (&cur), sizeof(cur));
}

int usersys::level()
{
	return cur.level;
}

void usersys::login(const string &id)
{
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	cur = x;
}

void usersys::login(const string &id, const string &pas)
{
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	if (!the_same(x.passwd, N1, pas)) { puts("Invalid"); return; }
	else cur = x;
}

void usersys::logout()
{
	cur.level = 0;
}

void usersys::useradd(const string &id, const string &pas, const string &lev, const string &na)
{
	user x = user(id, pas, lev, na);
	if (x.level >= cur.level) { puts("Invalid"); return; }
	if (u.exist(x)) { puts("Invalid"); return; }
	u.add(x);

	u_o.add(user_operations(cur.user_id, " add user: " + id));
}

void usersys::registerr(const string &id, const string &pas, const string &na)
{
	user x = user(id, pas, 1, na);
	u.add(x);

	u_o.add(user_operations(id, " is registered!"));
}

void usersys::deletee(const string &id)
{
	user a(id);
	u.remove(a);

	u_o.add(user_operations(id, " is removed!"));
}

void usersys::passwd(const string &id, const string &pas)
{
	if (cur.level != 7) { puts("Invalid"); return; }
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	x.set_passwd(pas);
	u.change(x);
	u_o.add(user_operations(id, "\'s password is changed!"));
}

void usersys::passwd(const string &id, const string &oldpas, const string &pas)
{
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	if (!the_same(x.passwd, N1, oldpas)) { puts("Invalid"); return; }
	x.set_passwd(pas);
	u.change(x);
	u_o.add(user_operations(id, "\'s password is changed!"));
}

bool usersys::the_same(const char *c, int len, const string &a)
{
	if (a.size() > len) return false;
	for (int i = 0; i < a.size(); ++i) if (c[i] != a[i]) return false;
	for (int i = a.size(); i < len; ++i) if (c[i] != 0) return false;
	return true;
}

void usersys::show()
{
	u.make_print();
}

string usersys::tostring(int num)
{
	string a;
	stringstream f;
	f << num;
	f >> a;
	return a;
}

string usersys::tostring(double num)
{
	string a;
	stringstream f;
	f << num;
	f >> a;
	return a;
}

void usersys::importt(int num, double price)
{
	u_o.add(user_operations(cur.user_id, " import " + tostring(num) + " books, and spend " + tostring(num) + " yuan!"));
}

void usersys::buy(const string &str, int n)
{
	u_o.add(user_operations(cur.user_id, " buy " + tostring(n) + " books of " + str));
}

void usersys::show_user_operation_detail()
{
	cout << "¨u¨w¨v" << endl;
	cout << "¨v¨w¨n©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤" << endl;
	u_o.make_print();
	cout << "¨u¨w¨v" << endl;
	cout << "¨v¨w¨n©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤" << endl;
}

void usersys::show_myself_operation_detail()
{
	cout << "¨u¨w¨v" << endl;
	cout << "¨v¨w¨n©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤" << endl;
	u_o.make_print(user_operations(cur.user_id, ""));
	cout << "¨u¨w¨v" << endl;
	cout << "¨v¨w¨n©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤" << endl;
}

usersys::user::user()
{
	memset(user_id, 0, sizeof(user_id));
	memset(passwd, 0, sizeof(passwd));
	memset(name, 0, sizeof(name));
	level = 0;
}

usersys::user::user(const string &id)
{
	set_user_id(id);
	set_passwd("");
	set_level(0);
	set_name("");
}

usersys::user::user(const string &id, const string &pas, int lev, const string &na)
{
	set_user_id(id);
	set_passwd(pas);
	set_level(lev);
	set_name(na);
}

usersys::user::user(const string &id, const string &pas, const string &lev, const string &na)
{
	set_user_id(id);
	set_passwd(pas);
	set_level(lev);
	set_name(na);
}

bool usersys::user::operator<(const user & a) const
{
	for (int i = 0; i < N1; ++i)
		if (user_id[i] < a.user_id[i]) return true;
		else if (user_id[i] > a.user_id[i]) return false;
	return false;
}

bool usersys::user::operator==(const user &a) const
{
	for (int i = 0; i < N1; ++i)
		if (user_id[i] != a.user_id[i]) return false;
	return true;
}

void usersys::user::set_user_id(const string &a)
{
	for (int i = 0; i < a.size(); ++i) user_id[i] = a[i];
	for (int i = a.size(); i < N1; ++i) user_id[i] = 0;
}

void usersys::user::set_passwd(const string &a)
{
	for (int i = 0; i < a.size(); ++i) passwd[i] = a[i];
	for (int i = a.size(); i < N1; ++i) passwd[i] = 0;
}

void usersys::user::set_name(const string &a)
{
	for (int i = 0; i < a.size(); ++i) name[i] = a[i];
	for (int i = a.size(); i < N2; ++i) name[i] = 0;
}

void usersys::user::set_level(const string &a)
{
	if (a == "0") this->level = 0;
	else if (a == "1") level = 1;
	else if (a == "3") level = 3;
	else if (a == "7") level = 7;
}

void usersys::user::set_level(int a)
{
	level = a;
}

void usersys::user::make_fail()
{
	level = 0;
}

void usersys::user::print()
{
	cout << "the user id = " << user_id << endl;
}

usersys::user_operations::user_operations()
{
	memset(user_id, 0, sizeof(user_id));
	memset(ope, 0, sizeof(ope));
}

usersys::user_operations::user_operations(const string &strusr, const string &strope)
{
	memset(user_id, 0, sizeof(user_id));
	memset(ope, 0, sizeof(ope));
	for (int i = 0; i < strusr.size(); ++i)
		user_id[i] = strusr[i];
	for (int i = 0; i < strope.size(); ++i)
		ope[i] = strope[i];
}

void usersys::user_operations::print() const
{
	printf("%s", user_id);  puts(ope);
}

bool operator<(const usersys::user_operations &a, const usersys::user_operations &b)
{
	for (int i = 0; i < usersys::N1; ++i) {
		if (a.user_id[i] < b.user_id[i]) return true;
		else if (a.user_id[i] > b.user_id[i]) return false;
	}
	return false;
}

bool operator==(const usersys::user_operations &a, const usersys::user_operations &b)
{
	for (int i = 0; i < usersys::N1; ++i)
		if (a.user_id[i] != b.user_id[i]) return false;
	return true;
}
