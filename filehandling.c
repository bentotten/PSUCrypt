// PSU CRYPT
// Written by Ben Totten
//
// CS585

#include "psucrypt.h"


int openPlaintext()
{
	FILE * fp;
	FILE* fopen(char* name, char* mode);

	fp = fopen("plaintextt.txt", "r");

	if (!fp)
		return (1);

	return (0);
}