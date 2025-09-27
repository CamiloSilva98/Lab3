#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

bool actualizarSaldo(std::string& archivoDesencriptado, unsigned int montoRetirar);
bool archivoExiste(const string& nombreArchivo);
void agregarArchivo(const string& nombreArchivo, const string& datos);
void escribirArchivo(const string& nombreArchivo, const string& datos);
string leerArchivo(const string& nombreArchivo);
string convertirCharABinario(char c);
string convertirABinario(const string& texto);
char convertirBinarioAChar(const string& binario);
string convertirBinarioATexto(const string& binario);
string encriptar(const string& texto, int n);
string desencriptar(const string& binario, int n);
void borrar(const string& nombreArchivo, const string& fraseInicial, int claveEncriptacion);


#endif // FUNCIONES_H
