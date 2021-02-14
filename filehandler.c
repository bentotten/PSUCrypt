/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int getKey()
{
	FILE* fp = NULL;
	/* unsigned long long int key; */
	unsigned long int key;
	int size;

	/* Open File */
	/* fp = fopen("key.txt", "r");	*/
	 fp = fopen("gradkey.txt", "r");	
	if (!fp || fp == 0)
		return 1;

	/* Check if 64 bit key or 80 bit key */
	size = getFileSize(fp, "k");
	printf("SIZE: %d\n", size);
	fclose(fp);
	/* fp = fopen("key.txt", "r"); */
	fp = fopen("gradkey.txt", "r");	

	printf("\nSuccessfully Opened File. \n");	/* TODO DELETE ME */

	/* Read key in */
	/* if (fscanf(fp, "%llx\n", &key) != 1) */
	if (fscanf(fp, "%lx\n", &key) != 1)
		return 1;

	/* printf("KEY FROM READKEY: %llx\n", key); */
	printf("KEY FROM READKEY: %lx\n", key);

	fclose(fp);

	return 0;
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
	int i = 0;
	char c;

	/* Check if for hex key or not*/
	if (!strcmp(flag, "k"))
	{
		printf("\nI'm a key\n");
		i = -2;	/* Compensated for the 0x at the beginning of the file */
	}

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

	return i;
}