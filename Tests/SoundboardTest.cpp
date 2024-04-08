/**
 * @file SoundboardTest.cpp
 * @author Alex Beck
 */
#include <pch.h>
#include <wx/sstream.h>
#include <Soundboard.h>
#include <Level.h>
#include "gtest/gtest.h"

TEST(SoundboardTest, GetTopWidth) {
    ma_engine* audioEngine = nullptr;
    std::unique_ptr<Level> level = std::make_unique<Level>(audioEngine);
    std::unique_ptr<Soundboard> soundboard = std::make_unique<Soundboard>(level.get());
    double expectedTopWidth = 0;
    ASSERT_EQ(expectedTopWidth, soundboard->GetTopWidth());
}
