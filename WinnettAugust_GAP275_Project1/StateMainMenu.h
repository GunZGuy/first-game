#pragma once
#include "GameState.h"
#include "StaticImage.h"
#include "Vector2.h"
#include "SDL_ttf.h"
#include <vector>
#include <SDL_mixer.h>
#include "UIButton.h"

class ExampleGame;

class StateMainMenu :
    public GameState
{
    using Vector2 = Vector2<float>;
private:
    //State Machine Operating this state
    ExampleGame* m_pOwner;

    //Storing game objects in vector
    std::vector<GameObject*> m_gameObjects;

    Mix_Music* m_pMusic;

    //Sets of all buttons in order, for keyboard interaction
    std::vector<UIButton*> m_buttonSet;

    //Keep Track of the currently selected button
    int m_keyboardButtonFocus;

public:
    StateMainMenu(ExampleGame* pOwner, TTF_Font* pFont);
    ~StateMainMenu();

    //Renders Scene
    virtual void Render(SDL_Renderer* pRenderer) override;

    //Handles event in scene
    virtual bool HandleEvent(SDL_Event* pEvent) override;

private:
    //Changes button focus when using keyboard
    void ChangeButtonFocus(int direction);
};

