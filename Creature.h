#ifndef CREATURE_H
#define CREATURE_H

class Creature
{
private:
    bool isAlive;
    int surroundingCreatures;

public:
    Creature() : isAlive(0), surroundingCreatures(0) {}
    void changeAliveness();
    void updateAlivenessStatus();
    bool showAliveness();
    void increaseSurroundingCreatures();
};

#endif