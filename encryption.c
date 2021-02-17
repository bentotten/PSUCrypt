/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

/* Global Table */
static unsigned char FTABLE[16][16] = {
		{0xa3,0xd7,0x09,0x83,0xf8,0x48,0xf6,0xf4,0xb3, 0x21,0x15,0x78,0x99,0xb1,0xaf,0xf9},
		{0xe7,0x2d,0x4d,0x8a,0xce,0x4c,0xca,0x2e,0x52,0x95,0xd9,0x1e,0x4e,0x38,0x44,0x28},
		{0x0a,0xdf,0x02,0xa0,0x17,0xf1,0x60,0x68,0x12,0xb7,0x7a,0xc3,0xe9,0xfa,0x3d,0x53},
		{0x96,0x84,0x6b,0xba,0xf2,0x63,0x9a,0x19,0x7c,0xae,0xe5,0xf5,0xf7,0x16,0x6a,0xa2},
		{0x39,0xb6,0x7b,0x0f,0xc1,0x93,0x81,0x1b,0xee,0xb4,0x1a,0xea,0xd0,0x91,0x2f,0xb8},
		{0x55,0xb9,0xda,0x85,0x3f,0x41,0xbf,0xe0,0x5a,0x58,0x80,0x5f,0x66,0x0b,0xd8,0x90},
		{0x35,0xd5,0xc0,0xa7,0x33,0x06,0x65,0x69,0x45,0x00,0x94,0x56,0x6d,0x98,0x9b,0x76},
		{0x97,0xfc,0xb2,0xc2,0xb0,0xfe,0xdb,0x20,0xe1,0xeb,0xd6,0xe4,0xdd,0x47,0x4a,0x1d},
		{0x42,0xed,0x9e,0x6e,0x49,0x3c,0xcd,0x43,0x27,0xd2,0x07,0xd4,0xde,0xc7,0x67,0x18},
		{0x89,0xcb,0x30,0x1f,0x8d,0xc6,0x8f,0xaa,0xc8,0x74,0xdc,0xc9,0x5d,0x5c,0x31,0xa4},
		{0x70,0x88,0x61,0x2c,0x9f,0x0d,0x2b,0x87,0x50,0x82,0x54,0x64,0x26,0x7d,0x03,0x40},
		{0x34,0x4b,0x1c,0x73,0xd1,0xc4,0xfd,0x3b,0xcc,0xfb,0x7f,0xab,0xe6,0x3e,0x5b,0xa5},
		{0xad,0x04,0x23,0x9c,0x14,0x51,0x22,0xf0,0x29,0x79,0x71,0x7e,0xff,0x8c,0x0e,0xe2},
		{0x0c,0xef,0xbc,0x72,0x75,0x6f,0x37,0xa1,0xec,0xd3,0x8e,0x62,0x8b,0x86,0x10,0xe8},
		{0x08,0x77,0x11,0xbe,0x92,0x4f,0x24,0xc5,0x32,0x36,0x9d,0xcf,0xf3,0xa6,0xbb,0xac},
		{0x5e,0x6c,0xa9,0x13,0x57,0x25,0xb5,0xe3,0xbd,0xa8,0x3a,0x01,0x05,0x59,0x2a,0x46}
};


int blockEncryption(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */
	unsigned int inProcess[4] = { 0 }; /* 16 bits each element */
	unsigned int ciphertext[4] = { 0 }; /* 16 bits each element */
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
		paddingFlag = getPlaintextBlock(fp, plaintextBlock);
		whiten(plaintextBlock, inProcess, key);
		encrypt(inProcess, subkeyTable);
	}
	*/

	paddingFlag = getPlaintextBlock(fp, plaintextBlock);
	whiten(plaintextBlock, inProcess, key);
	encrypt(inProcess, subkeyTable);

	ciphertext[0] = inProcess[2];
	ciphertext[1] = inProcess[3];
	ciphertext[2] = inProcess[0];
	ciphertext[3] = inProcess[1];

	lastWhiten(ciphertext, ciphertextBlock, key);

	/* TODO: LOOP THROUGH ENTIRE PLAINTEXT FILE, ADD PADDING BLOCK IF NEEDED, PRINT OUT CIPHERTEXT TO FILE, DECRYPT */

	/* DELETE ME */
	putchar('\n');
	int t;
	for (t = 0; t < 8; ++t)
	{
		printf("(% 02x)", ciphertextBlock[t]);
	}

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

