/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

/* Future TODO: use trees instead of for loops and do this in parallel */
int generateSubkeys(unsigned char * key, unsigned char subkeyTable[20][12])
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */
	int constant; /* constant that is added onto round number when sending to keyscheduler*/
	int keygenInput;

	if (initializeTable(subkeyTable) != 0)
		return 1;

	/*
	for(round = 0; round < 20; ++round) {
		for (subkeyNumber = 0; subkeyNumber < 12; ++subkeyNumber) {
			/* Determine Constant for G() and F() subkey generation*/

	/*
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
			
			*/
			/* Send to keyscheduler */

	/*
			keygenInput = 4 * round + constant;
			
			//subkeyTable[round][subkeyNumber] = K(keygenInput);
			subkeyTable[round][subkeyNumber] = "c";
			printf("\nRow: %d\n", round);
			printf("\nSubkey: %d\n", subkeyNumber);
			printf(subkeyTable[round][subkeyNumber]);
		}
	}
	*/
	return 0;
}


int initializeTable(unsigned char subkeyTable[ROUNDS][COLS])
{
	int round; /* Outer row: Rounds */
	int subkeyNumber; /* Inner row: Subkeys */

	for (round = 0; round < ROUNDS; ++round) {
		for (subkeyNumber = 0; subkeyNumber < COLS; ++subkeyNumber) {
			subkeyTable[round][subkeyNumber] = "01";
			printf("%u", subkeyTable[round][subkeyNumber]);
		}
	}

	return 0;
}

/*
unsigned char K(int x)
{
	return (unsigned char)x;
}
*/