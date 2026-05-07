#pragma once
#include "Enemy.h"

// Base Human Class
class Human : public IntelligentUnit {
public:
    Human(int x, int y) : IntelligentUnit(x, y, { "Human", 4, true, 2, 3, 1, 1 }) {}

    // Trait: Calculated
    void DecideAction(const vector<vector<char>>& grid) override {
        // TODO: Implement "Calculated" logic here. 
        // Seek 2-to-1 odds before attacking.

        IntelligentUnit::DecideAction(grid);
    }
};

class HumanSwordsman : public Human {
public:
    HumanSwordsman(int x, int y) : Human(x, y) {}
    // TODO: Logic to move 1 space as part of an attack action
};

class HumanRanger : public Human {
public:
    HumanRanger(int x, int y) : Human(x, y) {}
    // TODO: Logic to attack 1 space away
};