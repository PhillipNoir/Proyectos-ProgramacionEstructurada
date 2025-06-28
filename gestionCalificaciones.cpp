#include <iostream>
#include <vector>
void llenarArreglo(std::vector<int>&vec, int cantidad){
    int calificacion;
    for (int i = 0; i < cantidad; i++)
    {
        std::cout<<"Ingrese la calificación "<<i+1<<": ";
        std::cin>>calificacion;
        vec.push_back(calificacion);
    }
    
}
void imprimirArreglo(const std::vector<int>&vec){
    std::cout<<"Las calificaciones del grupo son: ";
    for (int num:vec)
    {
        std::cout<<num<<" ";
    }
    std::cout<<"\n";
}
int main(){
    std::vector<int> calificaciones;
    int cantidad;
    std::cout<<"¿Cuantas calificaciones desea ingresar?\n";
    std::cin>>cantidad;
    llenarArreglo(calificaciones, cantidad);
    imprimirArreglo(calificaciones);
    return 0;
}