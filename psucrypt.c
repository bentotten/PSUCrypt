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


	printf("Hello World\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		return (1);
	printf("\nSIZE: %d\n", keysize);

	printf("\nKEY FROM  GETKEY: %s\n", key); /*TODO DELETE ME*/


  return (0);
}
