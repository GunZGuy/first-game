#include "ExampleGameplay.h"
#include "StateMainMenu.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "StateGameOver.h"
#include "Movement.h"
#include "UITextField.h"
#include "Enemy.h"
#include <iostream>
#include "AiStateMachineEnemy.h"
#include "AiBoss.h"
#include "ParticleSystem.h"
#include "SDL_image.h"
#include <chrono>
#include <ctime>


ExampleGameplay::ExampleGameplay(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_pPlayer(nullptr)
    , m_gameObjects()
    , m_pBackground()
    , m_pHeal()
    , m_pEnemy()
    , m_pBoss()
    , m_pWall()
    , m_pWin()
    , m_pSpike()
    , m_pText()
    , m_pFont(pFont)
{

}

ExampleGameplay::~ExampleGameplay()
{
}

void ExampleGameplay::Enter()
{
    
    //Get SaveData Reference
    SaveData* pSave = m_pOwner->GetSave();
    SaveData::Data& data = pSave->GetData();

    //Check if loaded
    if (pSave->GetIsLoaded() == false)
    {
        data.m_playerPosition = Vector2{ (float)random->RandomLocation(), (float)random->RandomLocation() };
        data.m_enemyPosition = Vector2{ (float)random->RandomLocation(), (float)random->RandomLocation() };
        for (int i = 0; i < 20; ++i)
        {
            data.m_objectPosition[i] = SDL_Rect{ random->RandomLocation(), random->RandomLocation(), 50, 50 };
        }
        data.m_bossPosition = Vector2{ (float)random->RandomLocation(), (float)random->RandomLocation() };
        data.m_playerHealth = 10;
    }

    //Create Background
    m_pBackground = new Background(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ 0,0,32,32 }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pBackground);

    //Create Healing Station
    m_pHeal = new Healing(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ 0, 0,96,96 }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pHeal);

    //Get Player
    m_pPlayer = new Movement(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ 0, 0,16,16 }, m_pOwner->GetGame()->GetReferee(), m_pOwner);
    m_gameObjects.push_back(m_pPlayer);

    //Get Enemy
    m_pEnemy = new AiStateMachineEnemy(m_pOwner->GetGame()->GetRenderer(), Vector2{ data.m_enemyPosition }, Vector2{ 16, 16 }, m_pPlayer, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pEnemy);

    //Get Boss
    m_pBoss = new AiBoss(m_pOwner->GetGame()->GetRenderer(), Vector2{ data.m_bossPosition }, Vector2{ 100, 100 }, m_pPlayer, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pBoss);
    
    //Get Wall Obstacle
    m_pWall = new Wall(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ data.m_objectPosition[0] }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pWall);

    m_pWall = new Wall(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ data.m_objectPosition[1] }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pWall);

    m_pWall = new Wall(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ data.m_objectPosition[2] }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pWall);

    //Get Spike Obstacle
    m_pSpike = new Spike(m_pOwner->GetGame()->GetRenderer(),100,100, SDL_Rect{ data.m_objectPosition[3] }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pSpike);

    m_pSpike = new Spike(m_pOwner->GetGame()->GetRenderer(), 100, 100, SDL_Rect{ data.m_objectPosition[4] }, m_pOwner->GetGame()->GetReferee());
    m_gameObjects.push_back(m_pSpike);
    
    //Get WinZone
    m_pWin = new WinZone(m_pOwner->GetGame()->GetRenderer(), SDL_Rect{ data.m_objectPosition[5] }, m_pOwner->GetGame()->GetReferee(), m_pOwner);
    m_gameObjects.push_back(m_pWin);

    m_pPlayer->SetPosition(data.m_playerPosition);

}

void ExampleGameplay::Update(double deltaTime)
{
    for (GameObject* pObject : m_gameObjects)
    {
        pObject->Update(deltaTime);
    }
}

void ExampleGameplay::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderClear(pRenderer);

    for (GameObject* pObject : m_gameObjects)
    {
        pObject->Render(pRenderer);
    }

    SDL_RenderPresent(pRenderer);

}

bool ExampleGameplay::HandleEvent(SDL_Event* pEvent)
{
    //Event System for key presses
    switch (pEvent->type)
    {
        case SDL_WINDOWEVENT:
            if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
                return true;
            break;
        case SDL_KEYDOWN:
        {
            switch (pEvent->key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                m_pPlayer->TryMove(Vector2{ 0, -1 });
                break;
            case SDL_SCANCODE_A:
                m_pPlayer->TryMove(Vector2{ -1,0 });
                break;
            case SDL_SCANCODE_S:
                m_pPlayer->TryMove(Vector2{ 0,1 });

                break;
            case SDL_SCANCODE_D:
                m_pPlayer->TryMove(Vector2{ 1,0 });
                break;
            case SDL_SCANCODE_M:
                Save();
                
                m_pOwner->LoadScene(ExampleGame::SaveGame);
                break;
            }
            break;
        }
    }
    return false;
}

void ExampleGameplay::Exit()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;
    }
}

void ExampleGameplay::Save()
{
    //Get SaveData
    SaveData* pSave = m_pOwner->GetSave();
    SaveData::Data& saveData = pSave->GetData();

    //Write save data
    saveData.m_playerPosition = m_pPlayer->GetPosition();
    saveData.m_enemyPosition = m_pEnemy->GetPosition();
    saveData.m_bossPosition = m_pBoss->GetPosition();
    saveData.m_playerHealth = (float)m_pPlayer->health;

    std::cout << m_pPlayer->health << std::endl;

    //Get Current Time
    pSave->GetData().m_currentTime = GetTime();

    //Get Number of Saves
    ++pSave->GetData().m_numOfSaves;

    std::cout << pSave->GetData().m_currentTime << std::endl;
    std::cout << pSave->GetData().m_numOfSaves << std::endl;
}

std::string ExampleGameplay::GetTime()
{
    //Gets current system time
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    ctime_s(timeBuff, sizeof(timeBuff), &legacyStart);
    return timeBuff;
}
