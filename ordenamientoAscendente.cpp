/*Programa que solicita al usuario 5 números y los ordena de forma ascendente en un vector*/
#include<iostream>
#include<vector>
#include<algorithm> //Para std::sort
int main(){
    std::vector<int> vec(5);
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"Ingrese un número: \n";
        std::cin>>vec[i];
    }
    std::sort(vec.begin(), vec.end()); //Ordenamiento ascendente
    std::cout<<"Los números ingresados en orden ascendente son: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout<<vec[i]<<" ";
    }
    return 0;
}