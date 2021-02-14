// PSU CRYPT
// Written by Ben Totten
//
// CS585
// Last Modified: 2-9-2021

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	char* plaintext;
	long unsigned int key;
	int err;

	printf("Hello World\n");	//TODO DELETE ME

	err = getKey();
	if (err)
		return err;

  return (0);
}
