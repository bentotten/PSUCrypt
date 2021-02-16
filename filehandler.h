/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Key File */
int getKey(unsigned char *, int *);
void readKey(FILE*, unsigned char*);

/* Plaintext File */
int getPlaintextBlock(FILE*, unsigned char*);
int getTextSize();
int padBlock(int, unsigned char*);
void padBlockRecurse(int, unsigned char, unsigned char*, unsigned char*);

/* Utility */
void printFile(FILE*);
int getFileSize(FILE*, char*);
void printPlaintext(unsigned char* plaintext);
void printKey(unsigned char*);
