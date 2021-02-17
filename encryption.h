/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Structures */
struct fboxResults {
	unsigned int x0, x1;
};

/* Encryption */
int blockEncryption(unsigned char*, unsigned char [ROUNDS][COLS]);
void whiten (unsigned char*, unsigned int *, unsigned char *);
void encrypt(unsigned int*, unsigned char[ROUNDS][COLS]);

/* Decryption */
void decrypt(unsigned int*, unsigned char [ROUNDS][COLS]);

/* Subroutines */
struct fboxResults F(unsigned int*, unsigned int*, int, unsigned char[COLS]);
unsigned int G(unsigned int*, unsigned char*, unsigned char*, unsigned char*, unsigned char*, int);

/* Utility */
void joinChar(unsigned int*, unsigned char*, unsigned char*);