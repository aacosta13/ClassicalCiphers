#include "Caesar.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Caesar::setKey(const string& key)
{ 
    if (!isdigit(key[0]))
        return false;

    cipherKey = key;
	return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Caesar::encrypt(const string& plaintext)
{ 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string encryption;

    // Build Caesar matrix to encrypt plaintext
    matrix = alphabet.substr(stoi(cipherKey) % 26, 26-(stoi(cipherKey) % 26));
    matrix += alphabet.substr(0, stoi(cipherKey) % 26);

    for (int i = 0; i < plaintext.length(); i++) {
        encryption += matrix[alphabet.find(plaintext[i])];
    }

    return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Caesar::decrypt(const string& cipherText) 
{ 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string decryption;

    // Build Caesar matrix to decrypt ciphertext
    matrix = alphabet.substr(26 - stoi(cipherKey) % 26, (stoi(cipherKey) % 26));
    matrix += alphabet.substr(0, 26 - stoi(cipherKey) % 26);

    for (int i = 0; i < cipherText.length(); i++) {
        decryption += matrix[alphabet.find(cipherText[i])];
    }

    return decryption;
}

/*
 * Prints Caesar matrix to file
 * @param fp - the file to print to
 */
void Caesar::printMatrix(FILE* fp) {

    fprintf(fp, "%s ", matrix.c_str());

	return;
}
