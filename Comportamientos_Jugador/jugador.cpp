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

bool giroIzq (char tipoCasilla, Sensores sensor) {
	return (sensor.terreno[1] == tipoCasilla or (sensor.terreno[4] == tipoCasilla and esAccesible(sensor.terreno[1],sensor.superficie[1])) or (sensor.terreno[9] == tipoCasilla and esAccesible(sensor.terreno[1],sensor.superficie[1]) and esAccesible(sensor.terreno[4],sensor.superficie[4]))) ;
}

bool giroDer (char tipoCasilla, Sensores sensor) {
	return (sensor.terreno[3] == tipoCasilla or (sensor.terreno[8] == tipoCasilla and esAccesible(sensor.terreno[3],sensor.superficie[3])) or (sensor.terreno[15] == tipoCasilla and esAccesible(sensor.terreno[3],sensor.superficie[3]) and esAccesible(sensor.terreno[8],sensor.superficie[8]))) ;
}

bool sigoAlante (char tipoCasilla, Sensores sensor) {
	return (sensor.terreno[2] == tipoCasilla or (sensor.terreno[6] == tipoCasilla and esAccesible(sensor.terreno[2],sensor.superficie[2])) or (sensor.terreno[12] == tipoCasilla and esAccesible(sensor.terreno[2],sensor.superficie[2]) and esAccesible(sensor.terreno[6],sensor.superficie[6]))) ;
}

Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

	if (sensores.bateria <= 3000 /*and sensores.vida > sensores.bateria*/)
	{
		cargaNecesaria = true;
	}
	if (sensores.reset)
	{
		bien_situado = false;
		tieneBikini = false ;
		tieneZapatilla = false ;
	}

	int a;
	if (bien_situado)
	{
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
	}

	// Si se situa sobre una casilla G, comienza a guardar en el array del mapa
	if ((sensores.posF != -1 and !bien_situado))
	{
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	// Si las 3 casillas de en frente no han sido guardadas, las guardamos.
	if (bien_situado)
	{
		if (mapaResultado[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] == '?')
			mapaResultado[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] = sensores.terreno[1];
		if (mapaResultado[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] == '?')
			mapaResultado[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] = sensores.terreno[3];
		if (mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] == '?')
			mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] = sensores.terreno[2];
	}

	cout << "Fila: " << current_state.fil << " Columna:" << current_state.col << endl;
	cout << "Izquierda " << mapaTiempo[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] << endl;
	cout << "Siguiente " << mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] << endl;
	cout << "Derecha " << mapaTiempo[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] << endl;

	//Guarda si tiene el bikini
	if(sensores.terreno[0] == 'K') {
		tieneBikini=true ;
	}

	//Guarda si tiene zapatillas
	if (sensores.terreno[0] == 'D') {
		tieneZapatilla = true ;
	}

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
		if (sensores.bateria == 5000 /*or sensores.bateria >= sensores.vida*/)
			cargaNecesaria = false;
	}

	// Priorizamos girar a una casilla de G, para activar los sensores.
	else if (giroIzq('G', sensores) and !bien_situado and last_action != actTURN_BR)
	{

		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (sigoAlante('G',sensores) and !bien_situado)
	{
		accion = actFORWARD;
	}
	else if (giroDer('G',sensores) and !bien_situado and last_action != actTURN_BL)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]) and mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] == '?')
	{
		accion = actFORWARD;
	}

	//Priorizamos coger el bikini o las zapatillas
	else if ((sigoAlante('K', sensores) && !tieneBikini) || (sigoAlante('D', sensores) && !tieneZapatilla)) {
		accion = actFORWARD ;
	}
	else if ((giroDer('K',sensores) && !tieneBikini) || (giroDer('D',sensores) && !tieneZapatilla)) {
		accion = actTURN_SR ;
	}
	else if ((giroIzq('K', sensores) && !tieneBikini) || (giroIzq('D', sensores) && !tieneZapatilla)) {
		accion = actTURN_SL ;
	}

	//Priorizamos cambiar a una casilla que no sea agua, pues consume más energía si no tenemos el bikini
	else if (sensores.terreno[0]=='A' && esAccesible(sensores.terreno[2], sensores.superficie[2]) && sensores.terreno[2]!='A' && !tieneBikini){
		accion = actFORWARD ;
	}
	else if (sensores.terreno[0]=='A' && esAccesible(sensores.terreno[3], sensores.superficie[3]) && sensores.terreno[3]!='A' && !tieneBikini){
		accion = actTURN_SR ;
	}
	else if (sensores.terreno[0]=='A' && esAccesible(sensores.terreno[1], sensores.superficie[1]) && sensores.terreno[1]!='A' && !tieneBikini){
		accion = actTURN_SL ;
	}

	//Priorizamos cambiar a una casilla que no sea bosque si no tenemos las zapatillas, pues consume más energía
	else if (sensores.terreno[0]=='B' && esAccesible(sensores.terreno[2], sensores.superficie[2]) && sensores.terreno[2]!='B' && !tieneBikini){
		accion = actFORWARD ;
	}
	else if (sensores.terreno[0]=='B' && esAccesible(sensores.terreno[3], sensores.superficie[3]) && sensores.terreno[3]!='B' && !tieneBikini){
		accion = actTURN_SR ;
	}
	else if (sensores.terreno[0]=='B' && esAccesible(sensores.terreno[1], sensores.superficie[1]) && sensores.terreno[1]!='B' && !tieneBikini){
		accion = actTURN_SL ;
	}

	// Priorizamos ahora las casillas que no han sido visitadas y son accesibles
	else if (last_action != actTURN_BR and esAccesible(sensores.terreno[1], sensores.superficie[1]) and mapaResultado[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] == '?')
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (last_action != actTURN_BL and esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaResultado[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] == '?')
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}

	// Comprobamos de las 3 casillas que tenemos en frente cual es la que hace más tiempo que recorrimos y giramos hacia ella

	else if ((esAccesible(sensores.terreno[1], sensores.superficie[1]) or esAccesible(sensores.terreno[3], sensores.superficie[3])) and esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		if (last_action != actTURN_BR and esAccesible(sensores.terreno[1], sensores.superficie[1]) and mapaTiempo[calcFilIzq(current_state.brujula, current_state, true)][calcColDer(current_state.brujula, current_state, true)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
		{
			sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
		}
		else if (last_action != actTURN_BL and esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaTiempo[calcFilIzq(current_state.brujula, current_state, false)][calcColDer(current_state.brujula, current_state, false)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
		{
			sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
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

	// Actualizamos el tiempo de la casilla
	mapaTiempo[current_state.fil][current_state.col] = sensores.tiempo;

	// Determinar el efecto de la ultima accion enviada
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
