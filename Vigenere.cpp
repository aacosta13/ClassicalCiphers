#include "Vigenere.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Vigenere::setKey(const string& key)
{ 
    for (int i = 0; i < key.length(); i++) {
        if (isdigit(key[i]))
            return false;
    }

    cipherKey = key;
	return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Vigenere::encrypt(const string& plaintext)
{ 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string substring, extendedKey, encryption;
    int rowPos, colPos;

    // First build the matrix
    matrix.resize(26);
    for (int i = 0; i < 26; i++) {
        if (i > 0) {
            substring = alphabet.substr(i, 26-i);
            substring += alphabet.substr(0, i);

            matrix[i] = substring;
        }
        else
            matrix[i] = alphabet;
    }

    // Now we transform our plaintext into the provided key repeated over the length(plaintext) times
    for (int j = 0; j < plaintext.length(); j++) {
        extendedKey += cipherKey[j % cipherKey.length()];
    }

    for (int k = 0; k < plaintext.length(); k++) {
        rowPos = alphabet.find(extendedKey[k]);
        colPos = alphabet.find(plaintext[k]);

        encryption += matrix[rowPos][colPos];
    }

    return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Vigenere::decrypt(const string& cipherText) 
{ 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string substring, extendedKey, decryption;
    int rowPos, colPos;

    // First build the matrix
    matrix.resize(26);
    for (int i = 0; i < 26; i++) {
        if (i > 0) {
            substring = alphabet.substr(i, 26-i);
            substring += alphabet.substr(0, i);

            matrix[i] = substring;
        }
        else
            matrix[i] = alphabet;
    }

    // Now we transform our plaintext into the provided key repeated over the length(plaintext) times
    for (int j = 0; j < cipherText.length(); j++) {
        extendedKey += cipherKey[j % cipherKey.length()];
    }

    for (int k = 0; k < cipherText.length(); k++) {
        rowPos = alphabet.find(extendedKey[k]);
        colPos = matrix[rowPos].find(cipherText[k]);

        decryption += alphabet[colPos];
    }

    return decryption;
}

/*
 * Prints Vigenere matrix to file
 * @param fp - the file to print to
 */
void Vigenere::printMatrix(FILE* fp) {

    for (int i = 0; i < matrix.size(); i++) {
        fprintf(fp, "%s ", matrix[i].c_str());
        fprintf(fp, "\n");
    }

	return;
}
