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
	unsigned char z; /* delete me*/
	unsigned char keyPrime[KEYLENGTH] = { '0' };

	copyKey(keyPrime, key);

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
			subkeyTable[round][subkeyNumber] = K(keyPrime, keygenInput); 
		}
	}

	printTable(subkeyTable, 'h'); 

	return 0;
}


/*	We intentionally do not use the 9th and 10th byte of the key (so bytePrime will never be 1 or 0.
	the x input gets modded by 8 to give us which byte of the key we will be returning as the subkey.
	We then bitshift the key left (with a carry) to give us Key` or "shifted".
	The keys are from the right, so we must switch the mod results with its key_byte equivelant.
*/
unsigned char K(unsigned char * key, int x)
{
	int byteNumber;
	int bytePrime;

	byteNumber = x % 8;
	/* printf("\nByte number: %d", byteNumber); DELETE ME */ 

	switch (byteNumber) {
	case 0:
		bytePrime = 9;
		break;
	case 1:
		bytePrime = 8;
		break;
	case 2:
		bytePrime = 7;
		break;
	case 3:
		bytePrime = 6;
		break;
	case 4:
		bytePrime = 5;
		break;
	case 5:
		bytePrime = 4;
		break;
	case 6:
		bytePrime = 3;
		break;
	case 7:
		bytePrime = 2;
		break;
	default:
		printf("Input error in Key Scheduler");
		return (unsigned char)'00';
	}

	leftRotate(key);

	/* DELETE ME */
	/* printf("\nShifted Key should be ...\n     (0x57)(0x9B)(0xDE)(0x02)(0x46)(0x8A)(0xCF)(0x13)(0x57)(0x9B): ");	
	printKey(key);

	printf("\nByte Prime: %d", bytePrime);
	printf("\nByte Prime: (0x %02X)", key[bytePrime]);
	*/

	return key[bytePrime];
}


void leftRotate(unsigned char * shifted)
{
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	unsigned char hold = 0;
	int i;
	
	hold = shifted[0] & 0xFF;
	for (i = KEYLENGTH - 1; i >= 0; --i) {
		temp2 = shifted[i] & 0xFF;
		temp1 >>= 7;
		shifted[i] <<= 1;
		shifted[i] |= temp1;
		temp1 = temp2;
	}
	hold >>= 7;
	shifted[KEYLENGTH-1] |= hold;

	return;
}


void rightRotate(unsigned char* shifted)
{
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	unsigned char hold = 0;
	int i;

	hold = shifted[0] & 0xFF;
	for (i = KEYLENGTH - 1; i >= 0; --i) {
		temp2 = shifted[i] & 0xFF;
		temp1 <<= 7;
		shifted[i] >>= 1;
		shifted[i] |= temp1;
		temp1 = temp2;
	}
	hold <<= 7;
	shifted[KEYLENGTH - 1] |= hold;
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


void printTable(unsigned char table[ROUNDS][COLS], char flag)
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */

	if (tolower(flag) == 'c')
	{
		printf("\n\nPrinting Table as Chars\n\n");
			for (round = 0; round < ROUNDS; ++round) {
				for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
					printf("%c ", table[round][subkeyNumber]);
				}
			}
	}

	if (tolower(flag) == 'h')
	{
		printf("\n\nPrinting Table as Hex\n\n");
		for (round = 0; round < ROUNDS; ++round) {
			for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
				printf("(0x%02X) ", table[round][subkeyNumber]);
			}
			putchar('\n');
		}
	}

	return;
}


void copyKey(unsigned char* keyPrime, unsigned char* key)
{
	int i;

	for (i = 0; i < KEYLENGTH; ++i) {
		keyPrime[i] = key[i];
	}

	return;
}