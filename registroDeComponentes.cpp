/**
 * @mainpage Sistema de Gestión de Componentes Electrónicos
 * @brief Sistema para registro y búsqueda de componentes electrónicos en archivos
 * 
 * @section features_sec Características Principales
 * - Registro de componentes con validación de entrada
 * - Almacenamiento persistente en archivos de texto
 * - Búsqueda multicriterio
 * - Interfaz de menú intuitiva
 * 
 * @section usage_sec Modo de Uso
 * 1. Ejecutar el programa
 * 2. Seleccionar opciones del menú
 * 3. Los datos se guardan en archivos .txt
 * 
 * @author Sergio Felipe Gonzalez Cruz
 * @date Febrero 2025
 * @version 1.1
 */

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<limits>
#include<cctype>
#include<algorithm>

/**
 * @struct componente
 * @brief Estructura que almacena los datos de un componente electrónico
 * 
 * @var nombreDelComponente   Nombre descriptivo (ej: "Resistor 1kΩ")
 * @var tipoDeComponente      Categoría (ej: "Resistor", "Capacitor")
 * @var valorNominal          Valor principal (ej: 1000.00)
 * @var tolerancia            Tolerancia en porcentaje (ej: 5.0)
 * @var voltajeDeTrabajo      Voltaje máximo (ej: 12.5)
 * @var estado                Condición (ej: "Nuevo", "Usado")
 */
struct componente
{
    std::string nombreDelComponente; ///< Ej: "Resistor 1kΩ"
    std::string tipoDeComponente; ///< Ej: "Resistor", "Capacitor"
    float valorNominal{0.00}; ///< Valor principal (ej: 1000 para 1kΩ)
    float tolerancia{0.00};  ///< Tolerancia en porcentaje (ej: 5 para 5%)
    float voltajeDeTrabajo {0.00}; ///< Voltaje máximo (ej: 12.5)
    std::string estado; ///< Ej: "Nuevo", "Usado", "Dañado"
};

/**
 * @brief Solicita y valida la entrada de un número decimal al usuario
 * 
 * @param mensaje Texto que se muestra al usuario para solicitar el número (ej: "Ingrese valor: ")
 * @return float El número válido ingresado por el usuario
 * 
 * @details
 * Esta función implementa un bucle de validación robusto que:
 * 1. Muestra el mensaje proporcionado
 * 2. Intenta leer un número float de la entrada estándar
 * 3. Si falla la lectura (por entrada no numérica):
 *    - Muestra mensaje de error
 *    - Limpia los flags de error de cin
 *    - Descarta la entrada inválida
 *    - Vuelve a solicitar el número
 * 4. Si la lectura es exitosa:
 *    - Limpia el buffer de entrada
 *    - Retorna el valor numérico
 * 
 * @throws Nunca lanza excepciones (el manejo de errores es interno)
 * 
 * @note
 * - Usa numeric_limits para el máximo número de caracteres a ignorar
 * - El mensaje de error es genérico pero puede personalizarse
 * - El bucle continúa hasta recibir entrada válida
 * 
 * @par Ejemplo de uso:
 * @code
 * float precio = solicitarNumero("Ingrese el precio (ej: 12.99): ");
 * // Si usuario ingresa "abc":
 * // Muestra: "Error: Debe ingresar un número válido." y vuelve a solicitar
 * @endcode
 * 
 * @see std::numeric_limits
 * @see std::cin.fail()
 * @see std::cin.ignore()
 */
float solicitarNumero(const std::string& mensaje) {
    float valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.fail()) {
            std::cout << "Error: Debe ingresar un número válido.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
    }
}

/**
 * @brief Solicita y valida una cadena de texto al usuario con opciones de filtrado
 * 
 * @param mensaje Texto que se muestra al usuario para solicitar la entrada
 * @param permitirNumeros Si es true (por defecto), permite números en el texto
 * @return std::string Texto validado según los criterios
 * 
 * @details
 * Esta función implementa un sistema robusto de validación de texto que:
 * 1. Elimina espacios en blanco al inicio y final del texto
 * 2. Valida que la cadena no esté vacía
 * 3. Opcionalmente verifica que no contenga dígitos numéricos
 * 4. Mantiene un bucle hasta recibir una entrada válida
 * 
 * El proceso de validación incluye:
 * - Trim de espacios con find_first_not_of() y find_last_not_of()
 * - Verificación de cadena vacía
 * - Búsqueda de dígitos con isdigit() cuando !permitirNumeros
 * 
 * @throws Nunca lanza excepciones (manejo interno de errores)
 * 
 * @note
 * - El parámetro permitirNumeros activa/desactiva la validación de dígitos
 * - Los mensajes de error son informativos pero genéricos
 * - Se usa getline() para permitir espacios en el texto
 * 
 * @par Ejemplo 1 (Texto con números permitidos):
 * @code
 * string nombre = solicitarTexto("Ingrese modelo (ej: ABC123): ");
 * // Acepta: "Resistor 10kΩ"
 * @endcode
 * 
 * @par Ejemplo 2 (Solo texto):
 * @code
 * string estado = solicitarTexto("Ingrese estado (solo letras): ", false);
 * // Rechaza: "Dañado123", acepta: "Nuevo"
 * @endcode
 * 
 * @see std::getline()
 * @see std::string::erase()
 * @see std::isdigit()
 */
