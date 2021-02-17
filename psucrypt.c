/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/*
* Future improvements:
* Switch out for loops for trees (or recursion, but probably not if the loop has the potential to get huge)
* Immutable keys? Unneccessary? 
* Make so accepts 64 bit key and 80 bit key
*/

#include "psucrypt.h"


int main(int argc, char* argv[])
{
	unsigned char key[KEYLENGTH] = { 0 };	/* Future recast as immutable const? */
	unsigned char subkeys[ROUNDS][COLS]; /* 20 rounds, 12 subkeys, 1 byte each*/
	int keysize = 0;
	
	printf("Starting Encryption...\n");	/* TODO DELETE ME */
	
	if (getKey(key, &keysize) != 0) {
		printf("\nKey fetch error: %s", key);
		return 1;
	}

	if (generateSubkeys(key, subkeys) != 0) {
		printf("\nSubkey Generation Error");
		return 1;
	}

	if (blockEncryption(key, subkeys) != 0) {
		printf("\nEncryption Error");
		return 1;
	}

	putchar('\n');
	return 0;
}
