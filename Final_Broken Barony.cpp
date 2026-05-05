
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>

#include "Enemy.h"

using namespace std;

// CIS1202
// Joshua Powers
// Outlined 4/23/2026
//Broken Barony Game

int main()
{
	/*
	This program is a game where there will be a map that is generated ofa  local area.
	There will be a random number of control points, and you will choose a faction to be.
	There will be enemies of other factions, the goal is to end the game with the most Control Points.
	To take over a Control Point, you will have to be present and have the most amount of units.
	If at the end of a turn, there are equal numbers of opposing factions, then the Control Point is Contested.
	You must use your abilities based on your faction to take control of the Barony.
	At the end of the turn, you get a bonus number of units equal to the number of Control Points.
	Different Factions have Different Stats as well as Unit types.
	*/

	/*
	You can also hire Spies, which will be based on the number of Control Points you currently own.
	The more Control Points, the longer you can keep the spies bringing you information.
	Spies have their own stats and are neutral. There are only as many Spies available as Control Points.
	Size = Control Points
	Attack = 0
	HP = 1 (Cannot be attacked)
	Move = 5 times the number of Control Points. This is how far out they can move, then they come back.
	(This will need to be tracked because their increased movement compared to the others)
	Vision = (Move / 2)
	Units: 
		Bards: Spread the Truth
		Propagandist: Spreads Misinformation
		(Unit type is not told to the player or the enemies)
		(The console just reads them as "Spy")
		There are 2 bards for every Propagandist, so the game will calculate it this way. 2, 1, 2, 1...
		Until it runs out of Spies to assign Units.
	Once you use Spies, you cannot use spies until the start of the next year.
	*/

	/*
	Human: 
Size: 2
Attack: 3
HP: 1
Move: 1
Vision: 4
Units: 
Swordsmen: Can move 1 space as part of an attack.
Rangers: Can attack enemies 1 space away.
Traits: 
Calculated: Gets the number of units within range and determines if the attack is calculated. Humans prefer to out number the enemy 2 to 1.

Elf: 
Size: 2
Attack: 1
HP: 3
Move 2:
Vision: 6
Units: 
Assassins: Deal 1 extra damage on the first attack.
Archers: Can Attack enemies 2 spaces away.
Traits: 
Know they Enemy: Gets the number of units within range and determines if the attack is winnable. Elves will know the total attack of an enemy or group of enemies within range and will not fight a losing battle, they will instead defend.



Orc: 
Size: 3
Attack: 2
HP: 1
Move: 3
Vision: 2
Units: 
Berserkers: Ignores 1 damage from the first attack.
Shaman: Restores 1 HP to self or adjacent ally at the end of the turn.
Traits: 
Ambusher: Orcs do not calculate if a fight is winnable, they will send numbers to control points to take them over hard and fast.

	*/

	/*
	Terrain Types:
	Water: ~
	Mountain: ^
	Forest: f
	Plains: .
	Desert: #
	Arctic: *
	Swamp: s
	*/

	char water = '~', mountain = '^', forest = 'f', plains = '.', desert = '#', artctic = '*', swamp = 's';
	
	//vector <char> vWater = [water];

}
