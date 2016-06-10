#include "exm.h"

char dataR[LEN] = "R/data.txt";
char dataS[LEN] = "S/data.txt";

char selectR[LEN] = "R/selectA.txt";
char selectS[LEN] = "S/selectC.txt";

char projectR[LEN] = "R/projectA.txt";
char projectS[LEN] = "S/projectC.txt";

//for R:112, S:224
Buffer::Buffer(int addr, int num, int t)
{
	int tmpAddr = addr, counter = num;
	int i, divider, basis;

	FILE *fp = NULL;
	if (t == 0)
	{
		fp = fopen(dataR, "w");
		basis = 1;
		divider = 40;
	}
	else
	{
		fp = fopen(dataS, "w");
		basis = 20;
		divider = 41;
	}
	if (fp == NULL)
	{
		printf("Cannot create the file: data.txt\n");
		return;
	}
	tag = t;
	numIO = 0;
	srand((unsigned int)time(NULL));//the seed for random
	while (counter > 0)
	{
		for (i = 0; i < 7; i++)
		{
			container[i].first = rand() % divider + basis;
			container[i].second = rand() % 1000 + 1;
			fprintf(fp, "%d %d\n", container[i].first, container[i].second);
		}
		counter -= 7;
		container[i].first = 0;
		if (counter > 0)
			container[i].second = tmpAddr + 1;
		else
			container[i].second = 0;
		writeBlk(tmpAddr);
		tmpAddr++;
	}
	headAddr = addr;
	numBlk = tmpAddr - addr;
	fclose(fp);
	return;
}

Buffer::~Buffer()
{
	return;
}

bool Buffer::readBlk(int addr)
{
	char filename[LEN];
	if (tag == 0)
		sprintf(filename, "R/%d.txt", addr);
	else
		sprintf(filename, "S/%d.txt", addr);
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Cannot open the file: %s\n", filename);
		return false;
	}
	for (int i = 0; i < BLK; i++)
		fscanf(fp, "%d %d", &(container[i].first), &(container[i].second));
	fclose(fp);
	numIO++;
	return true;
}

bool Buffer::writeBlk(int addr)
{
	char filename[LEN];
	if (tag == 0)
		sprintf(filename, "R/%d.txt", addr);
	else
		sprintf(filename, "S/%d.txt", addr);
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Cannot create the file: %s\n", filename);
		return false;
	}
	for (int i = 0; i < BLK; i++)
		fprintf(fp, "%d %d\n", container[i].first, container[i].second);
	fclose(fp);
	numIO++;
	return true;
}

void Buffer::selectFirst(int f)
{
	int next = getHead();

	FILE *fp = NULL;
	if (tag == 0)
	{
		fp = fopen(selectR, "w");
		//printf("select B from R where A = %d\n", f);
		//printf(" B\n");
	}
	else
	{
		fp = fopen(selectS, "w");
		//printf("select D from S where C = %d\n", f);
		//printf(" D\n");
	}
	if (fp == NULL)
	{
		printf("Cannot create the file: select.txt\n");
		return;
	}
	while (next > 0)
	{
		if (readBlk(next))
		{
			for (int i = 0; i < BLK; i++)
				if (f == container[i].first)
				{
					//printf(" %d\n", container[i].second);
					fprintf(fp, " %d\n", container[i].second);
				}
		}
		else
			return;
		next = getNext();
	}
	//printf("\n");
	fclose(fp);
	return;
}

void Buffer::projectFirst()
{
	int next = getHead();

	FILE *fp = NULL;
	if (tag == 0)
	{
		fp = fopen(projectR, "w");
		//printf("select B from R\n");
		//printf(" B\n");
		fprintf(fp, "select A from R\n\n A\n");
	}
	else
	{
		fp = fopen(projectS, "w");
		//printf("select D from S\n");
		//printf(" D\n");
		fprintf(fp, "select C from S\n\n C\n");
	}
	if (fp == NULL)
	{
		printf("Cannot create the file: project.txt\n");
		return;
	}
	while (next > 0)
	{
		if (readBlk(next))
		{
			for (int i = 0; i < BLK; i++)
			{
				//printf(" %d\n", container[i].first);
				fprintf(fp, " %d\n", container[i].first);
			}
		}
		else
			return;
		next = getNext();
	}
	//printf("\n");
	fclose(fp);
	return;
}

bool Buffer::getAllPair(pair* contain)
{
	int counter = 0;
	int next = getHead();
	while (next > 0)
	{
		if (readBlk(next))
		{
			for (int i = 0; i < (BLK - 1); i++)
			{
				contain[counter].first = container[i].first;
				contain[counter].second = container[i].second;
				counter++;
			}
		}
		else
			return false;
		next = getNext();
	}
	return true;
}

int Buffer::getHead()
{
	return headAddr;
}

int Buffer::getNext()
{
	return container[BLK-1].second;
}

int Buffer::getNumBlk()
{
	return numBlk;
}

int Buffer::getNumIO()
{
	return numIO;
}

pair *Buffer::getContainer()
{
	return container;
}