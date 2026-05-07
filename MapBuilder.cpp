#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAP_WIDTH = 90;
const int MAP_HEIGHT = 30;
const int NUM_MAPS = 5;

int main() {
    // Dimensions: [5 maps] x [30 rows] x [90 columns]
    vector<vector<vector<char>>> allMaps(NUM_MAPS, vector<vector<char>>(MAP_HEIGHT, vector<char>(MAP_WIDTH, ' ')));

    // TODO: Populate 'allMaps' 5 maps

    // Open a file for binary writing
    ofstream outFile("maps.dat", ios::binary);

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    // Write the maps to the binary file
    for (int m = 0; m < NUM_MAPS; ++m) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            outFile.write(reinterpret_cast<const char*>(allMaps[m][y].data()), MAP_WIDTH * sizeof(char));
        }
    }

    outFile.close();
    cout << "maps.dat has been created." << endl;

    return 0;
}