#include<iostream>
#include<string>
#include<vector>
struct producto //Se declara una estructura de tipo "Producto" que contendará nombre, precio y cantidad
{
    std::string nombreDelProducto;
    float precio{0.00};
    int cantidad{0};
};
//Fucnión utilizada para llenar el vector a trabajar con distintos productos
void llenarVector(std::vector<producto>&productos){ 
    producto p; //Estructura temporal que almacenará los datos que contendrá la posición del vector que se está trabajando.
    std::cout<<"Ingrese los datos del producto\n";
    std::cout<<"Nombre: ";
    std::cin.ignore();
    std::getline(std::cin, p.nombreDelProducto);
    std::cout<<"Precio: ";
    std::cin>>p.precio;
    std::cout<<"Cantidad: ";
    std::cin>>p.cantidad;
    productos.push_back(p); //Comando que agrega la estructura a la posición final del vector
};
//Función para mostrar el inventario que mostrará el contenido del vector con el que se trabaja.
void mostrarInventario(const std::vector<producto>&productos){
    std::cout<<"Inventario: ";
    for (size_t i = 0; i < productos.size(); i++)
    {
        std::cout<<"Producto #"<<i + 1<<"\n";
        std::cout<<"Nombre: "<<productos[i].nombreDelProducto<<"\n";
        std::cout<<"Precio: "<<productos[i].precio<<"\n";
        std::cout<<"Cantidad: "<<productos[i].cantidad<<" unidades"<<"\n";
    };
};
//Función que calcula el valor total del inventario
float calcularValorInventario(const std::vector<producto>& productos){
    float total{0.00};
    for (const auto& p : productos) //Se utiliza una referencia para pasar por cada lugar del vector
    {
        total+= p.precio*p.cantidad;
    }
    return total;
};
int main(){
    int opcion{0};
    std::vector<producto> inventario;
    std::cout<<"¡Bienvenido!"<<"\n";
    do
    {   
        std::cout<<"1: Agregar producto"<<"\n";
        std::cout<<"2: Mostrar inventario actual"<<"\n";
        std::cout<<"3: Calcular valor total del inventario"<<"\n";
        std::cout<<"4: Salir"<<"\n";
        std::cout<<"Seleccione una opción: ";
        std::cin>>opcion;
        switch (opcion)
        {
        case 1:
            llenarVector(inventario);
            break;
        case 2:
            mostrarInventario(inventario);
            break;
        case 3:
            std::cout << "El valor total del inventario es: $" << calcularValorInventario(inventario) << "\n";
            break;
        case 4:
            std::cout<<"Saliendo..."<<"\n";
            break;
        default:
            std::cout<<"Error, introdúzca un valor válido";
            break;
        }
    } while (opcion!=4);
    std::cout<<"Gracias, vuelva pronto."<<"\n";
    return 0;
}