#include "database.h"
#include<fstream>
#include<string>


template<class T>
database<T>::database(string s)
{
	file_name = s;
	trash_pool_name = s + ".trash";

}

template<class T>
database<T>::~database()
{
}
