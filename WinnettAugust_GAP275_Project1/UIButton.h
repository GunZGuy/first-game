#pragma once
#include "GameObject.h"
#include <functional>

//Clickable Button

class UIButton :
    public GameObject
{
private:
    SDL_Rect m_transform;

    //Texture for highlighted button
    SDL_Texture* m_pHighlightTexture;

    //Standard button texture
    SDL_Texture* m_pTexture;

    //bool to check for hightlighted button
    bool m_isHighlighted;

    std::function<void()> m_callback;

    SDL_Surface* m_pImageSurface;
    SDL_Surface* m_pImageSurface2;

public:
    UIButton(SDL_Rect transform, SDL_Renderer* pRenderer, const char* filePath, const char* filePathHighlighted);
    ~UIButton();

    void SetCallback(std::function<void()> callback) { m_callback = callback; }

    void Trigger();

    void SetHighlight(bool value) { m_isHighlighted = value; }

    virtual void Render( SDL_Renderer* pRenderer) override;

    virtual void HandleEvent(SDL_Event* pEvent) override;

private:
    bool HitTest(int x, int y);
};

