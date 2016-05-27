#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extmem.h"

void initBuffer(unsigned int headAddr, size_t blkSize, Buffer *buf)
{
	buf->headAddr = headAddr;
    buf->blkSize = blkSize;
    buf->numAllBlk = 0;
    buf->data = (unsigned char*)malloc((blkSize+1) * sizeof(unsigned char));
    if (!(buf->data))
    {
        perror("Buffer Initialization Failed!\n");
        return;
    }
	memset(buf->data, 0, (blkSize+1) * sizeof(unsigned char));
	buf->numIO = 0;
    return;
}

void freeBuffer(Buffer *buf)
{
    free(buf->data);
	return;
}

void readBlockFromDisk(unsigned int addr, Buffer *buf)
{
	char filename[40];
	sprintf(filename, "%d.txt", addr);
	printf("Opening the file: %s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp)
	{
		fclose(fp);
        perror("Reading Block Failed!\n");
        return;
	}
	unsigned char *move = buf->data;
	unsigned char *end = move + buf->blkSize;
	for (; move < end; move++)
		(*move) = fgetc(fp);
    fclose(fp);
    buf->numIO++;
    return;
}

void writeBlockToDisk(unsigned int addr, Buffer *buf)
{
	FILE *fp = NULL;
	char filename[40];
	sprintf(filename, "R/%d.txt", addr);
	printf("You are in write, %s!\n", filename);
	fp = fopen(filename, "w");
    if (!fp)
	{
		fclose(fp);
        perror("Writing Block Failed!\n");
        return;
	}
	unsigned char *move = buf->data;
	unsigned char *end = buf->data + buf->blkSize;
	for (; move < end; move++)
		fprintf(fp, "%c", *move);
    fclose(fp);
	buf->numIO++;
	buf->numAllBlk++;
	memset(buf->data, 0, buf->blkSize*sizeof(unsigned int));
	printf("You out!\n");
    return;
}

void dropBlockOnDisk(unsigned int addr)
{
	char filename[40];
	sprintf(filename, "R/%d.txt", addr);
	if (remove(filename) == -1)
		perror("Dropping Block Fails!\n");
	return;
}

int getInt(unsigned char *blkPtr)
{
	int result = (*(int*)blkPtr);
	blkPtr = blkPtr + 4;
	return result;
}

unsigned int getNextAddr(Buffer *buf)
{
	return (*(unsigned int*)(buf->data + 60));
}
