#include <iostream>
#include <fstream>
#include "Funciones.h"
using namespace std;
int main()
{

crearSelecciones("selecciones_clasificadas_mundial.csv");
Seleccion::buscarYMostrar("Brazil");
Seleccion::mostrarPlantilla("Brazil");
    return 0;
}
