/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int blockEncryption(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */
	unsigned int inProcess[4] = { 0 }; /* 16 bits each element */
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
	whiten(plaintextBlock, inProcess, key);
	encrypt(inProcess, subkeyTable);


	switch (paddingFlag) {
		case 0:
			fclose(fp);
			return 0;
		case 1:
			fclose(fp);
			return 1;
		case 2:
			printf("\nCALL 64 BIT PADDING BLOCK HERE");
	}

	/* Close File */
	fclose(fp);

	return 0;
}

void whiten(unsigned char* plaintext, unsigned int* inprocess, unsigned char * key)
{
	unsigned int w0, w1, w2, w3, k0, k1, k2, k3;

	/* Divide into 16 bit words */
	joinChar(&w0, &plaintext[0], &plaintext[1]);
	joinChar(&w1, &plaintext[2], &plaintext[3]);
	joinChar(&w2, &plaintext[4], &plaintext[5]);
	joinChar(&w3, &plaintext[6], &plaintext[7]);
	
	/* Divide into 16 bit keys*/
	joinChar(&k0, &key[0], &key[1]);
	joinChar(&k1, &key[2], &key[3]);
	joinChar(&k2, &key[4], &key[5]);
	joinChar(&k3, &key[6], &key[7]);

	/* XOR with key with plaintext */
	inprocess[0] = w0 ^ k0;
	inprocess[1] = w1 ^ k1;
	inprocess[2] = w2 ^ k2;
	inprocess[3] = w3 ^ k3;
	
	return;
}


void encrypt(unsigned int* inprocess, unsigned char subkeys[ROUNDS][COLS])
{
	struct fboxResults fResults = { 0,0 };
	int round;

	for (round = 0; round < 20; ++round)
	{

		fResults = F(inprocess[0], inprocess[1], round, subkeys[round]);

	}

	return;
}

void decrypt(unsigned int* inprocess, unsigned char subkeys[ROUNDS][COLS])
{
	struct fboxResults fResults = { 0,0 };
	int round;

	for (round = 0; round < 20; ++round)
	{
		/* TODO: REVERSE KEYS AND SEND THEM */
		/* fResults = F(inprocess[0], inprocess[1], round, subkeys[round]); */

	}

	return;
}

struct fboxResults F(unsigned int* r0, unsigned int* r1, int round, unsigned char subkeys[COLS])
{
	struct fboxResults fresults = { 0,0 };
	struct fboxResults gresults = { 0,0 };

	/* G Permutation */
	gresults.x0 = G(r0, subkeys[0], subkeys[1], subkeys[2], subkeys[3], round);
	gresults.x1 = G(r1, subkeys[4], subkeys[5], subkeys[6], subkeys[7], round);

	/* TODO FINISH CALCULATING f0 and f1*/

	return fboxResults;
}


unsigned int G(unsigned int* r0, unsigned char* k0, unsigned char* k1, unsigned char* k2, unsigned char* k3, int round)
{
	unsigned char g0, g1 = {'0'};
	splitInt(&r0, &g0, &g1);

	/* Do stuff */

	joinChar(&r0, &g0, &g1);

	printf("\n(%02X)", r0);

	return;
}


void joinChar(unsigned int* w, unsigned char* a, unsigned char* b)
{
	*w = (*a << 8) | *b;
	return;
}


void splitInt(unsigned int* w, unsigned char* a, unsigned char* b)
{
	*w = (*a << 8) | *b;
	return;
}