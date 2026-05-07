#pragma once
#include "Enemy.h"

// Base Orc Class inherits from SwarmUnit
class Orc : public SwarmUnit {
public:
    Orc(int x, int y) : SwarmUnit(x, y, { "Orc", 2, false, 3, 2, 1, 3 }) {}

    // Trait: Ambusher
    void DecideAction(const vector<vector<char>>& grid) override {
        // Orcs call the Swarm behavior directly
        SwarmUnit::DecideAction(grid);
    }
};

class OrcBerserker : public Orc {
public:
    OrcBerserker(int x, int y) : Orc(x, y) {}
    // TODO: Logic to ignore 1 damage from the first attack
};

class OrcShaman : public Orc {
public:
    OrcShaman(int x, int y) : Orc(x, y) {}
    // TODO: Logic to restore 1 HP to self or adjacent ally at end of turn
};