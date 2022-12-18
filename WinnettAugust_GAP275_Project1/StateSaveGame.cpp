#include "StateSaveGame.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "UIButton.h"
#include "UITextField.h"
#include <iostream>
#include "SaveData.h"
StateSaveGame::StateSaveGame(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_gameObjects()
    , m_keyboardButtonFocus(-1)
{
    //Create objects for save game menu
    //Buttons and text

    m_gameObjects.push_back(new UITextField(pFont, "SAVE MENU", SDL_Color{ 255, 255, 0 }, Vector2{ 350, 0 }, pOwner->GetGame()->GetRenderer(), 1000));

    UIButton* pSave1 = new UIButton(SDL_Rect{ 300,100,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pSave1->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Save(1);
            pOwner->GetSave()->Load(1);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pSave1);

    UIButton* pSave2 = new UIButton(SDL_Rect{ 300,225,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pSave2->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Save(2);
            pOwner->GetSave()->Load(2);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pSave2);

    UIButton* pSave3 = new UIButton(SDL_Rect{ 300,350,200,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/saveSlot.png", "assets/saveSlotHighlight.png");

    pSave3->SetCallback([pOwner]()->void
        {
            pOwner->GetSave()->Save(3);
            pOwner->GetSave()->Load(3);
    pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pSave3);

    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 1", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 75 }, pOwner->GetGame()->GetRenderer(), 1000));
    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 2", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 200 }, pOwner->GetGame()->GetRenderer(), 1000));
    m_gameObjects.push_back(new UITextField(pFont, "Save Slot 3", SDL_Color{ 255, 255, 255 }, Vector2{ 350, 325 }, pOwner->GetGame()->GetRenderer(), 1000));

    m_buttonSet.push_back(pSave1);
    m_buttonSet.push_back(pSave2);
    m_buttonSet.push_back(pSave3);

}

StateSaveGame::~StateSaveGame()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;

    }
}

void StateSaveGame::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(pRenderer);

    for (GameObject* object : m_gameObjects)
    {
        object->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}

bool StateSaveGame::HandleEvent(SDL_Event* pEvent)
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

void StateSaveGame::ChangeButtonFocus(int direction)
{
    m_keyboardButtonFocus = (m_keyboardButtonFocus + direction) % m_buttonSet.capacity();
    for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
    {
        //if this is selected button, highlight.
        m_buttonSet[i]->SetHighlight(i == m_keyboardButtonFocus);
    }
}
