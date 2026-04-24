#include <iostream>
#include <fstream>
#include "Funciones.h"
using namespace std;
const int MAX_LINEA = 1024;  // Tamaño máximo de cada línea
char linea[MAX_LINEA];
int main()
{
 /* std::fstream archivo("selecciones_clasificadas_mundial.csv");
    if (archivo.is_open()) {
        while (archivo.getline(linea, MAX_LINEA)) {
        //    std::cout << linea << std::endl;
        }
        archivo.close();

    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }*/
    Jugador* jugador1=new Jugador();
Jugador* jugador2=new Jugador();
jugador1->actualizarEstadisticas(2,1,0,3,90);
  //  cout<<colombia->getGoles();
    delete jugador1;
    return 0;
}
