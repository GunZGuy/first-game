#include <iostream>
#include <SDL.h>
#include "GameLoop.h"
#include "Wall.h"
#include "ExampleGame.h"


int main(int argc, char* argv[])
{
    GameLoop game;
    ExampleGame stateMachine(&game);
    game.Setup(&stateMachine);
    game.RunGameLoop();
    game.Cleanup();
    return 0;
}
