/**
 * @file Scoreboard.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Score.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

/**
 * constructor
 * @param level the level to pass to item
 */
Scoreboard::Scoreboard(Level *level) : Item(level)
{
}

/**
<<<<<<< Updated upstream
 * Draws the score on scoreboard
 * @param graphics the graphics we use to draw on
 * @param str the string draw to
 * @param x the x position
 * @param y the y position
>>>>>>> Stashed changes
 */
void Scoreboard::DrawText(wxGraphicsContext *graphics, wstring str, double x, double y)
{
    double textWidth, textHeight;
    graphics->GetTextExtent(str, &textWidth, &textHeight);

    x = x - textWidth / 2 + GetX() - GetWidth() / 2;
    y = y - textHeight / 2 + GetY() - GetHeight() / 2;

    graphics->DrawText(str,
                       x,
                       y);
}

/**
<<<<<<< Updated upstream
 * Draws text and countdown and finally the score
 * @param graphics the graphics we use to draw
 * @param beat the beat so we can update to the beat
>>>>>>> Stashed changes
 */
void Scoreboard::Draw(wxGraphicsContext *graphics, double beat)
{
    Item::Draw(graphics, beat);
    wxPen blackPen(*wxBLACK, mReadySize);
    graphics->SetPen(blackPen);
    wxFont font(wxSize(0, mReadySize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);
    if (!mLevel->IsPlaying())
    {
        DrawText(graphics, L"Get Ready!", GetWidth() / 2, GetHeight() / 2 + mReadyY);
    }
    else if (beat < 0)
    {
        wxFont font1(wxSize(0, mBeatSize),
                     wxFONTFAMILY_SWISS,
                     wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_NORMAL);
        graphics->SetFont(font1, *wxBLACK);
        auto countdownStr = wxString::Format(wxT("%d"), (int) -beat + 1);
        DrawText(graphics, countdownStr.ToStdWstring(), GetWidth() / 2, GetHeight() / 2 + mBeatsY);
        wxFont font2(wxSize(0, mScoreSize),
                     wxFONTFAMILY_SWISS,
                     wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_NORMAL);
        graphics->SetFont(font2, *wxBLACK);
        auto scoreStr = wxString::Format(wxT("%06d"), mLevel->GetScore()->GetScore());
        DrawText(graphics, scoreStr.ToStdWstring(), GetWidth() / 2, GetHeight() / 2 + mScoreY);
    }
    else
    {
        if (mLevel->GetScore() != nullptr)
        {
            wxFont font2(wxSize(0, mScoreSize),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL);
            graphics->SetFont(font2, *wxBLACK);
            auto scoreStr = wxString::Format(wxT("%06d"), mLevel->GetScore()->GetScore());
            DrawText(graphics, scoreStr.ToStdWstring(), GetWidth() / 2, GetHeight() / 2 + mScoreY);
            mBeat = beat;
            mCurrentBeat = 0;
            mCurrentBeat = mBeat % mBeatPerMeasure;
            mCurrentMeasure = (mBeat - mCurrentBeat) / 4;
            mCurrentBeat = mCurrentBeat + 1;
            auto mCurrentBeat1 = wxString::Format(wxT("%d:%d"), mCurrentMeasure + 1, mCurrentBeat);
            DrawText(graphics, mCurrentBeat1.ToStdWstring(), GetWidth() / 2, GetHeight() / 2 + mBeatsY);
        }
    }
}
