/**
 * @file gtest_main.cpp
 * @author Alex Beck
 */

#include <pch.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "gtest/gtest.h"
#include <wx/filefn.h>
#include <Level.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}
