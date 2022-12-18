#include "SoundExampleObject.h"
#include <iostream>
#include <SDL_mixer.h>

SoundExampleObject::SoundExampleObject(const char* pPath)
    : m_pSound(nullptr)
    , m_activeSoundChannel(-1)
{
    m_pSound = Mix_LoadWAV(pPath);
    if (m_pSound == nullptr)
    {
        std::cout << "Failed to load sound. Error: " << SDL_GetError() << std::endl;
    }
}

SoundExampleObject::~SoundExampleObject()
{
    if (m_pSound != nullptr)
    {
        Mix_FreeChunk(m_pSound);
        m_pSound = nullptr;
    }
}

void SoundExampleObject::HandleEvent(SDL_Event* pEvent)
{
    switch (pEvent->type)
    {
        case SDL_KEYDOWN:
        {
            if (m_activeSoundChannel == -1)
            {
                m_activeSoundChannel = Mix_PlayChannel(-1, m_pSound, 0);
            }
            else
            {
                Mix_HaltChannel(m_activeSoundChannel);
                m_activeSoundChannel = -1;
            }
            break;
        }
    }
}
