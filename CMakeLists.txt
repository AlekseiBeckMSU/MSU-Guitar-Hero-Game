cmake_minimum_required(VERSION 3.25)
project(SpartanHero)
set(APPLICATION_LIBRARY SpartanHeroLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp
        GameApp.cpp
        GameApp.h
        pch.h
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

add_subdirectory(Tests)

# Fetch miniaudio from GitHub
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 0.11.21
)

FetchContent_MakeAvailable(miniaudio)
include_directories(${miniaudio_SOURCE_DIR})

# Fetch spartanhero-resources from GitHub
include(FetchContent)
FetchContent_Declare(
        spartanhero-resources
        GIT_REPOSITORY https://github.com/charles-owen/spartanhero-resources.git
        GIT_TAG origin/main
)

FetchContent_MakeAvailable(spartanhero-resources)

# Copy resources into output directory
file(COPY ${spartanhero-resources_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Copy levels
file(COPY ${PROJECT_SOURCE_DIR}/levels/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

# Copy any audio
file(COPY ${PROJECT_SOURCE_DIR}/audio/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/audio/)