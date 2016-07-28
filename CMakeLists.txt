cmake_minimum_required(VERSION 3.0)

project(GhostRunner)

set(GR_NAME GhostRunner)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GR_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR}/Common)
set(GR_SOUND_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/SoundEngine)
set(GR_PHYSIC_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/PhysicEngine)
set(GR_INPUT_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/InputEngine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake/Modules")
set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/SFML" CACHE PATH "Path to SFML root directory")

add_subdirectory(${GR_COMMON_DIR})
add_subdirectory(${GR_SOUND_ENGINE_DIR})
add_subdirectory(${GR_PHYSIC_ENGINE_DIR})
add_subdirectory(${GR_INPUT_ENGINE_DIR})

set(GR_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(GR_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(GR_SOURCES
    Tools/Ini.cpp
    Tools/WINFS.cpp
    Tools/WINFSReader.cpp
    Tools/TextInBox.cpp
    Tools/PauseOverlay.cpp
    Tools/WinOverlay.cpp

    AssetManager.cpp
    PatternTemplate.cpp
    main.cpp
    BasicWall.cpp
    Scene.cpp
    GameObject.cpp
    Player.cpp
    Animation.cpp
    BasicTrap.cpp
    Camera.cpp
    MapGenerator.cpp
    Block.cpp
    EndBlock.cpp
    GhostController.cpp
    HeroController.cpp
    GameGUI.cpp
    IAdditionalDrawableInfo.cpp
    AdditionalDrawableBar.cpp
    AdditionalDrawableText.cpp
    AdditionalDrawableHitboxOutline.cpp
    Animator.cpp

    Screens/GameScreen.cpp
    Screens/MainMenuScreen.cpp
	Screens/MenuScreen.cpp
    Screens/LoadingScreen.cpp
    Screens/HowToPlay.cpp
    Screens/Credits.cpp
    Screens/ConfirmationScreen.cpp

    FPSCounter.cpp
	RaceProgress.cpp
    Dash.cpp
    Dodge.cpp
    Inflate.cpp
	MenuController.cpp

    InputBox/InputBox.cpp
    InputBox/SFMLCustomStuff.cpp
)

set(GR_HEADERS
    Tools/Ini.hh
    Tools/WINFS.hh
    Tools/WINFSReader.hh
    Tools/TextInBox.hh
    Tools/PauseOverlay.hh
    Tools/WinOverlay.hh

    AssetManager.hh
    PatternTemplate.hh
    BasicWall.hh
    Scene.hh
    GameObject.hh
    Player.hh
    Animation.hh
    BasicTrap.hh
    Camera.hh
    MapGenerator.hh
    Block.hh
    EndBlock.hh
    GhostController.hh
    HeroController.hh
    GameGUI.hh
    IAdditionalDrawableInfo.hh
    AdditionalDrawableBar.hh
    AdditionalDrawableText.hh
    AdditionalDrawableHitboxOutline.hh
    Animator.hh

    Screens/IScreen.hh
    Screens/GameScreen.hh
    Screens/MainMenuScreen.hh
	Screens/MenuScreen.hh
    Screens/LoadingScreen.hh
    Screens/HowToPlay.hh
    Screens/Credits.hh
    Screens/ConfirmationScreen.hh

    FPSCounter.hh
	RaceProgress.hh
    IAction.hh
    Dash.hh
    Dodge.hh
    GlobalInfos.hh
    Inflate.hh
	MenuController.hh
	

    InputBox/InputBox.hh
    InputBox/SFMLCustomStuff.hh
    InputBox/IKeyboardTranslator.hh
    InputBox/IControllerTranslator.hh

)

function(prefix_list output_result input_prefix input_list)
  foreach(val ${${input_list}})
    set(FUNCTION_RESULT "${FUNCTION_RESULT};${input_prefix}${val}")
  endforeach(val)
  set(${output_result} ${FUNCTION_RESULT} PARENT_SCOPE)
endfunction(prefix_list)

macro(GroupSources Sources PathPrefix SourcePrefix)
    foreach(child ${${Sources}})
        SET(groupname ${SourcePrefix}/${child})
        string(REGEX REPLACE "/[^/]+$" "" groupname ${groupname})
        string(REPLACE "/" "\\" groupname ${groupname})
        source_group(${groupname} FILES ${PathPrefix}/${child})
    endforeach()
endmacro()

GroupSources(GR_HEADERS ${GR_INC_DIR} Headers)
GroupSources(GR_SOURCES ${GR_SRC_DIR} Sources)

prefix_list(GR_HEADERS_SRC "${GR_INC_DIR}/" GR_HEADERS)
prefix_list(GR_SOURCES_SRC "${GR_SRC_DIR}/" GR_SOURCES)

add_executable(${GR_NAME} ${GR_SOURCES_SRC} ${GR_HEADERS_SRC})

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED System window graphics)
if (SFML_FOUND)
    # Link SFML Include DIR
    target_include_directories(${GR_NAME} PRIVATE ${SFML_INCLUDE_DIR})

    # Link the lib to the binary.
    target_link_libraries(${GR_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif (SFML_FOUND)

target_link_libraries(${GR_NAME} CommonToolsLib)
target_link_libraries(${GR_NAME} SoundEngine)
target_link_libraries(${GR_NAME} PhysicEngine)
target_link_libraries(${GR_NAME} InputEngine)

target_include_directories(${GR_NAME} PRIVATE ${GR_INC_DIR})
target_include_directories(${GR_NAME} PRIVATE ${GR_COMMON_DIR}/include ${GR_COMMON_DIR}/dependencies/include)
target_include_directories(${GR_NAME} PRIVATE ${GR_SOUND_ENGINE_DIR}/include ${GR_SOUND_ENGINE_DIR}/dependencies/include)
target_include_directories(${GR_NAME} PRIVATE ${GR_PHYSIC_ENGINE_DIR}/include ${GR_PHYSIC_ENGINE_DIR}/dependencies/include)
target_include_directories(${GR_NAME} PRIVATE ${GR_INPUT_ENGINE_DIR}/include ${GR_INPUT_ENGINE_DIR}/dependencies/include)


add_custom_command(TARGET ${GR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/SFML/bin/"
        $<TARGET_FILE_DIR:${GR_NAME}>)

add_custom_command(TARGET ${GR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GR_SOUND_ENGINE_DIR}/dependencies/bin/"
        $<TARGET_FILE_DIR:${GR_NAME}>)

add_custom_command(TARGET ${GR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/Resources"
        $<TARGET_FILE_DIR:${GR_NAME}>/Resources)

add_custom_command(TARGET ${GR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/Resources"
        ${CMAKE_BINARY_DIR}/Resources)