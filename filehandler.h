/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/*
TODO:
- Read in plaintext (currently only prints it)
- Get key in hex to read in correctly
*/

int getPlaintext();
int getKey(unsigned char *);
void printFile(FILE*);
int getFileSize(FILE*, char *);
void readKey(FILE*, unsigned char *);

