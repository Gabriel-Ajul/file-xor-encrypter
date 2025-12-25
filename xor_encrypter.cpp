#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

//Prototype functions to be used

void encryptFile(ifstream &inputFile, ofstream &outputFile, const string &key);
void decryptFile(ifstream &inputFile, ofstream &outputFile, const string &key);

int main()
{
    //Declare variables to be used

    ifstream inputFile;
    ofstream outputFile;
    const string key = "mysecretkey";
    string filename;
    int choice;

    //Get the user's choice

    cout << "Welcome to the XOR Encrypter/Decrypter! Please enter your choice below:\n";

    //Loop selection screen until valid input is given

    do
    {
        cout << "\t1. Encrypt a file.\n";
        cout << "\t2. Decrypt a file.\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore();
    }
    while (choice != 1 && choice != 2);

    //Process user's choice

    switch (choice)
    {
        case 1:

            //Get the name of the file to encrypt from the user

            cout << "Enter the name of the file to encrypt: ";
            getline(cin, filename);

            //Open the input file in binary mode

            inputFile.open(filename, ios::binary);

            //Check for file open errors

            if (!inputFile)
            {
                cerr << "Error opening input file.\n";
                return 1;
            }

            //Opne the output file in binary mode

            outputFile.open("encrypted_" + filename, ios::binary);

            //Check for file open errors

            if (!outputFile)
            {
                cerr << "Error opening output file.\n";
                return 1;
            }

            //Call the file encryption function

            encryptFile(inputFile, outputFile, key);

            //Notify user of successful encryption and new file name

            cout << "File encrypted successfully to " << "encrypted_" + filename << "\n";

            //Close the input and output files

            inputFile.close();
            outputFile.close();

            break;

            case 2:

                //Comments unnecessary as process is similar to encryption

                cout << "Enter the name of the file to decrypt: ";
                getline(cin, filename);

                inputFile.open(filename, ios::binary);

                if (!inputFile)
                {
                    cerr << "Error opening input file.\n";
                    return 1;
                }

                outputFile.open("decrypted_" + filename, ios::binary);

                if (!outputFile)
                {
                    cerr << "Error opening output file.\n";
                    return 1;
                }

                decryptFile(inputFile, outputFile, key);
                
                cout << "File decrypted successfully to " << "decrypted_" + filename << "\n";

                inputFile.close();
                outputFile.close();

                break;
    }

    return 0;
}

void encryptFile(ifstream &inputFile, ofstream &outputFile, const string &key)
{
    char ch;
    size_t keyLength = key.length();
    size_t keyIndex = 0;
    while (inputFile.get(ch))
    {
        char encryptedChar = ch ^ key[keyIndex];
        outputFile << encryptedChar;
        keyIndex = (keyIndex + 1) % keyLength;
    }
}

void decryptFile(ifstream &inputFile, ofstream &outputFile, const string &key)
{
    char ch;
    size_t keyLength = key.length();
    size_t keyIndex = 0;
    while (inputFile.get(ch))
    {
        char decryptedChar = ch ^ key[keyIndex];
        outputFile << decryptedChar;
        keyIndex = (keyIndex + 1) % keyLength;
    }
}

