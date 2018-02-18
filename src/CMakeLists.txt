set(SOURCES
    main.cpp
    chip8.cpp
    EmuClock.cpp
    SdlScreen.cpp
)

add_executable (${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
    ${SDL2_INCLUDE_DIRS}
    "."   
)

TARGET_LINK_LIBRARIES(    
    ${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
)