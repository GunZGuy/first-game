#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "GameObject.h"
#include <unordered_map>


//Game Object component for handling Animation
class AnimationComponent:
    public GameObject
{
    using Vector2 = Vector2<float>;
    
private:

    //Named Animation Sequence
    struct AnimationSequence
    {
    public:
        std::string m_name;
        int m_firstFrame;
        int m_lastFrame;
    };

private:
    //Number of Frames to Show per second
    const double m_kFrameRate;

    //Number of animation frames placed horizontally
    int m_numSpriteSheetColumns;

    //Texture for spritesheet
    SDL_Texture* m_pSpriteSheet;

    SDL_Rect m_sourceTransform;

    std::unordered_map<std::string, AnimationSequence> m_allAnimations;

    std::string m_currentSequenceName;
    
    //Index of current frame
    int m_currentFrame;

    //Time Remaining until animation should advance
    double m_frameTime;

public:
    double m_x;
    double m_y;

    AnimationComponent(const char* pSpriteSheetPath,
        double frameRate, int frameWidth,
        int frameHeight, int frameCount,
        SDL_Renderer* pRenderer);
    ~AnimationComponent();

    SDL_Rect m_transform;

    //Add a new animation sequence to this object, if a sequence exists, it will be overwritten
    void AddAnimationSequence(std::string name, int firstFrame, int lastFrame);

    //Plays named animation
    void PlayAnimation(std::string sequenceName);

    //Resets time to next frame (based on frame rate)
    void ResetFrameTime();

    //Updates the position of the source transform of spritesheet
    void UpdateSourceTransform();

    void Render(SDL_Renderer* pRenderer);

    virtual void Update(double deltaTime) override;

    SDL_Rect* getRect()
    {
        return &m_transform;
    }

    SDL_Rect* setRectx(int x)
    {
        m_transform.x = x;
        return &m_transform;
    }

    SDL_Rect* setRecty(int y)
    {
        m_transform.y = y;
        return &m_transform;
    }

    SDL_Texture* getTexture()
    {
        return m_pSpriteSheet;
    }
};

