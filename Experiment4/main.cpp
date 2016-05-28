#include "exm.h"

#define LENR 112
#define LENS 224
#define TAGR 0
#define TAGS 1

typedef struct next
{
	int total;
	int index[40];
	next()
	{
		total = 0;
	}
} next;

char joinA_CN[LEN] = "joinA&CN.txt";
char joinA_CM[LEN] = "joinA&CM.txt";
char joinA_CH[LEN] = "joinA&CH.txt";
char unionA_C[LEN] = "unionA&C.txt";

void nestLoopJoin(Buffer& R, Buffer& S);
void mergeJoin(Buffer& R, Buffer& S);
void hashJoin(Buffer& R, Buffer& S);
void getHash(pair* container, next* hash, int len);
void sortUnion(Buffer& R, Buffer& S);

int cmp(const void *a, const void *b)
{
	return ((*(pair*)a).first > (*(pair*)b).first ? 1 : -1);
}

int countSame(pair *contain, int index, int end)
{
	int counter = 1;
	for (int i = index + 1; i < end; i++)
	{
		if (contain[i].first != contain[index].first)
			return counter;
		counter++;
	}
	return counter++;
}

int main()
{
	Buffer R = Buffer(1, LENR, TAGR);//0 for R, 1 for S
	R.selectFirst(30);
	R.projectFirst();

	Buffer S = Buffer(1, LENS, TAGS);
	S.selectFirst(30);
	S.projectFirst();

	nestLoopJoin(R, S);
	mergeJoin(R, S);
	hashJoin(R, S);
	sortUnion(R, S);
	return 0;
}

void nestLoopJoin(Buffer& R, Buffer& S)
{
	FILE *fp = fopen(joinA_CN, "w");
	if (fp == NULL)
	{
		printf("Cannot create the file: %s\n", joinA_CN);
		return;
	}
	fprintf(fp, "select * from R, S where R.A = S.C\n");
	fprintf(fp, "	A	B	C	D\n");
	pair* containerR = new pair[LENR];
	pair* containerS = new pair[LENS];
	if (R.getAllPair(containerR) && S.getAllPair(containerS))
	{
		for (int i = 0; i < LENR; i++)
			for (int j = 0; j < LENS; j++)
			{
				if (containerR[i].first == containerS[j].first)
					fprintf(fp, "	%d	%d	%d	%d\n", containerR[i].first, containerR[i].second,
						containerS[j].first, containerS[j].second);
			}
	}
	delete[]containerR;
	delete[]containerS;
	fclose(fp);
	return;
}

void mergeJoin(Buffer& R, Buffer& S)
{
	FILE *fp = fopen(joinA_CM, "w");
	if (fp == NULL)
	{
		printf("Cannot create the file: %s\n", joinA_CM);
		return;
	}
	fprintf(fp, "select * from R, S where R.A = S.C\n");
	fprintf(fp, "	A	B	C	D\n");
	pair* containerR = new pair[LENR];
	pair* containerS = new pair[LENS];
	if (R.getAllPair(containerR) && S.getAllPair(containerS))
	{
		qsort(containerR, LENR, sizeof(containerR[0]), cmp);
		//for (int i = 0; i < LENR; i++)
		//	printf("%d\n", containerR[i].first);
		qsort(containerS, LENS, sizeof(containerS[0]), cmp);
		int i = 0, j = 0;
		int lenI, lenJ;
		while (i < LENR && j < LENS)
		{
			if (containerR[i].first == containerS[j].first)
			{
				lenI = countSame(containerR, i, LENR);
				lenJ = countSame(containerS, j, LENS);
				for (int r = 0; r < lenI; r++)
					for (int s = 0; s < lenJ; s++)
						fprintf(fp, "	%d	%d	%d	%d\n", containerR[r+i].first, containerR[r+i].second,
						containerS[s+j].first, containerS[s+j].second);
				i += lenI;
				j += lenJ;
			}
			else if (containerR[i].first < containerS[j].first)
				i++;
			else
				j++;
		}
	}
	delete[]containerR;
	delete[]containerS;
	fclose(fp);
	return;
}

void hashJoin(Buffer& R, Buffer& S)
{
	FILE *fp = fopen(joinA_CH, "w");
	if (fp == NULL)
	{
		printf("Cannot create the file: %s\n", joinA_CH);
		return;
	}
	fprintf(fp, "select * from R, S where R.A = S.C\n");
	fprintf(fp, "	A	B	C	D\n");

	next* hashR = new next[61];
	next* hashS = new next[61];
	pair* containerR = new pair[LENR];
	pair* containerS = new pair[LENS];
	if (containerR && containerS && hashR && hashS)
	{
		if (R.getAllPair(containerR) && S.getAllPair(containerS))
		{
			getHash(containerR, hashR, LENR);
			getHash(containerS, hashS, LENS);

			int s, r, indexR, indexS;
			for (int i = 0; i < 61; i++)
			{
				if (hashR[i].total > 0 && hashS[i].total > 0)
				{
					for (r = 0; r < hashR[i].total; r++)
					{
						indexR = hashR[i].index[r];
						for (s = 0; s < hashS[i].total; s++)
						{
							indexS = hashS[i].index[s];
							fprintf(fp, "	%d	%d	%d	%d\n", containerR[indexR].first, containerR[indexR].second,
								containerS[indexS].first, containerS[indexS].second);
						}
					}
				}
			}
		}
	}
	else
		printf("The room is not enough for the buffer!\n");
	delete[]containerR;
	delete[]containerS;
	delete[]hashR;
	delete[]hashS;
	fclose(fp);
	return;
}

void getHash(pair* container, next* hash, int len)
{
	int index, total;
	qsort(container, len, sizeof(container[0]), cmp);
	for (int i = 0; i < len; i++)
	{
		index = container[i].first;
		total = hash[index].total;
		hash[index].index[total] = i;
		hash[index].total++;
	}
	return;
}

void sortUnion(Buffer& R, Buffer& S)
{
	FILE *fp = fopen(unionA_C, "w");
	if (fp == NULL)
	{
		printf("Cannot create the file: %s\n", unionA_C);
		return;
	}
	fprintf(fp, "select A from R union select C from S\n");
	fprintf(fp, "	A\n");

	next* hashR = new next[61];
	next* hashS = new next[61];
	pair* containerR = new pair[LENR];
	pair* containerS = new pair[LENS];
	if (containerR && containerS && hashR && hashS)
	{
		if (R.getAllPair(containerR) && S.getAllPair(containerS))
		{
			getHash(containerR, hashR, LENR);
			getHash(containerS, hashS, LENS);
			for (int i = 1; i < 61; i++)
			{
				if (hashR[i].total > 0 || hashS[i].total > 0)
					fprintf(fp, "	%d\n", i);
			}
		}
	}
	else
		printf("The room is not enough for the buffer!\n");
	delete[]containerR;
	delete[]containerS;
	delete[]hashR;
	delete[]hashS;
	fclose(fp);
	fclose(fp);
}