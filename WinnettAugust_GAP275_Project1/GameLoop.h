#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "CollisionReferee.h"
#include <vector>
#include "Movement.h"
#include <SDL_mixer.h>

class CharAnimation;
class Movement;
class Enemy;
class CollisionReferee;
class GameStateMachine;

class GameLoop
{
private:
    static constexpr int s_kpBackgroundColor[] = { 255, 255, 255, SDL_ALPHA_OPAQUE };

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    Movement* pMover;

    Enemy* pEnemy;

    CollisionReferee m_collisionReferee;

    GameStateMachine* m_pStateMachine;

    bool m_quit;

    bool songOnePlaying = false;

    Mix_Music* m_pMusic;
    Mix_Music* m_pMusic2;
public:

    GameLoop();
    ~GameLoop();

    SDL_Renderer* GetRenderer() { return m_pRenderer; }

    CollisionReferee* GetReferee() { return &m_collisionReferee; }

    int Setup(GameStateMachine* pStateMachine);
    void RunGameLoop();
    void Cleanup();

    void Quit();

    void BGM(Mix_Music* song1, Mix_Music* song2);
private:
    bool ProcessEvents();
    void UpdateGameState(double deltaTime);
    void DisplayOutput();
};

