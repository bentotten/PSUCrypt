/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/*
TODO:
- Read in plaintext (currently only prints it)
- Get key in hex to read in correctly
*/

/* Keys */
int getKey(unsigned char *, int *);
void readKey(FILE*, unsigned char*);

/* Plaintext */
int getPlaintext(unsigned char*, int*);
void readPlaintext(FILE*, char*);

/* Utility */
void printFile(FILE*);
int getFileSize(FILE*, char*);
