#include "ExampleGame.h"
#include "GameState.h"
#include "StateMainMenu.h"
#include "ExampleGameplay.h"
#include "GameLoop.h"
#include "StateGameOver.h"
#include "StateWinGame.h"
#include "WinZone.h"
#include "StateCredits.h"
#include <iostream>
#include "StateLoadGame.h"
#include "StateSaveGame.h"

ExampleGame::ExampleGame(GameLoop* pOwner)
    : m_pOwner(pOwner)
    , m_pCurrentState(nullptr)
    , m_pRenderer()
    , m_pNextState()
    , m_pFont()
    , m_pTexture()
{

}

ExampleGame::~ExampleGame()
{


    if (m_pFont != nullptr)
    {
        TTF_CloseFont(m_pFont);
    }

    //exit current state
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
    }

    //delete current state

    delete m_pCurrentState;
}

bool ExampleGame::Init()
{
    //Set Font
    m_pFont = TTF_OpenFont("assets/arial.ttf", 20);

    // Load main menu
    LoadScene(MainMenu);

    return true;
}

void ExampleGame::UpdateCurrentState(double deltaTime)
{
    if (m_pNextState != nullptr)
    {
        ChangeState(m_pNextState);
        m_pNextState = nullptr;
    }

    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Update(deltaTime);
    }

}

void ExampleGame::RenderCurrentState(SDL_Renderer* pRenderer)
{

    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Render(pRenderer);
    }
}

bool ExampleGame::HandleEvent(SDL_Event* pEvent)
{
    if (m_pCurrentState == nullptr)
    {
        return false;
    }
    else
    {
        return m_pCurrentState->HandleEvent(pEvent);
    }

}

void ExampleGame::ChangeState(GameState* pNewState)
{
    //exit current state
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
    }

    //delete old state

    delete m_pCurrentState;

    // load new state
    m_pCurrentState = pNewState;

    // enter new state
    pNewState->Enter();
}

//Load scenes
void ExampleGame::LoadScene(SceneName scene)
{
    switch (scene)
    {
    case SceneName::MainMenu:
        m_pNextState = new StateMainMenu(this, m_pFont);
        break;
    case SceneName::Gameplay:
        m_pNextState = new ExampleGameplay(this, m_pFont);
        break;
    case SceneName::GameOver:
        m_pNextState = new StateGameOver(this, m_pFont);
        break;
    case SceneName::GameWin:
        m_pNextState = new StateWinGame(this, m_pFont);
        break;
    case SceneName::LoadGame:
        m_pNextState = new StateLoadGame(this, m_pFont);
        break;
    case SceneName::SaveGame:
        m_pNextState = new StateSaveGame(this, m_pFont);
        break;
    case SceneName::Credits:
        m_pNextState = new StateCredits(this, m_pFont);
        break;
    }
}
