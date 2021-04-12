#include "Railfence.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Railfence::setKey(const string& key)
{ 
    if (!isalpha(key[0]))
        cipherKey = key;
        return true;

	return false;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Railfence::encrypt(const string& plaintext)
{ 
    // Form matrix for encryption
    int rowCount = 0;
    string encryption;
    matrix.resize(stoi(cipherKey));

    for (int i = 0; i < plaintext.length(); i++) {
        if (rowCount == stoi(cipherKey))
            rowCount = 0;
        
        matrix[rowCount] += plaintext[i];
        rowCount += 1;
    }

    for (int j = 0; j < matrix.size(); j++) {
        encryption += matrix[j];
    }

    return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Railfence::decrypt(const string& cipherText) 
{ 
    int railLength;
    int rowCount = 0;
    string decryption;

    // Calculate length of each rail
    if (cipherText.length() % stoi(cipherKey) != 0)
        railLength = (cipherText.length() / stoi(cipherKey)) + 1;
    else
        railLength = cipherText.length() / stoi(cipherKey);

    // Build matrix of ciphertext
    matrix.resize(stoi(cipherKey));

    for (int i = 0; i < cipherText.length(); i++) {
        if (i % railLength == 0)
            rowCount += 1;

        matrix[rowCount-1] += cipherText[i];
    }

    for (int j = 0; j < railLength; j++) {
        for (int k = 0; k < matrix.size(); k++) {
            decryption += matrix[k][j];
        }
    }

    return decryption;
}

/*
 * Prints Railfence matrix to file
 * @param fp - the file to print to
 */
void Railfence::printMatrix(FILE* fp) {

    for (int i = 0; i < matrix.size(); i++) {
        fprintf(fp, "%s ", matrix[i].c_str());
        fprintf(fp, "\n");
    }

	return;
}
