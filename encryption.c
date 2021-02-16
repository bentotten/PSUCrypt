/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int encrypt(unsigned char * key, unsigned char * subkey)
{
	unsigned char plaintextBlock[8] = { 0 }; /* 64 bits */

	printKey(key);
	printTable(subkey, 'h');

	return 0;
}