std::string solicitarTexto(const std::string& mensaje, bool permitirNumeros = true) {
    std::string entrada;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, entrada);

        // Eliminar espacios en blanco al inicio/final
        entrada.erase(0, entrada.find_first_not_of(" \t"));
        entrada.erase(entrada.find_last_not_of(" \t") + 1);

        if (entrada.empty()) {
            std::cout << "Error: No puede estar vacío.\n";
            continue;
        }

        if (!permitirNumeros) {
            bool esValido = true;
            for (char c : entrada) {
                if (isdigit(c)) {
                    esValido = false;
                    break;
                }
            }
            if (!esValido) {
                std::cout << "Error: No se permiten números en este campo.\n";
                continue;
            }
        }

        return entrada;
    }
}

/**
 * @brief Registra un nuevo componente electrónico con validación de datos
 * 
 * @param registros Referencia al vector donde se almacenarán los componentes
 * 
 * @details
 * Esta función guía al usuario a través del proceso de registro de un componente,
 * solicitando y validando cada campo mediante funciones especializadas:
 * 
 * 1. Nombre: Texto con números permitidos (ej: "Resistor 10kΩ")
 * 2. Tipo: Texto con números permitidos (ej: "Capacitor cerámico")
 * 3. Valor nominal: Número decimal (ej: 1000.0)
 * 4. Tolerancia: Número decimal (ej: 5.0 para 5%)
 * 5. Voltaje: Número decimal (ej: 12.5)
 * 6. Estado: Texto sin números (ej: "Nuevo", "Usado")
 * 
 * @post El componente validado se añade al vector 'registros'
 * @post Muestra confirmación del registro exitoso
 * 
 * @throws Nunca lanza excepciones (el manejo de errores es interno)
 * 
 * @note
 * - Usa solicitarTexto() y solicitarNumero() para validación robusta
 * - Mantiene consistencia con la estructura 'componente'
 * - La interfaz es interactiva y guiada paso a paso
 * 
 * @par Ejemplo de flujo:
 * @code{.sh}
 * Ingrese los datos del componente:
 * Nombre del componente: Resistor 1kΩ
 * Tipo del componente: Resistor de carbón
 * Valor nominal del componente: 1000
 * Tolerancia del componente: 5
 * Voltaje del componente: 12.5
 * Estado del componente: Nuevo
 * Componente registrado con éxito.
 * @endcode
 * 
 * @see componente
 * @see solicitarTexto()
 * @see solicitarNumero()
 */
void registroDeComponentes(std::vector<componente>&registros){
    componente x;
    std::cout << "Ingrese los datos del componente:\n";
    x.nombreDelComponente=solicitarTexto("Nombre del componente: ");
    x.tipoDeComponente=solicitarTexto("Tipo del componente: ");
    x.valorNominal=solicitarNumero("Valor nominal del componente: ");
    x.tolerancia=solicitarNumero("Tolerancia del componente: ");
    x.voltajeDeTrabajo=solicitarNumero("Voltaje del componente: ");
    x.estado=solicitarTexto("Estado del componente: ");
    registros.push_back(x);
    std::cout << "Componente registrado con éxito.\n\n";
}

/**
 * @brief Guarda un componente en un archivo de texto (sobrescribiendo si existe)
 * 
 * @param x Componente a serializar y guardar
 * @param nombreArchivo Ruta del archivo destino (debe incluir extensión .txt)
 * 
 * @details
 * Esta función implementa el almacenamiento persistente de componentes en archivos de texto,
 * usando el siguiente formato por cada componente:
 * 
 * --------------------------
 * NombreComponente
 * TipoComponente
 * ValorNominal
 * Tolerancia
 * VoltajeTrabajo
 * Estado
 * -----
 * --------------------------
 * 
 * El separador "-----" permite identificar componentes individuales al cargar los datos.
 * 
 * @post Crea/sobrescribe el archivo especificado
 * @post El archivo contendrá todos los campos del componente en orden predefinido
 * @post Muestra mensaje de error si no puede abrir el archivo
 * 
 * @warning Si el archivo existe, será sobrescrito completamente
 * 
 * @par Ejemplo de archivo generado:
 * @code
 * Resistor 1kΩ
 * Resistor
 * 1000
 * 5
 * 12.5
 * Nuevo
 * -----
 * @endcode
 * 
 * @see continuarConArchivo() Para añadir componentes sin sobrescribir
 * @see cargarDesdeArchivo() Para leer archivos en este formato
 */
void guardarEnArchivo(const componente& x, const std::string& nombreArchivo){
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        archivo<<x.nombreDelComponente<<"\n";
        archivo<<x.tipoDeComponente<<"\n";
        archivo<<x.valorNominal<<"\n";
        archivo<<x.tolerancia<<"\n";
        archivo<<x.voltajeDeTrabajo<<"\n";
        archivo<<x.estado<<"\n";
        archivo<<"-----\n"; // Separador entre componentes
        archivo.close();
    }
    else{
        std::cout<<"No se pudo abrir el archivo para guardar \n";
    }
}

/**
 * @brief Añade un componente al final de un archivo existente
 * 
 * @param x Componente a serializar y añadir
 * @param nombreArchivo Ruta del archivo destino (debe existir y tener extensión .txt)
 * 
 * @details
 * Esta función implementa escritura al final (append) de archivos para componentes,
 * manteniendo el mismo formato que guardarEnArchivo():
 * 
 * --------------------------
 * NombreComponente
 * TipoComponente
 * ValorNominal
 * Tolerancia
 * VoltajeTrabajo
 * Estado
 * -----
 * --------------------------
 * 
 * El modo std::ios::app garantiza que:
 * - Los nuevos datos se añaden después del último componente
 * - No se modifica el contenido existente
 * - Crea el archivo si no existe (comportamiento diferente a guardarEnArchivo())
 * 
 * @post El componente se añade al final del archivo
 * @post Preserva todos los componentes existentes
 * @post Muestra error si falla la apertura
 * 
 * @par Ejemplo de uso:
 * @code
 * componente c;
 * // ... inicializar c ...
 * continuarConArchivo(c, "componentes.txt");
 * @endcode
 * 
 * @throw Ninguno (errores se manejan con mensajes a stdout)
 * 
 * @see guardarEnArchivo() Para sobrescribir archivos
 * @see cargarDesdeArchivo() Para leer este formato
 * @see std::ofstream::app Para detalles del modo append
 */
