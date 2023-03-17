#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz)
{
	matriz[st.fil][st.col] = terreno[0];
}

bool esAccesible(char terreno, char superficie)
{
	return ((terreno == 'T' or terreno == 'S' or terreno == 'G' or terreno == 'B' or terreno == 'A' or terreno == 'K' or terreno == 'D' or terreno == 'X') and superficie == '_');
}

int calcFilSig(Orientacion direccion, state estado)
{
	int sol;
	switch (estado.brujula)
	{
	case norte:
		sol = estado.fil - 1;
		break;
	case noreste:
		sol = estado.fil - 1;
		break;
	case este:
		sol = estado.fil;
		break;
	case sureste: /*Actualizacion*/
		sol = estado.fil + 1;
		break;
	case sur: /*Actualizacion*/
		sol = estado.fil + 1;
		break;
	case suroeste: /*Actualizacion*/
		sol = estado.fil + 1;
		break;
	case oeste: /*Actualizacion*/
		sol = estado.fil;
		break;
	case noroeste: /*Actualizacion*/
		sol = estado.fil - 1;
		break;
	}
	return sol;
}

int calcColSig(Orientacion direccion, state estado)
{
	int sol;
	switch (estado.brujula)
	{
	case norte:
		sol = estado.col;
		break;
	case noreste:
		sol = estado.col + 1;
		break;
	case este:
		sol = estado.col + 1;
		break;
	case sureste: /*Actualizacion*/
		sol = estado.col + 1;
		break;
	case sur: /*Actualizacion*/
		sol = estado.col;
		break;
	case suroeste: /*Actualizacion*/
		sol = estado.col - 1;
		break;
	case oeste: /*Actualizacion*/
		sol = estado.col - 1;
		break;
	case noroeste: /*Actualizacion*/
		sol = estado.col - 1;
		break;
	}
	return sol;
}

int calcFilIzq(Orientacion direccion, state estado, bool izq)
{
	int sol;
	switch (estado.brujula)
	{
	case norte:
		izq ? sol = estado.fil - 1 : sol = estado.fil - 1;

		break;
	case noreste:
		izq ? sol = estado.fil - 1 : sol = estado.fil;
		break;
	case este:
		izq ? sol = estado.fil - 1 : sol = estado.fil + 1;
		break;
	case sureste: /*Actualizacion*/
		izq ? sol = estado.fil : sol = estado.fil + 1;
		break;
	case sur: /*Actualizacion*/
		izq ? sol = estado.fil + 1 : sol = estado.fil + 1;
		break;
	case suroeste: /*Actualizacion*/
		izq ? sol = estado.fil + 1 : sol = estado.fil;
		break;
	case oeste: /*Actualizacion*/
		izq ? sol = estado.fil + 1 : sol = estado.fil - 1;
		break;
	case noroeste: /*Actualizacion*/
		izq ? sol = estado.fil : sol = estado.fil - 1;
		break;
	}
	return sol;
}

