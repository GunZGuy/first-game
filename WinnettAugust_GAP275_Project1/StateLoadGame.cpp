#include "StateLoadGame.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "UIButton.h"
#include "UITextField.h"
#include <iostream>
#include <string>

StateLoadGame::StateLoadGame(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_gameObjects()
    , saveData()
{
    //Create objects for Load Screen
    //Text and buttons

    m_gameObjects.push_back(new UITextField(pFont, "LOAD MENU", SDL_Color{ 255, 255, 0 }, Vector2{ 350, 0 }, pOwner->GetGame()->GetRenderer(), 1000));


    UIButton* pLoadSave1 = new UIButton(SDL_Rect{ 300,100,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pLoadSave1->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Load(1);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pLoadSave1);

    UIButton* pLoadSave2 = new UIButton(SDL_Rect{ 300,225,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pLoadSave2->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Load(2);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pLoadSave2);

    UIButton* pLoadSave3 = new UIButton(SDL_Rect{ 300,350,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pLoadSave3->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Load(3);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pLoadSave3);

    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 1", SDL_Color{255, 255, 255}, Vector2{350, 75}, pOwner->GetGame()->GetRenderer(), 1000));
    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 2", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 200 }, pOwner->GetGame()->GetRenderer(), 1000));
    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 3", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 325 }, pOwner->GetGame()->GetRenderer(), 1000));
    m_buttonSet.push_back(pLoadSave1);
    m_buttonSet.push_back(pLoadSave2);
    m_buttonSet.push_back(pLoadSave3);
}

StateLoadGame::~StateLoadGame()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;

    }
}

void StateLoadGame::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(pRenderer);

    for (GameObject* object : m_gameObjects)
    {
        object->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}

bool StateLoadGame::HandleEvent(SDL_Event* pEvent)
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

void StateLoadGame::ChangeButtonFocus(int direction)
{
    m_keyboardButtonFocus = (m_keyboardButtonFocus + direction) % m_buttonSet.capacity();
    for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
    {
        //if this is selected button, highlight.
        m_buttonSet[i]->SetHighlight(i == m_keyboardButtonFocus);
    }
}
