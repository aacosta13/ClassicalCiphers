#include "Playfair.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{ 
	// Check if key is valid -- if any numbers passed in, return false
	for (int i = 0; i < key.length(); i++) {
		if (isdigit(key[i])) {
			return false;
		}
	}

	cipherKey = key;
	return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{ 
	string alphabet = "abcdefghiklmnopqrstuvwxyz";
	string usedLetters = "";
	string encryption = "";
	string keyPair = "";
	int j = 0;
	int k = 0;
	int savedIndex1X, savedIndex1Y, savedIndex2X, savedIndex2Y;

	// Begin forming matrix
	for (int i = 0; i < cipherKey.length(); i++) {
		// Used for formatting matrix
		if (k == 5) {
			j += 1;
			k = 0;
		}

		// Replace any j's with an i
		if (cipherKey[i] == 'j')
			cipherKey[i] = 'i';
		
		// Ignore spaces
		if (cipherKey[i] == ' ')
			continue;

		// Check if letter already placed in matrix; if it is, don't place again in matrix
		if (usedLetters.find(cipherKey[i]) != string::npos)
			continue;
		else
			usedLetters += cipherKey[i];

		matrix[j][k] = cipherKey[i];
		k += 1;
	}

	// Remove any remaining letters from alphabet to place the rest into the matrix
	for (int m = 0; m < usedLetters.length(); m++) {
		alphabet.erase(remove(alphabet.begin(), alphabet.end(), usedLetters[m]), alphabet.end());
	}

	// Fill rest of matrix
	for (int n = 0; n < alphabet.length(); n++) {
		// Used for formatting matrix
		if (k == 5) {
			j += 1;
			k = 0;
		}

		matrix[j][k] = alphabet[n];
		k += 1;
	}
	
	// We now perform the encryption process
	for (int p = 0; p < plaintext.length(); p++) {
		// Convert any j's to i
		if (plaintext[p] == 'j')
			keyPair += 'i';
		else
			keyPair += plaintext[p];

		// Check if at final letter of plaintext
		if (p+1 == plaintext.length() && keyPair.length() == 1)
			keyPair += 'x';

		if (keyPair.length() == 2) {
			for (int q = 0; q < 5; q++) {
				for (int r = 0; r < 5; r++) {
					// Save locations of plaintext letters from matrix
					if (keyPair[0] == matrix[q][r]) {
						savedIndex1X = r;
						savedIndex1Y = q;
					}
					if (keyPair[1] == matrix[q][r]) {
						savedIndex2X = r;
						savedIndex2Y = q;
					}
				}
			}

			// Form encryption based off of plaintext pairs' positioning in matrix
			// If same row
			if (savedIndex1Y == savedIndex2Y) {
				if (savedIndex1X + 1 == 5)
					savedIndex1X = 0;
				else
					savedIndex1X += 1;
				
				if (savedIndex2X + 1 == 5)
					savedIndex2X = 0;
				else
					savedIndex2X += 1;

				encryption += matrix[savedIndex1Y][savedIndex1X];
				encryption += matrix[savedIndex2Y][savedIndex2X];
			}
			// If same column
			else if (savedIndex1X == savedIndex2X) {
				if (savedIndex1Y + 1 == 5)
					savedIndex1Y = 0;
				else
					savedIndex1Y += 1;

				if (savedIndex2Y + 1 == 5)
					savedIndex2Y = 0;
				else
					savedIndex2Y += 1;

				encryption += matrix[savedIndex1Y][savedIndex1X];
				encryption += matrix[savedIndex2Y][savedIndex2X];
			}
			// If neither, grab corners of matrix box
			else {
				encryption += matrix[savedIndex1Y][savedIndex2X];
				encryption += matrix[savedIndex2Y][savedIndex1X];
			}

			keyPair = "";
		}
	}

	return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText) 
{ 
	string alphabet = "abcdefghiklmnopqrstuvwxyz";
	string usedLetters = "";
	string decryption = "";
	string keyPair = "";
	int j = 0;
	int k = 0;
	int savedIndex1X, savedIndex1Y, savedIndex2X, savedIndex2Y;

	// Begin forming matrix
	for (int i = 0; i < cipherKey.length(); i++) {
		// Used for formatting matrix
		if (k == 5) {
			j += 1;
			k = 0;
		}

		// Replace any j's with an i
		if (cipherKey[i] == 'j')
			cipherKey[i] = 'i';
		
		// Ignore spaces
		if (cipherKey[i] == ' ')
			continue;

		// Check if letter already placed in matrix; if it is, don't place again in matrix
		if (usedLetters.find(cipherKey[i]) != string::npos)
			continue;
		else
			usedLetters += cipherKey[i];

		matrix[j][k] = cipherKey[i];
		k += 1;
	}

	// Remove any remaining letters from alphabet to place the rest into the matrix
	for (int m = 0; m < usedLetters.length(); m++) {
		alphabet.erase(remove(alphabet.begin(), alphabet.end(), usedLetters[m]), alphabet.end());
	}

	// Fill rest of matrix
	for (int n = 0; n < alphabet.length(); n++) {
		// Used for formatting matrix
		if (k == 5) {
			j += 1;
			k = 0;
		}

		matrix[j][k] = alphabet[n];
		k += 1;
	}

	// We now perform the encryption process
	for (int p = 0; p < cipherText.length(); p++) {
		// Convert any j's to i
		if (cipherText[p] == 'j')
			keyPair += 'i';
		else
			keyPair += cipherText[p];

		// Check if at final letter of ciphertext
		if (p+1 == cipherText.length() && keyPair.length() == 1)
			keyPair += 'x';

		if (keyPair.length() == 2) {
			for (int q = 0; q < 5; q++) {
				for (int r = 0; r < 5; r++) {
					// Save locations of ciphertext letters from matrix
					if (keyPair[0] == matrix[q][r]) {
						savedIndex1X = r;
						savedIndex1Y = q;
					}
					if (keyPair[1] == matrix[q][r]) {
						savedIndex2X = r;
						savedIndex2Y = q;
					}
				}
			}

			// Form decryption based off of ciphertext pairs' positioning in matrix
			// If same row
			if (savedIndex1Y == savedIndex2Y) {
				if (savedIndex1X == 0)
					savedIndex1X = 4;
				else
					savedIndex1X -= 1;
				
				if (savedIndex2X == 0)
					savedIndex2X = 4;
				else
					savedIndex2X -= 1;

				decryption += matrix[savedIndex1Y][savedIndex1X];
				decryption += matrix[savedIndex2Y][savedIndex2X];
			}
			// If same column
			else if (savedIndex1X == savedIndex2X) {
				if (savedIndex1Y - 1 == -1)
					savedIndex1Y = 4;
				else
					savedIndex1Y -= 1;

				if (savedIndex2Y - 1 == -1)
					savedIndex2Y = 4;
				else
					savedIndex2Y -= 1;

				decryption += matrix[savedIndex1Y][savedIndex1X];
				decryption += matrix[savedIndex2Y][savedIndex2X];
			}
			// If neither, grab corners of matrix box
			else {
				decryption += matrix[savedIndex1Y][savedIndex2X];
				decryption += matrix[savedIndex2Y][savedIndex1X];
			}

			keyPair = "";
		}
	}
	
	return decryption;
}

/*
 * Prints Playfair matrix to file
 * @param fp - the file to print to
 */
void Playfair::printMatrix(FILE* fp) {
	// Print matrix to file
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			fprintf(fp, "%c ", matrix[x][y]);
		}
		fprintf(fp, "\n");
	}
}
