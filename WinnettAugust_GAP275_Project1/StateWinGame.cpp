#include "StateWinGame.h"
#include "ExampleGame.h"
#include "GameLoop.h"
#include "UITextField.h"
#include "UIButton.h"

StateWinGame::StateWinGame(ExampleGame* pOwner, TTF_Font* pFont)
    : m_pOwner(pOwner)
    , m_gameObjects()
{

    //Create Buttons and Text for Win Game State

    m_gameObjects.push_back(new UITextField(pFont, "YOUVE WON SOMETHING!", SDL_Color{ 255, 255, 255 }, Vector2{ 300, 100 }, pOwner->GetGame()->GetRenderer(), 1000));

    UIButton* pMainMenu = new UIButton(SDL_Rect{ 0, 0,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/mainmenu.png", "assets/mainmenuhighlight.png");

    pMainMenu->SetCallback([pOwner]()->void
        {
            pOwner->LoadScene(ExampleGame::MainMenu);
        });

    m_gameObjects.push_back(pMainMenu);

    UIButton* pPlayButton = new UIButton(SDL_Rect{ 350,200,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/startbutton.png", "assets/startbuttonhighlight.png");

    pPlayButton->SetCallback([pOwner]()->void
        {
            pOwner->LoadScene(ExampleGame::Gameplay);
        });

    m_gameObjects.push_back(pPlayButton);

    UIButton* pCredits = new UIButton(SDL_Rect{ 350,400,150,100 }, pOwner->GetGame()->GetRenderer(),
        "assets/credits.png", "assets/creditshighlight.png");

    pCredits->SetCallback([pOwner]()->void
        {
            pOwner->LoadScene(ExampleGame::Credits);
        });

    m_gameObjects.push_back(pCredits);

    UIButton* pQuitButton = new UIButton(SDL_Rect{ 350, 300, 150, 100 }, pOwner->GetGame()->GetRenderer(),
        "assets/quitbutton.png", "assets/quitbuttonhighlight.png");

    pQuitButton->SetCallback([pOwner]()->void
        {
            pOwner->GetGame()->Quit();
        });

    m_gameObjects.push_back(pQuitButton);
    m_buttonSet.push_back(pMainMenu);
    m_buttonSet.push_back(pPlayButton);
    m_buttonSet.push_back(pQuitButton);
    m_buttonSet.push_back(pCredits);
}

StateWinGame::~StateWinGame()
{
    for (GameObject* object : m_gameObjects)
    {
        delete object;

    }
}

void StateWinGame::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderClear(pRenderer);

    for (GameObject* object : m_gameObjects)
    {
        object->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}

bool StateWinGame::HandleEvent(SDL_Event* pEvent)
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

void StateWinGame::ChangeButtonFocus(int direction)
{
    m_keyboardButtonFocus = (m_keyboardButtonFocus + direction) % m_buttonSet.capacity();
    for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
    {
        //if this is selected button, highlight.
        m_buttonSet[i]->SetHighlight(i == m_keyboardButtonFocus);
    }
}
