cmake_minimum_required(VERSION 3.3)
project(Mercury_Pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES original.cpp Ball_Racket.cpp Ball_Racket.h Utilities.cpp Utilities.h MainLoop.cpp MainLoop.h main.cpp)
add_executable(Mercury_Pong ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics audio)
target_link_librarie(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${main.cpp} ${SFML_Libraries})
endif()