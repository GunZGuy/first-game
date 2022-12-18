#include "StateCredits.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "Movement.h"
#include "UITextField.h"
#include "UIButton.h"

StateCredits::StateCredits(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_gameObjects()
{
    //Create UI Text for credits screen
    m_gameObjects.push_back(new UITextField(pFont, "Credits", SDL_Color{ 255, 255, 255 }, 
        Vector2{ 350, 100 }, pOwner->GetGame()->GetRenderer(), 200));

    m_gameObjects.push_back(new UITextField(pFont, "Made by: August Winnett / GunZGuy \nAlso huge thanks to Professor Simons for not giving up on me." , SDL_Color{ 255, 255, 255 }, 
        Vector2{ 200, 150 }, pOwner->GetGame()->GetRenderer(), 400));

    m_gameObjects.push_back(new UITextField(pFont, "Also Rez And Scott for giving me the resources to do this. \nBiggest thanks to ShmellyOrc, who's been there since the streaming days, and doesn't know c++ but helps me think logically.", SDL_Color{ 255, 255, 255 },
        Vector2{ 200, 250 }, pOwner->GetGame()->GetRenderer(), 400));

    UIButton* pMainMenu = new UIButton(SDL_Rect{ 0,0,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/mainmenu.png", "assets/mainmenuhighlight.png");

    pMainMenu->SetCallback([pOwner]()->void
        {
            pOwner->LoadScene(ExampleGame::MainMenu);
        });

    m_gameObjects.push_back(pMainMenu);
    m_buttonSet.push_back(pMainMenu);
}

StateCredits::~StateCredits()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;

    }
}

void StateCredits::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderClear(pRenderer);

    for (GameObject* object : m_gameObjects)
    {
        object->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}

bool StateCredits::HandleEvent(SDL_Event* pEvent)
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

void StateCredits::ChangeButtonFocus(int direction)
{
    m_keyboardButtonFocus = (m_keyboardButtonFocus + direction) % m_buttonSet.capacity();
    for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
    {
        //if this is selected button, highlight.
        m_buttonSet[i]->SetHighlight(i == m_keyboardButtonFocus);
    }
}
