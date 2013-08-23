# CMake & Project Configuration

cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0015 NEW)
# cmake_policy(SET CMP0003 NEW)

project(client)

if (CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "${CMAKE_BUILD_TYPE} Build")

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

set(COMPILER_ID "")
set(COMPILER_LIBEXT "")

if (MINGW)
	set(COMPILED_ID "mingw")
	set(COMPILER_LIBEXT "a")
endif()

if (MSVC10)
	set(COMPILER_ID "msvc++10")
	set(COMPILER_LIBEXT "lib")
endif()

add_definitions(-DUSE_SFGRAPHICSMODULE)

#######################
# Find & configure SFML
#######################

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../libs/SFML/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/../libs/SFML/")

find_package(SFML 2.0 REQUIRED COMPONENTS NETWORK GRAPHICS WINDOW SYSTEM)

include_directories(${SFML_INCLUDE_DIR})

###########################
# Find & configure yaml-cpp
###########################

include_directories("${PROJECT_SOURCE_DIR}/../libs/yaml-cpp/include/")

set(YAMLLIB_EXT "")

if (MSVC10)
	set(YAMLLIB_EXT "md")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(YAML_LIBRARY "${PROJECT_SOURCE_DIR}/../libs/yaml-cpp/lib/${COMPILER_ID}/libyaml-cpp${YAMLLIB_EXT}.${COMPILER_LIBEXT}")
else()
	set(YAML_LIBRARY "${PROJECT_SOURCE_DIR}/../libs/yaml-cpp/lib/${COMPILER_ID}/libyaml-cpp${YAMLLIB_EXT}d.${COMPILER_LIBEXT}")
endif()

########################
# Find & configure Boost
########################

include_directories(../libs/Boost/include/)

####################
# Sources & Headers
####################

set(game_SOURCES
	Animation.h
	Application.h
	AssetBase.h
	Camera.h
	Config.h
	DataStream.h
	FileDataStream.h
	GameState.h
	general.h
	Graphic.h
	GraphicsManager.h
	handles.h
	InGame.h
	MainMenu.h
	NetworkPacket.h
	NetworkProcessor.h
	Properties.h
	SplashScreen.h
	Singleton.h
	Split.h
	UserEventsHandler.h
	WorldRenderer.h
	
	Animation.cpp
	Application.cpp
	Camera.cpp
	Config.cpp
	GameInputs.cpp
	GameState.cpp
	general.cpp
	Graphic.cpp
	GraphicsManager.cpp
	InGame.cpp
	main.cpp
	NetworkProcessor.cpp
	UserEventsHandler.cpp
	WorldRenderer.cpp
)

add_subdirectory("GUI")

ADD_EXECUTABLE(game ${game_SOURCES})
target_link_libraries(game GUI ${SFML_LIBRARIES} ${YAML_LIBRARY})