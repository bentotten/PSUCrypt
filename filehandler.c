/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int getKey(unsigned char key[])
{
	FILE* fp = NULL;
	int size;

	/* Open File */
	fp = fopen("gradkey.txt", "r");	
	if (!fp || fp == 0)
		return 1;

	/* Check if 64 bit key or 80 bit key */
	size = getFileSize(fp, "k");
	printf("SIZE: %d\n", size);
	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */
	printf("\nSuccessfully Opened File. \n");	/* TODO DELETE ME */

	/* Read in key */
	readKey(fp, key);

	printf("\nKEY FROM READKEY: %s\n", key); /*TODO DELETE ME*/

	fclose(fp);

	return 0;
}


void readKey(FILE* fp, unsigned char key[])
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
				printf("%c", c);
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

	/* Check if for hex key or not*/
	if (!strcmp(flag, "k"))
		printf("\nI'm a key\n");

	if (!fp || fp == 0)
		return 1;

	while (fp != NULL)
	{
		c = fgetc(fp);
		if (feof(fp))
			break;
		else
		{
			printf("%c", c);
			++i;
		}
	}

	if (i >= 20)
		printf("\nI'm the 80 bit key\n");
	else
		printf("\nI'm the 64 bit key\n");

	return i;
}