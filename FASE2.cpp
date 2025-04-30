#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, pair<string, string> > diccionario;

// Cargar diccionario desde diccionario.dat
void cargarDiccionario(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo del diccionario." << endl;
        return;
    }

    string palabra, traduccion, funcionalidad;
    while (getline(archivo, palabra)) {
        getline(archivo, traduccion);
        getline(archivo, funcionalidad);
        diccionario[palabra] = make_pair(traduccion, funcionalidad);
    }

    archivo.close();
}

// Traducir palabra y devolver funcionalidad si existe
string traducirPalabra(const string& palabraOriginal, string& funcionalidadUsada) {
    string palabra = palabraOriginal;
    string simbolo = "";

    if (!palabra.empty() && ispunct(palabra[palabra.length() - 1]) && palabra[palabra.length() - 1] != '_') {
        simbolo = palabra[palabra.length() - 1];
        palabra = palabra.substr(0, palabra.length() - 1);
    }

    if (diccionario.find(palabra) != diccionario.end()) {
        funcionalidadUsada = diccionario[palabra].second;
        return diccionario[palabra].first + simbolo;
    } else {
        funcionalidadUsada = "";
        return palabra + simbolo;
    }
}
    if (!palabra.empty() && ispunct(palabra[palabra.length() - 1]) && palabra[palabra.length() - 1] != '_') {
        simbolo = palabra[palabra.length() - 1];
        palabra = palabra.substr(0, palabra.length() - 1);
    }

    if (diccionario.find(palabra) != diccionario.end()) {
        funcionalidadUsada = diccionario[palabra].second;
        return diccionario[palabra].first + simbolo;
    } else {
        funcionalidadUsada = "";
        return palabra + simbolo;
    }
}

// Traducir una linea de codigo
string traducirLinea(string linea) {
    stringstream ss(linea);
    string palabra, resultado = "", comentarios = "";
    vector<string> funcionalidades;

    while (ss >> palabra) {
        string funcionalidad = "";
        string palabraTraducida = traducirPalabra(palabra, funcionalidad);
        resultado += palabraTraducida + " ";

        if (!funcionalidad.empty()) {
            funcionalidades.push_back(funcionalidad);
        }
    }

    // Agregar funcionalidades como comentario al final
    if (!funcionalidades.empty()) {
        resultado += "// ";
        for (int i = 0; i < funcionalidades.size(); i++) {
            resultado += funcionalidades[i];
            if (i < funcionalidades.size() - 1) resultado += ", ";
        }
    }

    return resultado;
}

// Procesar todo el bloque de codigo
string procesarCodigo(string codigo) {
    stringstream entrada(codigo);
    string linea, salida = "";
    string estructura = "";

    while (getline(entrada, linea)) {
        string lineaRecortada = linea;
        while (!lineaRecortada.empty() && (lineaRecortada[0] == ' ' || lineaRecortada[0] == '\t')) {
            lineaRecortada = lineaRecortada.substr(1);
        }

        if (lineaRecortada.find("if") == 0 || lineaRecortada.find("else") == 0 ||
            lineaRecortada.find("while") == 0 || lineaRecortada.find("for") == 0 ||
            lineaRecortada.find("switch") == 0 || lineaRecortada.find("try") == 0 ||
            lineaRecortada.find("catch") == 0) {
            estructura = traducirLinea(lineaRecortada);
            salida += traducirLinea(linea) + "\n";
        }
        else if (lineaRecortada.find("{") != string::npos) {
            if (!estructura.empty()) {
                salida += "inicio " + estructura + "\n";
            } else {
                salida += "{\n";
            }
        }
        else if (lineaRecortada.find("}") != string::npos) {
            if (!estructura.empty()) {
                salida += "fin " + estructura + "\n";
                estructura = "";
            } else {
                salida += "}\n";
            }
        }
        else {
            salida += traducirLinea(linea) + "\n";
        }
    }

    return salida;
}
