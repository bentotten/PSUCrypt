/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	unsigned char * plaintext = NULL;
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";	/*80 bit key; Extra element for terminating character*/
	int keysize = 0;
	int textsize = 0;


	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		printf("Key fetch error: %s", key);
	if (getPlaintext(plaintext, &textsize) != 0)
		printf("plaintext fetch error: %s", plaintext);

	printf("Keysize: %d\nTextsize: %d\n", keysize, textsize);

  return (0);
}
