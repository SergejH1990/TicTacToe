cmake_minimum_required(VERSION 3.5)

project(TicTacToe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

# Main application sources
set(PROJECT_SOURCES
		Sources/tttGame.cpp
		Sources/tttGame.h
		Sources/tttGeneral.h
		Sources/Resources/MyResources.qrc
)

# Create executable for main application
add_executable(TicTacToe
	Sources/main.cpp
	${PROJECT_SOURCES}
)

# Create executable for test cases
add_executable(TestGame
	Tests/Test_TicTacToe/tst_testwincondition.cpp
	${PROJECT_SOURCES}
	Tests/TTGame_Test.cpp
	Tests/TTGame_Test.h
)

# Link libraries for main application target and test cases target
target_link_libraries(TicTacToe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TestGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

set_target_properties(TicTacToe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
