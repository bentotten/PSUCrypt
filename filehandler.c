/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

#include "psucrypt.h"

int getKey(unsigned char * key, int * keysize)
{
	FILE* fp = NULL;

	/* Open File */
	fp = fopen("key.txt", "r");	
	if (!fp || fp == 0)
		return 1;

	/* Check if 64 bit key or 80 bit key and send back to main by reference */
	*keysize = getFileSize(fp, "k");
	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */

	/* Read in key */
	readKey(fp, key);

	clearerr(fp);
	fclose(fp);

	return 0;
}


void readKey(FILE* fp, unsigned char * key)
{
	int flag = 0;	
	unsigned hex;
	int i;

	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */
	
	/* Checks for leading 0x on key */
	if (fgetc(fp) == '0')
		if (fgetc(fp) == 'x')
			flag = 1;

	/* Return to beginning of file */
	fseek(fp, 0, SEEK_SET);	

	/* If leading 0x */
	if (flag == 1) {
		fseek(fp, 2, SEEK_SET);
		for (i = 0; i < 22; ++i) {
			if (fscanf(fp, "%2x", &hex) == 1)
			{
				key[i] = (char)hex;
			}
			else
				break;
		}
	}

	/* If no leading 0x */
	else if (flag == 0) {
		for (i = 0; i < 22; ++i) {
			if (fscanf(fp, "%2x", &hex) == 1)
			{
				key[i] = (char)hex;
			}
			else
				break;
		}
	}

	else
		printf("\nKey Read Error\n");

	return;
}


int getPlaintextBlock(unsigned char* plaintext)
{
	FILE* fp = NULL;

	/* Open File */
	fp = fopen("plaintext.txt", "r");
	if (!fp || fp == 0)
		return 1;

	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file  TODO DELETE ME*/  

	/* Read in key */
	readPlaintext(fp, plaintext);

	clearerr(fp);
	fclose(fp);

	return 0;
}


/* Reads in plaintext 64 bits at a time to be encrypted */
int readPlaintext(FILE * fp, unsigned char * plaintext)
{
	int c = 0;


	fseek(fp, 0, SEEK_SET);	/* Return to beginning of file */

	while(fp) {
		if (c < 8) {
			if (feof(fp)) {
				/* Apply padding */
				if (c == 8)
					return 2;	/* Needs a full block of padding */
				else {
					while (c < 8) {
						plaintext[c] = '0';
						++c;
					}
					return 0;
				}
			}
			plaintext[c] = fgetc(fp);
			++c;
		}
		else
			return 0;
	}
	return 1;
}


int getTextSize()
{
	FILE* fp = NULL;
	int size;

	fp = fopen("plaintext.txt", "r");
	if (!fp || fp == 0)
		return -1;

	/* Check if 64 bit key or 80 bit key and send back to main by reference */
	size = getFileSize(fp, "p");

	fclose(fp);

	return size;
}


void printFile(FILE* fp)
{
	char c;

	printf("Document:\n");

	while (fp != NULL) {
		c = fgetc(fp);
		if (feof(fp))
			break;
		else
			printf("%c", c);
	}

	return;
}


int getFileSize(FILE* fp, char* flag)
{
	int i = 1;

	if (!fp || fp == 0)
		return 1;

	while (fp != NULL) {
		if(fgetc(fp)) {
			if (feof(fp))
				break;
			++i;
		}	
	}

	return i;
}
