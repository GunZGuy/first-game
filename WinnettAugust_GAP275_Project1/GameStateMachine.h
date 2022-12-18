#pragma once
#include <SDL.h>

class GameState;
struct SDL_Renderer;
union SDL_Event;

//Handles Game state
class GameStateMachine
{
public:
    virtual ~GameStateMachine() {}

    virtual bool Init() = 0;

    //Update current state
    virtual void UpdateCurrentState(double deltaTime) = 0;

    //Render current state
    virtual void RenderCurrentState(SDL_Renderer* pRenderer) = 0;

    //Handle event in current state
    virtual bool HandleEvent(SDL_Event* pEvent) = 0;

    // Exists current state and enters new state
    virtual void ChangeState(GameState* pNewState) = 0;
};

