cmake_minimum_required(VERSION 3.31)
project(ThamerBiblio C)

set(CMAKE_C_STANDARD 11)

add_executable(ThamerBiblio main.c
        BibliographySystem.c
        BibliographySystem.h)
