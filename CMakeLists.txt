cmake_minimum_required(VERSION 3.2)
project("practicas")

set(OpenGlLinkers -lGL -lglut -lGLEW -lm -lGLU -Wdeprecated -Wwrite-strings) # setting all the Glut libraries as one variable.

set(CMAKE_CXX_STANDARD 14)

add_executable(practicas-graficacion
#        src/practica_1/main.cpp)
#        src/proyecto_1/juego_1.cpp)
#        ejercicio1.cpp)
#        src/practica_4/practica_4.cpp)
#        src/practica_rompecabezas.cpp)
#        src/practica_5/practica_5.cpp)
#        src/practica_recuperacion/cplusplus/getbmp.h
#        src/practica_recuperacion/cplusplus/getbmp.cpp
#        src/practica_recuperacion/cplusplus/practica_recuperacion.cpp)
#        src/proyecto_2/matrix.h
#        src/proyecto_2/game.h
#        src/proyecto_2/proyecto_2.cpp)
        src/practica_extra2/practica3.cpp)
#src/practica_pelotas.cpp)
target_link_libraries(practicas-graficacion ${OpenGlLinkers})