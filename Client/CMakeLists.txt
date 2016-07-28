cmake_minimum_required(VERSION 3.0)

project(Client)

set(CLIENT_NAME Client)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CLIENT_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR}/Common)
#set(CLIENT_SOUND_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/SoundEngine)
#set(CLIENT_PHYSIC_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/PhysicEngine)
#set(CLIENT_INPUT_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/InputEngine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake/Modules")

#add_subdirectory(${CLIENT_COMMON_DIR})
#add_subdirectory(${CLIENT_SOUND_ENGINE_DIR})
#add_subdirectory(${CLIENT_PHYSIC_ENGINE_DIR})
#add_subdirectory(${CLIENT_INPUT_ENGINE_DIR})

set(CLIENT_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/Sources)
set(CLIENT_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/Includes)

set(CLIENT_SOURCES
    main.cpp
)

set(CLIENT_HEADERS
)

function(prefix_list output_result input_prefix input_list)
  foreach(val ${${input_list}})
    set(FUNCTION_RESULT "${FUNCTION_RESULT};${input_prefix}${val}")
  endforeach(val)
  set(${output_result} ${FUNCTION_RESULT} PARENT_SCOPE)
endfunction(prefix_list)

macro(groupSources Sources PathPrefix SourcePrefix)
    foreach(child ${${Sources}})
        SET(groupname ${SourcePrefix}/${child})
        string(REGEX REPLACE "/[^/]+$" "" groupname ${groupname})
        string(REPLACE "/" "\\" groupname ${groupname})
        source_group(${groupname} FILES ${PathPrefix}/${child})
    endforeach()
endmacro()

groupSources(CLIENT_HEADERS ${CLIENT_INC_DIR} Headers)
groupSources(CLIENT_SOURCES ${CLIENT_SRC_DIR} Sources)

prefix_list(CLIENT_HEADERS_SRC "${CLIENT_INC_DIR}/" CLIENT_HEADERS)
prefix_list(CLIENT_SOURCES_SRC "${CLIENT_SRC_DIR}/" CLIENT_SOURCES)

add_executable(${CLIENT_NAME} ${CLIENT_SOURCES_SRC} ${CLIENT_HEADERS_SRC})

#target_link_libraries(${CLIENT_NAME} CommonToolsLib)
#target_link_libraries(${CLIENT_NAME} SoundEngine)
#target_link_libraries(${CLIENT_NAME} PhysicEngine)
#target_link_libraries(${CLIENT_NAME} InputEngine)

#target_include_directories(${CLIENT_NAME} PRIVATE ${CLIENT_INC_DIR})
#target_include_directories(${CLIENT_NAME} PRIVATE ${CLIENT_COMMON_DIR}/include ${CLIENT_COMMON_DIR}/dependencies/include)
#target_include_directories(${CLIENT_NAME} PRIVATE ${CLIENT_SOUND_ENGINE_DIR}/include ${CLIENT_SOUND_ENGINE_DIR}/dependencies/include)
#target_include_directories(${CLIENT_NAME} PRIVATE ${CLIENT_PHYSIC_ENGINE_DIR}/include ${CLIENT_PHYSIC_ENGINE_DIR}/dependencies/include)
#target_include_directories(${CLIENT_NAME} PRIVATE ${CLIENT_INPUT_ENGINE_DIR}/include ${CLIENT_INPUT_ENGINE_DIR}/dependencies/include)


#add_custom_command(TARGET ${CLIENT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${CMAKE_CURRENT_LIST_DIR}/SFML/bin/"
#        $<TARGET_FILE_DIR:${CLIENT_NAME}>)
