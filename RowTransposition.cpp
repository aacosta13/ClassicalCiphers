#include "RowTransposition.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool RowTransposition::setKey(const string& key)
{ 
    // Check if key is valid -- if any letters passed in, return false
	for (int i = 0; i < key.length(); i++) {
		if (isalpha(key[i]))
			return false;
        if (isspace(key[i]))
            continue;
	}

    cipherKey = key;
	return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string RowTransposition::encrypt(const string& plaintext)
{ 
    // Search for largest number of cipher key; use string container to build number
    int maxNum = 0;
    int rowCount = 0;
    int digitCount = 0; // keep track of which digit placement we are at for the index variable below
    vector<int> numberList; // used to build list of numbers passed in in-order
    string parsedDigit = "";
    string encryption;

    for (int i = 0; i < cipherKey.length(); i++) {
        if (isspace(cipherKey[i])) {
            digitCount += 1;
            numberList.push_back(stoi(parsedDigit));

            if (stoi(parsedDigit) > maxNum) {
                maxNum = stoi(parsedDigit);
                parsedDigit = "";
                continue;
            }
            else {
                parsedDigit = "";
                continue;
            }
        }
        else if (cipherKey[i] == cipherKey.back() && cipherKey[i] != ' ') {
            parsedDigit += cipherKey[i];
            numberList.push_back(stoi(parsedDigit));
            if (stoi(parsedDigit) > maxNum)
                maxNum = stoi(parsedDigit);
        }
        
        parsedDigit += cipherKey[i];
    }

    // Build matrix and return encryption
    matrix.resize(maxNum);

    for (int j = 0; j < plaintext.length(); j++) {
        if (rowCount == maxNum)
            rowCount = 0;
        
        matrix[rowCount] += plaintext[j];
        rowCount += 1;
    }

    for (int k = 0; k < numberList.size(); k++) {
        encryption += matrix[numberList[k]-1];
    }
    return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string RowTransposition::decrypt(const string& cipherText) 
{ 
    // Search for largest number of cipher key; use string container to build number
    int maxNum = 0;
    int rowCount = 0;
    int digitCount = 0; // keep track of which digit placement we are at for the index variable below
    int savedIndex = 0; // variable used to keep track of index position for ecnryption column from matrix
    int totalRows, rowRemainder; // Total rows in matrix to be used; remainder value of cipherText length % largest key value
    vector<int> numberList; // used to build list of numbers passed in in-order
    vector<string> decryptionMatrix; // used to move matrix over for easier printing after decryption
    string parsedDigit = "";
    string decryption;

    for (int i = 0; i < cipherKey.length(); i++) {
        if (isspace(cipherKey[i])) {
            digitCount += 1;
            numberList.push_back(stoi(parsedDigit));

            if (stoi(parsedDigit) > maxNum) {
                maxNum = stoi(parsedDigit);
                parsedDigit = "";
                savedIndex = digitCount - 1;
                continue;
            }
            else {
                parsedDigit = "";
                continue;
            }
        }
        else if (cipherKey[i] == cipherKey.back() && cipherKey[i] != ' ') {
            parsedDigit += cipherKey[i];
            numberList.push_back(stoi(parsedDigit));

            if (stoi(parsedDigit) > maxNum)
                maxNum = stoi(parsedDigit);
        }
        
        parsedDigit += cipherKey[i];
    }

    // Build matrix
    matrix.resize(maxNum);
    decryptionMatrix.resize(maxNum);
    totalRows = cipherText.length() / maxNum;
    rowRemainder = cipherText.length() % maxNum;
    if (cipherText.length() % maxNum != 0)
        totalRows += 1;

    for (int j = 0; j < numberList.size(); j++) {
        if (numberList[j] > rowRemainder && rowRemainder != 0) {
            for (int k = 0; k < totalRows-1; k++) {
                matrix[numberList[j]-1] += cipherText[rowCount];
                rowCount += 1;
            }
            matrix[numberList[j]-1] += 'x';
        }
        else {
            for (int k = 0; k < totalRows; k++) {
                matrix[numberList[j]-1] += cipherText[rowCount];
                rowCount += 1;
            }
        }

        decryptionMatrix[numberList[j]-1] = matrix[numberList[j]-1];
    }

    // Restructure matrix member to print properly after decryption
    for (int x = 0; x < numberList.size(); x++) {
        matrix[x] = decryptionMatrix[numberList[x]-1];
    }

    // Parse through matrix to form decryption
    for (int m = 0; m < decryptionMatrix[0].length(); m++) {
        for (int n = 0; n < maxNum; n++) {
            if (decryptionMatrix[n][m] == 'x')
                return decryption;

            decryption += decryptionMatrix[n][m];
        }
    }

    return decryption;
}

/*
 * Prints Row Transposition matrix to file
 * @param fp - the file to print to
 */
void RowTransposition::printMatrix(FILE* fp) {

    // Append x's to any columns that aren't equal size to first column
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i].length() < matrix[0].length())
            matrix[i] += 'x';
    }

    for (int j = 0; j < matrix[0].length(); j++) {
        for (int k = 0; k < matrix.size(); k++) {
            fprintf(fp, "%c ", matrix[k][j]);
        }
        fprintf(fp, "\n");
    }

	return;
}
