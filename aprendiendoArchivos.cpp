#include <iostream>
#include <fstream>

int main() {
std::ofstream archivo("datos.txt"); // Crear o sobrescribir el archivo
if (archivo.is_open()) // Verifica que el archivo se abrió bien
{ 
archivo << "Hola, mundo\n";
archivo << "Aprendiendo archivos en C++\n";
archivo.close(); // ¡No olvides cerrar el archivo!
std::cout << "Datos guardados en el archivo.\n";
} 
else {
std::cout << "Error al abrir el archivo.\n";
}
return 0;
}