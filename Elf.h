#pragma once
#include "Enemy.h"

// Base Elf Class
class Elf : public IntelligentUnit {
public:
    // Pass the specific Elf stats up to the IntelligentUnit constructor
    Elf(int x, int y) : IntelligentUnit(x, y, { "Elf", 6, true, 2, 1, 3, 2 }) {}

    // Trait: Know thy Enemy
    void DecideAction(const vector<vector<char>>& grid) override {
        // TODO: Implement "Know thy Enemy" logic here before moving
        // Count enemies in ViewDistance. If outnumbered, defend.

        // Else, use base intelligent behavior
        IntelligentUnit::DecideAction(grid);
    }
};

// Specific Elf Units
class ElfAssassin : public Elf {
public:
    ElfAssassin(int x, int y) : Elf(x, y) {}
    // TODO: Add logic for dealing 1 extra damage on the first attack
};

class ElfArcher : public Elf {
public:
    ElfArcher(int x, int y) : Elf(x, y) {}
    // TODO: Add logic to attack enemies 2 spaces away
};