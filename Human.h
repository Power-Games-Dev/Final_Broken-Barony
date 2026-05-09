#pragma once
#include "Enemy.h"

// Base Human Class
class Human : public IntelligentUnit
{
public:
    Human(int x, int y) : IntelligentUnit(x, y,
        {
        "Human", 4, true, 2, 3, 1, 1
        })
    {
    }

    // Trait: Calculated
    void DecideAction(const vector<vector<char>>& grid) override
    {
        // Added variables to tally my forces against the enemy within my ViewDistance.
        int friendlyCount = 0;
        int enemyCount = 0;

        // Iterate through the grid here based on my ViewDistance 
        // to update friendlyCount and enemyCount accurately later.

           // Added IF check, if there are enemies but I do not have 2-to-1 odds 
           // (friendlyCount < enemyCount * 2), I will delay my attack and reposition.
        if (enemyCount > 0 && friendlyCount < (enemyCount * 2))
        {
            cout << " -> " << Stats.FactionName << " lacks a 2-to-1 advantage! Regrouping." << endl;
            // Reposition logic goes here later
        }
        else
        {
            IntelligentUnit::DecideAction(grid);
        }
    }
};

class HumanSwordsman : public Human
{
public:
    HumanSwordsman(int x, int y) : Human(x, y)
    {
    }

    // Added Attack override to step forward after attack.
    virtual void Attack(Enemy* target) // I need to add this virtual method to Enemy.h later
    {
        int damageToDeal = Stats.Attack;

        // Target takes damageToDeal here later

        // After striking, I need to calculate the direction of the target 
        // and update my PosX and PosY by 1 space towards them as part of my attack.
        cout << " -> Swordsman attacks and advances!" << endl;
    }
};

class HumanRanger : public Human
{
public:
    HumanRanger(int x, int y) : Human(x, y)
    {
    }

    // Added GetAttackRange override so my rangers can attack enemies 1 space away.
    virtual int GetAttackRange() const // I need to add this virtual method to Enemy.h later
    {
        return 1;
    }
};