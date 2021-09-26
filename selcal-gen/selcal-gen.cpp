/*
 * SELCAL Code Generation Script designed for Cross the Pond
 * Version 3 written by Andrew Ogden (1336925) on 01/04/2020
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <random>

// Prototypes
void generatePair(int* pair, int* arrayToCompare);
void generateCodes(int amount, int& count);

// Pair generator
void generatePair(int* pair, int* arrayToCompare = nullptr)
{    
    // Generate first index
    pair[0] = ((double)std::rand() / RAND_MAX) * (14 - 0) + 0;

    // If this is the second pair to be generated
    if (arrayToCompare) {

        // Re-generatre the first index (ensure it is unique)
        while ((pair[0] == arrayToCompare[0]) || (pair[0] == arrayToCompare[1])) {
            pair[0] = ((double)std::rand() / RAND_MAX) * (14 - 0) + 0;
        }
    }

    // Generate second index - higher than first
    pair[1] = ((double)std::rand() / RAND_MAX) * ((int)15 - ((int)pair[0] + 1)) + ((int)pair[0] + 1);

    // If this is the second pair to be generated
    if (arrayToCompare) {

        // Re-generate the second index (ensure it is unique) - higher than first
        while ((pair[1] == arrayToCompare[0]) || (pair[1] == arrayToCompare[1]) || (pair[1] == pair[0])) {
            pair[1] = ((double)std::rand() / RAND_MAX) * ((int)15 - ((int)pair[0] + 1)) + ((int)pair[0] + 1);
        }
    }

    return;
}

// Generation function  
void generateCodes(int amount, int& count)
{

    // Define the characters permitted in the code
    char chars[17] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'P', 'Q', 'R', 'S', '\0' }; // R = 14 and S = 15

    // Variable to hold code data
    int pair1[2];
    int pair2[2];

    // Duplicates?
    bool dupes = true;

    // File stream
    std::ofstream filestream;

    // Open file
    filestream.open("selcal.csv");

    // Seed RNG
    srand(time(0));

    // Pair vector so we can then check for dupes (in format "1234")
    std::vector<std::string> pairs;

    for (int i = 0; i < amount; i++) {
        // Reset
        dupes = true;

        while (dupes) {
            // Generate the pairs 
            generatePair(pair1);
            generatePair(pair2, pair1);

            // Loop and check for dupes
            std::string code = "";
            bool match = false;
            int i = 0;
            for (i; i < pairs.size(); i++) {
                // String from pairs
                code = std::to_string(pair1[0]) + std::to_string(pair1[1]) + std::to_string(pair2[0]) + std::to_string(pair2[1]);
                if (code == pairs[i]) {
                    match = true;
                    break;
                }
            }

            // K so we got here, now check the match
            if (!match) {
                // Add code to vector and break
                pairs.push_back(code);
                dupes = false;
            }
        }
       

        // Output code in console
        std::cout << chars[pair1[0]] << chars[pair1[1]] << '-'
            << chars[pair2[0]] << chars[pair2[1]] << std::endl;

        // Write to file
        filestream << (i + 1) << ',' << chars[pair1[0]] << chars[pair1[1]]
            << '-' << chars[pair2[0]] << chars[pair2[1]] << std::endl;

        // Annul the pairs to prepare for next generation
        std::fill(pair1, pair1 + 1, 0);
        std::fill(pair2, pair2 + 1, 0);

        // For comfort's sake so we can know if the correct number have been generated
        count++;
    }

    // Close file
    filestream.close();
}

// Program entry
int main()
{

    // Number of codes to generate
    int numToGen = 0;
    while (numToGen == 0) { // This ensures that a 32-bit integer is entered
        if (std::cin.fail()) { // If a value other than a 32-bit integer was entered
            std::cout << "ERROR: Input was not a 32-bit integer." << std::endl; // Tell the user
            std::cin.clear(); // Reset the failure state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Remove the bad characters
        }
        else {
            // Query the user for input
            std::cout << "Please enter the number of codes to generate (32-bit integer greater than zero): ";
            std::cin >> numToGen; // Assign variable
        }
    }

    int count = 0;

    generateCodes(numToGen, count); // Generate the SELCAL codes

    // Closing message.
    std::cout << std::endl << "Generation successful. CSV placed into root directory. Count: " << count << std::endl;
    system("pause");

    return 0;
}
