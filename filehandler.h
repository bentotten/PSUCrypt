/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Key File */
int getKey(unsigned char *, int *);
void readKey(FILE*, unsigned char*);

/* Plaintext File */
int getPlaintextBlock(FILE*, unsigned char*);
int getPlaintext(FILE*, unsigned char*);
int getPlaintextPSU(FILE*, unsigned char* );
int getTextSize();
unsigned int padBlock(int, unsigned char*);
void padBlockRecurse(int, unsigned char, unsigned char*, unsigned char*);

/* Ciphertext File */
int writeCiphertext(unsigned char*);
int getCiphertextBlock(FILE*, unsigned char*);
int getCiphertext(unsigned char*);

/* Utility */
void printFile(FILE*);
int getFileSize(FILE*, char*);
void printPlaintext(unsigned char* plaintext);
void printKey(unsigned char*);
