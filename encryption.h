/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

int blockEncryption(unsigned char*, unsigned char [ROUNDS][COLS]);
void whiten (unsigned char*, unsigned int *, unsigned char *);
void encrypt(unsigned int*, unsigned char[ROUNDS][COLS]);

/* Utility */
void joinChar(unsigned int*, unsigned char*, unsigned char*);