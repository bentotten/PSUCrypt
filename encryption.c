/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int encrypt(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */
	FILE* fp = NULL;
	
	/* Open File */
	fp = fopen("plaintext.txt", "r");
	if (!fp || fp == 0)
		return 1;

	/* Loop until EOF */
	/*
	while (fp) {
		if (getPlaintextBlock(fp, plaintextBlock) != 0)
			return 1;
	}
	*/

	getPlaintextBlock(fp, plaintextBlock); /* DELETE ME */

	/* Close File */
	fclose(fp);

	/*
	printKey(key);
	printTable(subkey, 'h');
	*/

	return 0;
}
