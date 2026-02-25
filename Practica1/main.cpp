#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> separar(string linea, char delimitador) {
    vector<string> piezas;
    string pieza;
    stringstream ss(linea);
    while (getline(ss, pieza, delimitador)) {
        piezas.push_back(pieza);
    }
    return piezas;
}

int main() {
    vector<Estudiante> listaEstudiantes;
    int opcion;

    do {
        cout << "\n--- ANALISIS ACADEMICO (MODULO ESTUDIANTES) ---" << endl;
        cout << "1. Cargar archivo de Estudiantes (.lfp)" << endl;
        cout << "2. Mostrar Estudiantes cargados" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombreArchivo;

            ifstream archivo(nombreArchivo);
            string linea;

            if (archivo.is_open()) {
                while (getline(archivo, linea)) {
                    vector<string> datos = separar(linea, ',');
                    if (datos.size() == 5) {
                        Estudiante nuevo(datos[0], datos[1], datos[2], datos[3], stoi(datos[4]));
                        listaEstudiantes.push_back(nuevo);
                    }
                }
                archivo.close();
                cout << ">> Archivo cargado correctamente." << endl;
            } else {
                cout << ">> Error: No se pudo abrir el archivo." << endl;
            }
        }
        else if (opcion == 2) {
            cout << "\n--- LISTA DE ESTUDIANTES ---" << endl;
            for (int i = 0; i < listaEstudiantes.size(); i++) {
                cout << "Carnet: " << listaEstudiantes[i].carnet
                     << " | Nombre: " << listaEstudiantes[i].nombre << " " << listaEstudiantes[i].apellido << endl;
            }
        }

    } while (opcion != 3);

    return 0;
}
