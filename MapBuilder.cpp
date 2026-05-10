#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAP_WIDTH = 90;
const int MAP_HEIGHT = 30;
const int NUM_MAPS = 5;

int main()
{
    // Dimensions: [5 maps] x [30 rows] x [90 columns]
    vector<vector<vector<char>>> allMaps(NUM_MAPS, vector<vector<char>>(MAP_HEIGHT, vector<char>(MAP_WIDTH, ' ')));

    // Array to hold the exact names of map files.
    string fileNames[NUM_MAPS] =
    {
        "Barren Desert Map.txt",
        "Dense Jungle Map.txt",
        "Howling Tundra Map.txt",
        "Open Plains Map.txt",
        "Swamplands Map.txt"
    };

    // Loop and read the characters into 3D vector
    for (int m = 0; m < NUM_MAPS; ++m)
    {
        ifstream inFile(fileNames[m]);

        if (!inFile)
        {
            cerr << "ERROR: Could not find " << fileNames[m] << "!" << endl;
            cerr << "Make sure the text file is in the same folder as MapBuilder." << endl;
            return 1;
        }

        string line;
        for (int y = 0; y < MAP_HEIGHT; ++y)
        {
            // Read line by line. If a line exists, copy its characters to the grid.
            if (getline(inFile, line))
            {
                for (int x = 0; x < MAP_WIDTH && x < line.length(); ++x)
                {
                    allMaps[m][y][x] = line[x];
                }
            }
        }
        inFile.close();
        cout << " -> Successfully read " << fileNames[m] << " into memory." << endl;
    }

    // Open a file for binary writing
    ofstream outFile("maps.dat", ios::binary);

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    // Write the populated maps to the binary file
    for (int m = 0; m < NUM_MAPS; ++m) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            outFile.write(reinterpret_cast<const char*>(allMaps[m][y].data()), MAP_WIDTH * sizeof(char));
        }
    }

    outFile.close();
    cout << "\nSUCCESS! maps.dat has been generated with all map data." << endl;

    return 0;
}