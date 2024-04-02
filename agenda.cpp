#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Clase para representar un contacto
class Contacto {
public:
    string nombre;
    string telefono;
    string email;
    string nota;

    Contacto(string nombre, string telefono, string email, string nota = "") : nombre(nombre), telefono(telefono), email(email), nota(nota) {}
};

// Clase para representar un grupo de contactos
class Grupo {
public:
    string nombre;
    vector<Contacto> contactos;

    Grupo(string nombre) : nombre(nombre) {}
};

// Clase para gestionar la lista de contactos
class GestionContactos {
private:
    vector<Contacto> contactos;
    vector<Grupo> grupos;
    string archivoContactos = "contactos.txt";
    string archivoGrupos = "grupos.txt";

public:
    // Constructor
    GestionContactos() {
        cargarContactos();
        cargarGrupos();
    }

    // Destructor
    ~GestionContactos() {
        guardarContactos();
        guardarGrupos();
    }

    // Métodos CRUD
    void agregarContacto(Contacto contacto) {
        contactos.push_back(contacto);
    }

    void agregarGrupo(Grupo grupo) {
        grupos.push_back(grupo);
    }

    void mostrarContactos() {
        cout << "Lista de contactos:" << endl;
        for (const auto& contacto : contactos) {
            cout << "Nombre: " << contacto.nombre << ", Telefono: " << contacto.telefono << ", Email: " << contacto.email << ", Nota: " << contacto.nota << endl;
        }
    }

    void mostrarGrupos() {
        cout << "Lista de grupos:" << endl;
        for (const auto& grupo : grupos) {
            cout << grupo.nombre << endl;
            for (const auto& contacto : grupo.contactos) {
                cout << "- Nombre: " << contacto.nombre << ", Telefono: " << contacto.telefono << ", Email: " << contacto.email << ", Nota: " << contacto.nota << endl;
            }
        }
    }

    void exportarContactos(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contacto : contactos) {
                file << contacto.nombre << ',' << contacto.telefono << ',' << contacto.email << ',' << contacto.nota << endl;
            }
            file.close();
            cout << "Contactos exportados correctamente a " << filename << endl;
        } else {
            cout << "Error al exportar contactos." << endl;
        }
    }

    void buscarContacto(string nombre) {
        bool encontrado = false;
        for (const auto& contacto : contactos) {
            if (contacto.nombre == nombre) {
                encontrado = true;
                cout << "Contacto encontrado:" << endl;
                cout << "Nombre: " << contacto.nombre << ", Telefono: " << contacto.telefono << ", Email: " << contacto.email << ", Nota: " << contacto.nota << endl;
            }
        }
        if (!encontrado) {
            cout << "Contacto no encontrado." << endl;
        }
    }

    void registrarLlamada(string nombre) {
        cout << "Registrando llamada para el contacto " << nombre << "." << endl;
        // Aquí puedes implementar la lógica para registrar una llamada para el contacto dado
    }

    void agregarNota(string nombre, string nota) {
        for (auto& contacto : contactos) {
            if (contacto.nombre == nombre) {
                contacto.nota = nota;
                cout << "Nota agregada correctamente para el contacto " << nombre << "." << endl;
                return;
            }
        }
        cout << "Contacto no encontrado." << endl;
    }

    void agregarContactoAGrupo(string nombreContacto, string nombreGrupo) {
        for (auto& grupo : grupos) {
            if (grupo.nombre == nombreGrupo) {
                for (auto& contacto : contactos) {
                    if (contacto.nombre == nombreContacto) {
                        grupo.contactos.push_back(contacto);
                        cout << "Contacto agregado al grupo correctamente." << endl;
                        return;
                    }
                }
                cout << "Contacto no encontrado." << endl;
                return;
            }
        }
        cout << "Grupo no encontrado." << endl;
    }

    void menuPrincipal() {
        int opcion;
        do {
            cout << "\n----- Menú Principal -----" << endl;
            cout << "1. Agregar contacto" << endl;
            cout << "2. Mostrar contactos" << endl;
            cout << "3. Exportar contactos" << endl;
            cout << "4. Buscar contacto" << endl;
            cout << "5. Registrar llamada" << endl;
            cout << "6. Agregar nota" << endl;
            cout << "7. Mostrar grupos" << endl;
            cout << "8. Agregar contacto a grupo" << endl;
            cout << "9. Agregar grupo" << endl;
            cout << "10. Salir" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarContactoDesdeConsola();
                    break;
                case 2:
                    mostrarContactos();
                    break;
                case 3:
                    exportarContactosDesdeConsola();
                    break;
                case 4:
                    buscarContactoDesdeConsola();
                    break;
                case 5:
                    registrarLlamadaDesdeConsola();
                    break;
                case 6:
                    agregarNotaDesdeConsola();
                    break;
                case 7:
                    mostrarGrupos();
                    break;
                case 8:
                    agregarContactoAGrupoDesdeConsola();
                    break;
                case 9:
                    agregarGrupoDesdeConsola();
                    break;
                case 10:
                    cout << "Saliendo..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
            }
        } while (opcion != 10);
    }

