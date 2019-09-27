cmake_minimum_required(VERSION 3.2)
project("practicas")

set(OpenGlLinkers -lglut -lGLEW -lGL -lm -Wdeprecated -Wwrite-strings) # setting all the Glut libraries as one variable.

set(CMAKE_CXX_STANDARD 14)

add_executable(practicas-graficacion
        src/practica_1/main.cpp)

target_link_libraries(practicas-graficacion ${OpenGlLinkers})