#include <iostream>
#include <cstdlib>
using namespace std;

void menuFase1();
void menuFase2();

int main() {
    int opcion;

    do {
        system("cls");
  cout << "===== MENU PRINCIPAL =====\n";
        cout << "1. Fase 1\n";

cout << "2. Fase 2\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
switch(opcion) {
case 1: menuFase1(); break;
case 2: menuFase2(); break;
 case 0: cout << "Saliendo...\n"; break;
default: cout << "Opcion invalida.\n"; system("pause"); break;
}

void menuFase1() {
    int op;
    do {
 switch(op) {
            case 1: system("start FASE1.exe"); break;
 }

    } while(op != 0);
}
}

void menuFase2() {
    int op;
    do {
    	system("cls");
    	cout << "1. Iniciar Programa\n";
    	cout << "0. Regresar\n";
        cout << "Seleccione una opcion: ";
    	  cin >> op;