void lastWhiten(unsigned int* ciphertext, unsigned char* ciphertextBlock, unsigned char* key)
{
	unsigned int k0, k1, k2, k3;
	unsigned char y0, y1, y2, y3, y4, y5, y6, y7;

	/* Divide into 16 bit keys*/
	joinChar(&k0, &key[0], &key[1]);
	joinChar(&k1, &key[2], &key[3]);
	joinChar(&k2, &key[4], &key[5]);
	joinChar(&k3, &key[6], &key[7]);

	/* XOR with unrefined ciphertext */
	ciphertext[0] ^ k0;
	ciphertext[1] ^ k1;
	ciphertext[2] ^ k2;
	ciphertext[3] ^ k3;

	/* Split the ciphertext into chars */
	splitInt(&ciphertext[0], &y0, &y1);
	splitInt(&ciphertext[1], &y2, &y3);
	splitInt(&ciphertext[2], &y4, &y5);
	splitInt(&ciphertext[3], &y6, &y7);

	/* Assign to Ciphertext Block Array */
	ciphertext[0] = y0;
	ciphertext[1] = y1;
	ciphertext[2] = y2;
	ciphertext[3] = y3;
	ciphertext[4] = y4;
	ciphertext[5] = y5;
	ciphertext[6] = y6;
	ciphertext[7] = y7;

	return;
}

void encrypt(unsigned int* inprocess, unsigned char subkeys[ROUNDS][COLS])
{
	struct fboxResults fResults = { 0,0 };
	unsigned int temp[2] = { 0 }; /* 16 bits each element */
	int round;

	for (round = 0; round < 20; ++round)
	{
		fResults = F(inprocess[0], inprocess[1], round, subkeys[round]);

		temp[0] = inprocess[0];
		temp[1] = inprocess[1];
		inprocess[0] = fResults.x0 ^ inprocess[2];
		inprocess[1] = fResults.x1 ^ inprocess[3];
		inprocess[2] = temp[0];
		inprocess[3] = temp[1];
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

struct fboxResults F(unsigned int r0, unsigned int r1, int round, unsigned char subkeys[COLS])
{
	struct fboxResults fresults = { 0,0 };
	struct fboxResults gresults = { 0,0 };
	unsigned int con1 = { 0 };
	unsigned int con2 = { 0 };
	unsigned int power = (unsigned int)pow((double)2, (double)16);

	/* G Permutation */
	gresults.x0 = G(r0, subkeys[0], subkeys[1], subkeys[2], subkeys[3], round);
	gresults.x1 = G(r1, subkeys[4], subkeys[5], subkeys[6], subkeys[7], round); 

	joinChar(&con1, &subkeys[8], &subkeys[9]);
	joinChar(&con2, &subkeys[10], &subkeys[11]);

	fresults.x0 = (gresults.x0 + (2 * gresults.x1) + con1) % power;
	fresults.x1 = ((2 * gresults.x0) + gresults.x1 + con2) % power;

	return fresults;
}


unsigned int G(unsigned int r0, unsigned char k0, unsigned char k1, unsigned char k2, unsigned char k3, int round)
{
	unsigned char g1, g2, g3, g4, g5, g6 = {'0'};
	unsigned int result;

	splitInt(&r0, &g1, &g2);

	/* FTable Lookups and XORs */
	g3 = ftable((unsigned char)(g2 ^ k0)) ^ g1;
	g4 = ftable((unsigned char)(g3 ^ k0)) ^ g2;
	g5 = ftable((unsigned char)(g4 ^ k0)) ^ g3;
	g6 = ftable((unsigned char)(g5 ^ k0)) ^ g4;

	joinChar(&result, &g5, &g6);
	return result;
}


unsigned char ftable(unsigned char lookup)
{
	unsigned char row, col, hold;

	row = (lookup >> 4);
	hold = (lookup << 4);
	col = (hold >> 4);

	return FTABLE[row][col];
}


void joinChar(unsigned int* w, unsigned char* a, unsigned char* b)
{
	*w = (*a << 8) | *b;
	return;
}


void splitInt(unsigned int* w, unsigned char* a, unsigned char* b)
{
	unsigned int hold;

	*a = (*w >> 8 );
	hold = (*w << 24);
	*b = (hold >> 24);
	return;
}
