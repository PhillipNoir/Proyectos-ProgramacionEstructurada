#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ofstream archivo("datos.txt", std::ios::app); // Modo "append"
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::string entrada;
    std::cout << "Escribe líneas de texto (escribe 'salir' para terminar):\n";

    while (true) {
        std::getline(std::cin, entrada);
        if (entrada == "salir") break;
        archivo << entrada << "\n";
    }

    archivo.close();
    std::cout << "Datos añadidos a 'datos.txt'." << std::endl;
    return 0;
}