void continuarConArchivo(const componente& x, const std::string& nombreArchivo){
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (archivo.is_open())
    {
        archivo<<x.nombreDelComponente<<"\n";
        archivo<<x.tipoDeComponente<<"\n";
        archivo<<x.valorNominal<<"\n";
        archivo<<x.tolerancia<<"\n";
        archivo<<x.voltajeDeTrabajo<<"\n";
        archivo<<x.estado<<"\n";
        archivo<<"-----\n";
        archivo.close();
    }
    else{
        std::cout<<"No se pudo abrir el archivo para guardar \n";
    }
}

/**
 * @brief Muestra el contenido completo de un archivo de componentes en la consola
 * 
 * @param nombreArchivo Ruta del archivo a visualizar (debe incluir extensión .txt)
 * 
 * @details
 * Esta función realiza las siguientes operaciones:
 * 1. Abre el archivo en modo lectura
 * 2. Lee línea por línea todo el contenido
 * 3. Muestra el contenido formateado en la consola
 * 
 * El formato de visualización muestra exactamente el contenido crudo del archivo,
 * incluyendo los separadores "-----" entre componentes.
 * 
 * @post Muestra todo el contenido del archivo o un mensaje de error
 * @post No modifica el archivo original
 * @post Cierra el archivo automáticamente al finalizar
 * 
 * @throw Ninguno (los errores se manejan internamente)
 * 
 * @par Ejemplo de salida:
 * @code
 * Contenido del archivo línea por línea:
 * Resistor 1kΩ
 * Resistor
 * 1000
 * 5
 * 12.5
 * Nuevo
 * -----
 * Capacitor 10uF
 * ...
 * @endcode
 * 
 * @warning
 * - No interpreta la estructura de componentes, solo muestra líneas
 * - Archivos muy grandes pueden consumir mucha memoria
 * 
 * @see cargarDesdeArchivo() Para cargar componentes con estructura
 * @see guardarEnArchivo() Para entender el formato del archivo
 */
void mostrarArchivoExistente(const std::string& nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::vector<std::string> lineas;
    std::string linea;
    
    while (std::getline(archivo, linea)) { 
        lineas.push_back(linea); 
    }

    archivo.close();

    std::cout << "Contenido del archivo línea por línea:\n";
    for (const auto& l : lineas) {
        std::cout << l << std::endl;
    }

}

/**
 * @brief Vacía completamente el contenido de un archivo
 * 
 * @param nombreArchivo Ruta del archivo a vaciar (debe incluir extensión .txt)
 * 
 * @details
 * Esta función elimina todo el contenido del archivo especificado mediante:
 * 1. Apertura en modo truncate (std::ios::trunc)
 * 2. Cierre inmediato del archivo
 * 
 * El archivo permanece existente pero con 0 bytes de tamaño.
 * 
 * @post El archivo queda vacío si se abre correctamente
 * @post El archivo original es sobreescrito completamente
 * @post Muestra confirmación de éxito o error
 * 
 * @warning
 * - La operación es irreversible
 * - No solicita confirmación antes de vaciar
 * - El archivo debe tener permisos de escritura
 * 
 * @par Ejemplo de uso:
 * @code
 * eliminarContenidoArchivo("componentes_obsoletos.txt");
 * // Salida: "El archivo 'componentes_obsoletos.txt' fue vaciado con éxito."
 * @endcode
 * 
 * @see guardarEnArchivo() Para crear archivos nuevos
 * @see continuarConArchivo() Para añadir contenido sin borrar
 */
void eliminarContenidoArchivo(const std::string& nombreArchivo){
    std::ofstream archivo(nombreArchivo, std::ios::trunc);
    if (archivo.is_open()) {
        std::cout << "El archivo '" << nombreArchivo << "' fue vaciado con éxito.\n";
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo.\n";
    }
}

/**
 * @brief Muestra el menú principal de la aplicación con formato visual
 * 
 * @details 
 * Presenta las opciones disponibles en un formato visualmente organizado:
 * 
 * ============================
 * ¡Bienvenido! seleccione una opción:
 * (1) Nuevo registro de componentes
 * (2) Continuar registro desde un archivo existente
 * (3) Ver registros de un archivo existente
 * (4) Eliminar el contenido de un archivo
 * (5) Buscar un componente en un archivo
 * (6) Salir
 * ============================
 * 
 * Cada opción está numerada y alineada para mejor legibilidad.
 * 
 * @post Genera salida estándar con el menú formateado
 * @post No afecta el estado del programa
 * 
 * @note
 * - Las opciones están diseñadas para ser claras y autodescriptivas
 * - Los separadores "===" mejoran la legibilidad visual
 * - Corresponde a eleccionMenuprincipal() para procesar la selección
 * 
 * @see eleccionMenuprincipal() Para el manejo de la selección del usuario
 */
void mostrarMenu(){
    std::cout << "\n============================\n";
    std::cout<<"¡Bienvenido! seleccione una opción:\n";
    std::cout<<"(1)Nuevo registro de componentes \n";
    std::cout<<"(2)Continuar registro desde un archivo existente. \n";
    std::cout<<"(3)Ver registros de un archivo existente. \n";
    std::cout<<"(4)Eliminar el contenido de un archivo. \n";
    std::cout<<"(5)Buscar un componente en un archivo\n";
    std::cout<< "(6)Salir\n";
    std::cout << "\n============================\n";
}

