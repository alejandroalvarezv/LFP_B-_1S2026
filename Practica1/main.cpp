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
    vector<Curso> listaCursos;
    int opcion;

    do {
        cout << "\n--- ANALISIS ACADEMICO (MODULO COMPLETO) ---" << endl;
        cout << "1. Cargar archivo de Estudiantes (.lfp)" << endl;
        cout << "2. Cargar archivo de Cursos (.lfp)" << endl;
        cout << "3. Mostrar Estudiantes y Cursos cargados" << endl;
        cout << "4. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo de estudiantes: ";
            cin >> nombreArchivo;
            ifstream archivo(nombreArchivo);
            string linea;
            if (archivo.is_open()) {
                while (getline(archivo, linea)) {
                    if (linea.empty()) continue;
                    vector<string> datos = separar(linea, ',');
                    if (datos.size() == 5) {
                        Estudiante nuevo(datos[0], datos[1], datos[2], datos[3], stoi(datos[4]));
                        listaEstudiantes.push_back(nuevo);
                    }
                }
                archivo.close();
                cout << ">> Estudiantes cargados con exito." << endl;
            } else {
                cout << ">> Error: No se pudo abrir el archivo de estudiantes." << endl;
            }
        }
        else if (opcion == 2) {
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo de cursos: ";
            cin >> nombreArchivo;
            ifstream archivo(nombreArchivo);
            string linea;
            if (archivo.is_open()) {
                while (getline(archivo, linea)) {
                    if (linea.empty()) continue;
                    vector<string> datos = separar(linea, ',');
                    if (datos.size() == 5) {
                        Curso nuevo(datos[0], datos[1], stoi(datos[2]), stoi(datos[3]), datos[4]);
                        listaCursos.push_back(nuevo);
                    }
                }
                archivo.close();
                cout << ">> Cursos cargados con exito." << endl;
            } else {
                cout << ">> Error: No se pudo abrir el archivo de cursos." << endl;
            }
        }
        else if (opcion == 3) {
            cout << "\n--- LISTA DE ESTUDIANTES (" << listaEstudiantes.size() << ") ---" << endl;
            for (int i = 0; i < listaEstudiantes.size(); i++) {
                cout << "Carnet: " << listaEstudiantes[i].carnet
                     << " | Nombre: " << listaEstudiantes[i].nombre
                     << " " << listaEstudiantes[i].apellido << endl;
            }

            cout << "\n--- LISTA DE CURSOS (" << listaCursos.size() << ") ---" << endl;
            for (int i = 0; i < listaCursos.size(); i++) {
                cout << "Codigo: " << listaCursos[i].codigo
                     << " | Nombre: " << listaCursos[i].nombre
                     << " (" << listaCursos[i].carrera << ")" << endl;
            }
        }

    } while (opcion != 4);

    return 0;
}
