/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"


int main(int argc, char* argv[])
{
	unsigned char plaintextBlock[9] = { '\0' }; /* 64 bits (+ delimiter) */
	unsigned char key[KEYLENGTH] = { 0 };	/* Future recast as immutable const? */
	unsigned char subkeys[ROUNDS][COLS]; /* 20 rounds, 12 subkeys, 1 byte each*/
	int keysize = 0;
	int textsize = 0;
	int paddingFlag;

	/*
	test(); /* DELETE ME */

	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		printf("Key fetch error: %s", key);
	
	if (generateSubkeys(key, subkeys) != 0)
		printf("Subkey Generation Error");

	/*
	paddingFlag = getPlaintext(plaintextBlock);
	if (paddingFlag == 2)
		printf("\nADDITIONAL BLOCK OF PADDING HAPPENS HERE");
	if(paddingFlag != 0 && paddingFlag != 2)
		printf("plaintext fetch error: %s", plaintextBlock);
	
	textsize = getTextSize();
	printf("\n\nText: %s", plaintextBlock);
	printKey(key);
	printf("\nKeysize: %d", keysize);
	printf("\nTextsize:%d\n", textsize);

	*/

  return 0;
}


void printKey(unsigned char * key)
{
	int i;
	printf("\nKey: ");
	for (i = 0; i < KEYLENGTH; ++i) {
		printf("(0x%02X)", key[i]);
	}

	return;
}

/* DELETE ME */
void test()
{
	FILE* fp = fopen("key.txt", "r");
	unsigned char test[22] = { 0 };
	unsigned hex;
	int i;

	fseek(fp, 2, SEEK_SET);

	for (i = 0; i < 22; ++i) {
		if (fscanf(fp, "%2x", &hex) == 1)
		{
			printf("(0x%02X) ", (char)hex);
			test[i] = (char)hex;
		}
		else
			break;
	}

	fclose(fp);

	printf("\nHex: %x", test[0]);
	printf("\n(0x%02X)\n\n", test[0]);

	return;
}