// PSU CRYPT
// Written by Ben Totten
//
// CS585

#include "psucrypt.h"


int openPlaintext()
{
	FILE * fp = NULL;
	char c;
	errno_t err;

	err = fopen_s(&fp, "plaintext.txt", "r");
	
	if(err)
		return 1;

	printFile(fp);

	while (!err && fp != NULL)
	{
		c = fgetc(fp);
		if (feof(fp))
			break;
		else
			printf("%c\n", c);
	} 
	
	if (!err && fp != NULL)
		fclose(fp);

	return 0;
}


void printFile(FILE * fp)
{
	char c;

	do {
		c = fgetc(fp);

		if (feof(fp))
			return;
		else
			printf("%c\n", c);
	} while (c != EOF);

	return;
}
