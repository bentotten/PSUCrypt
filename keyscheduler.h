/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Global Macros */
#define ROUNDS 20
#define COLS 12

int generateSubkeys(unsigned char* , unsigned char [ROUNDS][COLS]);
/* unsigned char K(int x); */

/* Utility */
void printTable(unsigned char [ROUNDS][COLS]);
int initializeTable(unsigned char[ROUNDS][COLS]);