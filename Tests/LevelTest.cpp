/**
 * @file LevelTest.cpp
 *
 * @author Alex Beck
 *
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

/**
 * Check that the number of each type of declaration was in the level
 */
class CountVisitor : public DeclarationVisitor {
    int mSoundboardCount = 0;
    int mScoreboardCount = 0;
    int mMeterCount = 0;
    int mNoteCount = 0;
    int mItemCount = 0;
    int mImageCount = 0;

public:
    CountVisitor() {};

    void SetExpected(
        int soundboardCount,
        int scoreboardCount,
        int meterCount,
        int noteCount,
        int itemCount,
        int imageCount
    ) {
        mSoundboardCount = soundboardCount;
        mScoreboardCount = scoreboardCount;
        mMeterCount = meterCount;
        mNoteCount = noteCount;
        mItemCount = itemCount;
        mImageCount = imageCount;
    }

    bool GotExpected() {
        // Check that we have seen the
        // expected number of each element
        return
            mSoundboardCount == 0 &&
            mScoreboardCount == 0 &&
            mMeterCount == 0 &&
            mNoteCount == 0 &&
            mItemCount == 0 &&
            mImageCount == 0;
    }

    void VisitSoundboard(Soundboard* soundboard) override { mSoundboardCount--; }

    void VisitScoreboard(Scoreboard* scoreboard) override { mScoreboardCount--; }

    void VisitMeter(Meter* meter) override { mMeterCount--; }

    void VisitNote(Note* note) override { mNoteCount--; }

    void VisitItem(Item *item) override { mItemCount--; }

    void VisitImage(Image *image) override { mImageCount--; }
};

TEST(LevelTest, Construct) {
    Level level(nullptr);
}

TEST(LevelTest, LoadEmpty) {
    Level empty(nullptr);

    // Load level and check that level got everything
    empty.Load(L"levels/testemptylevel.xml");

    ASSERT_EQ(empty.GetWidth(), 200);
    ASSERT_EQ(empty.GetHeight(), 300);

    auto visitor = new CountVisitor();
    visitor->SetExpected(0, 0, 0, 0, 0, 0);
    empty.Accept(visitor);

    ASSERT_TRUE(visitor->GotExpected());
}

TEST(LevelTest, LoadTestLevel) {
    Level level(nullptr);
    level.Load(L"levels/testlevel.xml");

    ASSERT_EQ(level.GetWidth(), 1304);
    ASSERT_EQ(level.GetHeight(), 900);

    auto visitor = new CountVisitor();
    visitor->SetExpected(1, 1, 1, 8, 0, 1);
    level.Accept(visitor);

    ASSERT_TRUE(visitor->GotExpected());
}
