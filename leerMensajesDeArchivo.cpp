#include<iostream>
#include<fstream>
int main(){
    std::ifstream archivo("mensaje.txt");
    if (archivo.is_open())
    {
        std::string linea;
        std::getline(archivo, linea);
        std::cout<<"El contenido del mensaje es: \n";
        std::cout<<linea<<"\n";
        archivo.close();
    }
    else
    {
        std::cout<<"Error al abrir el archivo \n";
    }
    return 0;
}