#include "StateMainMenu.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "UIButton.h"
#include "UITextField.h"
#include <iostream>
#include "SaveData.h"

StateMainMenu::StateMainMenu(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_gameObjects()
    , m_keyboardButtonFocus(-1)
{
    //Create text and buttons for main menu
    m_gameObjects.push_back(new UITextField(pFont, "Game", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 100 }, pOwner->GetGame()->GetRenderer(), 1000));


    UIButton* pPlayButton = new UIButton(SDL_Rect{ 300,150,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/startbutton.png", "assets/startbuttonhighlight.png");

    pPlayButton->SetCallback([pOwner]()->void
    {
            pOwner->LoadScene(ExampleGame::Gameplay);
    });

    m_gameObjects.push_back(pPlayButton);

    UIButton* pQuitButton = new UIButton(SDL_Rect{ 300,300,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/quitbutton.png", "assets/quitbuttonhighlight.png");

    pQuitButton->SetCallback([pOwner]()->void
        {
            pOwner->GetGame()->Quit();
        });

    m_gameObjects.push_back(pQuitButton);

    UIButton* pCredits = new UIButton(SDL_Rect{ 300,400,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/credits.png", "assets/creditshighlight.png");

    pCredits->SetCallback([pOwner]()->void
        {
            pOwner->LoadScene(ExampleGame::Credits);
        });

    m_gameObjects.push_back(pCredits);

    UIButton* pLoadGameButton = new UIButton(SDL_Rect{ 225,500,300,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/loadGame2.png", "assets/loadGame2Highlight.png");

    pLoadGameButton->SetCallback([pOwner]()->void
        {
    pOwner->LoadScene(ExampleGame::LoadGame);
        });

    m_gameObjects.push_back(pLoadGameButton);

    m_buttonSet.push_back(pPlayButton);
    m_buttonSet.push_back(pQuitButton);
    m_buttonSet.push_back(pCredits);
    m_buttonSet.push_back(pLoadGameButton);
}

StateMainMenu::~StateMainMenu()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;

    }

}

void StateMainMenu::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(pRenderer);
    
    for (GameObject* object : m_gameObjects)
    {
        object->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}

bool StateMainMenu::HandleEvent(SDL_Event* pEvent)
{
    switch (pEvent->type)
    {
    case SDL_WINDOWEVENT:
        if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
        {
            return true;
        }
        break;
    case SDL_KEYDOWN:
    {
        switch (pEvent->key.keysym.scancode)
        {
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
        {
            ChangeButtonFocus(1);
            break;
        }
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
        {
            ChangeButtonFocus(-1);
            break;
        }
        case SDL_SCANCODE_RETURN:
        {
            m_buttonSet[m_keyboardButtonFocus]->Trigger();
            break;
        }
        }
    }
    }
    for (GameObject* object : m_gameObjects)
    {
        object->HandleEvent(pEvent);
    }
    return false;
}

//Changes button focus when using keyboard
void StateMainMenu::ChangeButtonFocus(int direction)
{
    m_keyboardButtonFocus = (m_keyboardButtonFocus + direction) % m_buttonSet.capacity();
    for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
    {
        //if this is selected button, highlight.
        m_buttonSet[i]->SetHighlight(i == m_keyboardButtonFocus);
    }
}
