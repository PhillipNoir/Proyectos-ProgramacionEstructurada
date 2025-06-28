/*Programa que evalúa si una calificación es aprobatoria o reprobatoria*/
#include<iostream>
int main(){
    int calificacion{0};
    constexpr int CALIFICACION_MINIMA=60;
    std::cout<<"¡Bienvenido! Ingrese la calificación del alumno (60-100): \n";
    std::cin>>calificacion;
    if (calificacion>=CALIFICACION_MINIMA)
    {
        std::cout<<"El alumno ha aprobado";
    }
    else
    {
        std::cout<<"El alumno ha reprobado";
    }
    return 0;
}