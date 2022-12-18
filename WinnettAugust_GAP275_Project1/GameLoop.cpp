#include "GameLoop.h"
#include <iostream>
#include "Movement.h"
#include <chrono>
#include "Wall.h"
#include "Enemy.h"
#include "Spike.h"
#include "Healing.h"
#include "Background.h"
#include "WinZone.h"
#include "GameStateMachine.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

GameLoop::GameLoop()
    : m_pWindow(nullptr)
    , m_pRenderer(nullptr)
    , pMover()
    , pEnemy()
    , m_collisionReferee()
    , m_pStateMachine()
    , m_pMusic()
    , m_pMusic2()
{
    m_pMusic = Mix_LoadMUS("assets/MainMenu.mp3");
    m_pMusic2 = Mix_LoadMUS("assets/sound2.mp3");
}

GameLoop::~GameLoop()
{
    if (m_pMusic != nullptr)
    {
        Mix_FreeMusic(m_pMusic);
        m_pMusic = nullptr;
    }
    if (m_pMusic2 != nullptr)
    {
        Mix_FreeMusic(m_pMusic2);
        m_pMusic2 = nullptr;
    }
}

int GameLoop::Setup(GameStateMachine* pStateMachine)
{
    int errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    if (errorCode == 0)
    {
        std::cout << "SDL_Init() succeeded" << std::endl;
    }
    else
    {
        std::cout << "SDL_Init() failed. Error code " << errorCode << ":" << SDL_GetError() << std::endl;
        system("pause");
        return errorCode;
    }

    m_pWindow = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        0);
    if (m_pWindow != nullptr)
    {
        std::cout << "SDL_CreateWindow() succeeded." << std::endl;
    }
    else
    {
        std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        system("pause");
        return -1;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pRenderer != nullptr)
    {
        std::cout << "SDL_CreateRenderer() succeeded" << std::endl;
    }
    else
    {
        std::cout << "SDL_CreateRenderer() failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return -1;
    }

    std::cout << "Movement: WASD" << std::endl;

    errorCode = TTF_Init();
    if (errorCode != 0)
    {
        std::cout << "TTF_Init() failed. Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        SDL_Quit();
        system("pause");
        return -1;
    }

    errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS, 1024);
    if (errorCode == 0)
    {
        std::cout << "Mix_OpenAudio() succeeded." << std::endl;
    }
    else
    {
        std::cout << "Mix_OpenAudio() failed. Error: " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return -1;
    }

    int audioFlags = MIX_INIT_MP3;
    errorCode = Mix_Init(audioFlags);
    if (errorCode != audioFlags)
    {
        std::cout << "Mixer_Init() failed. Error: " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return -1;
    }

    if (pStateMachine != nullptr && pStateMachine->Init())
    {
        std::cout << "State machine succeeded." << std::endl;
        m_pStateMachine = pStateMachine;
    }
    else
    {
        std::cout << "Failed to create state machine" << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        SDL_Quit();
        system("pause");
        return -1;
    }
    m_pMusic = Mix_LoadMUS("assets/MainMenu.mp3");
    m_pMusic2 = Mix_LoadMUS("assets/sound2.mp3");
    Mix_VolumeMusic(5);
    return 0;
}

void GameLoop::RunGameLoop()
{

    bool quit = false;
    
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!quit)
    {
        // Performance so it doesnt call 24/7
        if (Mix_PlayingMusic() == 0)
        {
            BGM(m_pMusic2, m_pMusic);
        }
        auto thisFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> lastFrameDuration = thisFrameTime - lastFrameTime;
        double deltaTime = lastFrameDuration.count();
        lastFrameTime = thisFrameTime;

        quit = ProcessEvents();
        UpdateGameState(deltaTime);
        DisplayOutput();
        if (m_quit == true)
            quit = true;

    }
}

void GameLoop::Cleanup()
{
    Mix_CloseAudio();
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void GameLoop::Quit()
{
    m_quit = true;
}

void GameLoop::BGM(Mix_Music* song1, Mix_Music* song2)
{

    if (Mix_PlayingMusic() == 0 && songOnePlaying == true)
    {
        Mix_PlayMusic(song2, 0);
        songOnePlaying = false;
    }
    if (Mix_PlayingMusic() == 0 && songOnePlaying == false)
    {
        Mix_PlayMusic(song1, 0);
        songOnePlaying = true;
    }
    if (m_pMusic == nullptr)
    {
        std::cout << "Failed to load sound. Error: " << SDL_GetError() << std::endl;
    }
}


bool GameLoop::ProcessEvents()
{
    if (m_pStateMachine == nullptr)
    {
        return true;
    }

    SDL_Event evt;

    while (SDL_PollEvent(&evt))
    {
        bool quit = m_pStateMachine->HandleEvent(&evt);
        if (quit)
            return true;
    }
    return false;
}


void GameLoop::UpdateGameState(double deltaTime)
{
    if (m_pStateMachine == nullptr)
    {
        return;
    }

    m_pStateMachine->UpdateCurrentState(deltaTime);
}

void GameLoop::DisplayOutput()
{
    if (m_pStateMachine == nullptr)
    {
        return;
    }

    m_pStateMachine->RenderCurrentState(m_pRenderer);
}
