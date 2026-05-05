#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Faction will be for specific abilities and deciding logic
struct FactionStats {
    string FactionName;
    int ViewDistance;
    bool bIsIntelligent;
};

class Enemy {
protected:
    FactionStats Stats;
    int PosX, PosY;
    int SpawnX, SpawnY;

    // Raw pointer to track a target's location if they find one, initialized to nullptr.
    pair<int, int>* TargetLocation = nullptr;

public:
    // Constructor
    Enemy(int startX, int startY, FactionStats stats)
        : PosX(startX), PosY(startY), SpawnX(startX), SpawnY(startY), Stats(stats) {
    }

    // Virtual Destructor
    virtual ~Enemy() {
        if (TargetLocation != nullptr) {
            delete TargetLocation;
        }
    }

    bool Survey(const vector<vector<char>>& grid) {
        cout << "[" << Stats.FactionName << " Unit] is surveying the area..." << endl;

        // Scan an area based on their ViewDistance
        int startY = max(0, PosY - Stats.ViewDistance);
        int endY = min((int)grid.size() - 1, PosY + Stats.ViewDistance);
        int startX = max(0, PosX - Stats.ViewDistance);
        int endX = min((int)grid[0].size() - 1, PosX + Stats.ViewDistance);

        for (int y = startY; y <= endY; ++y) {
            for (int x = startX; x <= endX; ++x) {
                if (grid[y][x] == '!') {
                    cout << " -> Key Point '!' spotted at X:" << x << " Y:" << y << "!" << endl;

                    // Dynamically allocate a pointer to remember this spot
                    if (TargetLocation == nullptr) {
                        TargetLocation = new pair<int, int>(x, y);
                    }
                    else {
                        *TargetLocation = make_pair(x, y);
                    }
                    return true; // Stop searching when found
                }
            }
        }
        return false; // Found nothing
    }

    // Pure virtual function. Child classes define how they move based on intelligence.
    virtual void DecideAction(const vector<vector<char>>& grid) = 0;
};


// Specific Classes for intelligent units, 2 step process
class IntelligentUnit : public Enemy {
public:
    IntelligentUnit(int x, int y, FactionStats stats) : Enemy(x, y, stats) {}

    void DecideAction(const vector<vector<char>>& grid) override {
        // Step 1: Scan for the Key Point
        if (Survey(grid)) {
            cout << " -> Using advanced tactics to move adjacent to the Key Point." << endl;
            // Still needs Logic to pathfind to TargetLocation
        }
        // Step 2: If nothing is found, execute standard movement based on intelligence
        else {
            if (Stats.bIsIntelligent) {
                cout << " -> No target. Continuing exploration." << endl;
                // Move logic: PosX += (PosX >= SpawnX) ? 1 : -1;
            }
        }
    }
};

// Lesser or non intelligent units class
class SwarmUnit : public Enemy {
public:
    SwarmUnit(int x, int y, FactionStats stats) : Enemy(x, y, stats) {}

    void DecideAction(const vector<vector<char>>& grid) override {
        if (Survey(grid)) {
            cout << " -> RUSHING THE KEY POINT WITH BRUTE FORCE!" << endl;
        }
        else {
            cout << " -> No target. Following the horde in a single direction." << endl;
        }
    }
};