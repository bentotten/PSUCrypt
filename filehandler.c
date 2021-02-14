/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int getKey(unsigned char * key, int * keysize)
{
	FILE* fp = NULL;

	/* Open File */
	fp = fopen("gradkey.txt", "r");	
	if (!fp || fp == 0)
		return 1;

	/* Check if 64 bit key or 80 bit key and send back to main by reference */
	*keysize = getFileSize(fp, "k");
	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */

	/* Read in key */
	readKey(fp, key);


	fclose(fp);

	return 0;
}


void readKey(FILE* fp, unsigned char * key)
{
	char c;
	int i;

	for (i = 0; i < 22 && (fp != NULL); ++i)
	{
		c = fgetc(fp);
		if (feof(fp))
			return;
		else
			if (i != 0 && i != 1)
			{
				key[i-2] = c;
			}
	}

	return;
}


void printFile(FILE* fp)
{
	char c;

	printf("Document:\n");

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

int getFileSize(FILE * fp, char * flag)
{
	int i = 1;
	char c;

	if (!fp || fp == 0)
		return 1;

	while (fp != NULL)
	{
		c = fgetc(fp);
		if (feof(fp))
			break;
		else
			++i;
	}

	return i;
}