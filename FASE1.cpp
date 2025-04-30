#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct Palabra {
    string traduccion;
    string funcionalidad;
};

map<string, Palabra> diccionario;
const string archivoNombre = "diccionario.dat";

// Lista inicial de palabras
string palabrasBase[] = {
    "asm", "auto", "bool", "break", "case", "catch", "char", "class", "const", "const_cast", "continue",
    "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "extern", "false",
    "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "operator",
    "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof",
    "static", "static_cast", "struct", "switch", "template", "this", "throw", "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "while"
};


// Funcion para cargar el archivo en memoria
void cargarDiccionario() {
    ifstream archivo(archivoNombre.c_str());
    if (!archivo.is_open()) {
        // Si no existe, lo creamos
        ofstream nuevoArchivo(archivoNombre.c_str());
        for (int i = 0; i < sizeof(palabrasBase)/sizeof(palabrasBase[0]); i++) {
            nuevoArchivo << palabrasBase[i] << endl;
            nuevoArchivo << palabrasBase[i] << " (traduccion)" << endl;
            nuevoArchivo << "Funcionalidad de " << palabrasBase[i] << endl;
            Palabra p;
            p.traduccion = palabrasBase[i] + " (traduccion)";
            p.funcionalidad = "Funcionalidad de " + palabrasBase[i];
            diccionario[palabrasBase[i]] = p;
        }
        nuevoArchivo.close();
        cout << "Archivo creado y palabras iniciales agregadas.\n";
        return;
    }

    // Si existe, lo cargamos
    string palabra, traduccion, funcionalidad;
    while (getline(archivo, palabra)) {
        getline(archivo, traduccion);
        getline(archivo, funcionalidad);
        Palabra p;
        p.traduccion = traduccion;
        p.funcionalidad = funcionalidad;
        diccionario[palabra] = p;
    }
    archivo.close();
}
