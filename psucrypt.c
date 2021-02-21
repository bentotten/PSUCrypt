/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/*
* Future improvements:
* Switch out for loops for trees (or recursion, but probably not if the loop has the potential to get huge)
* Immutable keys? Unneccessary? 
* Make so accepts 64 bit key and 80 bit key
* Find better way to access ftable that doesnt involve initializing it every single time
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	unsigned char key[KEYLENGTH] = { 0 };	/* Future recast as immutable const? */
	unsigned char subkeys[ROUNDS][COLS]; /* 20 rounds, 12 subkeys, 1 byte each*/
	int keysize = 0;
	char c = (char)argv[1];
	
	if (argc > 2) {
		printf("\nToo many arguments supplied. Please enter -e for encrypt or -d for decrypt\n");
		return 1;
	}
	else
	{
		printf("\nEnter 'e' for encrypt or 'd' to decrypt: ");
		c = getchar();
	}

	/* Get Key and Generate Subkeys*/
	if (getKey(key, &keysize) != 0) {
		printf("\nKey fetch error: %s", key);
		return 1;
	}

	if (generateSubkeys(key, subkeys) != 0) {
		printf("\nSubkey Generation Error");
		return 1;
	}

	switch (c)
	{
	case 'e':
		printf("Starting Encryption...\n");
		if (blockEncryption(key, subkeys) != 0) {
			printf("\nEncryption Error");
			return 1;
		}
		break;
	case 'd':
		printf("\nStarting Decryption...\n");
		if (blockDecryption(key, subkeys) != 0) {
			printf("Decryption Error");
			return 1;
		}
		break;
	default:
		printf("\nPlease enter e or d.\n");
		return 1;
	}

	printf("\nComplete.\n");
	return 0;
}
