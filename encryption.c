/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int encrypt(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */
	unsigned char blockInProcess[8] = { 0 }; /* 64 bits */
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

	paddingFlag = getPlaintext(fp, plaintextBlock);


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
