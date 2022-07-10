Project(Zauberberg)

set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_CXX_FLAGS "-fpermissive")

add_executable(Zauberberg main.cpp)
add_executable(Zauberberg game.cpp)
add_executable(Zauberberg land.cpp)
