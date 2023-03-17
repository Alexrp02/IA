#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <iostream>
using namespace std;

struct state {
  int fil;
  int col; 
  Orientacion brujula ;
} ;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado

      //Inicializamos el vector del tiempo en el que se pasó por las casillas a 0
      vector<double> aux(size, 0) ;
      for (size_t i = 0; i < size; i++)
        mapaTiempo.push_back(aux) ;
      
      current_state.fil = current_state.col = size-1 ;
      current_state.brujula = norte ;
      last_action = actIDLE ;
      girar_derecha=false ;
      bien_situado = false ;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  state current_state ;
  Action last_action ;
  bool girar_derecha ;
  bool bien_situado ;
  bool cargaNecesaria;
  vector <vector<double>> mapaTiempo ;

  // Declarar aquí las variables de estado

};

bool esAccesible(char terreno, char superficie) ;

#endif