private:
    void cargarContactos() {
        ifstream file(archivoContactos);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string nombre, telefono, email, nota;
                getline(ss, nombre, ',');
                getline(ss, telefono, ',');
                getline(ss, email, ',');
                getline(ss, nota, ',');
                Contacto nuevoContacto(nombre, telefono, email, nota);
                contactos.push_back(nuevoContacto);
            }
            file.close();
            cout << "Contactos cargados correctamente." << endl;
        } else {
            cout << "Error al cargar contactos. Se creará un archivo nuevo." << endl;
        }
    }

    void cargarGrupos() {
        ifstream file(archivoGrupos);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                Grupo nuevoGrupo(line);
                grupos.push_back(nuevoGrupo);
            }
            file.close();
            cout << "Grupos cargados correctamente." << endl;
        } else {
            cout << "Error al cargar grupos. Se creará un archivo nuevo." << endl;
        }
    }

    void guardarContactos() {
        ofstream file(archivoContactos);
        if (file.is_open()) {
            for (const auto& contacto : contactos) {
                file << contacto.nombre << ',' << contacto.telefono << ',' << contacto.email << ',' << contacto.nota << endl;
            }
            file.close();
            cout << "Contactos guardados correctamente." << endl;
        } else {
            cout << "Error al guardar contactos." << endl;
        }
    }

    void guardarGrupos() {
        ofstream file(archivoGrupos);
        if (file.is_open()) {
            for (const auto& grupo : grupos) {
                file << grupo.nombre << endl;
            }
            file.close();
            cout << "Grupos guardados correctamente." << endl;
        } else {
            cout << "Error al guardar grupos." << endl;
        }
    }

    void agregarContactoDesdeConsola() {
        string nombre, telefono, email;
        cout << "Ingrese el nombre del contacto: ";
        cin >> nombre;
        cout << "Ingrese el telefono del contacto: ";
        cin >> telefono;
        cout << "Ingrese el email del contacto: ";
        cin >> email;
        Contacto nuevoContacto(nombre, telefono, email);
        agregarContacto(nuevoContacto);
        cout << "Contacto agregado correctamente." << endl;
    }

    void exportarContactosDesdeConsola() {
        string filename;
        cout << "Ingrese el nombre del archivo para exportar los contactos: ";
        cin >> filename;
        exportarContactos(filename);
    }

    void buscarContactoDesdeConsola() {
        string nombre;
        cout << "Ingrese el nombre del contacto a buscar: ";
        cin >> nombre;
        bool encontrado = false;
        for (const auto& contacto : contactos) {
            if (contacto.nombre == nombre) {
                encontrado = true;
                cout << "Contacto encontrado:" << endl;
                cout << "Nombre: " << contacto.nombre << ", Telefono: " << contacto.telefono << ", Email: " << contacto.email << ", Nota: " << contacto.nota << endl;
            }
        }
        if (!encontrado) {
            cout << "Contacto no encontrado." << endl;
        }
    }

    void registrarLlamadaDesdeConsola() {
        string nombre;
        cout << "Ingrese el nombre del contacto para registrar la llamada: ";
        cin >> nombre;
        cout << "Registrando llamada para el contacto " << nombre << "." << endl;
        // Aquí puedes implementar la lógica para registrar una llamada para el contacto dado
    }

    void agregarNotaDesdeConsola() {
        string nombre, nota;
        cout << "Ingrese el nombre del contacto para agregar la nota: ";
        cin >> nombre;
        cout << "Ingrese la nota: ";
        cin.ignore();
        getline(cin, nota);
        agregarNota(nombre, nota);
    }

    void agregarGrupoDesdeConsola() {
        string nombreGrupo;
        cout << "Ingrese el nombre del nuevo grupo: ";
        cin >> nombreGrupo;
        Grupo nuevoGrupo(nombreGrupo);
        agregarGrupo(nuevoGrupo);
        cout << "Grupo agregado correctamente." << endl;
    }

    void agregarContactoAGrupoDesdeConsola() {
        if (grupos.empty()) {
            cout << "No hay grupos disponibles. Por favor, agregue un grupo primero." << endl;
            return;
        }

        string nombreContacto, nombreGrupo;
        cout << "Ingrese el nombre del contacto: ";
        cin >> nombreContacto;
        cout << "Ingrese el nombre del grupo: ";
        cin >> nombreGrupo;
        agregarContactoAGrupo(nombreContacto, nombreGrupo);
    }
};

int main() {
    GestionContactos gestion;
    gestion.menuPrincipal();

    return 0;
}