/**
 * @brief Carga componentes desde un archivo de texto al vector de registros
 * 
 * @param registros Vector donde se almacenarán los componentes cargados
 * @param nombreArchivo Ruta del archivo a cargar (debe incluir extensión .txt)
 * 
 * @details
 * Esta función implementa un parser para el formato específico de archivos de componentes:
 * 1. Abre el archivo en modo lectura
 * 2. Lee línea por línea reconstruyendo la estructura de cada componente
 * 3. Sigue estrictamente el formato:
 *    - Línea 1: Nombre
 *    - Línea 2: Tipo  
 *    - Línea 3: Valor nominal (float)
 *    - Línea 4: Tolerancia (float)
 *    - Línea 5: Voltaje (float)
 *    - Línea 6: Estado
 *    - Línea 7: Separador "-----"
 * 
 * @post El vector 'registros' contiene todos los componentes válidos del archivo
 * @post El vector se vacía antes de cargar nuevos registros
 * @post Muestra error si no puede abrir el archivo
 * 
 * @throw std::invalid_argument Si encuentra valores numéricos inválidos
 * @throw std::out_of_range Si los valores numéricos exceden los límites
 * 
 * @par Ejemplo de formato de archivo:
 * @code
 * Resistor 1kΩ
 * Resistor
 * 1000
 * 5  
 * 12.5
 * Nuevo
 * -----
 * @endcode
 * 
 * @note
 * - Usa std::stof() para conversión numérica (lanza excepciones)
 * - El contador maneja la posición de cada campo
 * - Reinicia el estado al encontrar "-----"
 * 
 * @see guardarEnArchivo() Para el formato de guardado equivalente
 * @see continuarConArchivo() Para añadir componentes a archivos
 */
void cargarDesdeArchivo(std::vector<componente>& registros, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo.\n";
        return;
    }

    registros.clear();  // Limpiamos para evitar mezclar registros anteriores
    componente temp;
    std::string linea;
    int contador = 0;

    while (std::getline(archivo, linea)) {
        switch (contador) {
            case 0: 
                temp.nombreDelComponente = linea; 
                break;
            case 1: 
                temp.tipoDeComponente = linea; 
                break;
            case 2: 
                temp.valorNominal = std::stof(linea); 
                break;
            case 3: 
                temp.tolerancia = std::stof(linea); 
                break;
            case 4: 
                temp.voltajeDeTrabajo = std::stof(linea); 
                break;
            case 5: 
                temp.estado = linea; 
                break;
            case 6:
                if (linea == "-----") {
                    registros.push_back(temp);
                    temp = componente();  // Limpiar para el siguiente
                    contador = -1;       // Reiniciar para el siguiente bloque
                }
                break;
        }
        contador++;
    }

    archivo.close();
}

/**
 * @brief Muestra el menú de parámetros de búsqueda disponibles
 * 
 * @details
 * Presenta un menú formateado con las diferentes opciones para buscar componentes:
 * 
 * ============================
 * (1) Nombre
 * (2) Tipo
 * (3) Valor nominal
 * (4) Tolerancia  
 * (5) Voltaje de trabajo
 * (6) Estado
 * (7) Salir
 * Elija el parámetro de búsqueda a utilizar:
 * ============================
 * 
 * Cada opción corresponde a un campo específico de la estructura 'componente'.
 * 
 * @post Genera salida estándar con el menú formateado
 * @post No modifica ningún estado del programa
 * 
 * @note
 * - Diseñado para usarse con buscarPorParametro()
 * - Las opciones 1-6 corresponden a campos de búsqueda
 * - La opción 7 permite salir sin buscar
 * - Los separadores "===" mejoran la legibilidad
 * 
 * @see buscarPorParametro() Para el procesamiento de la selección
 * @see componente Para la estructura de datos relacionada
 */
void menuParametro(){
    std::cout << "\n============================\n";
    std::cout<<"(1) Nombre. \n";
    std::cout<<"(2) Tipo. \n";
    std::cout<<"(3) Valor nominal. \n";
    std::cout<<"(4) Tolerancia. \n";
    std::cout<<"(5) Voltaje de trabajo. \n";
    std::cout<<"(6) Estado  \n";
    std::cout<<"(7) Salir  \n";
    std::cout<<"Elija el parámetro de búsqueda a utilizar: \n";
    std::cout << "\n============================\n";
}

/**
 * @brief Muestra los detalles de un componente electrónico en formato legible
 * 
 * @param c Componente a mostrar (referencia constante)
 * 
 * @details
 * Esta función despliega todos los campos de un componente en un formato consistente:
 * 
 * --------------------------
 * Componente encontrado:
 * Nombre: [nombreDelComponente]
 * Tipo: [tipoDeComponente]  
 * Valor nominal: [valorNominal]
 * Tolerancia: [tolerancia]%
 * Voltaje: [voltajeDeTrabajo]V
 * Estado: [estado]
 * -----
 * --------------------------
 * 
 * @post Genera salida estándar con el formato especificado
 * @post No modifica el componente recibido
 * 
 * @note
 * - Formato diseñado para máxima legibilidad
 * - Incluye unidades donde es relevante (% y V)
 * - Separador "-----" al final para delimitar visualmente
 * - Campos alineados verticalmente para fácil escaneo
 * 
 * @par Ejemplo de salida:
 * @code
 * Componente encontrado:
 * Nombre: Resistor 1kΩ
 * Tipo: Resistor de carbón
 * Valor nominal: 1000
 * Tolerancia: 5%
 * Voltaje: 12.5V  
 * Estado: Nuevo
 * -----
 * @endcode
 * 
 * @see componente Para la estructura de datos mostrada
 * @see buscarPorNombre() Como una de las funciones que usa esta visualización
 */
