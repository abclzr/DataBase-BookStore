#pragma once

#include<fstream>
#include<string>

const int B = 100;

template<class T>
class database
{
public:
	int head, tail, num, top;
	fstream file, trash;

	//deliver a file name to the constructing function, if the file doesn't exist, make a new one.
	database(std::string);
	~database();

	//find the position of the block that fits x;
	int get(const T &);

	//return the position of a new block;
	int getnew();

	//move a slice of the block;
	void move(int, int, int, int)

	//add x into the block-shape links;
	void add(const T &);


	void remove(const T &);

	void show(const T &);
};

