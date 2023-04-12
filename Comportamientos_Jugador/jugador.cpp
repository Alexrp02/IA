#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

// Función que guarda la casilla actual en el mapa resultado.
void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz)
{
	matriz[st.fil][st.col] = terreno[0];
}

// Función para calcular si la casilla dada es accesible
bool esAccesible(char terreno, char superficie)
{
	return ((terreno == 'T' or terreno == 'S' or terreno == 'G' or terreno == 'B' or terreno == 'A' or terreno == 'K' or terreno == 'D' or terreno == 'X') and superficie == '_');
}

// Función para calcular la fila de la casilla siguiente
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

// Función para calcular la columna de la casilla siguiente
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

// Función para calcular la fila de la casilla a la izquierda o derecha
int calcFillIzqDer(Orientacion direccion, state estado, bool izq)
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

// Función para calcular la columna de la casilla a la izquierda o derecha
int calcColIzqDer(Orientacion direccion, state estado, bool izq)
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

// Función para dibujar el terreno cuando la orientación es en diagonal
void dibujarDiagonales(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz, int fil0, int col0, int sumaf, int sumac, bool comienzaCol)
{
	int pos = 0;
	int posF0 = st.fil;
	int posC0 = st.col;
	matriz[posF0][posC0] = terreno[pos];
	pos++;

	// Bucle para primera profundidad
	int posF = posF0 + fil0;
	int posC = posC0 + col0;
	for (pos; pos <= 3; pos++)
	{
		// Si está dentro de los límites escribimos
		if (posF >= 0 && posF < matriz.size() && posC >= 0 && posC < matriz[0].size())
			matriz[posF][posC] = terreno[pos];

		// Actualizamos la posición, dependiendo de si empieza a sumar por columnas o no
		if (comienzaCol && pos < 2)
			posC = posC + sumac;
		else if (!comienzaCol && pos < 2)
			posF = posF + sumaf;
		else if (comienzaCol && pos >= 2)
			posF = posF + sumaf;
		else if (!comienzaCol && pos >= 2)
			posC = posC + sumac;
	}

	// Bucle para segunda profundidad
	posF = posF0 + fil0 * 2;
	posC = posC0 + col0 * 2;
	for (pos; pos <= 8; pos++)
	{
		if (posF >= 0 && posF < matriz.size() && posC >= 0 && posC < matriz[0].size())
			matriz[posF][posC] = terreno[pos];

		if (comienzaCol && pos < 6)
			posC = posC + sumac;
		else if (!comienzaCol && pos < 6)
			posF = posF + sumaf;
		else if (comienzaCol && pos >= 6)
			posF = posF + sumaf;
		else if (!comienzaCol && pos >= 6)
			posC = posC + sumac;
	}

	// Bucle para tercera profundidad
	posF = posF0 + fil0 * 3;
	posC = posC0 + col0 * 3;
	for (pos; pos <= 15; pos++)
	{
		if (posF >= 0 && posF < matriz.size() && posC >= 0 && posC < matriz[0].size())
			matriz[posF][posC] = terreno[pos];

		if (comienzaCol && pos < 12)
			posC = posC + sumac;
		else if (!comienzaCol && pos < 12)
			posF = posF + sumaf;
		else if (comienzaCol && pos >= 12)
			posF = posF + sumaf;
		else if (!comienzaCol && pos >= 12)
			posC = posC + sumac;
	}
}

// Función para dibujar el terreno cuando las orientaciones no son diagonales
void dibujarRecto(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz, int factor, bool sumaColumna)
{
	int cont = 1;

	int filaInicial;
	int columnaInicial;
	for (int i = 1; i <= 3; i++)
	{
		if (sumaColumna)
		{
			columnaInicial = filaInicial = i * factor;
		}
		else
		{
			filaInicial = i * factor;
			columnaInicial = i * (-factor);
		}
		for (int j = 0; j < 1 + i * 2; j++)
		{

			if (sumaColumna)
			{
				if (st.fil + filaInicial >= 0 and st.fil + filaInicial < matriz.size() and st.col + columnaInicial >= 0 and st.col + columnaInicial < matriz[0].size())
				{
					matriz[st.fil + filaInicial][st.col + columnaInicial] = terreno[cont];
					cont++;
					columnaInicial -= factor;
				}
			}
			else
			{
				if (st.fil + filaInicial >= 0 and st.fil + filaInicial < matriz.size() and st.col + columnaInicial >= 0 and st.col + columnaInicial < matriz[0].size())
				{
					matriz[st.fil + filaInicial][st.col + columnaInicial] = terreno[cont];
					cont++;
					filaInicial -= factor;
				}
			}
		}
	}
}