void mostrarComponente(const componente& c) {
    std::cout<< "\nComponente encontrado:\n";
    std::cout<< "Nombre: " << c.nombreDelComponente << "\n";
    std::cout<< "Tipo: " << c.tipoDeComponente << "\n";
    std::cout<< "Valor nominal: " << c.valorNominal << "\n";
    std::cout<< "Tolerancia: " << c.tolerancia << "%\n";
    std::cout<< "Voltaje: " << c.voltajeDeTrabajo << "V\n";
    std::cout<< "Estado: " << c.estado << "\n";
    std::cout<< "-----\n";
}

/**
 * @brief Busca componentes por coincidencia parcial de nombre
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Esta función implementa una búsqueda case-sensitive de subcadenas en los nombres:
 * 1. Solicita al usuario el texto a buscar mediante solicitarTexto()
 * 2. Recorre todos los componentes comparando nombres
 * 3. Muestra cada coincidencia usando mostrarComponente()
 * 4. Informa cuando no encuentra resultados
 * 
 * La comparación es por coincidencia parcial (subcadena):
 * - "res" encontrará "Resistor 10kΩ" y "RESISTOR 1MΩ"
 * - Búsqueda exacta requiere ingresar el nombre completo
 * 
 * @post Muestra por pantalla todos los componentes coincidentes
 * @post No modifica el vector de registros
 * 
 * @throw Ninguno (errores manejados internamente)
 * 
 * @par Ejemplo de uso:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorNombre(inventario);
 * // Usuario ingresa: "10k"
 * // Muestra todos los componentes con "10k" en su nombre
 * @endcode
 * 
 * @note
 * - Sensible a mayúsculas/minúsculas (case-sensitive)
 * - Muestra múltiples coincidencias si existen
 * - Usa string::find() para búsqueda parcial
 * 
 * @see solicitarTexto() Para la entrada del usuario
 * @see mostrarComponente() Para el formato de visualización
 */
