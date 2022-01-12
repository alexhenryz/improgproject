
# Sätt ett namn på projektet
project(imperativ-programmering-Projektarbete)

# För säkerhets skull, speca vilken version av CMake vi använder
cmake_minimum_required(VERSION 3.5)

# Våra flaggor till GCC.
set(CMAKE_C_FLAGS "-std=c99 -Wall -g")


add_executable(textspel textspel.c world.c player.c)
