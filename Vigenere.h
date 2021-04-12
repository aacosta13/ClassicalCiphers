#ifndef VIGENERE_H
#define VIGENERE_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the vigenere cipher.
 * The class extends the abstract class 
 * CipherInterface.
 */

class Vigenere: public CipherInterface
{
	/** The public members **/
	public:

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/**	
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);
			
		/**
		 * Prints the Vigenere matrix
		 * @param fp - the file pointer
		 */
		void printMatrix(FILE* fp);
		
		/* The protected members */
	protected:
		string cipherKey;
        vector<string> matrix;
};

#endif
