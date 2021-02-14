/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int getKey(char key[])
{
	FILE* fp = NULL;
	//unsigned long int key = 1;
	int size;
	int byte_size = 1;

	/* Open File */
	fp = fopen("gradkey.txt", "r");	
	if (!fp || fp == 0)
		return 1;

	/* Check if 64 bit key or 80 bit key */
	size = getFileSize(fp, "k");
	printf("SIZE: %d\n", size);
	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */
	printf("\nSuccessfully Opened File. \n");	/* TODO DELETE ME */

	/* Read key in */
	/*if (fscanf(fp, "%lx\n", &key) != 1)
		return 1;
	*/

	readKey(fp, key);

	printf("\nKEY FROM READKEY: %s\n", key); /*TODO DELETE ME*/

	fclose(fp);

	return key;
}


void readKey(FILE* fp, char key[])
{
	char c;

	for (int i = 0; i < 22 && (fp != NULL); ++i)
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