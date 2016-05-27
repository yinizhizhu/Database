#include "stdafx.h"

int main()
{
	Buffer R;
	//tuple *dataR = NULL, *dataS = NULL;
	initBuffer(1, 64, &R);

	//if (R.data)
	//	printf("headAddr=%d, blkSize=%d\n", R.headAddr, R.blkSize);
	//else
	//	printf("No room for data!\n");

	//initDataR(dataR);
	initR(&R);
	//selectRA(&R, 30);
	freeBuffer(&R);

	//initBuffer(30, 64, &S);
	//initDataS(dataS);
	//initS(&S);
	//selectSC(&S, 50);

	return 0;
}
