cmake_minimum_required(VERSION 3.16)

project(UdeaAWorldCup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UdeaAWorldCup main.cpp
    Funciones.h)

include(GNUInstallDirs)
install(TARGETS UdeaAWorldCup
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
