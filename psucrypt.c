/*	PSU CRYPT
	Written by Ben Totten
	CS585
*/

/* Overall: *//*
1. 64 bit block of plaintext whitened with 64 bits of key (XOR)
2. Keys go to key scheduler to gen subkeys
3. plaintext block split into four 16 bit "words". Front half (R_0 and R_1) goes to F-box
4. results are XOR'd with back half R_2 and R_3 to become the new R_0 and R_1.
5. Old R_0 and R_1 become new R_2 and R_3
6. Continues for 20 rounds
7. Whiten again by XORing with the key to get the ciphertext.
*/

/* Key Scheduler K(x) *//*
1. There will be 12 subkeys in each row.
2. Divy up key into bytes.
3. To encrypt, left rotate the key by 1 bit and store new value as K`
4. Take the key input (x) and mod it by 8 byte of the key (where 0 is the first byte)
*/

/* F Box *//*
1. Construct four values (T_0, T_1, F_0, and F_1) and return the last two.
2. Send r_0, K_0, K_1, K_2, K_3, and round # to G permutation function - Uses r0, four keys, and round number
3. Send r1, k4, k5, k6, k7, and round # to G permutation function
4. Take those results (T_0, and T_1), concatenate K_8 and k_9 and add it, t_0, and 2*T_1 together then mod 2^16 to get F_0
5. Take T_0 and T_1, concatenate k_10 and k_11 and add it, 2*T_0, and t_1 together than mod 2^16 to get F_1
6. Return F_0 and F_1
*/

/* G Permutation *//*
1. g_1 is the high 8 bits of r_0 (the left-most bits)
2. g_2 is the low 8 bits of r_0 (the right-most bits)
3. g3 = XOR g2 with k0 and Do Ftable lookup (S-box) of the result, then XOR it with g1
4. g4 is the same, but with g3 and k1 and then g2
5. g5 is the same, but with g4 and k2 and then g3
6. g6 is the same, but with g5 and k3 and then g4.
7. concatenate g5 and g6 (for 16 bits) and return the value
*/

/* S-Box *//*
		   
*/

/* PADDING *//*
The last block will need to be padded. 
While in hex form, 00 will be added to the end of the block and the last byte of padding will be 0x where x is the number of bytes of padding.
If the block is evenly 64 bits, then an entire block of padding will be added.
*/

#include "psucrypt.h"

int main(int argc, char* argv[])
{
	unsigned char plaintextBlock[9] = "\0\0\0\0\0\0\0\0\0"; /* 64 bits (+ delimiter) */
	unsigned char key[21] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	int keysize = 0;
	int textsize = 0;
	int flag;


	printf("Running...\n");	/* TODO DELETE ME */

	if (getKey(key, &keysize) != 0)
		printf("Key fetch error: %s", key);
	
	flag = getPlaintext(plaintextBlock);
	if (flag == 2)
		printf("\nADDITIONAL BLOCK OF PADDING HAPPENS HERE");
	if(flag != 0 && flag != 2)
		printf("plaintext fetch error: %s", plaintextBlock);
	
	textsize = getTextSize();
	printf("\nText: %s", plaintextBlock);
	printf("\nKey: %s", key);
	printf("\nKeysize: %d", keysize);
	printf("\nTextsize:%d\n", textsize);

  return 0;
}
