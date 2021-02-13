// PSU CRYPT
// Written by Ben Totten
//
// CS585
// Last Modified: 2-9-2021

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	char* plaintext;
	printf("Hello World\n");

	if (openPlaintext() != 0)
	{
		printf("Error handling file.");
		return (1);
	}

  return (0);
}
