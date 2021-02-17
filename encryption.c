/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int encrypt(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */
	unsigned int inProcess[4] = { 0 }; /* 64 bits */
	unsigned char ciphertextBlock[8] = { 0 }; /* 64 bits */
	FILE* fp = NULL;
	int paddingFlag;
	
	/* Open File */
	fp = fopen("plaintext.txt", "r");
	if (!fp || fp == 0)
		return 1;

	/* Loop until EOF */
	/*
	while (fp) {
		paddingFlag = getPlaintext(fp, plaintextBlock);
	}
	*/

	paddingFlag = getPlaintextBlock(fp, plaintextBlock);

	whiten(plaintextBlock, inProcess, subkeyTable);


	switch (paddingFlag) {
		case 0:
			fclose(fp);
			return 0;
		case 1:
			fclose(fp);
			return 1;
		case 2:
			printf("\nCALL PADDING HERE");
	}

	/* Close File */
	fclose(fp);

	return 0;
}

void whiten(unsigned char* plaintext, unsigned char* inprocess, unsigned char subkeys[ROUNDS][COLS])
{
	unsigned int w0, w1, w2, w3;

	/* Divide into 16 bit words */
	printf("Chars: ");
	printf("%c ", plaintext[0]);
	printf("%c", plaintext[1]);
	joinChar(&w0, &plaintext[0], &plaintext[1]);
	joinChar(&w1, &plaintext[2], &plaintext[3]);
	joinChar(&w2, &plaintext[4], &plaintext[5]);
	joinChar(&w3, &plaintext[6], &plaintext[7]);

	printf("\n(%2X)", w0);
	
	return;
}


void joinChar(unsigned int* w, unsigned char* a, unsigned char* b)
{
	*w = (*a << 8)  | *b; 
	return;
}
