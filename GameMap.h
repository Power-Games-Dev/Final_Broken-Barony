
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <stdexcept>

// Included to access Enemy Getter methods for the DisplayMap function
#include "Enemy.h"

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

    // Constructor initialized to an empty grid of spaces
    GameMap(int width, int height) : MapWidth(width), MapHeight(height)
    {
        Grid = vector<vector<char>>(MapHeight, vector<char>(MapWidth, ' '));
    }

    // function for loading map
    void LoadMapFromBinary(int mapIndex)
    {
        if (mapIndex < 0 || mapIndex > 4)
        {
            throw out_of_range("Invalid map index! Must be between 0 and 4.");
        }

        ifstream inFile("maps.dat", ios::binary);
        if (!inFile) {
            throw runtime_error("ERROR 6-7: maps.dat could not be found or opened.");
        }

        int offset = mapIndex * (MapWidth * MapHeight) * sizeof(char);
        inFile.seekg(offset, ios::beg);

        for (int y = 0; y < MapHeight; ++y)
        {
            inFile.read(reinterpret_cast<char*>(Grid[y].data()), MapWidth * sizeof(char));
        }

        inFile.close();
    }

    // Accessor function: Pass by const reference so Enemies can read it safely
    const vector<vector<char>>& GetGrid() const
    {
        return Grid;
    }

    // Getter so the game loop can read the Control Points to generate the Annual Update
    const vector<ControlPoint>& GetControlPoints() const
    {
        return ControlPoints;
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

    // DisplayMap accepts activeUnits and playerUnit so it can print character tokens within viewDistance
    void DisplayMap(const vector<Enemy*>& activeUnits, Enemy* playerUnit)
    {
        int pX = playerUnit->GetPosX();
        int pY = playerUnit->GetPosY();
        int pVision = playerUnit->GetViewDistance();

        for (int y = 0; y < MapHeight; ++y)
        {
            for (int x = 0; x < MapWidth; ++x)
            {
                char symbolToPrint = Grid[y][x];

                for (Enemy* unit : activeUnits)
                {
                    if (unit->GetPosX() == x && unit->GetPosY() == y)
                    {
                        // This was added to Hide any INACTIVE units, because trying to know which Unit I was
                        // commanding became a challenge at 3+ Units
                        if (unit->GetFactionName() == "Human" && unit != playerUnit)
                        {
                            continue;
                        }

                        if (unit == playerUnit)
                        {
                            symbolToPrint = unit->GetSymbol();
                            break;
                        }

                        int dx = abs(unit->GetPosX() - pX);
                        int dy = abs(unit->GetPosY() - pY);

                        if (max(dx, dy) <= pVision)
                        {
                            symbolToPrint = unit->GetSymbol();
                        }
                        break;
                    }
                }
                cout << symbolToPrint;
            }
            cout << endl;
        }
    }

    // Handles Control Point Capturing, searches data, changes ownership and updates visual from 'i' to '!'
    bool CaptureCP(int targetX, int targetY, string faction)
    {
        for (auto& cp : ControlPoints)
        {
            if (cp.x == targetX && cp.y == targetY)
            {
                // Updated to prevent Infinite Farming for Units
                if (cp.controllingFaction != faction) {
                    cp.bIsControlled = true;
                    cp.controllingFaction = faction;
                    UpdateMapVisuals();
                    return true;
                }
            }
        }
        return false;
    }
};