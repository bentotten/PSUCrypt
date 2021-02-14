/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	char* plaintext;
	long unsigned int key;
	int err;

	printf("Hello World\n");	/* TODO DELETE ME */

	key = getKey();
	printf("KEY FROM GETKEY: %lx\n", key);	/*TODO DELETE ME*/
	if (key == 1)
		return key;

  return (0);
}
