#ifndef GAME_H
#define GAME_H
#include "Creature.h"
class Game
{
private:
    int tickSpeed;
    int gen;
    enum class Choice
    {
        first = 1,
        second,
        third
    };

public:
    static const int HEIGHT = 50;
    static const int WIDTH = 150;
    static const int CREATURE_COUNT = HEIGHT * WIDTH;
    Game() : creature(), gen(0) {}
    void menu();
    void start();
    void info();
    void setup();
    void render();
    void draw();
    void r_pentomino();
    void chaos();
    void gosperGliderGun();
    void clearScreen();

    Choice choice();

private:
    Creature creature[CREATURE_COUNT];
};

#endif