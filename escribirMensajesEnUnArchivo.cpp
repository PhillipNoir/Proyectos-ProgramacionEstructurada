//Pide al usuario un mensaje y guárdalo en mensaje.txt.
#include<iostream>
#include<fstream> //Biblioteca para el uso de archivos
int main(){
    std::ofstream archivo("mensaje.txt"); //Crea un archivo llamado "archivo" en formato .txt
    if (archivo.is_open()) //Condición que evalúa si el archivo se ha abrierto correctamente
    {
        std::string entrada;
        std::cout<<"Ingrese un mensaje: \n";
        std::getline(std::cin, entrada);
        archivo<<entrada; //Escribe en el archivo el valor de "entrada"
        archivo.close(); //Cierra el archivo
    }
    else{
        std::cout<<"Error al abrir el archivo \n"; //Muestra un mensaje de error si el archivo no se abrió correctamente.
    }
    std::cout<<"Datos guardados en ´mensaje.txt´. \n";
    return 0;
}