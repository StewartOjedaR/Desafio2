#include <iostream>
#include <fstream>
#include "Funciones.h"
using namespace std;
int main()
{

crearSelecciones("selecciones_clasificadas_mundial.csv");
Seleccion::buscarYMostrar("Brazil");

    return 0;
}
