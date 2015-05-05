cmake_minimum_required (VERSION 2.8)
project (game-of-life)

add_executable (game-of-life game.c)
target_link_libraries (game-of-life ncursesw)
