//Programa que vacía un archivo
#include <iostream>
#include <fstream>
// Función que vacía un archivo
void vaciarArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::trunc); // Trunc = borrar contenido
    if (archivo.is_open()) {
        std::cout << "El archivo '" << nombreArchivo << "' fue vaciado con éxito.\n";
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo.\n";
    }
}
int main() {
    std::string nombre;
    std::cout << "Ingrese el nombre del archivo que desea vaciar: ";
    std::getline(std::cin, nombre);

    vaciarArchivo(nombre);

    return 0;
}