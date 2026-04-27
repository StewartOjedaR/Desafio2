#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
using namespace std;
bool cadenasIguales(const char *cadena1, const char *cadena2)
{
    int i = 0;
    while (cadena1[i] != '\0' && cadena2[i] != '\0')
    {
        if (cadena1[i] != cadena2[i])
            return false;
        i++;
    }
    return cadena1[i] == cadena2[i]; // Retorna true si ambos terminan al mismo tiempo
}
short CtoNum(char *c)
{
    short num = 0;
    for (int i = 0; c[i] != '\0'; i++)
    {
        num = num * 10 + (c[i] - '0');
    }
    return num;
}

class Jugador
{
    char nombre[10] = "nombre";
    char apellido[10] = "apellido";
    char asistencias, tarjetasRojas, tarjetasAmarillas, faltas;
    short numeroCamiseta, minutosTotales, goles;

public:
    Jugador(short _num);
    void actualizarEstadisticas(short goles, char amarillas, char rojas, char faltas, short minutos);
    void migrarCSV();
    void setNumCamiseta();
    void setNombre();
    void setApellido();
    short getGoles();
    void getAmonestacion(char roja, char amarilla, char falta);
    short getMinutos();
    void getNombre();
    bool resultadoPartido(bool resultado); // true ganado, false perdido
    ~Jugador()
    {
    }
};

class Seleccion
{
private:
    short ranking;
    char pais[20];
    char directorTecnico[30];
    char federeracion[30];
    char confederacion[30];
    short golesFavor;
    short golesContra;
    short partidosGanados, partidosEmpatados, partidosPerdidos, tarjetasAmarillas, tarjetasRojas, faltas;
    static Seleccion *listaEquipos[48]; // Almacena los punteros a los equipos
    static short contadorEquipos;       // Lleva la cuenta de cuántos hay
    Jugador **jugadores;

public:
    Seleccion(short _ranking, char *_pais, char *_directorTecnico, char *_federeracion, char *_confederacion, short _golesFavor, short _golesContra, short _partidosGanados, short _partidosEmpatados, short _partidosPerdidos);
    ~Seleccion();
  //  static Seleccion* obtenerPorNombre(const char *nombreBuscado);
    void agregarJugador();
    void statsPartido(short golesFavor, short golesContra, char resultado, char amarillas, char rojas, char faltas);
    void mejorarRanking();
    void empeorarRanking();
    void mostrarPlantilla();
    static void buscarYMostrar(const char *nombreBuscado);
};

Seleccion *Seleccion::listaEquipos[48] = {nullptr};
short Seleccion::contadorEquipos = 0;
class Grupo
{
};
class Partido
{
};

