#pragma once
#include "GameObject.h"
class StaticImage :
    public GameObject
{
private:
    SDL_Rect m_transform;

    SDL_Texture* m_pTexture;

public:
    StaticImage(SDL_Rect transform, const char* pImagePath, SDL_Renderer* pRenderer);
    ~StaticImage();

    virtual const char* GetName() override { return "Static Image"; }

    virtual void Render(SDL_Renderer* pRenderer) override;
};

