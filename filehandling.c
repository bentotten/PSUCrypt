// PSU CRYPT
// Written by Ben Totten
//
// CS585

#include "psucrypt.h"

int getKey()
{
	FILE* fp = NULL;
	errno_t err;

	fp = openKey(fp);
	if (!fp)
		return 1;

	printFile(fp);

	return 0;
}

int getPlaintext()
{
	FILE* fp = NULL;
	errno_t err;

	fp = openPlaintext(fp);
	if (!fp)
		return 1;

	printFile(fp);

	return 0;
}


FILE* openKey()
{
	FILE* fp = NULL;
	errno_t err;

	err = fopen_s(&fp, "key.txt", "r");
	if (err)
		return NULL;

	printf("Successfully Opened Document. \n");	//TODO DELETE ME

	return fp;
}


FILE * openPlaintext()
{
	FILE* fp = NULL;
	errno_t err;

	err = fopen_s(&fp, "plaintext.txt", "r");
	if(err)
		return NULL;

	printf("Successfully Opened Document. \n");	//TODO DELETE ME

	return fp;
}


void printFile(FILE * fp)
{
	char c;

	printf("Document:\n");	//TODO DELETE ME

	while (fp != NULL)
	{
		c = fgetc(fp);
		if (feof(fp))
			break;
		else
			printf("%c", c);
	}

	if (fp != NULL)
		fclose(fp);

	return;
}
