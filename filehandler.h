/*	PSU CRYPT
	Written by Ben Totten
	CS585 Cryptography
	DES Project
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
int writeCiphertextNoNewline(unsigned char* );
int getCiphertextBlock(FILE*,unsigned char*);
int getCiphertext(FILE*, unsigned char*);
int getCiphertextPSU(FILE*, unsigned char*);
int writePlaintext(unsigned char*);

/* Utility */
void printFile(FILE*);
int getFileSize(FILE*, char*);
void printText(unsigned char* plaintext);
void printKey(unsigned char*);
