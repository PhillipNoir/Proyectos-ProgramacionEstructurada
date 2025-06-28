/*Programa que captura 5 productos y permite al usuario buscar un producto por su nombre y mostrar sus detalles*/
#include<iostream>
#include<string>
struct productos
{
    std::string producto;
    float precio;
    int cantidad;
};
int main (){
    productos p[5];
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"Ingrese los datos del producto "<<i+1<<": \n",
        std::cout<<"Producto: ";
        std::cin.ignore();
        std::getline(std::cin, p[i].producto);
        std::cout<<"Precio: ";
        std::cin>>p[i].precio;
        std::cout<<"Cantidad: ";
        std::cin>>p[i].cantidad;
    }
    std::string prod;
    std::cout<<"Ingresa el producto que deseas buscar: ";
    std::cin.ignore();
    std::getline(std::cin, prod);
    bool encontrado=false;
    for (int i = 0; i < 5; i++)
    {
        if (p[i].producto==prod)
        {
            std::cout<<"Producto encontrado: \n";
            std::cout<<"Producto: "<<p[i].producto<<"\n";
            std::cout<<"Precio: "<<p[i].precio<<"\n";
            std::cout<<"Cantidad: "<<p[i].cantidad<<"\n";
            encontrado=true;
            break;
        }
    }
    if (!encontrado)
    {
        std::cout<<"No se encontró ningún producto con ese nombre.";
    }
    return 0;
}