#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "../include/comportamientos/comportamiento.hpp"
#include <iostream>
using namespace std;

struct state
{
  int fil;
  int col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento
{

public:
  ComportamientoJugador(unsigned int size) : Comportamiento(size)
  {
    // Constructor de la clase
    // Dar el valor inicial a las variables de estado

    // Inicializamos la siguiente acción a IDLE
    siguienteAccion = actIDLE;

    // Inicializamos el vector del tiempo en el que se pasó por las casillas a 0
    vector<double> aux(size, 0);
    for (size_t i = 0; i < size; i++)
      mapaTiempo.push_back(aux);

    // Inicializamos el mapaResultado con los precipicios de los bordes
    for (unsigned int i = 0; i < size; i++)
    {
      // Filas
      mapaResultado[0][i] = 'P';
      mapaResultado[1][i] = 'P';
      mapaResultado[2][i] = 'P';
      mapaResultado[size - 1][i] = 'P';
      mapaResultado[size - 2][i] = 'P';
      mapaResultado[size - 3][i] = 'P';

      // Columnas
      mapaResultado[i][0] = 'P';
      mapaResultado[i][1] = 'P';
      mapaResultado[i][2] = 'P';
      mapaResultado[i][size - 1] = 'P';
      mapaResultado[i][size - 2] = 'P';
      mapaResultado[i][size - 3] = 'P';
    }

    current_state.fil = current_state.col = size - 1;
    current_state.brujula = norte;
    last_action = actIDLE;
    girar_derecha = false;
    bien_situado = false;
  }

  ComportamientoJugador(const ComportamientoJugador &comport) : Comportamiento(comport) {}
  ~ComportamientoJugador() {}

  Action think(Sensores sensores);
  int interact(Action accion, int valor);

private:
  void dibujarDiagonales(Sensores sensor, int fil0, int col0, int sumaf, int sumac) ;
  Action comprobarTiempo(Sensores sensores);
  state current_state;
  Action last_action;
  bool girar_derecha;
  bool bien_situado;
  bool cargaNecesaria;
  bool tieneBikini;
  bool tieneZapatilla;
  Action siguienteAccion;
  vector<vector<double>> mapaTiempo;

  // Declarar aquí las variables de estado
};

bool esAccesible(char terreno, char superficie);

#endif
