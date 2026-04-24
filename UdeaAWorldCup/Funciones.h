#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
using namespace std;
auto tamCadena = [](char* cadenaCaracteres) {
    int i = 0;
    while (cadenaCaracteres[i] != '\0') {
        i++;
    }
    return i;
};
class Jugador{
    char nombre[8];
    char apellido[9];
    char numeroCamiseta=0, asistencias=0, tarjetasRojas=0, tarjetasAmarillas=0, faltas=0;
    short minutosTotales=0, goles=0;
    static char contadorNumeroCamiseta;

public:
    Jugador();
    void actualizarEstadisticas(short goles,char amarillas, char rojas, char faltas, short minutos);
    void migrarCSV();
    void setNumCamiseta();
    void setNombre();
    void setApellido();
    short getGoles();
    void getAmonestacion(char roja, char amarilla, char falta);
    short getMinutos();
    void getNombre();
    bool resultadoPartido(bool resultado);//true ganado, false perdido
    ~Jugador(){
    }


};
char Jugador::contadorNumeroCamiseta = 0;
void Jugador::setNumCamiseta(){
    contadorNumeroCamiseta++;
    if (contadorNumeroCamiseta > 26){// Si el contador supera 26, reiniciamos a 1, porqeu son 26 jugadores por seleccion
        contadorNumeroCamiseta = 1;
    }
    this->numeroCamiseta = contadorNumeroCamiseta;
}
Jugador::Jugador(){
    tarjetasAmarillas=0;
    tarjetasRojas=0;
    asistencias=0;
    minutosTotales=0;
    setNumCamiseta();
    goles=5;
    setNombre();
    setApellido();
    getNombre();

}
short Jugador::getMinutos(){
    return minutosTotales;
}
short Jugador::getGoles(){
    return goles;
}
void Jugador::setNombre(){
    const char name[7] = "nombre";
    for (int i =0 ; i<8 ; i++){
        if (name[i]=='\0'){
            nombre[i] = '0' + numeroCamiseta; 
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
            apellido[i] = '0' + numeroCamiseta;
            apellido[i+1]='\0';
            i++;
            break;
        }
        apellido[i]=nickname[i];
    }
}
void Jugador::actualizarEstadisticas(short goles,char amarillas, char rojas, char faltas, short minutos){
    this->goles+=goles;
    this->tarjetasAmarillas+=amarillas;
    this->tarjetasRojas+=rojas;
    this->faltas+=faltas;
    this->minutosTotales+=minutos;
}
void Jugador::getAmonestacion(char roja, char amarilla, char falta){
    cout<<"Jugador "<<nombre<<" "<<apellido<<" tiene "<<int(amarilla)<<" tarjetas amarillas, "<<int(roja)<<" tarjetas rojas y "<<int(falta)<<" faltas."<<endl;
}
void Jugador::migrarCSV(){
    fstream archivo("jugadores.csv", ios::out | ios::app);
    if (archivo.is_open()) {
        archivo << nombre << "," << apellido << "," << int(numeroCamiseta) << "," << goles << "," << int(tarjetasAmarillas) << "," << int(tarjetasRojas) << "," << int(faltas) << "," << minutosTotales << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
}
void Jugador::getNombre(){
    cout<<"El nombre del jugador es "<<nombre<<" "<<apellido<<endl;
}
class Seleccion{
private:
    char ranking;
    char* pais;
    char* directorTecnico;
    char* federeracion;
    char* confederacion;
    short golesFavor;
    short golesContra;
    char partidosGanados, partidosPerdidos, tarjetasAmarillas, tarjetasRojas, faltas;
    char** jugadores[26];
public:
    Seleccion(char pais, char cantJugadores);
    ~Seleccion();
    void agregarJugador(Jugador* jugador);
    void statsPartido(short golesFavor, short golesContra, char resultado, char amarillas, char rojas, char faltas);
    void mejorarRanking();
    void empeorarRanking();
    static Seleccion** importarDesdeCSV(fstream archivo);

};
class Grupo{

};
class Partido{

};

#endif // FUNCIONES_H
