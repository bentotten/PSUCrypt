/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

int encrypt(unsigned char*, unsigned char subkeyTable[ROUNDS][COLS]);
void whiten (unsigned char*, unsigned char *, unsigned char subkeyTable[ROUNDS][COLS]);

/* Utility */
void joinChar(unsigned int*, unsigned char*, unsigned char*);