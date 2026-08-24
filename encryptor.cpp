#include <iostream>
#include <fstream>
#include <vector> 
#include <string> 
using namespace std; // I do this because I do not have to write std:: everywhere.

// This function is used for RC4 Encryption
// It gets the file data and key and encrypts all of it
void rc4_HD(vector<unsigned char>& data, string key) {
    // I construct the S-box array consisting of 256 bytes
    unsigned char S[256];
    
    // I put values between 0 and 255 into the S-box
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    
    //I use this variable to exchange values.
    int j = 0;
    
    //I randomize the S-box using the key
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.length()]) % 256;
        
        // I interchange the values at locations i and j
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    
    // This is what I use to generate the keystream
    int i = 0;
    j = 0;
    
    // Looping is done for every byte of the file
    for (int k = 0; k < data.size(); k++) {
        // I update the counters
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        
        // I interchenge S[i] and S[j]
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        
        // I use this to generate a keystream byte
        unsigned char keystream = S[(S[i] + S[j]) % 256];
        
        // I XOR the data with the key stream to encrypt the data
        data[k] = data[k] ^ keystream;
    }
}

int main() {
    // I define the file name and encryption key
    string filename = "hundaol.txt";
    string key = "dechassa";
    
    //I use binary mode to open the file for reading.
    ifstream inputFile(filename.c_str(), ios::binary);
    
    // I check whether the file exists
    if (!inputFile) {
        cout << "Error: Could not open file '" << filename << "'" << endl;
        return 1;
    }
    
    // I create a buffer to store file data
    vector<unsigned char> buffer;
    unsigned char byte;
    
    // I have scanned through the whole file byte-by-byte
    while (inputFile.read((char*)&byte, 1)) {
        buffer.push_back(byte);
    }
    inputFile.close();
    
    // I calling the RC4 algorithm on the data for encryption
    rc4_HD(buffer, key);
    
    // I use this code for open the file to write the encrypted data
    ofstream outputFile(filename.c_str(), ios::binary);
    if (!outputFile) {
        cout << "Error: Could not write to file" << endl;
        return 1;
    }
    
    //I write the encoded byte back into the file
    for (int i = 0; i < buffer.size(); i++) {
        outputFile.write((char*)&buffer[i], 1);
    }
    outputFile.close();
    
    // I use this code to display success message
    cout << "Encryption complete!" << endl;
    cout << "File is now encrypted." << endl;
    
    return 0;
}