#pragma once

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include "extmem.h"

typedef struct tuple
{
	int first;
	int second;
	tuple()
	{
		first = second = 0;
	}
} tuple;

/*For the initialization of R&S*/
void initR(Buffer *r);
void initS(Buffer *s);
void initDataR(tuple *r);
void initDataS(tuple *s);

/*For the selection algorithm*/
void selectRA(Buffer *buf, int a);
//void selectRB(Buffer *buf, int b);
//void selectRAB(Buffer *buf, int a, int b);
void selectSC(Buffer *buf, int c);
//void selectSD(Buffer *buf, int d);
//void selectSCD(Buffer *buf, int c, int d);

/*For the projection*/
void projection(Buffer *buf);

/*For the join*/
void join(Buffer *s, Buffer *r);
void joinHash(Buffer *s, Buffer *r);
void joinNextLoop(Buffer *s, Buffer *r);

/*For the uion*/
void uion(Buffer *s, Buffer *r);
