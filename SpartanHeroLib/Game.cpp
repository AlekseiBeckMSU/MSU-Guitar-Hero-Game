/**
 * @file Game.cpp
 * @author Alex Beck
 */
#include "pch.h"
#include "Game.h"
#include "UpdateVisitor.h"
#include <wx/graphics.h>

using namespace std;

/// The default folder to look for level files
const wstring DefaultLevelDir = L"levels";

/**
 * Constructor
 * @param level The default level to load
 */
Game::Game(wstring level)
{
    auto result = ma_engine_init(nullptr, &mEngine);

    if (result == MA_SUCCESS)
    {
        mCurrentLevel = make_unique<Level>(&mEngine);
        mCurrentLevel->Load(DefaultLevelDir + L"/" + level);
        mAudioLoaded = true;
    }
}

/**
 * Destructor
 */
Game::~Game()
{
    // delete the level so all sounds are freed
    mCurrentLevel = nullptr;

    // uninit the audio engine
    if (mAudioLoaded)
    {
        ma_engine_uninit(&mEngine);
        mAudioLoaded = false;
    }
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    auto pixelWidth = mCurrentLevel->GetWidth();
    auto pixelHeight = mCurrentLevel->GetHeight();

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    // Store current graphics state
    graphics->PushState();

    // Set translation and scale as calculated above
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);
    //
    // Draw all items in virtual pixels on the graphics context
    //
    mCurrentLevel->OnDraw(graphics);

    graphics->PopState();

}
/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
    auto scale = mScale;
    double oX = (x - mXOffset) / scale;
    double oY = (y - mYOffset) / scale;
}

/**
 * Load a new level
 * @param levelFile The file to load the level from
 */
void Game::LoadLevel(std::wstring levelFile)
{
    bool autoplay = mCurrentLevel->GetAutoPlay();

    mCurrentLevel = make_shared<Level>(&mEngine);

    if (autoplay)
        mCurrentLevel->SetAutoPlay();

    mCurrentLevel->Load(DefaultLevelDir + L"/" + levelFile);
}
/**
 * Update the game with a deltatime
 * @param elapsed The time since the last frame
 */
void Game::Update(double elapsed)
{
    mCurrentLevel->Update(elapsed);
}

/**
 * checks if the key is up
 * @param key the key we check
 */
void Game::OnKeyUp(wxChar key)
{
    mCurrentLevel->OnKeyRelease(key);
}

/**
 * checks if the key is down
 * @param key the key we check
 */
void Game::OnKeyDown(wxChar key)
{
    mCurrentLevel->OnKeyPress(key);
}

/**
 * sets the auto play to automatically play it
 */
void Game::SetAutoPlay()
{
    mCurrentLevel->SetAutoPlay();
}

/**
 * plays the game
 */
void Game::Play()
{
	mCurrentLevel->Play();
}
