
#pragma once
#include "Enemy.h"

// Struct for gathering intel when hired
struct IntelReport
{
    bool bFoundEnemies;
    string EnemyFactionSeen;
    bool bFoundControlPoint;
    string CPController;
};

// Spy getting actual information to keep Bard logic Simple by just returning values
class Spy : public IntelligentUnit
{
protected:
    bool bTellsTruth;
    // Added variables to track where the spy was hired so they can return to the player
    int OriginX;
    int OriginY;
    bool bIsDeployed;
    int TurnsUntilReturn;
    bool bMissionComplete;
public:
    // Spies might have standard human-like stats, but vision is high to gather info
    // Might just make them adopt the faction of who hired them.
    Spy(int x, int y, string name, bool tellsTruth)
        : IntelligentUnit(x, y,
            {
                name, 10, true, 1, 0, 1, 12
            }
        ), bTellsTruth(tellsTruth)
    {
        OriginX = x;
        OriginY = y;
        bIsDeployed = false;
        TurnsUntilReturn = 0;
        bMissionComplete = false;
    }

    // Getter for Mission Complete
    bool IsMissionComplete() const
    {
        return bMissionComplete;
    }

    bool DoesTellTruth() const
    {
        return bTellsTruth;
    }

    // GetSymbol override to print character token to hide Bard or Propagandist.
    virtual char GetSymbol() const override
    {
        return 'S';
    }

protected:
    // I need a protected helper function that gets the truth from the map
    // Both my Bard and Propagandist will use this, but the Propagandist will alter the results before returning them
    IntelReport GetTrueIntel(const vector<vector<char>>& grid)
    {
        IntelReport truth = { false, "None", false, "None" };

        // Scanning logic: Look at the grid boundaries around the Spy based on their ViewDistance to find Control Points
        int startY = max(0, PosY - Stats.ViewDistance);
        int endY = min((int)grid.size() - 1, PosY + Stats.ViewDistance);
        int startX = max(0, PosX - Stats.ViewDistance);
        int endX = min((int)grid[0].size() - 1, PosX + Stats.ViewDistance);

        for (int y = startY; y <= endY; ++y)
        {
            for (int x = startX; x <= endX; ++x)
            {
                if (grid[y][x] == '!') {
                    truth.bFoundControlPoint = true;
                    truth.CPController = "Unknown"; // Defaulting to unknown for testing
                    return truth; // Found one, no need to keep checking
                }
            }
        }
        return truth;
    }

public:
    // The main loop will call this on the turn I am hired and passesthe direction the player chose
    void Deploy(char direction)
    {
        bIsDeployed = true;
        TurnsUntilReturn = 1;

        // Pac-Man wrap-around logic. The Spy travels instantly based on their Stats.Move to scout ahead
        int speed = Stats.Move;

        if (direction == 'N') PosY = (PosY - speed + 300) % 30; // +300 prevents negative modulo errors
        else if (direction == 'S') PosY = (PosY + speed) % 30;
        else if (direction == 'W') PosX = (PosX - speed + 900) % 90;
        else if (direction == 'E') PosX = (PosX + speed) % 90;

        cout << " -> [Spy Unit] departs " << direction << " into the shadows to gather intel." << endl;
    }

    //Logic for Spy turn
    void ProcessTurn()
    {
        if (bIsDeployed && TurnsUntilReturn > 0)
        {
            TurnsUntilReturn--;
            if (TurnsUntilReturn == 0)
            {
                // Destroy Spy oncce intel is delivered and change Mision Complete flag
                PosX = -1;
                PosY = -1;
                bIsDeployed = false;
                bMissionComplete = true;
            }
        }
    }

    // Pure virtual function to have Bard and Propagandist handle reporting differently
    virtual IntelReport ReportIntel(const vector<vector<char>>& grid) = 0;
};

class Propagandist : public Spy
{
public:
    Propagandist(int x, int y) : Spy(x, y, "Spy", false)
    {
    }

    // Override intel to make Propagandists lie
    IntelReport ReportIntel(const vector<vector<char>>& grid) override
    {
        IntelReport realIntel = GetTrueIntel(grid);
        IntelReport fakeIntel;

        fakeIntel.bFoundEnemies = !realIntel.bFoundEnemies;
        fakeIntel.EnemyFactionSeen = fakeIntel.bFoundEnemies ? "Orc" : "None";
        fakeIntel.bFoundControlPoint = !realIntel.bFoundControlPoint;
        fakeIntel.CPController = fakeIntel.bFoundControlPoint ? "Elf" : "None";

        return fakeIntel;
    }
};

class Bard : public Spy
{
public:
    Bard(int x, int y) : Spy(x, y, "Spy", true)
    {
    }

    IntelReport ReportIntel(const vector<vector<char>>& grid) override
    {
        return GetTrueIntel(grid);
    }
};