#pragma once
#include "Enemy.h"

class Spy : public IntelligentUnit
{
protected:
    bool bTellsTruth;
public:
    // Spies might have standard human-like stats, but vision is high to gather info
    // Might just make them adopt the faction of who hired them.
    Spy(int x, int y, string name, bool tellsTruth)
        : IntelligentUnit(x, y,
            {
                name, 5, true, 1, 0, 1, 2
            }
        ), bTellsTruth(tellsTruth)
    {
    }

    bool DoesTellTruth() const
    {
        return bTellsTruth;
    }
};

class Propagandist : public Spy
{
public:
    Propagandist(int x, int y) : Spy(x, y, "Propagandist", false)
    {
    }
};

class Bard : public Spy
{
public:
    Bard(int x, int y) : Spy(x, y, "Bard", true)
    {
    }
};