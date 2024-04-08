/**
 * @file NoteTest.cpp
 * @author Alex Beck
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Note.h>
#include <Level.h>

// Test fixture for the Note class
class NoteTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Code here will be called immediately after the constructor (right before each test)
		level = new Level(nullptr); // Create a Level object for testing
		note = new Note(level); // Create a Note object for testing
	}

	void TearDown() override {
		// Code here will be called immediately after each test (right before the destructor)
		delete note;
		delete level;
	}

	// Declare variables needed for tests
	Level* level;
	Note* note;
};

// Test case to check the default tolerance value
TEST_F(NoteTest, DefaultTolerance) {
	ASSERT_EQ(0.0, note->GetTolerance());
}

// Test case to check the Accept method
TEST_F(NoteTest, AcceptMethod) {
	class MockVisitor : public DeclarationVisitor {
	public:
		void VisitNote(Note* note) override {
			visited = true;
		}
		bool visited = false;
	};

	MockVisitor visitor;
	note->Accept(&visitor);
	EXPECT_TRUE(visitor.visited);
}

// Test case to check XML load for Note
TEST_F(NoteTest, XmlLoad) {
	wxXmlNode* node = new wxXmlNode(wxXML_ELEMENT_NODE, "Note");
	//adding all the elements of the node
	node->AddAttribute("id", "t1");
	node->AddAttribute("track", "1");
	node->AddAttribute("image" , "puck-a.png");
	node->AddAttribute("size" , "60,60");
	node->AddAttribute("tolerance", "0.5");

	//loading the node
	note->XmlDeclarationLoad(node);

	//testing tolerance
	ASSERT_EQ(0.5, note->GetTolerance());
	//testing the name
	ASSERT_EQ(1.0, note->GetTrackNum());
	//tesitng the id
	ASSERT_EQ(L"t1", note->GetID());
	//tesitng the width
	ASSERT_EQ(60, note->GetWidth());
	//testing the height
	ASSERT_EQ(60, note->GetHeight());

	delete node;
}