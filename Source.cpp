//Andrea Peña Calvin

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int MV = 5;
const std::string xxx = "XXX";

enum tElemento { piedra, papel, tijeras, lagarto, Spock };
enum tResultado { humano, computadora, empate };


				   // Escribir aqui la funcion leeOpcion.N1
int leeOpcion(std::string pregunta, std::string mensajeError, int valMin, int valMax) {

	int opt; //opcion elegida 
	std::cout << pregunta;
	std::cin >> opt;

	while (!((valMin <= opt) && (opt <= valMax))) {
		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> opt;
	}
	return opt;
}
//segunda.



tElemento leeJugada(std::string pregunta) {
	tElemento var;
	std::string jug; //elemento elegido por el jugador
	std::cout << pregunta;
	std::cin >> jug;

	while (!(jug == "piedra" || jug == "papel" || jug == "tijeras" || jug == "lagarto" || jug == "Spock")) //jug no correcto
	{
		std::cout << pregunta;
		std::cin >> jug;
	}

	if (jug == "piedra") var = piedra; //conversion de string a tElemento
	else if (jug == "papel") var = papel;
	else if (jug == "tijeras") var = tijeras;
	else if (jug == "lagarto") var = lagarto;
	else if (jug == "Spock") var = Spock;


	return var;
}

std::string toString(tElemento elem) {

	//if (elem == piedra) return "piedra";
	//else if (elem == papel) return "papel";
	//else if (elem == tijeras) return "tijeras";
	//else if (elem == lagarto) return "lagarto";
	//else return "Spock";
	switch (elem) {
	case piedra: return "piedra";
	case papel: return"papel";
	case tijeras: return "tijeras";
	case lagarto: return "lagarto";
	case Spock: return "SPOCK";
	}
}

//parte 3


bool gana(tElemento j1, tElemento j2) {

	if (j1 == piedra && (j2 == lagarto || j2 == tijeras)) return true;

	else if (j1 == papel && (j2 == Spock || j2 == piedra)) return true;

	else if (j1 == tijeras && (j2 == lagarto || j2 == papel)) return true;

	else if (j1 == lagarto && (j2 == Spock || j2 == papel)) return true;

	else if (j1 == Spock && (j2 == piedra || j2 == tijeras)) return true;

	else return false; //los empates y perder

}

// hasta aqui las funciones de la version 1

bool localizacionJugador(std::string apodo) {
	std::ifstream registro;
	std::string guardar;

	registro.open("registro.txt");

	if (registro.is_open()) {

		getline(registro, guardar);
		//leer el primero y comprobar que no es xxx o que lo has encontrado
		while (guardar != xxx && guardar != apodo) {
			getline(registro, guardar);
		}

		registro.close();
		return guardar == apodo;
	}
	else {
		std::cout << "Archivo de registro inexistente. Imposible jugar";
		return false;
	}
}

//

bool escribeFichero(std::string nombreFichero, std::string marcaFin) {

	std::ifstream nFichero;
	std::string mensaje;

	nFichero.open(nombreFichero); //reglas del juego

	if (nFichero.is_open()) {
		getline(nFichero, mensaje);

		while (mensaje != marcaFin) { //leer las lineas y escribirlas

			std::cout << mensaje << '\n';
			getline(nFichero, mensaje);

		}
		nFichero.close();
		return true;
	}
	else return false;
}


tResultado juegaPartida() {

	//srand(time(NULL));
	tElemento ordenador = tElemento(rand() % MV); //elemento elegido por el ordenador

	std::string preg = "Elige un elemento: piedra, papel, tijeras, lagarto o Spock: ";
	tElemento jugador = leeJugada(preg); //elemento elegido por el jugador


	std::cout << "Eleccion computadora: " << toString(ordenador) << '\n';
	std::cout << "Tu eleccion: " << toString(jugador) << '\n';

	bool res = gana(jugador, ordenador); //decide el ganador

	if (jugador == ordenador) return empate;
	else {
		if (res) return humano; //bool true

		else return computadora; //bool false
	}
}


void sesionDeJuego() {
	int ganarsDJ = 0, perdersDJ = 0, empatarsDJ = 0; //nº de partidas ganadas/perdidas/empatadas
	int npartidas = 0; //numero de partidas jugadas

	std::cout << "1- Jugar una partida" << '\n';
	std::cout << "2- Ver instrucciones" << '\n';
	std::cout << "0- Salir" << '\n';
	std::string pregunta = "Opcion: ";
	std::string mError = "Ingrese una opcion valida: ";
	int min = 0;
	int max = 2;
	int opcion = leeOpcion(pregunta, mError, min, max);

	while (opcion != 0) {

		if (opcion == 1) {
			tResultado opc = juegaPartida();

			npartidas++;

			if (opc == humano) {
				++ganarsDJ;
				std::cout << "Has ganado." << '\n';
			}
			else if (opc == computadora) {
				++perdersDJ;
				std::cout << "Has perdido." << '\n';
			}
			else if (opc == empate) {
				++empatarsDJ;
				std::cout << "Se ha producido un empate." << '\n';
			}

		}

		else if (opcion == 2) {

			std::string nFich = "reglas.txt"; //nombre del fichero
			
			bool normas = escribeFichero(nFich, xxx);

		}
		std::cout << "1- Jugar una partida" << '\n';
		std::cout << "2- Ver instrucciones" << '\n';
		std::cout << "0- Salir" << '\n';
		opcion = leeOpcion(pregunta, mError, min, max);
	}

	//if (opcion == 0) 

		std::cout << "Has jugado " << npartidas << " partida(s)" << '\n';
		std::cout << "Partidas ganadas: " << ganarsDJ << '\n';
		std::cout << "Partidas empatadas: " << empatarsDJ << '\n';
		std::cout << "Partidas perdidas: " << perdersDJ << '\n';
	
	
}



int main() {
	srand(time(NULL));
	std::string apodo;
	std::cout << "Introduce tu apodo: ";
	std::cin >> apodo;
	bool nombre = localizacionJugador(apodo);

	if (nombre) sesionDeJuego();

	else std::cout << "Jugador no registrado" << '\n';
		

	system("PAUSE");
	return 0;
}