// Función general para guardar el mapa resultado, dependiendo de la orientación llama a una función u otra.
void dibujarEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz, Orientacion direccion)
{
	switch (direccion)
	{
	case norte:
		dibujarRecto(terreno, st, matriz, -1, true);
		break;
	case sur:
		dibujarRecto(terreno, st, matriz, 1, true);
		break;
	case este:
		dibujarRecto(terreno, st, matriz, -1, false);
		break;
	case oeste:
		dibujarRecto(terreno, st, matriz, 1, false);
		break;
	case noroeste:
		dibujarDiagonales(terreno, st, matriz, 0, -1, -1, 1, false);
		break;
	case noreste:
		dibujarDiagonales(terreno, st, matriz, -1, 0, 1, 1, true);
		break;
	case sureste:
		dibujarDiagonales(terreno, st, matriz, 0, 1, 1, -1, false);
		break;
	case suroeste:
		dibujarDiagonales(terreno, st, matriz, 1, 0, -1, -1, true);
		break;
	}

	// // Noroeste
	// if (direccion == noroeste)
	// 	dibujarDiagonales(terreno, st, matriz, 0, -1, -1, 1, false);

	// // Noreste
	// if (direccion == noreste)
	// 	dibujarDiagonales(terreno, st, matriz, -1, 0, 1, 1, true);

	// // Sureste
	// if (direccion == sureste)
	// 	dibujarDiagonales(terreno, st, matriz, 0, 1, 1, -1, false);

	// // Suroeste
	// if (direccion == suroeste)
	// 	dibujarDiagonales(terreno, st, matriz, 1, 0, -1, -1, true);
}

// Función que determina si debería de girar a la izquierda.
bool giroIzq(char tipoCasilla, Sensores sensor)
{
	return (sensor.terreno[1] == tipoCasilla or (sensor.terreno[4] == tipoCasilla and esAccesible(sensor.terreno[1], sensor.superficie[1])) or (sensor.terreno[9] == tipoCasilla and esAccesible(sensor.terreno[1], sensor.superficie[1]) and esAccesible(sensor.terreno[4], sensor.superficie[4])));
}

// Función que determina si debería de girar a la derecha.
bool giroDer(char tipoCasilla, Sensores sensor)
{
	return (sensor.terreno[3] == tipoCasilla or (sensor.terreno[8] == tipoCasilla and esAccesible(sensor.terreno[3], sensor.superficie[3])) or (sensor.terreno[15] == tipoCasilla and esAccesible(sensor.terreno[3], sensor.superficie[3]) and esAccesible(sensor.terreno[8], sensor.superficie[8])));
}

// Función que determina si debería de seguir recto.
bool sigoAlante(char tipoCasilla, Sensores sensor)
{
	return (sensor.terreno[2] == tipoCasilla and esAccesible(sensor.terreno[2], sensor.superficie[2]) or (sensor.terreno[6] == tipoCasilla and esAccesible(sensor.terreno[2], sensor.superficie[2])) or (sensor.terreno[12] == tipoCasilla and esAccesible(sensor.terreno[2], sensor.superficie[2]) and esAccesible(sensor.terreno[6], sensor.superficie[6])));
}

