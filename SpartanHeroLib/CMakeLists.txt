project(SpartanHeroLib)

set(SOURCE_FILES
        Level.cpp
        Level.h
        GameView.cpp
        GameView.h
        pch.h
        Sound.cpp
        Sound.h
        Music.cpp
        Music.h
        Track.cpp
        Track.h
        Scoreboard.cpp
        Scoreboard.h
        Soundboard.cpp
        Soundboard.h
        Meter.cpp
        Meter.h
        Note.cpp
        Note.h
        Item.cpp
        Item.h
        MainFrame.cpp
        MainFrame.h
        Game.cpp
        Game.h
        ids.h
        Image.cpp
        Image.h
        NoteTiming.cpp
        NoteTiming.h
        Declaration.h
        Declaration.cpp
        DeclarationVisitor.cpp
        DeclarationVisitor.h
        DrawVisitor.cpp
        DrawVisitor.h
        ItemLoadVisitor.cpp
        ItemLoadVisitor.h
        NoteAddVisitor.cpp
        NoteAddVisitor.h
        KeyDownVisitor.cpp
        KeyDownVisitor.h
        KeyUpVisitor.cpp
        KeyUpVisitor.h
        Score.cpp
        Score.h
        UpdateVisitor.cpp
        UpdateVisitor.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 0.11.21
)

FetchContent_MakeAvailable(miniaudio)
include_directories(${miniaudio_SOURCE_DIR})