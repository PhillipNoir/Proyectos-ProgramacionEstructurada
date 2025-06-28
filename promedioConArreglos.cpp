/*Programa que solicite al usuario sus calificaciones, las almacene en un arreglo y calcule su promedio.*/
#include<iostream>
#include<vector>
#include<numeric> //Para usar std::accumulate
int main(){
    float n{0};
    std::cout<<"Bienvenido. ¿Cuántas calificaciones desea ingresar?\n";
    std::cin>>n;
    if (n>0)
    {
        float promedio{0};
        std::vector<int> calificaciones(n);
        for (int i = 0; i < n; i++)
        {
            std::cout<<"Ingrese una calificación: \n";
            std::cin>>calificaciones[i]; //Añade una calificación al vector
        }
        float suma=std::accumulate(calificaciones.begin(), calificaciones.end(), 0); //Accumulate suma el contenido del vector
        promedio=suma/n;
        std::cout<<"El promedio es: "<<promedio;
    }
    else
    {
        std::cout<<"Se ingresó un número inválido";
    }
    return 0;
}