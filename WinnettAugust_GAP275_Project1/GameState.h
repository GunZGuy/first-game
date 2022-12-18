#pragma once
#include <SDL.h>

struct SDL_Renderer;
union SDL_Event;

//Game state interface
class GameState
{
public:
    virtual ~GameState() {}

    //Initializes Scene
    virtual void Enter() {}

    //Updates the scene
    virtual void Update(double deltaTime) {}

    //Renders Scene
    virtual void Render(SDL_Renderer* pRenderer) = 0;

    //Handles event in scene
    virtual bool HandleEvent(SDL_Event* pEvent) = 0;

    //Cleans up state before exit
    virtual void Exit() {}

};

