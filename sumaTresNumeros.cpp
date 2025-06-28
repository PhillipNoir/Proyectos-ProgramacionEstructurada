/*Programa que solicita 3 numeros y muestre la suma de ellos solo si el primero es mayor que el segundo*/
#include<iostream>
int main(){
    int num1{0};
    int num2{0};
    int num3{0};
    std::cout<<"¡Bienvenido! Ingrese el primer número: \n";
    std::cin>>num1;
    std::cout<<"Ingrese el segundo número: \n";
    std::cin>>num2;
    std::cout<<"Ingrese el tercer número: \n";
    std::cin>>num3;
    if (num1>num2)
    {
        int sum{0};
        sum=num1+num2+num3;
        std::cout<<"La suma de los tres números es: "<<sum<<"\n";
    }
    else
    {
        std::cout<<"Error: "<<num1<<" es menor que "<<num2<<"\n";
    }
    return 0;
}