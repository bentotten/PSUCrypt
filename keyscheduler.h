/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Global Macros */
#define ROUNDS 20
#define COLS 12
#define KEYLENGTH 10

/* Keys */
int generateSubkeys(unsigned char* , unsigned char [ROUNDS][COLS]);
unsigned char K(unsigned char*, int);
unsigned char leftRotate(unsigned char);
void rightRotate(unsigned char* n, unsigned char*);

/* Utility */
void printTable(unsigned char [ROUNDS][COLS]);
int initializeTable(unsigned char[ROUNDS][COLS]);
void copyKey(unsigned char*, unsigned char* );