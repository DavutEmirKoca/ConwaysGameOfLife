#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Game.h"

using namespace std;

void Game::menu()
{
    bool isRunning = 1;
    while (isRunning)
    {
        clearScreen();
        cout << "+----------------------+" << '\n'
             << "| Conway's Game of Life|" << '\n'
             << "+----------------------+" << '\n'
             << "|Start - 1             |" << '\n'
             << "|Info  - 2             |" << '\n'
             << "|Exit  - 3             |" << '\n'
             << "+----------------------+" << '\n';
        switch (choice())
        {
        case Choice::first:
            start();
            break;
        case Choice::second:
            info();
            break;
        case Choice::third:
            isRunning = 0;
            break;
        default:
            cout << "ERROR: Invalid choice." << '\n'
                 << '\n';
        }
    }
}

Game::Choice Game::choice()
{
    cout << "Enter your choice: ";
    string choiceString;
    getline(cin, choiceString);
    Choice choice = static_cast<Choice>(atoi(choiceString.c_str()));
    return choice;
}

void Game::info()
{
    clearScreen();

    cout << "================================================" << '\n';
    cout << "           CONWAY'S GAME OF LIFE" << '\n';
    cout << "================================================" << '\n'
         << '\n';

    cout << "WHAT IS IT?" << '\n';
    cout << "------------------------------------------------" << '\n';
    cout << "Devised by British mathematician John Horton Conway" << '\n';
    cout << "in 1970, this is a 'cellular automaton'." << '\n';
    cout << "It is a zero-player game, meaning that its evolution" << '\n';
    cout << "is determined by its initial state, requiring no" << '\n';
    cout << "further input." << '\n'
         << '\n';

    cout << "LEGEND" << '\n';
    cout << "------------------------------------------------" << '\n';
    cout << "Alive Cell : O" << '\n';
    cout << "Dead Cell  : #" << '\n'
         << '\n';

    cout << "RULES (The Cycle of Life)" << '\n';
    cout << "------------------------------------------------" << '\n';
    cout << "Each cell interacts with its 8 neighbors (horizontal," << '\n';
    cout << "vertical, and diagonal)." << '\n';
    cout << "At each step in time, the following transitions occur:" << '\n'
         << '\n';

    cout << "1. UNDERPOPULATION (DEATH):" << '\n';
    cout << "   Any live cell with fewer than 2 live neighbors dies." << '\n';

    cout << "2. OVERPOPULATION (DEATH):" << '\n';
    cout << "   Any live cell with more than 3 live neighbors dies." << '\n';

    cout << "3. SURVIVAL:" << '\n';
    cout << "   Any live cell with 2 or 3 live neighbors lives on" << '\n';
    cout << "   to the next generation." << '\n';

    cout << "4. REPRODUCTION (BIRTH):" << '\n';
    cout << "   Any dead cell with exactly 3 live neighbors becomes" << '\n';
    cout << "   a live cell." << '\n'
         << '\n';

    cout << "AVAILABLE GAME MODES" << '\n';
    cout << "------------------------------------------------" << '\n';
    cout << "1. CHAOS:" << '\n';
    cout << "   Initializes the board with a random scatter of" << '\n';
    cout << "   cells. Every simulation is unique and unpredictable." << '\n'
         << '\n';

    cout << "2. GOSPER GLIDER GUN:" << '\n';
    cout << "   The first known finite pattern that grows indefinitely." << '\n';
    cout << "   It acts as a factory, constantly producing 'Gliders'" << '\n';
    cout << "   that travel across the board." << '\n'
         << '\n';

    cout << "3. R-PENTOMINO (Methuselah):" << '\n';
    cout << "   A classic pattern starting with only 5 cells." << '\n';
    cout << "   It explodes into a chaotic evolution that lasts" << '\n';
    cout << "   for 1103 generations before stabilizing." << '\n'
         << '\n';

    cout << "================================================" << '\n';
    cout << "Press [ENTER] to return to the menu..." << '\n';

    string birTus;
    getline(cin, birTus);
}

void Game::start()
{
    setup();
    bool isRunning = 1;
    chrono::milliseconds timespan(1000 / tickSpeed);
    this_thread::sleep_for(timespan);
    while (isRunning)
    {
        clearScreen();
        render();
        draw();
        // Sleep the program according to tick speed
        chrono::milliseconds timespan(1000 / tickSpeed);
        this_thread::sleep_for(timespan);
    }
}

