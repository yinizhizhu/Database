#include <time.h>
#include "stdafx.h"

const int N = 36;

char dataR[N] = "R/initR.txt";
char dataS[N] = "S/initS.txt";

char firstR[N] = "R/selectRA.txt";
char firstS[N] = "S/selectSC.txt";

char second[N] = "projection.txt";

char thirdF[N] = "join.txt";
char thirdS[N] = "joinHash.txt";
char thirdT[N] = "joinNextLoop.txt";

char fourth[N] = "uion.txt";

/*For the initialization of R&S*/
void initR(Buffer *r)
{
	srand((unsigned)time(NULL));
	FILE *out = fopen(dataR, "w");

	int A, B;
	int len = 112, counter;
	unsigned char *buf;
	unsigned int addr = r->headAddr;
	for (; len > 0;)
	{
		buf = r->data;
		for (counter = 0; counter < 7; counter++)
		{
			A = rand() % 40 + 1;
			B = rand() % 1000 + 1;
			fprintf(out, "%d %d\n", A, B);//contain in the file which can be shown to Teacher
			memcpy(buf, &A, sizeof(int));		//store the Data A
			memcpy(buf + 4, &B, sizeof(int));	//store the Data B
			buf += 8;							//4 chars for int
		}
		len -= 7;
		if (len > 0)
		{
			addr += 1;
			memcpy(buf + 4, &addr, sizeof(unsigned int));//store the next addr
			writeBlockToDisk(addr - 1, r);
		}
		else
			writeBlockToDisk(addr, r);
	}
	fclose(out);
	return;
}
void initS(Buffer *s)
{
	srand((unsigned)time(NULL));
	FILE *out = fopen(dataS, "w");

	fclose(out);
	return;
}

void initDataR(tuple *r)
{
	FILE *out = fopen(dataR, "w");

	int len = 112, A, B;
	r = (tuple*)malloc(len*sizeof(tuple));

	srand((unsigned)time(NULL));
	while (len)
	{
		A = rand() % 40 + 1;
		B = rand() % 1000 + 1;
		fprintf(out, "%d %d\n", A, B);
		r->first = A;
		r->second = B;
		len--;
	}
	fclose(out);
	return;
}
void initDataS(tuple *s)
{
	FILE *out = fopen(dataS, "w");

	int len = 224, C, D;
	s = (tuple*)malloc(len*sizeof(tuple));
	
	srand((unsigned)time(NULL));
	while (len)
	{
		C = rand() % 41 + 20;
		D = rand() % 1000 + 1;
		fprintf(out, "%d %d\n", C, D);
		s->first = C;
		s->second = D;
		len--;
	}
	fclose(out);
	return;
}

/*For the selection algorithm*/
void selectRA(Buffer *r, int a)
{
	printf("select B from R where A = %d\n", a);
	FILE *out = fopen(firstR, "w");
	printf(" B\n");
	fprintf(out, " B\n");

	int A, B, counter;
	unsigned int nextAddr = 1;
	unsigned char *buf = NULL;
	readBlockFromDisk(r->headAddr, r);

	while (nextAddr)
	{
		counter = 7;
		buf = r->data;
		while (counter)
		{
			A = getInt(buf);
			B = getInt(buf);
			printf("%d, %d\n", A, B);
			if (A == a)
			{
				printf(" %d\n", B);
				fprintf(out, " %d\n", B);
			}
			counter--;
		}
		nextAddr = getNextAddr(r);
		readBlockFromDisk(nextAddr, r);
	}
	fclose(out);
	printf("\n\n");
	return;
}
void selectSC(Buffer *s, int c)
{
	printf("select D from S where C = c\n", c);
	FILE *out = fopen(firstS, "w");
	printf(" D\n");
	fprintf(out, " D\n");

	//int C, D;
	//unsigned int addr = 30, counter = 0;

	fclose(out);
	printf("\n\n");
	return;
}

/*For the projection*/
void projection(Buffer *buf)
{
	FILE *out = fopen(second, "w");
	fclose(out);
	return;
}

/*For the join*/
void join(Buffer *s, Buffer *r)
{
	FILE *out = fopen(thirdF, "w");
	fclose(out);
	return;
}
void joinHash(Buffer *s, Buffer *r)
{
	FILE *out = fopen(thirdS, "w");
	fclose(out);
	return;
}
void joinNextLoop(Buffer *s, Buffer *r)
{
	FILE *out = fopen(thirdT, "w");
	fclose(out);
	return;
}

/*For the uion*/
void uion(Buffer *s, Buffer *r)
{
	FILE *out = fopen(fourth, "w");
	fclose(out);
	return;
}
