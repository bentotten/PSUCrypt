// PSU CRYPT
// Written by Ben Totten
//
// CS585

#include "psucrypt.h"

int getPlaintext()
{
	FILE* fp = NULL;

	fp = openPlaintext(fp);
	if (!fp)
		return 1;

	printFile(fp);

	return 0;
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


int getKey()
{
	FILE* fp = NULL;
	long unsigned int key;
	errno_t err;

	fp = openKey(fp);
	if (!fp || fp == 0)
		return 1;

	key = readKey(fp);	//TODO NOT WORKING CORRECTLY. HARD CODING FOR NOW
	key = 3;

	fclose(fp);

	return 0;
}



FILE* openKey()
{
	FILE* fp = NULL;
	errno_t err;

	err = fopen_s(&fp, "key.txt", "r");
	//err = fopen_s(&fp, "test.txt", "r");	//TODO Delete me
	if (err)
		return NULL;

	if (!fp || fp == 0)
		return NULL;
	printf("Successfully Opened Document. \n");	//TODO DELETE ME

	return fp;
}


int readKey(FILE* fp)
{
	unsigned long int key;

	if (fscanf(fp, "%lx", &key) != 1)
		return 1;

	printf("KEY FROM READKEY: %lx\n", key);

	return 0;
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

	return;
}
