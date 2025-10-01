#include "funciones.h"
using namespace std;
bool actualizarSaldo(std::string& archivoDesencriptado, unsigned int montoRetirar)
{
    montoRetirar = montoRetirar + 1000;
    size_t pos = archivoDesencriptado.find("Saldo: ");

    if (pos != string::npos)
    {
        pos += 7;
        unsigned int saldoActual = stoi(archivoDesencriptado.substr(pos));

        if (saldoActual < montoRetirar)
        {
            throw invalid_argument("Saldo insuficiente.");
        }
        unsigned int nuevoSaldo = saldoActual - montoRetirar;
        archivoDesencriptado.replace(pos, string::npos, to_string(nuevoSaldo));
        return true;
    }
    else
    {
        cerr << "No se encontró la línea de saldo." << endl;
        return false;
    }
}
bool archivoExiste(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    bool existe = archivo.is_open();

    if (existe)
    {
        archivo.close();
    }

    return existe;
}
void agregarArchivo(const string& nombreArchivo, const string& datos)
{
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open())
    {
        archivo << datos << endl;
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}
// Función para escribir datos en un archivo
void escribirArchivo(const string& nombreArchivo, const string& datos)
{
    ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        archivo << datos;
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

// Función para leer datos de un archivo
string leerArchivo(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string datos, linea;
    if (!archivo.is_open())
    {
         throw runtime_error("No se pudo abrir el archivo");
    }
    while (getline(archivo, linea))
    {
        datos += linea;
    }
    archivo.close();
    return datos;
}

// Convierte un carácter a su representación binaria de 8 bits en forma de string
string convertirCharABinario(char c)
{
    string binario;
    for (int i = 7; i >= 0; --i)
    {
        binario += ((c >> i) & 1) ? '1' : '0';
    }
    return binario;
}

// Convierte un texto completo a su representación binaria
string convertirABinario(const string& texto)
{
    string binario;
    for (char c : texto)
    {
        binario += convertirCharABinario(c);
    }
    return binario;
}

// Convierte una cadena de binario de 8 bits a un carácter
char convertirBinarioAChar(const string& binario)
{
    char c = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (binario[i] == '1')
        {
            c |= (1 << (7 - i));
        }
    }
    return c;
}

// Convierte una cadena binaria completa a texto
string convertirBinarioATexto(const string& binario)
{
    string texto;
    for (size_t i = 0; i < binario.size(); i += 8)
    {
        string bloque = binario.substr(i, 8);
        texto += convertirBinarioAChar(bloque);
    }
    return texto;
}

// Encriptación mediante desplazamiento de bits dentro de bloques de tamaño n
string encriptar(const string& texto, int n)
{
    string binario = convertirABinario(texto);
    string resultado;

    // Recorremos los bloques de n bits
    for (size_t i = 0; i < binario.size(); i += n)
    {
        string bloque = binario.substr(i, n);
        string bloqueEncriptado = bloque;
        // Desplazamos los bits una posición dentro del bloque (hacia la derecha)
        for (int j = 0; j < n; ++j)
        {
            bloqueEncriptado[(j + 1) % n] = bloque[j];  // Desplazamos los bits
        }

        resultado += bloqueEncriptado;
    }

    return convertirBinarioATexto(resultado);
}

// Desencriptación mediante desplazamiento de bits inverso dentro de bloques de tamaño n
string desencriptar(const string& binario, int n)
{
    string resultado;
    // Recorremos los bloques de n bits
    for (size_t i = 0; i < binario.size(); i += n)
    {
        string bloque = binario.substr(i, n);  // Obtenemos un bloque de tamaño n
        string bloqueDesencriptado = bloque;   // Hacemos una copia del bloque

        // Desplazamos los bits una posición hacia la izquierda
        for (int j = 0; j < n; ++j)
        {
            bloqueDesencriptado[j] = bloque[(j + 1) % n];  // Desplazamos los bits a la izquierda
        }

        resultado += bloqueDesencriptado;
    }

    return convertirBinarioATexto(resultado);  // Convertimos el binario desencriptado a texto
}
void borrar(const string& nombreArchivo, const string& fraseInicial, int claveEncriptacion)
{
    ifstream archivoEntrada(nombreArchivo);  // Abrir archivo para lectura
    ofstream archivoTemporal("temp.txt");    // Crear archivo temporal para escribir los datos modificados

    string linea;
    if (archivoEntrada.is_open() && archivoTemporal.is_open()) {
        while (getline(archivoEntrada, linea)) {
            // Desencriptamos la línea para compararla
            string lineaDesencriptada = desencriptar(convertirABinario(linea), claveEncriptacion);

            // Buscar la frase inicial en la línea desencriptada
            size_t pos = lineaDesencriptada.find(fraseInicial);

            // Si la frase inicial se encuentra al comienzo de la línea desencriptada
            if (pos == 0) {
                // No agregar la línea al archivo temporal (es decir, eliminarla)
                continue;
            }

            // Encriptamos nuevamente la línea antes de escribirla en el archivo temporal
            archivoTemporal << linea << endl;  // Escribir las líneas que no coinciden
        }

        archivoEntrada.close();
        archivoTemporal.close();

        // Reemplazar el archivo original por el archivo temporal
        remove(nombreArchivo.c_str());            // Eliminar el archivo original
        rename("temp.txt", nombreArchivo.c_str());  // Renombrar el archivo temporal con el nombre original

        cout << "El usuario ha sido eliminado correctamente." << endl;

    } else {
        cerr << "Error al abrir los archivos." << endl;
    }
}
