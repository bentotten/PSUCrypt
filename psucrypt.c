/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	/* char * plaintext; */
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";	/*80 bit key; Extra element for terminating character*/
	int keysize = 0;


	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		return (1);

  return (0);
}
