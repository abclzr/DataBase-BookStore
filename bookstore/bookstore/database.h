#pragma once

#include<fstream>
#include<string>

template<class T>
class database
{
public:
	string file_name, trash_pool_name;
	int head, tail;

	database(string);
	~database();
};

