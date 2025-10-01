#include <iostream>
#include <funciones.h>

using namespace std;

int main()
{
    int rSaldo, num = 0;
    string usuario, cedula, clave, saldo, nDatos, datos;
    bool admin = false;
    cout << "Ingrese su usuario: ";
    getline(cin, usuario);
    cout<<"Ingrese su clave: ";
    getline(cin, clave);
    // nDatos = usuario + clave;//cambiar el nombre y clave del admin
    //escribirArchivo("sudo.txt", encriptar(nDatos,4));
    try
    {
        nDatos = desencriptar(leerArchivo("sudo.txt"), 4);
    }
    catch (const runtime_error& e)
    {
        cerr << "ERROR " << e.what() << endl;
    }
    if (nDatos.find(usuario) != string::npos && nDatos.find(clave) != string::npos)
    {
        admin = true;
        cout << "BIENVENIDO ADMINISTRADOR\n";
    }
    else
    {
        nDatos = desencriptar(convertirABinario(leerArchivo("usuarios.txt")) ,4);
        if (nDatos.find(usuario) != string::npos && nDatos.find(clave) != string::npos)
        {
            cout<<"Bienvenido, dijite:\n"
                 <<"1. Retirar dinero.\n"
                 <<"2. Consultar saldo.\n"
                 <<"3. Salir.\n";
            try
            {
                if (!(cin >> num))
                {
                    throw invalid_argument("Entrada invalida, debe ingresar un numero entre 1 y 3.");
                }
            }
            catch (const exception& e)
            {
                cerr << "Error, " << e.what() << endl;
                cin.clear();             // limpiar estado de cin
                cin.ignore(10000, '\n'); // limpiar basura
            }
            while(num != 3)
            {
                nDatos = desencriptar(convertirABinario(leerArchivo(usuario+".txt")), 4);
                if(num == 1)
                {
                    string::npos;
                    size_t pos = nDatos.find("Saldo: ");
                    cout<<"Actualmente su ";
                    cout << nDatos.substr(pos) << endl;

                    try
                    {
                        cout<<"Ingrese el valor que desea retirar: ";
                        if (!(cin >> rSaldo))
                        {
                            throw invalid_argument("Debe ingresar un numero valido para el retiro.");
                        }
                        cin.ignore(10000, '\n');
                        if (actualizarSaldo(nDatos, rSaldo))
                        {
                            escribirArchivo(usuario + ".txt", encriptar(nDatos, 4));
                            cout << "Su dinero fue retirado.\n";
                        }
                    }
                catch (const invalid_argument& e)
                {
                    cerr << "Error: " << e.what() << endl;
                    cin.clear();                                   // limpiar estado de error
                    cin.ignore(10000, '\n'); // limpiar todo el buffer
                }
                }
                else if(num == 2)
                {

                    if (nDatos.find("Saldo: ") != string::npos)
                    {
                        size_t pos = nDatos.find("Saldo: ");
                        actualizarSaldo(nDatos,0);
                        escribirArchivo(usuario+ ".txt",encriptar(nDatos, 4));
                        cout << nDatos.substr(pos) << endl;
                    }

                }
                cout<<"1. Retirar dinero.\n";
                cout<<"2. Consultar saldo.\n";
                cout<<"3. Salir.\n";
                cin>>num;
            }
        }
        else
        {
            cout<<"Usuario o clave incorrectas.";
        }

    }
    while(admin)
    {
        cout << "1. Agregar usuario nuevo.\n";
        cout << "2. Eliminar usuario.\n";
        cout << "3. Salir.\n";
        cin>> num;
        cin.ignore();
        if(num==1)
        {
            cout << "Ingrese nombre de usuario: ";
            getline(cin, usuario);
            if(archivoExiste(usuario))
            {
                cout<<"el usuario ya existe";
            }
            else
            {
                cout<<"Ingrese la clave: ";
                getline(cin, clave);
                cout << "Ingrese la cedula: ";
                getline(cin, cedula);
                cout << "Ingrese el saldo: ";
                getline(cin, saldo);
                datos = "Usuario: " + usuario + " clave: " + clave + '\n';
                agregarArchivo("usuarios.txt", encriptar(datos, 4));
                datos = "Cedula: " + cedula + "\nSaldo: " + saldo;
                escribirArchivo(usuario+ ".txt",encriptar(datos, 4));
            }
        }
        if(num==2)
        {
            cout << "Ingrese nombre de usuario: ";
            getline(cin, usuario);
            string usuario1 =usuario + ".txt";
            if (remove(usuario1.c_str()) == 0)
            {
                borrar("usuarios.txt","Usuario: "+ usuario, 4);
                cout << "El usuario ha sido eliminado exitosamente." << endl;
            } else
            {
                perror("Error al intentar eliminar");
            }
        }
        if(num==3)
        {
            admin = false;
        }
    }
    return 0;
}
