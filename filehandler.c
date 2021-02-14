// PSU CRYPT
// Written by Ben Totten
//
// CS585

#include "psucrypt.h"


int getKey()
{
	FILE* fp = NULL;
	unsigned long int key;
	int err;

	// Open File
	//err = fopen_s(&fp, "key.txt", "r");
	fp = fopen("test.txt", "r");	//TODO Delete me
	if (!fp || fp == 0)
		return 1;

	printf("Successfully Opened Document. \n");	//TODO DELETE ME

	// Read key in
	if (fscanf(fp, "%lx\n", &key) != 1)
		return 1;

	printf("KEY FROM READKEY: %lx\n", key);

	fclose(fp);

	return 0;
}


void printFile(FILE* fp)
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