void buscarPorNombre(const std::vector<componente>& registros){
    std::string nombreComponente=solicitarTexto("Ingrese el nombre del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.nombreDelComponente.find(nombreComponente)!=std::string::npos)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
    {
        std::cout << "No se encontró ningún componente con ese nombre.\n";
    }
}

/**
 * @brief Busca componentes por coincidencia parcial en el tipo
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Implementa búsqueda de subcadena case-sensitive en el campo tipoDeComponente:
 * 
 * 1. Solicita el tipo a buscar usando solicitarTexto()
 * 2. Recorre todos los componentes comparando tipos
 * 3. Muestra coincidencias con mostrarComponente()
 * 4. Informa si no hay resultados
 * 
 * La comparación es por subcadena:
 * - "cap" encontrará "Capacitor" y "CAPACITOR"
 * - Coincidencia en cualquier posición del texto
 * 
 * @post Muestra componentes con tipos coincidentes
 * @post No modifica el vector original
 * 
 * @throw Ninguno (errores manejados internamente)
 * 
 * @par Ejemplo:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorTipo(inventario);
 * // Usuario ingresa: "resis"
 * // Muestra resistores con cualquier valor
 * @endcode
 * 
 * @note 
 * - Sensible a mayúsculas/minúsculas
 * - Muestra múltiples coincidencias
 * - Usa string::find() para búsqueda parcial
 * 
 * @see solicitarTexto() Para entrada validada
 * @see mostrarComponente() Para formato de visualización
 */
void buscarPorTipo(const std::vector<componente>& registros){
    std::string tipo=solicitarTexto("Ingrese el tipo del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.tipoDeComponente.find(tipo)!=std::string::npos)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
    {
        std::cout << "No se encontró ningún componente de ese tipo.\n";
    }
}

/**
 * @brief Busca componentes por valor nominal exacto
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Realiza una búsqueda exacta por valor numérico en el campo valorNominal:
 * 
 * 1. Solicita el valor a buscar usando solicitarNumero()
 * 2. Compara usando igualdad exacta (==)
 * 3. Muestra coincidencias con mostrarComponente()
 * 4. Informa si no hay resultados
 * 
 * @post Muestra componentes con valores nominales idénticos
 * @post No modifica el vector original
 * 
 * @warning
 * - Comparación exacta puede omitir valores equivalentes
 * - Problemas potenciales con precisión de floats
 * 
 * @par Ejemplo:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorValorNominal(inventario);
 * // Usuario ingresa: 1000
 * // Muestra componentes con valor exacto 1000
 * @endcode
 * 
 * @note 
 * - Para búsqueda por rango usar buscarPorParametro()
 * - Considerar margen de error para valores float
 * 
 * @see solicitarNumero() Para entrada validada
 * @see mostrarComponente() Para formato de visualización
 */
void buscarPorValorNominal(const std::vector<componente>& registros){
    float valor=solicitarNumero("Ingrese el valor nominal del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.valorNominal==valor)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
        {
            std::cout << "No se encontró ningún componente con ese valor nominal.\n";
        }
}

/**
 * @brief Busca componentes por valor exacto de tolerancia
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Realiza una búsqueda exacta por el porcentaje de tolerancia:
 * 
 * 1. Solicita el valor de tolerancia mediante solicitarNumero()
 * 2. Compara usando igualdad exacta (==) con el campo tolerancia
 * 3. Muestra coincidencias usando mostrarComponente()
 * 4. Informa si no encuentra resultados
 * 
 * @post Muestra componentes con tolerancias idénticas
 * @post No modifica el vector original
 * 
 * @warning
 * - La comparación es exacta (puede omitir valores cercanos)
 * - Problemas potenciales con precisión de punto flotante
 * - La tolerancia debe ingresarse como porcentaje (ej: 5 para 5%)
 * 
 * @par Ejemplo de uso:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorTolerancia(inventario);
 * // Usuario ingresa: 5
 * // Muestra componentes con ±5% de tolerancia
 * @endcode
 * 
 * @note
 * - Para resistores, valores comunes son: 1%, 5%, 10%
 * - Para capacitores, típicamente 10%, 20%
 * - Considerar implementar búsqueda por rango
 * 
 * @see solicitarNumero() Para entrada validada
 * @see mostrarComponente() Para formato de visualización
 * @see buscarPorParametro() Para búsqueda parametrizada
 */
void buscarPorTolerancia(const std::vector<componente>& registros){
    float toleranciaBuscada=solicitarNumero("Ingrese la tolerancia del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.tolerancia==toleranciaBuscada)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
        {
            std::cout << "No se encontró ningún componente con esa tolerancia.\n";
        }
}

/**
 * @brief Busca componentes por voltaje de trabajo exacto
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Realiza una búsqueda exacta por el voltaje de trabajo especificado:
 * 
 * 1. Solicita el voltaje mediante solicitarNumero()
 * 2. Compara usando igualdad exacta (==) con el campo voltajeDeTrabajo
 * 3. Muestra coincidencias con mostrarComponente()
 * 4. Informa si no hay resultados
 * 
 * @post Muestra componentes con voltajes idénticos
 * @post No modifica el vector original
 * 
 * @warning
 * - La comparación es exacta (puede omitir valores cercanos)
 * - Problemas potenciales con precisión de punto flotante
 * - El voltaje debe ingresarse en voltios (ej: 12.5)
 * 
 * @par Ejemplo de uso:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorVoltaje(inventario);
 * // Usuario ingresa: 12
 * // Muestra componentes para 12V exactos
 * @endcode
 * 
 * @note
 * - Valores típicos: 3.3V, 5V, 12V, 24V, etc.
 * - Para capacitores: voltaje máximo soportado
 * - Para reguladores: voltaje de salida
 * 
 * @see solicitarNumero() Para entrada validada
 * @see mostrarComponente() Para formato de visualización
 */
void buscarPorVoltaje(const std::vector<componente>& registros){
    float voltajeBuscado=solicitarNumero("Ingrese el voltaje del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.voltajeDeTrabajo==voltajeBuscado)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
        {
            std::cout << "No se encontró ningún componente con ese voltaje.\n";
        }
}

/**
 * @brief Busca componentes por coincidencia parcial en el estado
 * 
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Realiza una búsqueda de subcadena case-sensitive en el campo estado:
 * 
 * 1. Solicita el texto a buscar usando solicitarTexto()
 * 2. Compara con el campo estado de cada componente
 * 3. Muestra coincidencias con mostrarComponente()
 * 4. Informa si no hay resultados
 * 
 * La comparación es por subcadena:
 * - "nue" encontrará "Nuevo" y "nuevo"
 * - Coincidencia en cualquier posición del texto
 * 
 * @post Muestra componentes con estados coincidentes
 * @post No modifica el vector original
 * 
 * @warning
 * - Sensible a mayúsculas/minúsculas
 * - No realiza búsqueda fonética o aproximada
 * 
 * @par Ejemplo de uso:
 * @code
 * vector<componente> inventario = {...};
 * buscarPorEstado(inventario);
 * // Usuario ingresa: "usad"
 * // Muestra componentes marcados como "Usado" o "usado"
 * @endcode
 * 
 * @note
 * - Estados comunes: "Nuevo", "Usado", "Dañado", "Reparado"
 * - Considerar normalizar los estados (siempre misma capitalización)
 * - Para búsqueda exacta, ingresar el estado completo
 * 
 * @see solicitarTexto() Para entrada validada
 * @see mostrarComponente() Para formato de visualización
 * @see buscarPorParametro() Para búsqueda parametrizada
 */
void buscarPorEstado(const std::vector<componente>& registros){
    std::string estado=solicitarTexto("Ingrese el estado del componente que desea encontrar \n");
    bool encontrado{false};
    for (const auto& c : registros)
    {
        if (c.estado.find(estado)!=std::string::npos)
        {
            mostrarComponente(c);
            encontrado = true;
        }
    }
    if (encontrado==false)
    {
        std::cout << "No se encontró ningún componente en ese estado.\n";
    }
}

/**
 * @brief Función de despacho para búsquedas de componentes por diferentes parámetros
 * 
 * @param opcion Entero que especifica el tipo de búsqueda a realizar (1-7)
 * @param registros Vector de componentes donde buscar (referencia constante)
 * 
 * @details
 * Esta función actúa como un router que dirige a las funciones específicas de búsqueda
 * según la opción seleccionada en el menú de parámetros:
 * 
 * 1. Búsqueda por nombre (buscarPorNombre)
 * 2. Búsqueda por tipo (buscarPorTipo)
 * 3. Búsqueda por valor nominal (buscarPorValorNominal)
 * 4. Búsqueda por tolerancia (buscarPorTolerancia)
 * 5. Búsqueda por voltaje (buscarPorVoltaje)
 * 6. Búsqueda por estado (buscarPorEstado)
 * 7. Salir al menú principal
 * 
 * @post Ejecuta la función de búsqueda correspondiente
 * @post Maneja opciones inválidas mostrando mensaje
 * @post No modifica el vector de componentes
 * 
 * @throw Ninguno (los errores se manejan internamente)
 * 
 * @par Ejemplo de uso:
 * @code
 * vector<componente> inventario = {...};
 * int opcion = 3; // Buscar por valor nominal
 * buscarPorParametro(opcion, inventario);
 * @endcode
 * 
 * @note
 * - Debe usarse junto con menuParametro()
 * - Las opciones deben coincidir con las mostradas en el menú
 * - El caso default maneja entradas fuera de rango
 * 
 * @see menuParametro() Para el menú de opciones correspondiente
 * @see buscarPorNombre() Para detalles de búsqueda por nombre
 * @see buscarPorTipo() Para detalles de búsqueda por tipo
 * @see buscarPorValorNominal() Para detalles de búsqueda por valor
 * @see buscarPorTolerancia() Para detalles de búsqueda por tolerancia
 * @see buscarPorVoltaje() Para detalles de búsqueda por voltaje
 * @see buscarPorEstado() Para detalles de búsqueda por estado
 */
void buscarPorParametro(const int& opcion, const std::vector<componente>& registros){
    switch (opcion)
    {
    case 1:
        buscarPorNombre(registros);
        break;
    case 2:
        buscarPorTipo(registros);
        break;
    case 3:
        buscarPorValorNominal(registros);
        break;
    case 4:
        buscarPorTolerancia(registros);
        break;
    case 5:
        buscarPorVoltaje(registros);
        break;
    case 6:
        buscarPorEstado(registros);
        break;
    case 7:
        std::cout<<"Volviendo al menú principal...";
    default:
        std::cout<<"Entrada inválida, volviendo al menú principal...";
        break;
    }
}

/**
 * @brief Solicita y valida la selección del menú principal del usuario
 * 
 * @return int Opción válida seleccionada por el usuario (1-6)
 * 
 * @details
 * Esta función implementa un bucle robusto de validación que:
 * 1. Muestra el menú principal mediante mostrarMenu()
 * 2. Solicita la entrada del usuario
 * 3. Valida que la entrada sea un número entero
 * 4. Verifica que esté en el rango válido (1-6)
 * 5. Continúa solicitando hasta recibir una entrada válida
 * 
 * El proceso de validación incluye:
 * - Manejo de errores de entrada con cin.fail()
 * - Limpieza del buffer de entrada con cin.ignore()
 * - Reinicio del estado de cin con cin.clear()
 * - Verificación de rango numérico
 * 
 * @post Garantiza que el valor retornado es siempre una opción válida del menú
 * @post No modifica ningún estado global del programa
 * 
 * @throw Nunca lanza excepciones (el manejo de errores es interno)
 * 
 * @note
 * - Las opciones válidas corresponden a las mostradas por mostrarMenu()
 * - El mensaje de error es informativo pero genérico
 * - Usa 10000 como límite arbitrario para ignore() (suficiente para limpieza)
 * 
 * @par Ejemplo de flujo:
 * @code
 * int opcion = eleccionMenuprincipal();
 * // Si usuario ingresa "a":
 * // Muestra: "Entrada inválida. Por favor, ingresa un número del 1 al 6."
 * // Si usuario ingresa "7":
 * // Muestra: "Opción fuera de rango. Ingresa un número entre 1 y 6."
 * // Cuando ingresa 3: retorna 3
 * @endcode
 * 
 * @see mostrarMenu() Para el menú que se presenta al usuario
 * @see std::cin.fail() Para el manejo de errores de entrada
 * @see std::cin.ignore() Para la limpieza del buffer de entrada
 */
int eleccionMenuprincipal(){
    int eleccion{0};
    while (true) {
        mostrarMenu();
        std::cin >> eleccion;

        if (std::cin.fail()) {
            std::cin.clear(); // limpiar el estado de error
            std::cin.ignore(10000, '\n'); // limpiar el búfer de entrada
            std::cout << "Entrada inválida. Por favor, ingresa un número del 1 al 6.\n";
            continue;
        }

        if (eleccion >= 1 && eleccion <= 6) break;
        std::cout << "Opción fuera de rango. Ingresa un número entre 1 y 6.\n";
        std::cin.ignore(10000, '\n');
    }
    return eleccion;
}

/**
 * @brief Maneja el proceso completo de registro de componentes en archivos
 * 
 * @param registros Referencia al vector donde se almacenan temporalmente los componentes
 * @param nombreArchivo Referencia al string que almacenará el nombre del archivo
 * @param sobrescribir Flag que determina el modo de operación:
 *                     - true: Sobrescribe archivos existentes
 *                     - false: Añade a archivos existentes
 * 
 * @details
 * Esta función coordina el flujo completo de registro de componentes:
 * 1. Solicita el nombre del archivo (debe incluir .txt)
 * 2. Valida la existencia del archivo según el modo:
 *    - Modo sobrescritura: Pide confirmación si el archivo existe
 *    - Modo continuación: Verifica que el archivo exista
 * 3. Limpia el vector de registros temporal
 * 4. Ciclo de registro de componentes:
 *    - Usa registroDeComponentes() para capturar datos
 *    - Guarda usando guardarEnArchivo() o continuarConArchivo()
 *    - Permite registrar múltiples componentes
 * 
 * @post El archivo especificado contendrá los componentes registrados
 * @post El vector 'registros' queda vacío al finalizar
 * @post Muestra mensajes de estado/error durante el proceso
 * 
 * @warning
 * - En modo sobrescritura, los datos existentes se perderán sin confirmación
 * - El nombre de archivo debe incluir la extensión .txt explícitamente
 * 
 * @throw Ninguno (los errores se manejan con mensajes y retornos tempranos)
 * 
 * @par Ejemplo 1 (Modo sobrescritura):
 * @code
 * vector<componente> reg;
 * string archivo;
 * iniciarRegistro(reg, archivo, true);
 * // Si archivo existe: pregunta antes de sobrescribir
 * // Si no existe: crea nuevo archivo
 * @endcode
 * 
 * @par Ejemplo 2 (Modo continuación):
 * @code
 * vector<componente> reg;
 * string archivo;
 * iniciarRegistro(reg, archivo, false);
 * // Si archivo no existe: muestra error y aborta
 * // Si existe: añade nuevos componentes al final
 * @endcode
 * 
 * @note
 * - Usa funciones auxiliares para operaciones específicas
 * - El ciclo continúa hasta que el usuario elija salir
 * - Siempre limpia el vector antes de comenzar
 * 
 * @see registroDeComponentes() Para el ingreso de datos
 * @see guardarEnArchivo() Para guardado en modo sobrescritura
 * @see continuarConArchivo() Para guardado en modo añadir
 */
void iniciarRegistro(std::vector<componente>& registros, std::string& nombreArchivo, bool sobrescribir) {
    std::cin.ignore();
    std::cout << "Ingresa el nombre del archivo (agrega .txt al final): \n";
    std::getline(std::cin, nombreArchivo);

    std::ifstream test(nombreArchivo);
    if (sobrescribir && test.is_open()) {
        int seleccion{0};
        std::cout << "El archivo ya existe y será sobrescrito\n";
        std::cout << "¿Continuar?\nSi(1) No(2)\n";
        std::cin >> seleccion;
        std::cin.ignore();
        if (seleccion != 1) return;
    }

    if (!sobrescribir && !test.is_open()) {
        std::cout << "El archivo no existe. No se puede continuar\n";
        return;
    }

    registros.clear();
    int continuar = 1;
    while (continuar == 1) {
        registroDeComponentes(registros);
        if (sobrescribir) {
            guardarEnArchivo(registros.back(), nombreArchivo);
        } else {
            continuarConArchivo(registros.back(), nombreArchivo);
        }
        std::cout << "Componente guardado correctamente.\n";
        std::cout << "¿Deseas ingresar otro componente? (1 = Sí, 2 = No): ";
        std::cin >> continuar;
        std::cin.ignore();
    }
    std::cout << "Archivo guardado correctamente.\n";
}

/**
 * @brief Punto de entrada principal del sistema de gestión de componentes electrónicos
 * 
 * @return int Código de salida del programa (0 para terminación exitosa)
 * 
 * @details
 * Función principal que implementa el flujo de control del sistema completo:
 * 
 * 1. Inicializa las estructuras de datos necesarias
 * 2. Presenta un bucle infinito del menú principal hasta que el usuario elija salir
 * 3. Maneja todas las operaciones principales mediante una estructura switch-case
 * 
 * Las operaciones disponibles son:
 * - (1) Nuevo registro (sobrescribe archivos existentes)
 * - (2) Continuar registro (añade a archivo existente)
 * - (3) Visualización de archivos existentes
 * - (4) Vaciar contenido de archivos
 * - (5) Búsqueda multicriterio de componentes
 * - (6) Salida del sistema
 * 
 * @note
 * - Todos los nombres de archivo deben incluir explícitamente la extensión .txt
 * - El vector 'registros' se reutiliza entre operaciones
 * - La función mantiene coherencia con la documentación del sistema completo
 * 
 * @par Ejemplo de flujo de ejecución:
 * @code{.sh}
 * ============================
 * ¡Bienvenido! seleccione una opción:
 * (1) Nuevo registro de componentes
 * (2) Continuar registro desde un archivo existente
 * (3) Ver registros de un archivo existente
 * (4) Eliminar el contenido de un archivo
 * (5) Buscar un componente en un archivo
 * (6) Salir
 * ============================
 * > 1
 * Ingresa el nombre del archivo...
 * @endcode
 * 
 * @see eleccionMenuprincipal() Para el manejo de la selección de opciones
 * @see iniciarRegistro() Para las operaciones de registro
 * @see mostrarArchivoExistente() Para visualización de archivos
 * @see eliminarContenidoArchivo() Para vaciado de archivos
 * @see buscarPorParametro() Para el subsistema de búsqueda
 */
int main(){
    std::vector<componente> registros;
    std::string nombreArchivo;
    while (true)
    {
        int eleccion = eleccionMenuprincipal();
        int continuar{1};
        switch (eleccion)
        {
        case 1: {
            iniciarRegistro(registros, nombreArchivo, true);
            break;
        }
        case 2:{
            iniciarRegistro(registros, nombreArchivo, false);
            break;
        }
        case 3:
            std::cin.ignore();
            std::cout << "Ingresa el nombre del archivo que deseas ver (agrega .txt al final): \n";
            std::getline(std::cin, nombreArchivo);
            mostrarArchivoExistente(nombreArchivo);
            break;
        case 4:
            std::cin.ignore();
            std::cout << "Ingresa el nombre del archivo que deseas vaciar (agrega .txt al final): \n";
            std::getline(std::cin, nombreArchivo);
            eliminarContenidoArchivo(nombreArchivo);
            break;
        case 5:
            std::cin.ignore();
            int opcion;
            std::cout<<"Ingresa el nombre del archivo con en el que deseas buscar tu componente (agrega .txt al final): \n";
            std::getline(std::cin, nombreArchivo);
            cargarDesdeArchivo(registros, nombreArchivo);
            menuParametro();
            std::cin>>opcion;
            std::cin.ignore();
            buscarPorParametro(opcion, registros);
            break;
        case 6:
            std::cout<<"Vuelva pronto \n";
            return 0;
        default:
            std::cout<<"Error, opción no válida. \n";
            break;
        }
    }
    return 0;
}