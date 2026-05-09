#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <stdexcept>

using namespace std;

// Struct to hold backend data for Control Points
struct ControlPoint
{
    int x;
    int y;
    string controllingFaction; // "None", "Human", "Elf", "Orc"
    bool bIsControlled;
};

class GameMap
{
private:
    vector<vector<char>> Grid;
    vector<ControlPoint> ControlPoints;
    int MapWidth;
    int MapHeight;

public:
    
    // function for loading map
    void LoadMapFromBinary(int mapIndex)
    {
        if (mapIndex < 0 || mapIndex > 4)
        {
            throw out_of_range("Invalid map index! Must be between 0 and 4.");
        }

        ifstream inFile("maps.dat", ios::binary);
        if (!inFile) {
            throw runtime_error("ERROR: maps.dat could not be found or opened.");
        }

        int offset = mapIndex * (MapWidth * MapHeight) * sizeof(char);
        inFile.seekg(offset, ios::beg);

        for (int y = 0; y < MapHeight; ++y)
        {
            inFile.read(reinterpret_cast<char*>(Grid[y].data()), MapWidth * sizeof(char));
        }

        inFile.close();
    }
    
    // Constructor and initialize an empty grid of spaces
    GameMap(int width, int height) : MapWidth(width), MapHeight(height)
    {

        Grid = vector<vector<char>>(MapHeight, vector<char>(MapWidth, ' '));
    }

    // Accessor function: Pass by const reference so Enemies can read it safely
    const vector<vector<char>>& GetGrid() const
    {
        return Grid;
    }

    // Update the visual map based on control point status
    void UpdateMapVisuals()
    {
        for (const auto& cp : ControlPoints)
        {
            if (cp.bIsControlled) {
                Grid[cp.y][cp.x] = '!'; // Controlled
            }
            else {
                Grid[cp.y][cp.x] = 'i'; // Uncontrolled
            }
        }
    }

    // Keep Control Points more than 6 spaces away.
    bool IsTooCloseToAnotherCP(int newX, int newY)
    {
        for (const auto& cp : ControlPoints)
        {

            double distance = std::hypot(newX - cp.x, newY - cp.y);
            if (distance <= 6.0)
            {
                return true;
            }
        }
        return false;
    }

    // Spawn a single CP randomly
    void spawnCP()
    {
        random_device randomEngine;
        uniform_int_distribution<int> dist1to6(1, 6);
        uniform_int_distribution<int> distX(0, MapWidth - 1);
        uniform_int_distribution<int> distY(0, MapHeight - 1);

        bool bPlaced = false;
        int attempts = 0; // Prevent infinite loops

        while (!bPlaced && attempts < 1000)
        {
            // Custom random logic
            int dieRollX = dist1to6(randomEngine) + 6;
            int dieRollY = dist1to6(randomEngine) + 6;

            // Generate a random spot, modified by die roll
            int potentialX = (distX(randomEngine) + dieRollX) % MapWidth;
            int potentialY = (distY(randomEngine) + dieRollY) % MapHeight;

            if (!IsTooCloseToAnotherCP(potentialX, potentialY))
            {
                spawnCP(potentialX, potentialY); // Call the overloaded function
                bPlaced = true;
            }
            attempts++;
        }
    }

    // Spawn a CP at specific coordinates
    void spawnCP(int specificX, int specificY)
    {
        ControlPoint newCP = { specificX, specificY, "None", false };
        ControlPoints.push_back(newCP);
        UpdateMapVisuals();
    }
};

void LoadMapFromBinary(int mapIndex)
{
    if (mapIndex < 0 || mapIndex > 4)
    {
        // Throw an out_of_range exception for bad indexes
        throw out_of_range("Invalid map index! Must be between 0 and 4.");
    }

    // Open the file for binary reading
    ifstream inFile("maps.dat", ios::binary);
    if (!inFile)
    {
        throw runtime_error("CRITICAL FILE ERROR: maps.dat could not be found or opened.");
    }

    // Calculate where this map starts in the binary file
    int offset = mapIndex * (MapWidth * MapHeight) * sizeof(char);

    // Jump to specific spot in the file
    inFile.seekg(offset, ios::beg);

    // Read the binary data back into GameMap Grid
    for (int y = 0; y < MapHeight; ++y)
    {
        inFile.read(reinterpret_cast<char*>(Grid[y].data()), MapWidth * sizeof(char));
    }

    inFile.close();
}