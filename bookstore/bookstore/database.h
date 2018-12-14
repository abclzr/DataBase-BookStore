#pragma once

#include<fstream>
#include<string>
using namespace std;

template<class T>
class database
{
public:
	static const int B = 100;
	int head, tail, num, top;
	fstream file, trash;

	//deliver a file name to the constructing function, if the file doesn't exist, make a new one.
	database(std::string);
	~database();

	//return whether the element exits in the database
	bool exist(const T&);

	//return the tot number of the elements;
	int get_num();

	//return the position of next block;
	int get_next(int);

	//return the size of the block;
	int get_size(int);

	//set the next positon;
	void set_next(int, int);

	//set the size of the block;
	void set_size(int, int);

	//find the position of the block that fits x;
	int get(const T &);

	int get_(const T &);

	//find the position of the fits x in the file;
	int get_pos_in_block(const T &, int);

	//return the position of a new block;
	int getnew();

	//move a slice of the block;
	void move(int, int, int, int, int);

	//insert an element in one block;
	void insert(int, const T &);

	//add x into the block-shape links;
	void add(const T &);

	//find the previous position of the block;
	int get_pre(int);

	//remove a block;
	void del(int);

	//delete an element in a block;
	void rem(int, const T &);

	//delete an element
	void remove(const T &);

	void change(const T &);

	//find the element
	const T &get_acc(const T &) const;

	//print all
	void make_print();

	//print the specific books
	void make_print(const T &);
};
