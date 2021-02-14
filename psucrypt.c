/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	unsigned char plaintextBlock[9]; /* 64 bits (+ delimiter) */
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";	
	int keysize = 0;
	int textsize = 0;
	int flag;


	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		printf("Key fetch error: %s", key);
	
	flag = getPlaintext(plaintextBlock);
	if (flag == 2)
		printf("\nADDITIONAL BLOCK OF PADDING HAPPENS HERE");
	if(flag != 0 && flag != 2)
		printf("plaintext fetch error: %s", plaintextBlock);
	
	textsize = getTextSize();
	printf("\nText: %s", plaintextBlock);
	printf("\nKey: %s", key);
	printf("\nKeysize: %d", keysize);
	printf("\nTextsize:% d\n", textsize);

  return (0);
}
