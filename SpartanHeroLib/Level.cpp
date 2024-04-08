/**
 * @file Level.cpp
 * @author Alex Beck
 */

#include "pch.h"

#include <wx/graphics.h>

#include "DrawVisitor.h"
#include "ItemLoadVisitor.h"
#include "Level.h"
#include "Image.h"
#include "Soundboard.h"
#include "Scoreboard.h"
#include "Meter.h"
#include "NoteTiming.h"
#include "NoteAddVisitor.h"
#include "KeyDownVisitor.h"
#include "KeyUpVisitor.h"
#include "UpdateVisitor.h"

using namespace std;

/**
 * Clear a level, erase all mItems and mNotes
 */
void Level::Clear()
{
    mSounds.clear();
    mNotes.clear();
    mDeclarations.clear();
    mScore->Reset();
    mPlaying = false;
}

/**
 * Level constructor
 */
Level::Level(ma_engine *audio) : mAudioEngine(audio)
{
    mScore = make_shared<Score>();
}

/**
 * Handle a node of type Audio
 * @param node The audio node to load
 */
void Level::XmlAudio(wxXmlNode *node)
{
    // Load each child of the audio node as a sound
    auto soundNode = node->GetChildren();
    for (; soundNode; soundNode = soundNode->GetNext())
    {
        auto sound = make_shared<Sound>();
        sound->XmlLoad(soundNode, mAudioEngine);
        mSounds.push_back(sound);
    }
}
/**
 * Load a declarations node
 * @param node The xml node representing the declarations
 */
void Level::XmlDeclarations(wxXmlNode *node)
{
    // Setup loop by getting the first child element
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // For each element, get the name so we know
        // what type of item it is
        auto name = child->GetName();
        shared_ptr<Declaration> to_add;

        // Create the proper item
        if(name == L"note")
        {
            auto tmp = make_shared<Note>(this);
            mNotes.push_back(tmp);
            to_add = tmp;
        }
        else if(name == L"sound-board")
        {
            to_add = make_shared<Soundboard>(this);
        }
        else if(name == L"score-board")
        {
            to_add = make_shared<Scoreboard>(this);
        }
        else if (name == L"meter")
        {
            to_add = make_shared<Meter>(this);
        }
        else if (name == L"image")
        {
            to_add = make_shared<Image>(this);
        }

        // XmlLoad the item, and add it to our
        // items list if we actually created a
        // item
        if (to_add != nullptr)
        {
            to_add->XmlDeclarationLoad(child);
            mDeclarations.push_back(to_add);
        }
    }
}

/**
 * Find a sound in the level by id
 * @param id The id of the sound to find
 * @return The sound with the corresponding id, or nullptr if none match
 */
shared_ptr<Sound> Level::GetSound(wstring id)
{
    for (auto sound : mSounds)
    {
        // Return the item if the ID matches
        if (sound->GetName() == id)
            return sound;
    }
    return nullptr;
}

/**
 * Find a note in the level by id
 * @param id The id of the note to find
 * @return The note with the corresponding id, or nullptr if none match
 */
shared_ptr<Note> Level::GetNote(wstring id)
{
    for (auto note : mNotes)
    {
        // Return the item if the ID matches
        if (note->GetID() == id)
            return note;
    }
    return nullptr;
}

/**
 * Load a items node
 * @param node The items node to parse
 */
void Level::XmlItems(wxXmlNode *node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto id = child->GetAttribute(L"id");
        auto visitor = new ItemLoadVisitor(id.ToStdWstring(), child);
        Accept(visitor);
        delete visitor;
    }
}

/**
 * Load a music node
 * @param node The music node to parse
 */
void Level::XmlMusic(wxXmlNode *node)
{
    // Load the conversion data into a music class
    mMusicData.XmlLoad(node);
    mCountDownBeat = mMusicData.MeasuresToBeats(1);

    // Load each note timing and add it to the proper track
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // Get note id
        auto id = child->GetAttribute(L"id");
        auto note = GetNote(id.ToStdWstring());

        // Get sound id
        auto soundName = child->GetAttribute(L"sound");
        auto sound = GetSound(soundName.ToStdWstring());


        auto timing = make_shared<NoteTiming>(note, sound);
        timing->XmlLoad(child, &mMusicData);

        // Add timing to the soundboard
        auto visitor = new NoteAddVisitor(timing);
        Accept(visitor);
        delete visitor;
    }
