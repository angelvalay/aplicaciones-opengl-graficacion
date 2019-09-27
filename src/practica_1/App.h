//
// Created by angel on 27/09/19.
//

#ifndef PRACTICAS_APP_H
#define PRACTICAS_APP_H

/// Clase para inicializar la app
class App {
private:
    double alturaVentana; /// Altura de la ventana
    double anchoVentana; /// Ancho de la ventana
    ColorRGB colorFore{}; /// Color del dibujado
    ColorRGB colorBack{}; /// Color de fondo
    int canArg; /// Cantidad de argumentos
    char **args; /// Argumentos de la app
    unsigned int modoDisplay; /// Modo de la ventana
public:

    /// Constructor de clase
    App(unsigned int modoDisplay, double alturaV,
            double anchoV, ColorRGB colorFore, ColorRGB colorBack){
        this->modoDisplay = modoDisplay;
        this->alturaVentana = alturaV;
        this->anchoVentana = anchoV;
        this->colorFore = colorFore;
        this->colorBack = colorBack;
        this->canArg = 0;
        this->args = nullptr;
    }
    void inicializar(char* titulo);
};


#endif //PRACTICAS_APP_H
