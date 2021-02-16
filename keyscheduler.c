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
			subkeyTable[round][subkeyNumber] = K(key, keygenInput);
		}
	}

	printTable(subkeyTable);

	return 0;
}


unsigned char K(unsigned char * key, int x)
{
	unsigned char subkey = 'z';

	printf(" K() key: %s ", key);

	return subkey;
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