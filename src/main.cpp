/*
 * SELCAL Code Generation Script designed for Cross the Pond
 * Version 2 written by Andrew Ogden (1336925) on 01/04/2020
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <random>

using namespace std;

int* generatePair(int* pair, int* arrayToCompare = nullptr) { // Pair generator
    
    // Generate character indexes
    pair[0] = rand() % 14; // Generate first index 
    pair[1] = rand() % (15 - pair[0]) + (pair[0] + 1); // Generate second index - higher than first
    
    // If this is the second pair to be generated
    if (arrayToCompare) {
        
        // Generate the first index (ensure it is unique)
        while ((pair[0] == arrayToCompare[0]) || (pair[0] == arrayToCompare[1])) {
            pair[0] = rand() % 14;
        }
        
        // Generate the second index (ensure it is unique) - higher than first
        while ((pair[1] == arrayToCompare[0]) || (pair[1] == arrayToCompare[1])) {
            pair[1] = rand() % (15 - pair[0]) + (pair[0] + 1);
        }
    }
    
    // Return the pair
    return pair;
}

void generateCodes(int amount) { // Generation function    
    
    // Define the characters permitted in the code
    char chars[17] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'P', 'Q', 'R', 'S', '\0'}; // R = 14 and S = 15
    
    // Variable to hold code data
    int pair1[2]; 
    int pair2[2];
    
    // File stream
    ofstream filestream;
    
    // Open file
    filestream.open("selcal.csv");
    
    // Seed RNG
    srand(time(0));
    
    for (int i = 0; i < amount; i++) {
        // Generate the pairs 
        generatePair(pair1);
        generatePair(pair2, pair1);
        
        // Output code in console
        cout << chars[pair1[0]] << chars[pair1[1]] << '-'  
        << chars[pair2[0]] << chars[pair2[1]] << endl;
        
        // Write to file
        filestream << chars[pair1[0]] << chars[pair1[1]]
        << '-' << chars[pair2[0]] << chars[pair2[1]] << endl;
        
        // Annul the pairs to prepare for next generation
        fill(pair1, pair1+1, 0);
        fill(pair2, pair2+1, 0);
    }
    
    // Close file
    filestream.close();
}

int main() { // Main function

    // Number of codes to generate
    int numToGen = 0;
    while (numToGen == 0) { // This ensures that a 32-bit integer is entered
        if (cin.fail()) { // If a value other than a 32-bit integer was entered
            cout << "ERROR: Input was not a 32-bit integer." << endl; // Tell the user
            cin.clear(); // Reset the failure state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Remove the bad characters
        } else {
            // Query the user for input
            cout << "Please enter the number of codes to generate (32-bit integer greater than zero): ";
            cin >> numToGen; // Assign variable
        }
    }

    generateCodes(numToGen); // Generate the SELCAL codes
    
    // Closing message.
    cout << endl << "Generation successful. CSV placed into root directory." << endl;
    system("pause");
    
    return 0;
}