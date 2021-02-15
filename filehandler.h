/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Keys */
int getKey(unsigned char *, int *);
void readKey(FILE*, unsigned char*);

/* Plaintext */
int getPlaintext(unsigned char*);
int readPlaintext(FILE*, unsigned char*);
int getTextSize();

/* Utility */
void printFile(FILE*);
int getFileSize(FILE*, char*);
