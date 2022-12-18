#include "AnimationComponent.h"
#include "SDL_image.h"


AnimationComponent::AnimationComponent(const char* pSpriteSheetPath, 
    double frameRate, int frameWidth, int frameHeight, 
    int frameCount, SDL_Renderer* pRenderer)
    : m_kFrameRate(frameRate)
    , m_pSpriteSheet(nullptr)
    , m_currentFrame(-1)
    , m_x()
    , m_y()
{
    SDL_Surface* pSpriteSheetSurface = IMG_Load(pSpriteSheetPath);

    m_numSpriteSheetColumns = pSpriteSheetSurface->w / frameWidth;

    m_transform.x = static_cast<int>(m_x);
    m_transform.y = static_cast<int>(m_y);
    m_transform.w = frameWidth;
    m_transform.h = frameHeight;

    m_sourceTransform = m_transform;

    m_pSpriteSheet = SDL_CreateTextureFromSurface(pRenderer, pSpriteSheetSurface);

    SDL_FreeSurface(pSpriteSheetSurface);

    ResetFrameTime();
}


AnimationComponent::~AnimationComponent()
{
    SDL_DestroyTexture(m_pSpriteSheet);
}

void AnimationComponent::AddAnimationSequence(std::string name, int firstFrame, int lastFrame)
{
    m_allAnimations[name] = AnimationSequence{ name, firstFrame, lastFrame };
}

void AnimationComponent::PlayAnimation(std::string sequenceName)
{
    //If named sequence already palying, do nothing
    if (sequenceName == m_currentSequenceName || m_allAnimations.find(sequenceName) == m_allAnimations.end())
    {
        return;
    }

    //Access named sequence and set to first frame
    AnimationSequence& newSequence = m_allAnimations[sequenceName];
    m_currentFrame = newSequence.m_firstFrame;

    //Update sequence name, frame time, and source rect
    m_currentSequenceName = sequenceName;
    ResetFrameTime();
    UpdateSourceTransform();
}

void AnimationComponent::ResetFrameTime()
{
    //Divide 1 by framerate to get frame time
    m_frameTime = 1 / m_kFrameRate;
}

void AnimationComponent::UpdateSourceTransform()
{
    //Do math to get right position
    int frameX = m_currentFrame % m_numSpriteSheetColumns;
    int frameY = m_currentFrame / m_numSpriteSheetColumns;
    m_sourceTransform.x = frameX * m_sourceTransform.w;
    m_sourceTransform.y = frameY * m_sourceTransform.h;
}

void AnimationComponent::Update(double deltaTime)
{
    //If m_currentFrame is -1, nothing is playing.
    if (m_currentFrame == -1)
        return;

    double deltaPosition = deltaTime * 100;

    AnimationSequence& currentSequence = m_allAnimations[m_currentSequenceName];

    bool frameIsDirty = false;

    while (deltaTime > m_frameTime)
    {
        frameIsDirty = true;

        deltaTime -= m_frameTime;
        ResetFrameTime();

        if (currentSequence.m_lastFrame == m_currentFrame)
        {
            m_currentFrame = currentSequence.m_firstFrame;
        }
        else
        {
            ++m_currentFrame;
        }
    }

    m_frameTime -= deltaTime;

    if (frameIsDirty)
    {
        UpdateSourceTransform();
    }
}

void AnimationComponent::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_pSpriteSheet, &m_sourceTransform, &m_transform);
}
