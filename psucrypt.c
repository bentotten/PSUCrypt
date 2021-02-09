// PSU CRYPT
// Written by Ben Totten
//
// CS585
// Last Modified: 2-9-2021

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	printf("Hello World\n");

	if (openPlaintext() == 1)
	{
		printf("Error opening file. Does not Exist.");
		return (1);
	}

  return (0);
}
