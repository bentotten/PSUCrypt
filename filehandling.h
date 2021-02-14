// PSU CRYPT
// Written by Ben Totten
//
// CS585

/*
TODO:
- Read in plaintext (currently only prints it)
- Get key in hex to read in correctly
*/

int getPlaintext();
FILE * openPlaintext();

int getKey();
FILE* openKey();
int readKey(FILE*);

void printFile(FILE*);