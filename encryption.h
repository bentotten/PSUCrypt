/*	PSU CRYPT
	Written by Ben Totten
	CS585 Cryptography
	DES Project
*/

/* Structures and Globals */
struct fboxResults {
	unsigned int x0, x1;
};

/* Encryption */
int blockEncryption(unsigned char*, unsigned char [ROUNDS][COLS]);
int addPaddingBlock(unsigned char*, unsigned char[ROUNDS][COLS]);
void whiten (unsigned char*, unsigned int *, unsigned char *);
void encrypt(unsigned int*, unsigned char[ROUNDS][COLS]);
void lastWhiten(unsigned int*, unsigned char*, unsigned char*);

/* Decryption */
int blockDecryption(unsigned char*, unsigned char[ROUNDS][COLS]);
int removePadding(unsigned char*);

/* Subroutines */
struct fboxResults F(unsigned int, unsigned int, int, unsigned char[COLS]);
unsigned int G(unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, int);
unsigned char ftable(unsigned char);

/* Utility */
void joinChar(unsigned int*, unsigned char*, unsigned char*);
void splitInt(unsigned int*, unsigned char*, unsigned char*);
void reverseSubkeys(unsigned char[ROUNDS][COLS]);
void copyArray(unsigned char*, unsigned char[COLS]);