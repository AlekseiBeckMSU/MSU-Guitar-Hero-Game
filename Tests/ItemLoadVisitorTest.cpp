/**
 * @file ItemLoadVisitorTest.cpp
 * @author Alex Beck
 */

#include <pch.h>
#include <wx/sstream.h>
#include <ItemLoadVisitor.h>
#include <Soundboard.h>
#include <Level.h>
#include "gtest/gtest.h"

//TEST(ItemLoadVisitorTest, VisitsSoundboardAddsTrackToSoundboard)
//{
//    Level testLevel;
//    Soundboard soundboard(&testLevel);
//
//    wxXmlNode* rootNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"soundboard");
//    wxXmlNode* trackNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"track");
//    trackNode->AddAttribute(L"key-image", L"key-a.png");
//    trackNode->AddAttribute(L"key-size", L"large");
//    trackNode->AddAttribute(L"key", L"A");
//    trackNode->AddAttribute(L"track", L"1");
//    rootNode->AddChild(trackNode);
//
//    ItemLoadVisitor visitor(L"some_id", rootNode);
//
//    // Perform the visitation
//    visitor.VisitSoundboard(&soundboard);
//
//    // Check that a track was added to the soundboard
//    auto tracks = soundboard.GetTracks();
//    EXPECT_EQ(tracks.size(), 1); // Check that exactly one track was added
//    // Additionally, check if the track data matches expected values
//    EXPECT_EQ(tracks[0]->GetKey(), L'A');
//    // Additionally, check if the track num is the same
//    EXPECT_EQ(tracks[0]->GetTrackNum(), 1);
//}
