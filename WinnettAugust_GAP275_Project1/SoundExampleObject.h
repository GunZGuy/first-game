#pragma once
#include "GameObject.h"

struct Mix_Chunk;
struct Mix_Channel;

class SoundExampleObject : 
    public GameObject
{
private: 
    Mix_Chunk* m_pSound;

    int m_activeSoundChannel;

public:
    SoundExampleObject(const char* pPath);
    ~SoundExampleObject();

    virtual void HandleEvent(SDL_Event* pEvent) override;

};

