#include "Creature.h"
#include <iostream>
#include "Game.h"
using namespace std;

void Creature::changeAliveness()
{
    isAlive = !isAlive;
}

bool Creature::showAliveness()
{
    return isAlive;
}

void Creature::updateAlivenessStatus()
{
    if (isAlive)
    {
        if (surroundingCreatures > 3 || surroundingCreatures < 2)
            changeAliveness();
    }
    else
    {
        if (surroundingCreatures == 3)
            changeAliveness();
    }
    surroundingCreatures = 0;
}

void Creature::increaseSurroundingCreatures()
{
    surroundingCreatures++;
}