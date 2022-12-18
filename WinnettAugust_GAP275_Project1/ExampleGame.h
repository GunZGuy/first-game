#pragma once
#include "GameStateMachine.h"
#include "Movement.h"
#include "StateGameOver.h"
#include "SDL_ttf.h"
#include "UIButton.h"
#include <SDL_mixer.h>
#include "SaveData.h"

class GameLoop;
class GameState;
class Movement;

class ExampleGame :
    public GameStateMachine
{
public:
    enum SceneName
    {
        MainMenu,
        Gameplay,
        GameOver,
        GameWin,
        LoadGame,
        SaveGame,
        Credits
    };

private:

    GameLoop* m_pOwner;

    GameState* m_pCurrentState;

    GameState* m_pNextState;

    GameLoop* m_pRenderer;

    TTF_Font* m_pFont;

    SDL_Texture* m_pTexture;

    SaveData m_saveData;
public:
    ExampleGame(GameLoop* pOwner);
    ~ExampleGame();

    virtual bool Init() override;

    GameLoop* GetGame() { return m_pOwner; }

    GameLoop* GetRenderer() { return m_pRenderer; }

    SDL_Texture* GetTexture() { return m_pTexture; }

    //Update current state
    virtual void UpdateCurrentState(double deltaTime) override;

    //Render current state
    virtual void RenderCurrentState(SDL_Renderer* pRenderer) override;

    //Handle event in current state
    virtual bool HandleEvent(SDL_Event* pEvent) override;

    // Exists current state and enters new state
    virtual void ChangeState(GameState* pNewState) override;

    //Loads the given scene
    void LoadScene(SceneName scene);

    SaveData* GetSave() { return &m_saveData; }
};

