#include <string>
#include <iostream>
#include <fstream>
#include "CipherInterface.h"
#include "Playfair.h"
#include "RowTransposition.h"
#include "Railfence.h"
#include "Vigenere.h"
#include "Caesar.h"

using namespace std;

int main(int argc, char** argv)
{
	// Default instance
	CipherInterface* cipher = NULL;

	/* Create an instance of the Playfair cipher */		
	if (strcmp(argv[1], "plf") == 0) {
		cipher = new Playfair();

		// Return error if invalid key
		if (cipher->setKey(argv[2]) == false)
			cipher = NULL;
	
		// If encrypt, read input from file then call method
		if (strcmp(argv[3], "enc") == 0) {
			string plaintext, encryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> plaintext;
			encryption = cipher->encrypt(plaintext);

			// Write encrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The encrypted string is: %s\n", encryption.c_str());
			fprintf(outFile, "\nThe Playfair matrix used is below: \n");
			static_cast<Playfair*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
		// Else if decrypt, read input from file then call method
		else if (strcmp(argv[3], "dec") == 0) {
			string ciphertext, decryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> ciphertext;
			decryption = cipher->decrypt(ciphertext);
			
			// Write decrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The decrypted string is: %s\n", decryption.c_str());
			fprintf(outFile, "\nThe Playfair matrix used is below: \n");
			static_cast<Playfair*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
	}

	/* Create instance of the row transposition cipher */
	else if (strcmp(argv[1], "rts") == 0) {
		cipher = new RowTransposition();

		// Return error if invalid key
		if (cipher->setKey(argv[2]) == false)
			cipher = NULL;

		if (strcmp(argv[3], "enc") == 0) {
			string plaintext, encryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> plaintext;
			encryption = cipher->encrypt(plaintext);
			
			// Write encrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The encrypted string is: %s\n", encryption.c_str());
			fprintf(outFile, "\nThe Row Transposition matrix used is below: \n");
			static_cast<RowTransposition*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
		// Else if decrypt, read input from file then call method
		else if (strcmp(argv[3], "dec") == 0) {
			string ciphertext, decryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> ciphertext;
			decryption = cipher->decrypt(ciphertext);

			// Write decrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The decrypted string is: %s\n", decryption.c_str());
			fprintf(outFile, "\nThe Row Transposition matrix used is below: \n");
			static_cast<RowTransposition*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
	}

	// Instance of Railfence cipher
	else if (strcmp(argv[1], "rfc") == 0) {
		cipher = new Railfence();

		// Return error if invalid key
		if (cipher->setKey(argv[2]) == false)
			cipher = NULL;

		if (strcmp(argv[3], "enc") == 0) {
			string plaintext, encryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> plaintext;
			encryption = cipher->encrypt(plaintext);

			// Write encrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The encrypted string is: %s\n", encryption.c_str());
			fprintf(outFile, "\nThe Railfence matrix used is below: \n");
			static_cast<Railfence*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
		else if (strcmp(argv[3], "dec") == 0) {
			string ciphertext, decryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> ciphertext;
			decryption = cipher->decrypt(ciphertext);

			// Write decrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The decrypted string is: %s\n", decryption.c_str());
			fprintf(outFile, "\nThe Railfence matrix used is below: \n");
			static_cast<Railfence*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
	}

	// Instance of Vigenre cipher
	else if (strcmp(argv[1], "vig") == 0) {
		cipher = new Vigenere();

		// Return error if invalid key
		if (cipher->setKey(argv[2]) == false)
			cipher = NULL;

		if (strcmp(argv[3], "enc") == 0) {
			string plaintext, encryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> plaintext;
			encryption = cipher->encrypt(plaintext);

			// Write encrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The encrypted string is: %s\n", encryption.c_str());
			fprintf(outFile, "\nThe Vigenere matrix used is below: \n");
			static_cast<Vigenere*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
		else if (strcmp(argv[3], "dec") == 0) {
			string ciphertext, decryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> ciphertext;
			decryption = cipher->decrypt(ciphertext);

			// Write decrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The decrypted string is: %s\n", decryption.c_str());
			fprintf(outFile, "\nThe Vigenere matrix used is below: \n");
			static_cast<Vigenere*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
	}

	// Instance of Caesar cipher
	else if (strcmp(argv[1], "ces") == 0) {
		cipher = new Caesar();

		// Return error if invalid key
		if (cipher->setKey(argv[2]) == false)
			cipher = NULL;

		if (strcmp(argv[3], "enc") == 0) {
			string plaintext, encryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> plaintext;
			encryption = cipher->encrypt(plaintext);

			// Write encrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The encrypted string is: %s\n", encryption.c_str());
			fprintf(outFile, "\nThe Caesar matrix used is below: \n");
			static_cast<Caesar*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
		else if (strcmp(argv[3], "dec") == 0) {
			string ciphertext, decryption;
			ifstream inputFile;
			FILE* outFile;
			inputFile.open(argv[4]);

			inputFile >> ciphertext;
			decryption = cipher->decrypt(ciphertext);

			// Write decrypted text and matrix to file
			outFile = fopen(argv[5], "w");
			fprintf(outFile, "The decrypted string is: %s\n", decryption.c_str());
			fprintf(outFile, "\nThe Caesar matrix used is below: \n");
			static_cast<Caesar*>(cipher)->printMatrix(outFile);

			// Close any open files
			inputFile.close();
			fclose(outFile);
		}
	}

	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}	
	
	return 0;
}
