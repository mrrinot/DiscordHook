cmake_minimum_required(VERSION 3.0)

project(HookDll)

set(DLL_NAME Hook)

set(DLL_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/Sources)
set(DLL_HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/Includes)

# Server Sources File (*.cpp)
set(DLL_SRC_FILES
 ${DLL_SRC_PATH}/Dll.cpp
)

# Server Headers File (*.hh, *.hpp)
set(DLL_HEADER_FILES
 ${DLL_HEADER_PATH}/Header.hh
)

# Build the library.
add_library(${DLL_NAME} MODULE ${DLL_SRC_FILES} ${DLL_HEADER_FILES})

target_include_directories(${DLL_NAME} PRIVATE ${DLL_HEADER_PATH})