void Game::setup()
{
    clearScreen();
    bool tickEntered = 0;
    while (!tickEntered)
    {
        clearScreen();
        cout << "Enter the tick speed(1-100): ";
        cin >> tickSpeed;
        cin.ignore();
        if (tickSpeed < 1 || tickSpeed > 100)
            cout << "ERROR: Invalid choice." << '\n'
                 << '\n';
        else
            tickEntered = 1;
    }
    bool gameModeEntered = 0;
    while (!gameModeEntered)
    {
        clearScreen();
        cout << "+---------------------+" << '\n'
             << "|      Game Mode      |" << '\n'
             << "+---------------------+" << '\n'
             << "|Chaos Mode        - 1|" << '\n'
             << "|Gosper Glider Gun - 2|" << '\n'
             << "|R-Pentomino       - 3|" << '\n'
             << "+---------------------+" << '\n';
        switch (choice())
        {
        case Choice::first:
            chaos();
            gameModeEntered = 1;
            break;
        case Choice::second:
            gosperGliderGun();
            gameModeEntered = 1;
            break;
        case Choice::third:
            r_pentomino();
            gameModeEntered = 1;
        }
    }
    draw();
}

void Game::render()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // To detect the creature's surroundings
            for (int i = y - 1; i <= y + 1; i++)
            {
                for (int j = x - 1; j <= x + 1; j++)
                {
                    if (!(i == y && j == x))
                        if ((i >= 0 && j >= 0 && i < HEIGHT && j < WIDTH) && (creature[i * WIDTH + j].showAliveness()))
                            creature[y * WIDTH + x].increaseSurroundingCreatures();
                }
            }
        }
    }
    for (int i = 0; i < CREATURE_COUNT; i++)
    {
        creature[i].updateAlivenessStatus();
    }
}

void Game::draw()
{
    string frame = "";
    for (int i = 0; i < WIDTH; i++)
    {
        frame += '=';
    }
    frame += '\n';
    for (int i = 0; i < (WIDTH - 23) / 2; i++)
        frame += " ";
    frame += "Conway's Game of Life\n";
    for (int i = 0; i < WIDTH; i++)
    {
        frame += '=';
    }
    frame += '\n';
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            bool isAlive = creature[i * WIDTH + j].showAliveness();
            if (isAlive)
                frame += 'O';
            else
                frame += '#';
        }
        frame += '\n';
    }
    frame += "\n\nGeneration : ";
    frame += to_string(gen++);
    frame += '\n';
    cout << frame;
}

void Game::gosperGliderGun()
{
    int startX = 2;
    int startY = 2;
    int gunCoords[][2] = {
        {1, 5}, {2, 5}, {1, 6}, {2, 6}, {11, 5}, {11, 6}, {11, 7}, {12, 4}, {12, 8}, {13, 3}, {13, 9}, {14, 3}, {14, 9}, {15, 6}, {16, 4}, {16, 8}, {17, 5}, {17, 6}, {17, 7}, {18, 6}, {21, 3}, {21, 4}, {21, 5}, {22, 3}, {22, 4}, {22, 5}, {23, 2}, {23, 6}, {25, 1}, {25, 2}, {25, 6}, {25, 7}, {35, 3}, {35, 4}, {36, 3}, {36, 4}};
    int totalPoints = sizeof(gunCoords) / sizeof(gunCoords[0]);
    for (int i = 0; i < totalPoints; i++)
    {
        int x = startX + gunCoords[i][0];
        int y = startY + gunCoords[i][1];
        if (x < WIDTH && y < HEIGHT)
        {
            creature[y * WIDTH + x].changeAliveness();
        }
    }
}

void Game::r_pentomino()
{
    int midX = WIDTH / 2;
    int midY = HEIGHT / 2;
    creature[midY * WIDTH + (midX + 1)].changeAliveness();
    creature[midY * WIDTH + (midX + 2)].changeAliveness();
    creature[(midY + 1) * WIDTH + midX].changeAliveness();
    creature[(midY + 1) * WIDTH + (midX + 1)].changeAliveness();
    creature[(midY + 2) * WIDTH + (midX + 1)].changeAliveness();
}

void Game::chaos()
{
    srand(time(NULL));
    for (int i = 0; i < CREATURE_COUNT; i++)
    {
        if (!(rand() % 10))
            creature[i].changeAliveness();
    }
}

void Game::clearScreen()
{
#ifdef _WIN32

    system("cls");
#else

    std::cout << "\033[2J\033[1;1H" << '\n';
#endif
}