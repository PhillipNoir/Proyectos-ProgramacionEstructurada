//Programa que almacena las entradas del ususario en un archivo
#include<iostream>
#include<fstream>
int main(){
    std::ofstream archivo("usuario.txt"); // Abrir el archivo para escritura
    if (archivo.is_open())
    {
        std::string entrada;
        std::cout<<"Ingresa tus datos (escribe ´Salir´ para terminar): \n";
        while (entrada != "salir")
        {
            std::getline(std::cin, entrada);
            if (entrada == "salir")
            {
                break; // Terminar si el usuario escribe "salir"
            }
            archivo << entrada << "\n"; // Escribir directamente en el archivo usando los datos almacenados en la variable entrada
            
        }
        
    }
    else{
        std::cout<<"Error al abrir el archivo";
    }
    archivo.close();
    std::cout<<"Datos guardados en ´usuario.txt´. \n";
    return 0;
}