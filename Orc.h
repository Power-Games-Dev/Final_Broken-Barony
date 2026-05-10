#pragma once
#include "Enemy.h"

// Base Orc Class inherits from SwarmUnit
class Orc : public SwarmUnit
{
public:
    Orc(int x, int y) : SwarmUnit(x, y,
        {
            "Orc", 2, false, 3, 2, 1, 3
        })
    {
    }

    // Trait: Ambusher
    void DecideAction(const vector<vector<char>>& grid) override
    {
        // Orcs call the Swarm behavior directly
        SwarmUnit::DecideAction(grid);
    }
};

class OrcBerserker : public Orc
{
private:
    // Added boolean to track if I have been struck yet in combat.
    bool bHasTakenDamage = false;

public:
    OrcBerserker(int x, int y) : Orc(x, y)
    {
    }

    // Added TakeDamage override so I can reduce the damage of the first hit.
    virtual void TakeDamage(int damageAmount) // I need to add this virtual method to Enemy.h later
    {
        if (!bHasTakenDamage)
        {
            cout << " -> Berserker shrugs off the initial blow!" << endl;
            damageAmount -= 1;

            // I must ensure the damage does not drop below zero, 
            // otherwise weak attacks might accidentally heal.
            if (damageAmount < 0)
            {
                damageAmount = 0;
            }

            bHasTakenDamage = true;
        }

        // Subtract damageAmount from my Stats.HP here later
    }
};

class OrcShaman : public Orc
{
public:
    OrcShaman(int x, int y) : Orc(x, y)
    {
    }

    // Added EndTurn override to handle my end-of-turn healing ability.
    virtual void EndTurn() // I need to add this virtual method to Enemy.h later
    {
        /* Check the coordinates directly adjacent to my PosX and PosY.
           If an ally is detected in one of those spaces, add 1 to their Stats.HP.
           If there is not an adjacent ally, add 1 to my own Stats.HP. */

        cout << " -> Shaman channels restorative energy at the end of the turn." << endl;
    }
};