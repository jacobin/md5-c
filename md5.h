#ifndef MD5_H
#define MD5_H

typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

void MD5Init(MD5_CTX* context);
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);
void MD5Final(MD5_CTX* context, unsigned char digest[16]);

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void md5String(char *input, uint8_t *result);
void md5File(FILE *file, uint8_t *result);

#endif
