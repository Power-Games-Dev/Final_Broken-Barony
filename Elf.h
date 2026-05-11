
#pragma once
#include "Enemy.h"

// Base Elf Class
class Elf : public IntelligentUnit
{
public:
    // Pass the specific Elf stats up to the IntelligentUnit constructor
    Elf(int x, int y) : IntelligentUnit(x, y,
        {
            "Elf", 6, true, 2, 1, 3, 8
        })
    {
    }

    // Trait: Know thy Enemy
    void DecideAction(const vector<vector<char>>& grid) override
    {
        // Added variables to tally my forces against the enemy within my ViewDistance.
        int friendlyCount = 0;
        int enemyCount = 0;

        // I will need to iterate through the grid here based on my ViewDistance
        // to update friendlyCount and enemyCount accurately later.

           // Added IF outNumbered check, I will switch to a defensive posture.
        if (enemyCount > friendlyCount)
        {
            cout << " -> " << Stats.FactionName << " is outnumbered! Taking a defensive stance." << endl;
            // Add Defensive logic here later
        }
        else
        {
            // Else, use base intelligent behavior
            IntelligentUnit::DecideAction(grid);
        }
    }
};

// Specific Elf Units
class ElfAssassin : public Elf
{
private:
    // Added boolean to track if I have made my first strike yet.
    bool bHasAttacked = false;

public:
    ElfAssassin(int x, int y) : Elf(x, y)
    {
    }

    // GetSymbol override to print character token
    virtual char GetSymbol() const override
    {
        return 'V';
    }

    // Added Attack override to deal my extra damage on the first hit.
    virtual void Attack(Enemy* target) // I need to add this virtual method to Enemy.h later
    {
        int damageToDeal = Stats.Attack;

        if (!bHasAttacked)
        {
            damageToDeal += 1;
            bHasAttacked = true;
            cout << " -> Assassin strikes for extra damage!" << endl;
        }

        // Target takes damageToDeal here later
    }
};

class ElfArcher : public Elf
{
public:
    ElfArcher(int x, int y) : Elf(x, y)
    {
    }

    // GetSymbol override to print character token
    virtual char GetSymbol() const override
    {
        return 'A';
    }

    // Added GetAttackRange override so my archers can attack from 2 spaces away.
    virtual int GetAttackRange() const // I need to add this virtual method to Enemy.h later
    {
        return 2;
    }
};