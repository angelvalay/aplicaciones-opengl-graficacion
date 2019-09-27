//
// Created by angel on 27/09/19.
//

#include "App.h"

void App::inicializar(char* titulo) {
    glutInit(&this->canArg, this->args);
    glutInitDisplayMode(this->modoDisplay);
    glutInitWindowSize(this->anchoVentana, this->alturaVentana);
    glutCreateWindow(titulo);

    //Verificar su funcionalidad
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