// Función para decidir la acción a realizar en función de hace cuanto se visitó las 3 casillas de en frente.
Action ComportamientoJugador::comprobarTiempo(Sensores sensores)
{
	if (last_action == actTURN_BL or last_action == actTURN_BR or last_action == actTURN_SL or last_action == actTURN_SR)
	{
		return actFORWARD;
	}
	else if ((last_action != actTURN_BL or last_action != actTURN_SL) and esAccesible(sensores.terreno[1], sensores.superficie[1]) and mapaTiempo[calcFillIzqDer(current_state.brujula, current_state, true)][calcColIzqDer(current_state.brujula, current_state, true)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
	{
		// sensores.terreno[0] == 'A' ? accion = actTURN_BL :
		return actTURN_SL;
	}
	else if ((last_action != actTURN_BR or last_action != actTURN_SR) and esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaTiempo[calcFillIzqDer(current_state.brujula, current_state, false)][calcColIzqDer(current_state.brujula, current_state, false)] < mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)])
	{
		// sensores.terreno[0] == 'A' ? accion = actTURN_BR :
		return actTURN_SR;
	}
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		return actFORWARD;
	}
	return actTURN_SR;
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
		tieneBikini = false;
		tieneZapatilla = false;
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

	if(!bien_situado){
		switch (last_action)
		{
		case actFORWARD:
			// Actualización en caso de avanzar
			switch (current_state_imaginario.brujula)
			{
			case norte:
				current_state_imaginario.fil--;
				break;
			case noreste:
				current_state_imaginario.fil--;
				current_state_imaginario.col++;
				break;
			case este:
				current_state_imaginario.col++;
				break;
			case sureste: /*Actualizacion*/
				current_state_imaginario.fil++;
				current_state_imaginario.col++;
				break;
			case sur: /*Actualizacion*/
				current_state_imaginario.fil++;
				break;
			case suroeste: /*Actualizacion*/
				current_state_imaginario.fil++;
				current_state_imaginario.col--;
				break;
			case oeste: /*Actualizacion*/
				current_state_imaginario.col--;
				break;
			case noroeste: /*Actualizacion*/
				current_state_imaginario.fil--;
				current_state_imaginario.col--;
				break;
			}
			break;
		case actTURN_SL:
			a = current_state_imaginario.brujula;
			a = (a + 7) % 8;
			// girar_derecha = (rand() % 2 == 0);
			current_state_imaginario.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_SR:
			a = current_state_imaginario.brujula;
			a = (a + 1) % 8;
			// girar_derecha = (rand() % 2 == 0);
			current_state_imaginario.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BL:
			// Actualización de girar 135º a la izquierda
			a = current_state_imaginario.brujula;
			a = (a + 5) % 8;
			current_state_imaginario.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BR:
			// Actualización en caso de girar 135º a la derecha
			a = current_state_imaginario.brujula;
			a = (a + 3) % 8;
			current_state_imaginario.brujula = static_cast<Orientacion>(a);
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
		dibujarEnMatriz(sensores.terreno, current_state, mapaResultado, current_state.brujula);
		if (mapaResultado[calcFillIzqDer(current_state.brujula, current_state, true)][calcColIzqDer(current_state.brujula, current_state, true)] == '?')
			mapaResultado[calcFillIzqDer(current_state.brujula, current_state, true)][calcColIzqDer(current_state.brujula, current_state, true)] = sensores.terreno[1];
		if (mapaResultado[calcFillIzqDer(current_state.brujula, current_state, false)][calcColIzqDer(current_state.brujula, current_state, false)] == '?')
			mapaResultado[calcFillIzqDer(current_state.brujula, current_state, false)][calcColIzqDer(current_state.brujula, current_state, false)] = sensores.terreno[3];
		if (mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] == '?')
			mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] = sensores.terreno[2];
	}

	cout << "Fila: " << current_state.fil << " Columna:" << current_state.col << endl;
	cout << "Izquierda " << mapaTiempo[calcFillIzqDer(current_state.brujula, current_state, true)][calcColIzqDer(current_state.brujula, current_state, true)] << endl;
	cout << "Siguiente " << mapaTiempo[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] << endl;
	cout << "Derecha " << mapaTiempo[calcFillIzqDer(current_state.brujula, current_state, false)][calcColIzqDer(current_state.brujula, current_state, false)] << endl;

	// Guarda si tiene el bikini
	if (sensores.terreno[0] == 'K')
	{
		tieneBikini = true;
	}

	// Guarda si tiene zapatillas
	if (sensores.terreno[0] == 'D')
	{
		tieneZapatilla = true;
	}

	// Guarda en el array del mapa si ha pasado por G
	if (bien_situado)
	{
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
		// mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
	}

	// Decidir la proxima accion

	// Si hay una siguiente acción definida, se ejecuta
	if(siguienteAccion != actIDLE) {
		accion = siguienteAccion;
		siguienteAccion = actIDLE;
	}

	// Priorizamos recargar y esperar a estar recargado
	else if (giroIzq('X', sensores) and cargaNecesaria)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	}
	else if (giroDer('X', sensores) and cargaNecesaria)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}
	else if (sigoAlante('X', sensores) and cargaNecesaria)
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
	else if (sigoAlante('G', sensores) and !bien_situado)
	{
		accion = actFORWARD;
	}
	else if (giroDer('G', sensores) and !bien_situado and last_action != actTURN_BL)
	{
		sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	}
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]) and mapaResultado[calcFilSig(current_state.brujula, current_state)][calcColSig(current_state.brujula, current_state)] == '?')
	{
		accion = actFORWARD;
	}

	// Priorizamos coger el bikini o las zapatillas
	else if ((sigoAlante('K', sensores) && !tieneBikini) || (sigoAlante('D', sensores) && !tieneZapatilla))
	{
		accion = actFORWARD;
	}
	else if ((giroDer('K', sensores) && !tieneBikini) || (giroDer('D', sensores) && !tieneZapatilla))
	{
		accion = actTURN_SR;
	}
	else if ((giroIzq('K', sensores) && !tieneBikini) || (giroIzq('D', sensores) && !tieneZapatilla))
	{
		accion = actTURN_SL;
	}

	// // Comprobamos qué hacer si no tenemos las zapatillas o el bikini
	// else if (!tieneBikini or !tieneZapatilla)
	// {

	// }

	//Comprobamos si lo que tenemos al lado es un muro, si es así la siguiente acción será girar para entrar por la puerta.
	// A la izquierda
	else if (!esAccesible(sensores.terreno[1], sensores.superficie[1]) and esAccesible(sensores.terreno[5], sensores.superficie[5]) and esAccesible(sensores.terreno[2], sensores.superficie[2])){
		siguienteAccion = actTURN_SL;
		accion = actFORWARD;
	}
	// A la derecha
	else if (!esAccesible(sensores.terreno[3], sensores.superficie[3]) and esAccesible(sensores.terreno[7], sensores.superficie[7]) and esAccesible(sensores.terreno[2], sensores.superficie[2])){
		siguienteAccion = actTURN_SR;
		accion = actFORWARD;
	}

	// Priorizamos cambiar a una casilla que no sea agua, pues consume más energía si no tenemos el bikini
	else if (!tieneBikini)
	{
		if ((!sigoAlante('A', sensores) or sensores.terreno[2] != 'A') && esAccesible(sensores.terreno[2], sensores.superficie[2]))
		{
			accion = comprobarTiempo(sensores);
		}
		else if (!giroDer('A', sensores) && !tieneBikini && esAccesible(sensores.terreno[3], sensores.superficie[3]))
		{
			accion = actTURN_SR;
		}
		else if (!giroIzq('A', sensores) && !tieneBikini && esAccesible(sensores.terreno[1], sensores.superficie[1]))
		{
			accion = actTURN_SL;
		}
		else if (last_action == actTURN_SR and esAccesible(sensores.terreno[2], sensores.superficie[2]))
		{
			accion = actFORWARD;
		}
		else
		{
			accion = actTURN_SR;
		}
	}

	// Priorizamos cambiar a una casilla que no sea bosque si no tenemos las zapatillas, pues consume más energía
	else if (!tieneZapatilla)
	{
		if ((!sigoAlante('B', sensores) or sensores.terreno[2] != 'B') && esAccesible(sensores.terreno[2], sensores.superficie[2]))
		{
			accion = comprobarTiempo(sensores);
		}
		else if (!giroDer('B', sensores) && !tieneZapatilla && esAccesible(sensores.terreno[3], sensores.superficie[3]))
		{
			accion = actTURN_SR;
		}
		else if (!giroIzq('B', sensores) && !tieneZapatilla && esAccesible(sensores.terreno[1], sensores.superficie[1]))
		{
			accion = actTURN_SL;
		}
		else if (last_action == actTURN_SR and esAccesible(sensores.terreno[2], sensores.superficie[2]))
		{
			accion = actFORWARD;
		}
		else
		{
			accion = actTURN_SR;
		}
	}

	// // Priorizamos ahora las casillas que no han sido visitadas y son accesibles
	// else if (last_action != actTURN_BR and esAccesible(sensores.terreno[1], sensores.superficie[1]) and mapaResultado[calcFillIzqDer(current_state.brujula, current_state, true)][calcColIzqDer(current_state.brujula, current_state, true)] == '?')
	// {
	// 	sensores.terreno[0] == 'A' ? accion = actTURN_BL : accion = actTURN_SL;
	// }
	// else if (last_action != actTURN_BL and esAccesible(sensores.terreno[3], sensores.superficie[3]) and mapaResultado[calcFillIzqDer(current_state.brujula, current_state, false)][calcColIzqDer(current_state.brujula, current_state, false)] == '?')
	// {
	// 	sensores.terreno[0] == 'A' ? accion = actTURN_BR : accion = actTURN_SR;
	// }

	// Comprobamos de las 3 casillas que tenemos en frente cual es la que hace más tiempo que recorrimos y giramos hacia ella

	else if ((esAccesible(sensores.terreno[1], sensores.superficie[1]) or esAccesible(sensores.terreno[3], sensores.superficie[3])) and esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		accion = comprobarTiempo(sensores);
	}
	// Si es una casilla accesible, da un paso alante
	else if (esAccesible(sensores.terreno[2], sensores.superficie[2]))
	{
		accion = actFORWARD;
	}
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
	if(bien_situado)
		mapaTiempo[current_state.fil][current_state.col] = sensores.tiempo;
	// Si no está bien situado se guardará en el imaginario
	if(!bien_situado)
		mapaTiempoImaginario[current_state_imaginario.fil][current_state_imaginario.col] = sensores.tiempo;

	// Determinar el efecto de la ultima accion enviada
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
