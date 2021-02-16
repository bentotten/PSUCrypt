/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"


int main(int argc, char* argv[])
{
	unsigned char plaintextBlock[9] = "\0\0\0\0\0\0\0\0\0"; /* 64 bits (+ delimiter) */
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";	/* Future recast as immutable const? */
	unsigned char subkeys[ROUNDS][COLS]; /* 20 rounds, 12 subkeys, 1 byte each with 1 element for delimiter*/
	int keysize = 0;
	int textsize = 0;
	int paddingFlag;


	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		printf("Key fetch error: %s", key);
	
	if (generateSubkeys(key, subkeys) != 0)
		printf("Subkey Generation Error");


	paddingFlag = getPlaintext(plaintextBlock);
	if (paddingFlag == 2)
		printf("\nADDITIONAL BLOCK OF PADDING HAPPENS HERE");
	if(paddingFlag != 0 && paddingFlag != 2)
		printf("plaintext fetch error: %s", plaintextBlock);
	
	textsize = getTextSize();
	printf("\nText: %s", plaintextBlock);
	printf("\nKey: %s", key);
	printf("\nKeysize: %d", keysize);
	printf("\nTextsize:%d\n", textsize);

  return 0;
}
