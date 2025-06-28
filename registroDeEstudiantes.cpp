/*Programa que solicita la información de 5 estudiantes e imprime los nombres de aquellos que tienen una calificación mayor a 70.*/
#include<iostream>
#include<string>
struct estudiante //Estructura de datos para estudiantes
{
    std::string nombre;
    int edad;
    int calificacion;
};
int main(){
    estudiante e[5]; //Arreglo de estructuras
    for (int i = 0; i < 5; i++) //Captura de datos
    {
        std::cout<<"Ingrese los datos del alumno "<<i+1<<": \n",
        std::cout<<"Nombre: ";
        std::cin.ignore();
        std::getline(std::cin, e[i].nombre);
        std::cout<<"Edad: ";
        std::cin>>e[i].edad;
        std::cout<<"Calificación: ";
        std::cin>>e[i].calificacion;
    }
    std::cout<<"Los alumnos con calificación mayor a 70 son: \n";
    for (int i = 0; i < 5; i++) //Mostrar alumnos con calificación mayor a 70
    {
        if (e[i].calificacion>70)
        {
            std::cout<<e[i].nombre<<"\n";
            std::cout<<e[i].edad<<"\n";
            std::cout<<e[i].calificacion<<"\n";
            std::cout<<"\n";
        }
        
    }
    return 0;
}