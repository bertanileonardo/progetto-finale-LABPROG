cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(progetto-finale LANGUAGES CXX)

add_executable(a
    src/Interface.cpp
    src/Casella.cpp
    src/Giocatore.cpp
    src/GiocatorePc.cpp
    src/GiocatorePcHuman.cpp
    src/main.cpp 
)