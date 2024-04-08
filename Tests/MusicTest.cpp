/**
 * @file MusicTest.cpp
 * @author Alex Beck
 */

#include <pch.h>
#include <wx/sstream.h>
#include <Music.h>
#include "gtest/gtest.h"

using namespace std;

const wstring MusicDoc = L"<music beats-per-minute=\"100.0\" beats-per-measure=\"4\" measures=\"9\" backing=\"BACK\"></music>";

TEST(MusicTest, Construction) {
    // Construct the music class
    Music music;
}

TEST(MusicTest, Load) {
    // Get a stream of our example xml
    wxStringInputStream stream(MusicDoc);

    // Load the xml doc
    wxXmlDocument doc;
    doc.Load(stream);

    // Construct the music class
    Music music;
    music.XmlLoad(doc.GetRoot());

    // Check that values are loaded as intended
    ASSERT_EQ(music.GetBacking(), L"BACK");
    ASSERT_EQ(music.MeasuresToBeats(1), 4);
    ASSERT_EQ(music.GetMeasures(), 9);
    // 100 beats = 1 min = 60 sec
    ASSERT_NEAR(music.BeatsToSeconds(100.0), 60.0, 0.1);
}