int calcColDer(Orientacion direccion, state estado, bool izq)
{
	int sol;
	switch (estado.brujula)
	{
	case norte:
		izq ? sol = estado.col - 1 : sol = estado.col + 1;

		break;
	case noreste:
		izq ? sol = estado.col : sol = estado.col + 1;
		break;
	case este:
		izq ? sol = estado.col + 1 : sol = estado.col + 1;
		break;
	case sureste: /*Actualizacion*/
		izq ? sol = estado.col + 1 : sol = estado.col;
		break;
	case sur: /*Actualizacion*/
		izq ? sol = estado.col + 1 : sol = estado.col - 1;
		break;
	case suroeste: /*Actualizacion*/
		izq ? sol = estado.col : sol = estado.col - 1;
		break;
	case oeste: /*Actualizacion*/
		izq ? sol = estado.col - 1 : sol = estado.col - 1;
		break;
	case noroeste: /*Actualizacion*/
		izq ? sol = estado.col - 1 : sol = estado.col;
		break;
	}
	return sol;
}

Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

	if (sensores.bateria <= 3000)
	{
		cargaNecesaria = true;
	}

	mapaTiempo[current_state.fil - 1][current_state.col - 1] = sensores.tiempo;
	int a;
	switch (last_action)
	{
	case actFORWARD:
		// Actualización en caso de avanzar
		switch (current_state.brujula)
		{
		case norte:
			current_state.fil--;
			break;
		case noreste:
			current_state.fil--;
			current_state.col++;
			break;
		case este:
			current_state.col++;
			break;
		case sureste: /*Actualizacion*/
			current_state.fil++;
			current_state.col++;
			break;
		case sur: /*Actualizacion*/
			current_state.fil++;
			break;
		case suroeste: /*Actualizacion*/
			current_state.fil++;
			current_state.col--;
			break;
		case oeste: /*Actualizacion*/
			current_state.col--;
			break;
		case noroeste: /*Actualizacion*/
			current_state.fil--;
			current_state.col--;
			break;
		}
		break;
	case actTURN_SL:
		a = current_state.brujula;
		a = (a + 7) % 8;
		// girar_derecha = (rand() % 2 == 0);
		current_state.brujula = static_cast<Orientacion>(a);
		break;
	case actTURN_SR:
		a = current_state.brujula;
		a = (a + 1) % 8;
		// girar_derecha = (rand() % 2 == 0);
		current_state.brujula = static_cast<Orientacion>(a);
		break;
	case actTURN_BL:
		// Actualización de girar 135º a la izquierda
		a = current_state.brujula;
		a = (a + 5) % 8;
		current_state.brujula = static_cast<Orientacion>(a);
		break;
	case actTURN_BR:
		// Actualización en caso de girar 135º a la derecha
		a = current_state.brujula;
		a = (a + 3) % 8;
		current_state.brujula = static_cast<Orientacion>(a);
		break;
	}

	// Si se situa sobre una casilla G, comienza a guardar en el array del mapa
	if ((sensores.posF != -1 and !bien_situado))
	{
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	cout << "Izquierda " << mapaTiempo[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] << endl;
	cout << "Siguiente " << mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] << endl;
	cout << "Derecha " << mapaTiempo[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] << endl;


	// Guarda en el array del mapa si ha pasado por G
	if (bien_situado)
	{
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
		// mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
	}

	// Decidir la proxima accion

	// Priorizamos recargar y esperar a estar recargado
	if (sensores.terreno[1] == 'X' and cargaNecesaria)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (sensores.terreno[3] == 'X' and cargaNecesaria)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}
	else if (sensores.terreno[2] == 'X' and cargaNecesaria)
	{
		accion = actFORWARD;
	}
	else if (sensores.terreno[0] == 'X' and cargaNecesaria)
	{
		accion = actIDLE;
		if (sensores.bateria == 5000)
			cargaNecesaria = false;
	}

	// Priorizamos girar a una casilla de G, para activar los sensores.
	else if (sensores.terreno[1] == 'G' and !bien_situado)
	{

		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (sensores.terreno[2] == 'G' and !bien_situado)
	{
		accion = actFORWARD;
	}
	else if (sensores.terreno[3] == 'G' and !bien_situado)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]) and mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] == '?')
	{
		accion = actFORWARD;
	}

	// Priorizamos ahora las casillas que no han sido visitadas y son accesibles
	else if (esAccesible(sensores.terreno[1], sensores.superficie[1]) and mapaResultado[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] == '?')
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaResultado[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] == '?')
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}

	// Comprobamos de las 3 casillas que tenemos en frente cual es la que hace más tiempo que recorrimos y giramos hacia ella

	else if (esAccesible(sensores.terreno[1], sensores.superficie[1]) and esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		if (mapaTiempo[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
		{
			accion = actTURN_SL;
		}
		else if (esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaTiempo[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
		{
			accion = actTURN_SR;
		}
		else
		{
			accion = actFORWARD;
		}
		// switch (current_state.brujula)
		// {
		// case norte:
		// 	if (mapaTiempo[sensores.posF-1][sensores.posC-1] <= mapaTiempo[sensores.posF-1][sensores.posC] and mapaTiempo[sensores.posF-1][sensores.posC-1] <= mapaTiempo[sensores.posF-1][sensores.posC+1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case noreste:
		// 	if (mapaTiempo[sensores.posF-1][sensores.posC] <= mapaTiempo[sensores.posF-1][sensores.posC+1] and mapaTiempo[sensores.posF-1][sensores.posC] <= mapaTiempo[sensores.posF][sensores.posC+1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case este:
		// 	if (mapaTiempo[sensores.posF-1][sensores.posC+1] <= mapaTiempo[sensores.posF][sensores.posC+1] and mapaTiempo[sensores.posF-1][sensores.posC+1] <= mapaTiempo[sensores.posF+1][sensores.posC+1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case sureste: /*Actualizacion*/
		// 	if (mapaTiempo[sensores.posF][sensores.posC+1] <= mapaTiempo[sensores.posF+1][sensores.posC+1] and mapaTiempo[sensores.posF][sensores.posC+1] <= mapaTiempo[sensores.posF-1][sensores.posC])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case sur: /*Actualizacion*/
		// 	if (mapaTiempo[sensores.posF+1][sensores.posC+1] <= mapaTiempo[sensores.posF+1][sensores.posC] and mapaTiempo[sensores.posF+1][sensores.posC+1] <= mapaTiempo[sensores.posF+1][sensores.posC-1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case suroeste: /*Actualizacion*/
		// 	if (mapaTiempo[sensores.posF+1][sensores.posC] <= mapaTiempo[sensores.posF+1][sensores.posC-1] and mapaTiempo[sensores.posF+1][sensores.posC] <= mapaTiempo[sensores.posF][sensores.posC-1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case oeste: /*Actualizacion*/
		// 	if (mapaTiempo[sensores.posF+1][sensores.posC-1] <= mapaTiempo[sensores.posF][sensores.posC-1] and mapaTiempo[sensores.posF+1][sensores.posC-1] <= mapaTiempo[sensores.posF-1][sensores.posC-1])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// case noroeste: /*Actualizacion*/
		// 	if (mapaTiempo[sensores.posF][sensores.posC-1] <= mapaTiempo[sensores.posF-1][sensores.posC-1] and mapaTiempo[sensores.posF][sensores.posC-1] <= mapaTiempo[sensores.posF-1][sensores.posC])
		// 		accion = actTURN_SL;
		// 	else
		// 		accion = actFORWARD ;
		// 	break;
		// }
	}
	// Si es una casilla accesible, da un paso alante
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		accion = actFORWARD;
	}
	// else if (!girar_derecha)
	// {
	// 	accion = actTURN_SL;
	// 	girar_derecha = (rand() % 2 == 0);
	// }
	else
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
		girar_derecha = (rand() % 2 == 0);
	}

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch (sensores.sentido)
	{
	case 0:
		cout << "Norte" << endl;
		break;
	case 1:
		cout << "Noreste" << endl;
		break;
	case 2:
		cout << "Este" << endl;
		break;
	case 3:
		cout << "Sureste" << endl;
		break;
	case 4:
		cout << "Sur " << endl;
		break;
	case 5:
		cout << "Suroeste" << endl;
		break;
	case 6:
		cout << "Oeste" << endl;
		break;
	case 7:
		cout << "Noroeste" << endl;
		break;
	}
	cout << "Terreno: ";
	for (int i = 0; i < sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i = 0; i < sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "Tiempo: " << sensores.tiempo << endl;
	cout << endl;

	// Determinar el efecto de la ultima accion enviada
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
