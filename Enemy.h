
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Faction will be for specific abilities and deciding logic
struct FactionStats
{
	string FactionName;
	int ViewDistance;
	bool bIsIntelligent;
	int Size;
	int Attack;
	int HP;
	int Move;
};

class Enemy
{
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
		if (TargetLocation != nullptr)
		{
			delete TargetLocation;
		}
	}

	// Getters and Setters methods so GameMap can read where my units are 
	int GetPosX() const
	{
		return PosX;
	}
	int GetPosY() const
	{
		return PosY;
	}
	void SetPosX(int x)
	{
		PosX = x;
	}
	void SetPosY(int y)
	{
		PosY = y;
	}
	int GetViewDistance() const
	{
		return Stats.ViewDistance;
	}
	int GetMove() const
	{
		return Stats.Move;
	}

	// Cleans up dead units to fix issue with units and control points not dying correctly
	bool IsAlive() const { return Stats.HP > 0; }
	string GetFactionName() const { return Stats.FactionName; }

	// Virtual method here so each specific subclass can return its own token
	virtual char GetSymbol() const
	{
		return '?';
	}

	// Virtual methods so my specific units like ElfAssassin, OrcBerserker can override them

	virtual void Attack(Enemy* target)
	{
		if (target != nullptr)
		{
			cout << " -> [" << Stats.FactionName << " Unit] attacks for " << Stats.Attack << " damage!" << endl;
			target->TakeDamage(Stats.Attack);
		}
	}

	virtual void TakeDamage(int damageAmount)
	{
		Stats.HP -= damageAmount;
		cout << " -> [" << Stats.FactionName << " Unit] takes " << damageAmount << " damage. HP remaining: " << Stats.HP << endl;
	}

	virtual int GetAttackRange() const
	{
		return 1; // I set the default to 1 for standard melee units.
	}

	virtual void EndTurn()
	{
		// Default does nothing, but my OrcShaman will override this to heal.
	}

	bool Survey(const vector<vector<char>>& grid)
	{
		// Scan an area based on their ViewDistance
		int startY = max(0, PosY - Stats.ViewDistance);
		int endY = min((int)grid.size() - 1, PosY + Stats.ViewDistance);
		int startX = max(0, PosX - Stats.ViewDistance);
		int endX = min((int)grid[0].size() - 1, PosX + Stats.ViewDistance);

		for (int y = startY; y <= endY; ++y)
		{
			for (int x = startX; x <= endX; ++x)
			{
				// Ignores the location of the enemy, because they were getting stuck
				if (x == PosX && y == PosY) continue;

				// Checks for Conrtrolled AND Uncontrolled Control Points now instead of only Controlled ones.
				if (grid[y][x] == 'i' || grid[y][x] == '!')
				{
					if (TargetLocation == nullptr) {
						TargetLocation = new pair<int, int>(x, y);
					}
					else
					{
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
class IntelligentUnit : public Enemy
{
public:
	IntelligentUnit(int x, int y, FactionStats stats) : Enemy(x, y, stats) {}

	void DecideAction(const vector<vector<char>>& grid) override
	{
		if (Survey(grid))
		{
			cout << "===================================" << endl;
			cout << " ENEMY: [" << Stats.FactionName << "] Moving tactically towards a Key Point." << endl;
			cout << "===================================" << endl;

			// Movement towards the target
			int steps = Stats.Move;
			while (steps > 0 && TargetLocation != nullptr && (PosX != TargetLocation->first || PosY != TargetLocation->second)) {
				if (PosX < TargetLocation->first) PosX++;
				else if (PosX > TargetLocation->first) PosX--;
				else if (PosY < TargetLocation->second) PosY++;
				else if (PosY > TargetLocation->second) PosY--;
				steps--;
			}
		}
		else {
			if (Stats.bIsIntelligent)
			{
				// Logic to move enemies around the map and Patrol.
				PosX = (PosX + (rand() % 3 - 1) * Stats.Move + 900) % 90;
				PosY = (PosY + (rand() % 3 - 1) * Stats.Move + 300) % 30;
			}
		}
	}
};

// Lesser or non intelligent units class
class SwarmUnit : public Enemy
{
protected:
	// Added to track the sweep pattern
	int eastStepCount = 0;

public:
	SwarmUnit(int x, int y, FactionStats stats) : Enemy(x, y, stats) {}

	void DecideAction(const vector<vector<char>>& grid) override
	{
		if (Survey(grid))
		{
			cout << "========== ENEMY SPEAKING ==========" << endl; // TESTING ADDED TO SEE WHEN THIS IS HAPPENING
			cout << " ENEMY: [" << Stats.FactionName << "] RUSHING THE CONTROL POINT!" << endl;

			// Moves aggressively towards targets using X and Y movement
			int steps = Stats.Move;
			while (steps > 0 && TargetLocation != nullptr && (PosX != TargetLocation->first || PosY != TargetLocation->second)) {
				if (PosX < TargetLocation->first) PosX++;
				else if (PosX > TargetLocation->first) PosX--;
				if (PosY < TargetLocation->second) PosY++;
				else if (PosY > TargetLocation->second) PosY--;
				steps--;
			}
		}
		else
		{
			// Changed the Swarm Logic because they were never doing anything but running
			// Run East until they "Find Something"
			if (eastStepCount < 6)
			{
				PosX = (PosX + Stats.Move) % 90;
				eastStepCount++;
			}
			else {
				// Shift North or South after 6 Eastward moves
				if (rand() % 2 == 0)
				{
					PosY = (PosY - Stats.Move + 300) % 30;
				}
				else {
					PosY = (PosY + Stats.Move) % 30;
				}
				eastStepCount = 0; // Reset counter
			}
		}
	}
};