/*
    // Start the backing
    if (mMusicData.GetBacking() != L"")
    {
		//delays the whole program 5 seconds
		//Sleep(5000);
        GetSound(mMusicData.GetBacking())->Play();
		//starts audio then displays the program after 5 seconds
		//Sleep(5000);
    }
    */
}

/**
 * Load a level from an xml document describing the level layout
 * Call Refresh() in view after call
 * @param fileName The path to the xml document
 */
void Level::Load(const wstring &fileName)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(fileName)) {
        wxMessageBox(L"Unable to load level!");
        return;
    }

    // Get xml root
    auto root = xmlDoc.GetRoot();

    // Get the virtual width and height from the root node
    auto size = root->GetAttribute(L"size");
    auto split = wxSplit(size, L',');

    if (split.size() < 2 || !split[0].ToDouble(&mWidth) || !split[1].ToDouble(&mHeight))
    {
        wxMessageBox(L"Unable to load width and height of level!");
        return;
    }

    // Clear current level
    Clear();

    // Get the first child, and iterate through all children
    auto node = root->GetChildren();
    for (; node; node = node->GetNext())
    {
        if (node->GetName() == L"audio")
        {
            XmlAudio(node);
        }
        else if (node->GetName() == L"declarations")
        {
            XmlDeclarations(node);
        }
        else if (node->GetName() == L"items")
        {
            XmlItems(node);
        }
        else if (node->GetName() == L"music")
        {
            XmlMusic(node);
        }
    }
}

/**
 * Have a visitor visit all the declarations in the level
 * @param visitor The visitor
 */
void Level::Accept(DeclarationVisitor *visitor)
{
    for (auto i : mDeclarations)
    {
        i->Accept(visitor);
    }
}

/**
 * Draw the level, and all the items within it
 * @param graphics The device context to draw on
 */
void Level::OnDraw(shared_ptr<wxGraphicsContext> graphics)
{

    if (mCountDownBeat > 0)
    {
        DrawVisitor visitor(0, -(mCountDownBeat), graphics.get());
        Accept(&visitor);
    }
    else
    {
        auto sound = GetSound(mMusicData.GetBacking());
        DrawVisitor visitor(0, mMusicData.SecondsToBeats(sound->GetElapsed()), graphics.get());
        Accept(&visitor);
    }

}

void Level::OnKeyPress(wxChar key)
{
    auto sound = GetSound(mMusicData.GetBacking());
    auto beat = mMusicData.SecondsToBeats(sound->GetElapsed());
    KeyDownVisitor visitor(key, beat);
    Accept(&visitor);
}

void Level::OnKeyRelease(wxChar key)
{
    auto sound = GetSound(mMusicData.GetBacking());
    auto beat = mMusicData.SecondsToBeats(sound->GetElapsed());
    KeyUpVisitor visitor(key, beat);
    Accept(&visitor);
}
void Level::SetAutoPlay()
{
    if(mAutoPlay)
    {
        mAutoPlay=false;
    }
    else{
        mAutoPlay=true;
    }
}

/**
 * Called every frame with the time since the last frame
 * @param deltaTime The time between the current frame and the last frame (seconds)
 */
void Level::Update(double deltaTime)
{
    UpdateVisitor visitor(deltaTime);
    Accept(&visitor);
    if ((mCountDownBeat > 0 && mPlaying))
    {
        mCountDownBeat -= mMusicData.SecondsToBeats(deltaTime);
        if (mCountDownBeat < 0 || mCountDownBeat == 0)
        {
            GetSound(mMusicData.GetBacking())->Play();
        }
    }
}

/**
 * sets the beat to the level
 * @param beat the current beat
 */
void Level::SetBeat(double beat)
{
    mBeat=beat;
}
