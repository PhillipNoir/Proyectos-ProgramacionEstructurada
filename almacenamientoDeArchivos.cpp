#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream archivo("datos.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::vector<std::string> lineas;
    std::string linea;
    
    while (std::getline(archivo, linea)) { 
        lineas.push_back(linea); 
    }

    archivo.close();

    std::cout << "Contenido del archivo línea por línea:\n";
    for (const auto& l : lineas) {
        std::cout << l << std::endl;
    }

    return 0;
}