short Jugador::getGoles()
{
    return goles;
}
/*void Jugador::setNombre(){
    const char name[8] = "nombre";
    for (int i =0 ; i<8 ; i++){
        if (name[i]=='\0'){
            nombre[i] =int(numeroCamiseta);
            nombre[i+1]='\0';
            i++;
            break;
        }
        nombre[i]=name[i];
    }

}
void Jugador::setApellido(){
    const char* nickname = "apellido";
    for (int i =0 ; i<9 ; i++){
        if (nickname[i]=='\0'){
            apellido[i] =numeroCamiseta;
            apellido[i+1]='\0';
            i++;
            break;
        }
        apellido[i]=nickname[i];
    }
}*/
void Jugador::actualizarEstadisticas(short goles, char amarillas, char rojas, char faltas, short minutos)
{
    this->goles += goles;
    this->tarjetasAmarillas += amarillas;
    this->tarjetasRojas += rojas;
    this->faltas += faltas;
    this->minutosTotales += minutos;
}
void Jugador::getAmonestacion(char roja, char amarilla, char falta)
{
    cout << "Jugador " << nombre << " " << apellido << " tiene " << int(amarilla) << " tarjetas amarillas, " << int(roja) << " tarjetas rojas y " << int(falta) << " faltas." << endl;
}
void Jugador::migrarCSV()
{
    fstream archivo("jugadores.csv", ios::out | ios::app);
    if (archivo.is_open())
    {
        archivo << nombre << "," << apellido << "," << int(numeroCamiseta) << "," << goles << "," << int(tarjetasAmarillas) << "," << int(tarjetasRojas) << "," << int(faltas) << "," << minutosTotales << endl;
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
}
void Jugador::getNombre()
{
    cout << "El nombre del jugador es " << nombre << numeroCamiseta << " " << apellido << numeroCamiseta << endl;
}
void Seleccion::buscarYMostrar(const char *nombreBuscado)
{
    bool encontrado = false;
    for (int i = 0; i < contadorEquipos; i++)
    {
        if (cadenasIguales(listaEquipos[i]->pais, nombreBuscado))
        {
            // Imprimimos los datos del equipo encontrado
            cout << "--- Equipo Encontrado ---" << endl;
            cout << "Pais: " << listaEquipos[i]->pais << endl;
            cout << "Director: " << listaEquipos[i]->directorTecnico << endl;
            cout << "Ranking: " << listaEquipos[i]->ranking << endl;
            cout << "Goles a Favor: " << listaEquipos[i]->golesFavor << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
    {
        cout << "La seleccion '" << nombreBuscado << "' no existe." << endl;
    }
}
void setSeleccion(char *linea)
{
    char arreglo_aux[10][30];
    int j = 0;
    int contador = 0;
    for (int i = 0; linea[i] != '\0'; i++)
    {
        // cout << linea[i];
        if (linea[i] == ';')
        {
            arreglo_aux[contador][j] = '\0';
            j = 0;
            contador++;
            if (contador >= 10)
            {
                break;
            }
            continue;
        }
        arreglo_aux[contador][j] = linea[i];
        j++;
        if (linea[i + 1] == '\0')
        {
            arreglo_aux[contador][j] = '\0';
            break;
        }
    }
    Seleccion *seleccion = new Seleccion(CtoNum(arreglo_aux[0]), arreglo_aux[1], arreglo_aux[2], arreglo_aux[3], arreglo_aux[4], CtoNum(arreglo_aux[5]), CtoNum(arreglo_aux[6]), CtoNum(arreglo_aux[7]), CtoNum(arreglo_aux[8]), CtoNum(arreglo_aux[9]));
    // cout<<endl<<arreglo_aux[0]<<arreglo_aux[1]<<arreglo_aux[2]<<arreglo_aux[3]<<arreglo_aux[4]<<arreglo_aux[5]<<arreglo_aux[6]<<arreglo_aux[7]<<arreglo_aux[8]<<arreglo_aux[9]<<endl;
}
void crearSelecciones(char file[])
{
    int primeraPosicion = '0' + 1;
    bool bandera = false;
    bool *ptrBandera = &bandera;
    const int MAX_LINEA = 1024; // Tamaño máximo de cada línea
    char linea[MAX_LINEA];
    std::fstream archivo(file);
    if (archivo.is_open())
    {
        while (archivo.getline(linea, MAX_LINEA))
        {
            for (int i = 0; linea[i] != '\0'; i++)
            {
                if (linea[i] == ',')
                {
                    linea[i] = ' '; // Reemplaza la coma por un espacio
                }
            }
            if (linea[0] == primeraPosicion)
            {
                *ptrBandera = true;
                primeraPosicion = 0;
            }

            if (*ptrBandera)
            {
                setSeleccion(linea);
   //             std::cout << linea << std::endl;
            }
        }
        archivo.close();
    }
    else
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }
};

Seleccion::Seleccion(short _ranking, char *_pais, char *_directorTecnico, char *_federeracion, char *_confederacion, short _golesFavor, short _golesContra, short _partidosGanados, short _partidosEmpatados, short _partidosPerdidos)
{
ranking = _ranking;
    golesFavor = _golesFavor;
    golesContra = _golesContra;
    partidosGanados = _partidosGanados;
    partidosEmpatados = _partidosEmpatados;
    partidosPerdidos = _partidosPerdidos;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    int k = 0;
    while (_pais[k])
    {
        pais[k] = _pais[k];
        k++;
    }
    pais[k] = '\0';
    k = 0;
    while (_directorTecnico[k])
    {
        directorTecnico[k] = _directorTecnico[k];
        k++;
    }
    directorTecnico[k] = '\0';
    k = 0;
    while (_federeracion[k])
    {
        federeracion[k] = _federeracion[k];
        k++;
    }
    federeracion[k] = '\0';
    k = 0;
    while (_confederacion[k])
    {
        confederacion[k] = _confederacion[k];
        k++;
    }
    confederacion[k] = '\0';
    if (contadorEquipos < 48)
    {
        listaEquipos[contadorEquipos] = this;
        contadorEquipos++;
    }
    jugadores = new Jugador *[26];
    short num = 1;
    for (int i = 0; i < 26; i++)
    {
        jugadores[i] = new Jugador(num);
        num++;
    }
}
Seleccion::~Seleccion()
{
    for (int i = 0; i < 26; i++)
    {
        delete jugadores[i]; // Borramos cada jugador
    }
    delete[] jugadores;
} // Borramos el arreglo de punteros;

Jugador::Jugador(short _num)
{
    numeroCamiseta = _num;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    asistencias = 0;
    minutosTotales = 0;
    goles = 0;
}
#endif // FUNCIONES_H
