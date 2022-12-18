#pragma once
#include "GameState.h"
#include "Movement.h"
#include "Wall.h"
#include <vector>
#include "GameObject.h"
#include "Spike.h"
#include "Enemy.h"
#include "Background.h"
#include "Healing.h"
#include "WinZone.h"
#include "GameObject.h"
#include "SDL_ttf.h"
#include "UITextField.h"
#include <sstream>
#include "HealthBar.h"
#include "Boss.h"
#include "RNG.h"
#include "ParticleSystem.h"

class GameObject;
class ExampleGame;
class Wall;
class Spike;
class Healing;
class WinZone;
struct SDL_Renderer;
class Movement;
class HealthBar;
class RNG;

class ExampleGameplay :
    public GameState
{
    using Vector2 = Vector2<float>;

private:
    //All Objects For Gameplay
    ExampleGame* m_pOwner;
    Movement* m_pPlayer;
    Wall* m_pWall;
    Spike* m_pSpike;
    Background* m_pBackground;
    Enemy* m_pEnemy;
    Boss* m_pBoss;
    Healing* m_pHeal;
    WinZone* m_pWin;
    HealthBar m_pHealthBar;
    UITextField* m_pText;
    TTF_Font* m_pFont;
    ParticleSystem* m_pParticle;

    std::vector<GameObject*> m_gameObjects;

    //String Stream for HP Bar
    std::stringstream strm;


public:
    RNG* random;

    //Char array for hp string
    char text[16];
    char timeBuff[255] = {0};

    ExampleGameplay(ExampleGame* pOwner, TTF_Font* pFont);
    ~ExampleGameplay();

    virtual void Enter() override;

    virtual void Update(double deltaTime) override;

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool HandleEvent(SDL_Event* pEvent) override;

    virtual void Exit() override;

    //Save Game
    void Save();

    //Get Current System Time
    std::string GetTime();
};

