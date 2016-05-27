#ifndef EXTMEM_H
#define EXTMEM_H

typedef struct tagBuffer {
	unsigned int headAddr;
    size_t blkSize; /* Block size */
    size_t numAllBlk; /* Number of blocks that can be kept in the buffer */
	unsigned char *data; /* Starting address of the buffer */
	unsigned long numIO; /* Number of IO's*/
} Buffer;

void initBuffer(unsigned int headAddr, size_t blkSize, Buffer *buf);

void freeBuffer(Buffer *buf);

unsigned int getNextAddr(Buffer *buf);

void readBlockFromDisk(unsigned int addr, Buffer *buf);

void writeBlockToDisk(unsigned int addr, Buffer *buf);

void dropBlockOnDisk(unsigned int addr);

int getInt(unsigned char *blkPtr);

#endif // EXTMEM_H
