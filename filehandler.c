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

/* If PSU is set to 0, not in PSU environment */
int getPlaintextBlock(FILE* fp, unsigned char* plaintext)
{
	if (PSU == 0)
		return getPlaintext(fp, plaintext);
	if (PSU == 1)
		return getPlaintextPSU(fp, plaintext);
}


/* Non-PSU: Reads in plaintext 64 bits (8 chars) at a time to be encrypted */
int getPlaintext(FILE* fp, unsigned char* plaintext)
{
	unsigned char paddingSize;
	unsigned char c;
	int i;

	/* Read in 64 bits; Apply padding; return 2 if full block of padding is needed */
	for (i = 0; i < 8; ++i) {

		c = fgetc(fp);

		if (feof(fp)) {
			if (i == 7)
			{
				paddingSize = padBlock(i, plaintext);
				plaintext[i] = paddingSize;
				return 0;
			}
			else {
				paddingSize = padBlock(i, plaintext);
				plaintext[i] = paddingSize;
				return 0;
			}
		}

		plaintext[i] = c;
	}

	/* If next move of pointer is EOF, then text block was perfectly sized 64 bits */
	c = fgetc(fp);

	if (feof(fp)) {
		return 2;
	}
	else {
		fseek(fp, -1, SEEK_CUR);
		return 0;
	}

	return 1;
}


/* PSU Environment: Reads in plaintext 64 bits (8 chars) at a time to be encrypted with off-by-one-error fixed*/
int getPlaintextPSU(FILE* fp, unsigned char* plaintext)
{
	unsigned char paddingSize;
	unsigned char c;
	int i;

	printf("\n\nIN PSU ENVIRONMENT\n");

	/* Read in 64 bits; Apply padding; return 2 if full block of padding is needed */
	for (i = 0; i < 9; ++i) {

		c = fgetc(fp);
		if (feof(fp)) {
			--i;
			if (i == 7)
			{
				paddingSize = padBlock(i, plaintext);
				plaintext[i] = paddingSize;
				return 0;
			}
			else {
				paddingSize = padBlock(i, plaintext);
				plaintext[i] = paddingSize;
				printPlaintext(plaintext);
				return 0;
			}
		}

		plaintext[i] = c;
	}

	/* If next move of pointer is EOF, then text block was perfectly sized 64 bits */
	c = fgetc(fp);
	if (feof(fp)) {
		return 2;
	}
	else {
		fseek(fp, -2, SEEK_CUR);
		return 0;
	}

	return 1;
}


unsigned int padBlock(int i, unsigned char* plaintext)
{
	unsigned char hold;
	unsigned int paddingSize = 0;

	padBlockRecurse(i, paddingSize, plaintext, &hold);

	return hold;
}

void padBlockRecurse(int i, unsigned char paddingSize, unsigned char * test, unsigned char * hold)
{
	if (i >= 7) {
		*hold = ++paddingSize;
		return;
	}

	padBlockRecurse(++i, ++paddingSize, test, hold);

	test[i] = *hold;
	return;
}

int writeCiphertext(unsigned char* ciphertext)
{
	FILE* fp; 
	char toWrite[17];
	int i;

	fp = fopen("ciphertext.txt", "a");
	if (!fp || fp == 0)
		return 1;

	

	sprintf(toWrite, "%02x%02x%02x%02x%02x%02x%02x%02x", ciphertext[0], ciphertext[1], ciphertext[2], ciphertext[3], ciphertext[4], ciphertext[5], ciphertext[6], ciphertext[7]);
	printf("\nTo Write: %s", toWrite);

	for (i = 0; i < 9; ++i) {
		fputc(toWrite[i], fp);
	}

	fclose(fp);

	return 0;
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


void printKey(unsigned char* key)
{
	int i;
	printf("\nKey: ");
	for (i = 0; i < KEYLENGTH; ++i) {
		printf("(0x%02X)", key[i]);
	}

	return;
}


void printPlaintext(unsigned char* plaintext)
{
	int i;
	printf("\nPlaintext: ");
	for (i = 0; i < 8; ++i) {
		printf("%c", plaintext[i]);
	}

	return;
}