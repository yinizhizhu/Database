#pragma once
#if !defined EXM_H
#define EXM_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLK 8
#define LEN 39

typedef struct pair
{
	int first;
	int second;
} pair;

class Buffer
{
public:
	Buffer(int head, int num, int tag);
	~Buffer();
	bool readBlk(int addr);
	bool writeBlk(int addr);
	void selectFirst(int f);
	void projectFirst();
	bool getAllPair(pair* contain);
	int getHead();
	int getNext();
	int getNumBlk();
	int getNumIO();
	pair *getContainer();
private:
	int headAddr;
	int numBlk;
	int numIO;
	int tag;
	pair container[BLK];
};

#endif