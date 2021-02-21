# PSUCrypt
Implementation of Dr Mocas' PSUCrypt algorithm in C for CS585 Cryptography.

This is a block encryption scheme using an 80 bit key size to encrpyt and decrypt arbritrarily large text files. 

## Setup
Create an 80 bit hexadecimal key and save it to a key.txt file in the working directory.

To encrypt, create a plaintext message and save it to a plaintext.txt file in the working directory.

To decrypt, create a ciphertext.txt file (in hexadecimal, with no leading 0's, but with newlines between every 64 bits (product of a collective vote)) by encrypting a plaintext message through this program or another compatible PSU graduate students encryption implementation.

Note: Current setup will append to the end of plaintext.txt and ciphertext.txt, delete these files prior to encrypting or decrypting to ensure clean message.

## To Run
In a linux environment, use makefile or GCC to compile program. After launching program, choose encryption or decryption, and whether to run in ANSI X9.23 padding mode or ECB Compatibility mode.

## Overview:
This is an ECB implementation of Dr. Mocas' homerolled encryption algorithm (PSUCrypt) based on SKIPJACK and Two-Fish.
1. A rolling 64 bits of plaintext are whitened with the first 64 bits of key.
2. Keys go to key scheduler to generate table of subkeys.
3. Plaintext block split into four 16 bit "words". High order words go to F-box for processing.
4. Results are XOR'd with low order words. 
5. Old low order words switch with old high order words and vise versa.
6. Continues for 20 rounds, completely rotating the key three times.
7. Final swap is reversed and resulting words are whitened with the key.
8. Ciphertext is appended to the end of ciphertext.txt.

## Key Generation
The key is fed into a k sheduler to account for four calls in G() and two calls in F() each round. Because all offsets and round numbers are constant, the subkeys are generated en-masse at the program start.

One Round:

k0 = K(4* R# + 0)  [from the 1st call to the G function]
k2 = K(4* R# +1)
k3 = K(4* R#+2)
k4 = K(4* R#+3)
k5 = K(4* R#)      [from the 2st call to the G function]
k6 = K(4* R# + 1)
k7 = K(4* R# + 2)
k8 = K(4* R# + 3)
k9 = K(4* R# + 0)  [from the F function]
k10 = K(4* R# + 1)
k11 = K(4* R# + 2)
k12 = K(4* R# + 3)

This is done for 20 rounds (16 for a 64 bit key) in order to completely rotate the key three times.

## Key Scheduler K(x) for Encryption
* x is the round number *4 + an offset. For 80 bit keys, we will never use k_9 or k_10.
1. There will be 12 subkeys in each row.
2. Each key (K) is labeled by bytes (8 bytes for 64 bit and 10 bytes for 80 bit) with the highest order bit as k0.
3. To encrypt, left rotate the subkey by 1 bit and store new value as K\`.
4. Take the round number (x) and mod it by 8 (even with the 80 bit key). 
5. Take that output as the labeled byte of K\`. So if x mod 8 = 1, take K_1\`.
6. Return that sub K\` value.

## Key Scheduler K(x) for Decryption
For this program, because this is a feistel cipher, the subkey table is generated like normal and the rows are input in reverse. Future versions (for larger keys) may include a decryption key scheduler where the key is right rotated instead of left rotated.

## F Box
1. Construct four values (T_0, T_1, F_0, and F_1) and return F_0, and F_1.
2. Send r_0, K_0, K_1, K_2, K_3, and the round # to G permutation function - Uses r0, four keys, and round number.
3. Send r1, k4, k5, k6, k7, and round # to G permutation function.
4. Take those results (T_0, and T_1), concatenate K_8 and k_9 and add it, t_0, and 2\*T_1 together then mod 2^16 to get F_0.
5. Take T_0 and T_1, concatenate k_10 and k_11 and add it, 2\*T_0, and t_1 together than mod 2^16 to get F_1.
6. Return F_0 and F_1.

## G Permutation
1. g_1 is the high 8 bits of r_0.
2. g_2 is the low 8 bits of r_0.
3. g3 = XOR g2 with k0 and Do Ftable lookup (S-box) of the result, then XOR it with g1.
4. g4 is the same, but with g3 and k1 and then g2.
5. g5 is the same, but with g4 and k2 and then g3.
6. g6 is the same, but with g5 and k3 and then g4.
7. concatenate g5 and g6 (for 16 bits) and return the value.

## S-Box / F-table
The SKIPJACK F-table in hexadecimal. The high order 4 bits of input index the row and the low order 4 bits index the column.

## PADDING 
All plaintext files will be padded to reach a size divisible by 64 bits. In the event a plaintext file is evenly divisibly into 64 bits, an extra 64 bit block entirely of padding will be added. In ANSI X.93 mode, the padding will consist of the hex representation of how many bytes of padding have been added. In ECB mode, all padding will be represented by 0x00. Padding is removed during decryption.



