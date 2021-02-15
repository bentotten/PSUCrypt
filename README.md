# PSUCrypt
Implementation of Dr Mocas' PSUCrypt algorithm in C for CS585 Cryptography.

This is a block encryption scheme using a 64 bit block size and an 80 bit key size.
A 64 bit key can also be used.

## Overall:
1. 64 bit block of plaintext whitened with 64 bits of key (XOR)
2. Keys go to key scheduler to gen subkeys
3. plaintext block split into four 16 bit "words". Front half (R_0 and R_1) goes to F-box
4. results are XOR'd with back half R_2 and R_3 to become the new R_0 and R_1.
5. Old R_0 and R_1 become new R_2 and R_3
6. Continues for 20 rounds
7. Whiten again by XORing with the key to get the ciphertext.

## Key Generation
The key is fed into a k sheduler to account for four calls in G() and two calls in F() each round. Because all offsets and round numbers are constant, the subkeys are generated en-masse at the program start.

One Round:

k0 = K(4* R# + 0) [from the 1st call to the G function]
k2 = K(4* R# +1)
k3 = K(4* R#+2)
k4 = K(4* R#+3)
k5 = K(4* R#) [from the 2st call to the G function]
k6 = K(4* R# + 1)
k7 = K(4* R# + 2)
k8 = K(4* R# + 3)
k9 = K(4* R# + 0) [from the F function]
k10 = K(4* R# + 1)
k11 = K(4* R# + 2)
k12 = K(4* R# + 3)

This is done for 20 rounds (16 for a 64 bit key) in order to completely rotate the key three times.

## Key Scheduler K(x) for Encryption
* x is the round number *4 + an offset. Because this is an 80 bit key, we will never use k_9 or k_10
1. There will be 12 subkeys in each row.
2. Label the key (K) by bytes (8 bytes for 64 bit and 10 bytes for 80 bit). Label 0-10 with highest bit as k0.
3. To encrypt, left rotate the subkey by 1 bit and store new value as K`
4. Take the round number (x) and mod it by 8 (even with the 80 bit key). 
5. Take that output as the labeled byte of K`. So if x mod 8 = 1, take K_1`.
6. Return that sub K` value.

## Key Scheduler K(x) for Decryption
The key scheduler, but with bits rotated right instead. For this program, because this is a feistel cipher, the subkey table is generated like normal and the rows are just run in reverse.

## F Box
1. Construct four values (T_0, T_1, F_0, and F_1) and return the last two.
2. Send r_0, K_0, K_1, K_2, K_3, and round # to G permutation function - Uses r0, four keys, and round number
3. Send r1, k4, k5, k6, k7, and round # to G permutation function
4. Take those results (T_0, and T_1), concatenate K_8 and k_9 and add it, t_0, and 2*T_1 together then mod 2^16 to get F_0
5. Take T_0 and T_1, concatenate k_10 and k_11 and add it, 2*T_0, and t_1 together than mod 2^16 to get F_1
6. Return F_0 and F_1


## G Permutation
1. g_1 is the high 8 bits of r_0 (the left-most bits)
2. g_2 is the low 8 bits of r_0 (the right-most bits)
3. g3 = XOR g2 with k0 and Do Ftable lookup (S-box) of the result, then XOR it with g1
4. g4 is the same, but with g3 and k1 and then g2
5. g5 is the same, but with g4 and k2 and then g3
6. g6 is the same, but with g5 and k3 and then g4.
7. concatenate g5 and g6 (for 16 bits) and return the value

## S-Box / F-table
Dr Mocas prescribes the SKIPJACK F-table in hexadecimal. The high order 4 bits of input index the row and the low order 4 bits index the column.
		   

## PADDING 
The last block will need to be padded. 
While in hex form, 00 will be added to the end of the block and the last byte of padding will be 0x where x is the number of bytes of padding.
If the block is evenly 64 bits, then an entire block of padding will be added.



