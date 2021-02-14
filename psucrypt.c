/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	char * plaintext;
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";	/*80 bit key; Extra element for terminating character*/


	printf("Hello World\n");	/* TODO DELETE ME */

	if (getKey(key) != 0)
		return (1);

	printf("\nKEY FROM  GETKEY: %s\n", key); /*TODO DELETE ME*/


  return (0);
}
