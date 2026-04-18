cmake_minimum_required(VERSION 3.20)
project(RestoranSimulasyonu C)

set(CMAKE_C_STANDARD 11)

# Raylib'i otomatik indirip kuran yapı
include(FetchContent)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/master.tar.gz
)
FetchContent_MakeAvailable(raylib)

add_executable(RestoranSimulasyonu main.c)

# Raylib'i projeye bağla
target_link_libraries(RestoranSimulasyonu raylib)