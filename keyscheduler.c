/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

/* Future TODO: use trees instead of for loops and do this in parallel */
int generateSubkeys(unsigned char * key, unsigned char subkeyTable[ROUNDS][COLS])
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */
	int constant; /* constant that is added onto round number when sending to keyscheduler*/
	int keygenInput;
	unsigned char z = 'y'; /* delete me*/

	if (initializeTable(subkeyTable) != 0)
		return 1;

	for(round = 0; round < ROUNDS; ++round) {
		for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {

			/* Determine Constant for G() and F() subkey generation*/
			if (subkeyNumber == 0 || subkeyNumber == 4 || subkeyNumber == 8)
				constant = 0;
			else if (subkeyNumber == 1 || subkeyNumber == 5 || subkeyNumber == 9)
				constant = 1;
			else if (subkeyNumber == 2 || subkeyNumber == 6 || subkeyNumber == 10)
				constant = 2;
			else if (subkeyNumber == 3 || subkeyNumber == 7 || subkeyNumber == 11)
				constant = 3;
			else
				return 1;

			keygenInput = 4 * round + constant;

			/* Send to keyscheduler */
			/* subkeyTable[round][subkeyNumber] = K(key, keygenInput); */
		}
	}

	z = K(key, keygenInput);

	printf("\nChar: %c \nHex: (0x%02X)", z, z);

	/* printTable(subkeyTable); */

	return 0;
}


/* We intentionally do not use the 9th and 10th byte of the key*/
unsigned char K(unsigned char * key, int x)
{
	unsigned char shifted[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	unsigned char subkey = 'z';
	int byteNumber;
	unsigned char byte;

	printf("\nK() - \nOriginal Key:");
	printKey(key);

	/***********************************/
	x = 0;	/* DELETE ME!!!!!!*/
	/***********************************/

	byteNumber = x % 8;
	
	printf("\n0 mod 8 should be 0: %d", byteNumber);
	printf("\nK[0] should be a: %c", key[byteNumber]);
	byte = key[byteNumber];
	printf("\nByte should be a: %c", byte);

	subkey = leftRotate(byte);

	printf("\nSubkey should be a: %c", subkey);


	/* printf(" K() key: %s", key); */
	
	/* printf("(0x%02X)", key); */

	return subkey;
}


/* Thank you https://www.geeksforgeeks.org/rotate-bits-of-an-integer/ */
unsigned char leftRotate(unsigned char byte)
{
	unsigned char subkey = byte;
	/*
	int i;

	(keyPrime << 1) | (keyPrime >> (8 - 1));

	printf("\nKey: %s \nKey Prime: %s\n", key, keyPrime);
	*/

	return subkey;
}

/*Function to right rotate n by d bits*/
void rightRotate(unsigned char* key, unsigned char* keyPrime)
{
	/*
	(*n >> 1) | (*n << (8 - 1));
	*/
	return;
}


int initializeTable(unsigned char subkeyTable[ROUNDS][COLS])
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */

	for (round = 0; round < ROUNDS; ++round) {
		for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
			subkeyTable[round][subkeyNumber] = (unsigned) '0';
		}
	}

	return 0;
}


void printTable(unsigned char table[ROUNDS][COLS])
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */

	printf("\n\nPrinting Table as Chars\n\n");
	for (round = 0; round < ROUNDS; ++round) {
		for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
			printf("%c ", table[round][subkeyNumber]);
		}
	}

	printf("\n\nPrinting Table as Hex\n\n");
	for (round = 0; round < ROUNDS; ++round) {
		for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
			printf("(0x%02X)", table[round][subkeyNumber]);
		}
	}

	return;
}


void copyKey(unsigned char* key, unsigned char* keyPrime)
{
	int i;

	for (i = 0; i < KEYLENGTH; ++i) {
		keyPrime[i] = key[i];
	}

	return;
}