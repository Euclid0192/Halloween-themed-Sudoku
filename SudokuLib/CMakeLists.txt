project(SudokuLib)

set(SOURCE_FILES
        MainFrame.h
        MainFrame.cpp
        pch.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        SudokuGame.cpp
        SudokuGame.h
        Item.cpp
        Item.h
        Sparty.cpp
        Sparty.h
        Digit.cpp
        Digit.h
        Xray.cpp
        Xray.h
        Level.cpp
        Level.h
        Container.cpp
        Container.h
        Solver.cpp
        Solver.h
        ScoreBoard.cpp
        ScoreBoard.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})