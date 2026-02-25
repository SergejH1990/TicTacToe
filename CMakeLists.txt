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

# Create executable for main application
add_executable(TicTacToe)

target_sources(TicTacToe PUBLIC
	Sources/main.cpp
	Sources/tttGeneral.h
	Sources/tttGame.cpp
	Sources/tttGame.h
	Sources/tttGameMenu.cpp
	Sources/tttGameMenu.h
	Sources/tttMatchResult.h
	Sources/tttMatchResult.cpp
	Sources/Resources/MyResources.qrc
)

# Create executable for test cases
add_executable(TestWinCondition)

target_sources(TestWinCondition PUBLIC
	Sources/tttGeneral.h
	Sources/tttMatchResult.h
	Sources/tttMatchResult.cpp
	Tests/Test_TicTacToe/tst_testwinconditions.cpp
)


# Link libraries for main application target and test cases target
target_link_libraries(TicTacToe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TestWinCondition PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

set_target_properties(TicTacToe PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

set_target_properties(TicTacToe PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TicTacToe"
)

set_target_properties(TestWinCondition PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TestWinCondition"
)

