#pragma once
#include "GameState.h"
#include "StaticImage.h"
#include "Vector2.h"
#include "SDL_ttf.h"
#include <vector>
#include "UIButton.h"

class ExampleGame;

class StateWinGame :
    public GameState
{
    using Vector2 = Vector2<float>;
private:
    ExampleGame* m_pOwner;

    std::vector<GameObject*> m_gameObjects;

    //Sets of all buttons in order, for keyboard interaction
    std::vector<UIButton*> m_buttonSet;

    //Keep Track of the currently selected button
    int m_keyboardButtonFocus;
public:
    StateWinGame(ExampleGame* pOwner, TTF_Font* pFont);
    ~StateWinGame();
    //Renders Scene
    virtual void Render(SDL_Renderer* pRenderer) override;

    //Handles event in scene
    virtual bool HandleEvent(SDL_Event* pEvent) override;

private:
    //Changes button focus when using keyboard
    void ChangeButtonFocus(int direction);
};

