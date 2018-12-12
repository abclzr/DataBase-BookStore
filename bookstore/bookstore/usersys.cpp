#include "usersys.h"

usersys::usersys() : u("user_file")
{
	if (u.get_num() == 0)
		u.add(user("-1", "sjtu", 7, "root"));
	ifstream in("current_user");
	if (in.is_open()) in.read(reinterpret_cast<char *> (&cur), sizeof(cur));
	else cur.level = 0;
}

usersys::~usersys()
{
	ofstream of("current_user");
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
	if (!the_same(x.passwd, 30, pas)) { puts("Invalid"); return; }
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
	u.add(x);
}

void usersys::registerr(const string &id, const string &pas, const string &na)
{
	user x = user(id, pas, 1, na);
	u.add(x);
}

void usersys::deletee(const string &id)
{
	u.remove(user(id));
}

void usersys::passwd(const string &id, const string &pas)
{
	if (cur.level != 7) { puts("Invalid"); return; }
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	x.set_passwd(pas);
	u.change(x);
}

void usersys::passwd(const string &id, const string &oldpas, const string &pas)
{
	user x = u.get_acc(user(id));
	if (x.level == 0) { puts("Invalid"); return; }
	if (!the_same(x.passwd, 30, oldpas)) { puts("Invalid"); return; }
	x.set_passwd(pas);
	u.change(x);
}

bool usersys::the_same(const char *c, int len, const string &a)
{
	if (a.size() > len) return false;
	for (int i = 0; i < a.size(); ++i) if (c[i] != a[i]) return false;
	for (int i = a.size(); i < len; ++i) if (c[i] != 0) return false;
	return true;
}

usersys::user::user(const string &id, const string &pas = "", int lev = 0, const string &na = "")
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
	for (int i = 0; i < 30; ++i)
		if (user_id[i] < a.user_id[i]) return true;
		else if (user_id[i] > a.user_id[i]) return false;
	return false;
}

bool usersys::user::operator==(const user &a) const
{
	for (int i = 0; i < 30; ++i)
		if (user_id[i] != a.user_id[i]) return false;
	return true;
}

void usersys::user::set_user_id(const string &a)
{
	for (int i = 0; i < a.size(); ++i) user_id[i] = a[i];
	for (int i = a.size(); i < 30; ++i) user_id[i] = 0;
}

void usersys::user::set_passwd(const string &a)
{
	for (int i = 0; i < a.size(); ++i) passwd[i] = a[i];
	for (int i = a.size(); i < 30; ++i) passwd[i] = 0;
}

void usersys::user::set_name(const string &a)
{
	for (int i = 0; i < a.size(); ++i) name[i] = a[i];
	for (int i = a.size(); i < 20; ++i) name[i] = 0;
}

void usersys::user::set_level(const string &a)
{
	if (a == "0") level = 0;
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
}
