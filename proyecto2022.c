#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 1001

typedef struct data{
    char arreglo[NMAX][31];
    int cant;
}TData;

TData data;

// perfil de las funciones y acciones.
bool Vacia(TData* data);  
bool Llena(TData* data);  
void Insertar(TData* data, char apellido[31]);  
void Suprimir(TData* data, char apellido[31]);
void Modificar(TData* data, char apellido[31]);
void Mostrar(TData* data);  
int Encontrar(TData* data, char apellido[31]);  
bool Repetidos(char apellido1[31], char apellido2[31]);  

int main() {
    int num;
    char apellido[31];

    do{
        // esto se repetira cada vez que el usuario ingrese al programa o que se termine de correr un comando (1-5).
        printf("-----------------------------------");
        printf("\nAlta de empleado (1)\n");
        printf("Baja de empleado (2)\n");
        printf("Modificar datos de empleado (3)\n");
        printf("Listar (4)\n");
        printf("Buscar un empleado (5)\n");
        printf("Salir (6)\n");
        printf("-----------------------------------");
        printf("\nIngrese el numero de lo que desea hacer: ");
        scanf("%d", &num);

        // sentencia switch que interpretara la opcion elegida por el usuario.
        switch (num){
            case 1:
                if (Llena(&data) == true){
                    printf("No se pueden añadir mas empleados");
                }else{
                    // si la lista no esta llena, leo el apellido ingresado.
                    do{
                        // ciclo que asegura que la entrada del apellido es de menos de 30 caracteres.
                        printf("\nIngrese el apellido (maximo: 30 caracteres) del nuevo empleado (no pueden haber dos apellidos iguales): ");
                        scanf("%s", apellido);
                        if (strlen(apellido) > 30){
                            printf("\nEl apellido debe tener como maximo 30 caracteres. Ingrese el apellido nuevamente\n");
                        }
                    } while (strlen(apellido) > 30);
                    Insertar(&data, apellido);
                    // elimina todos los apellidos repetidos.
                    for (int i = 0; i < data.cant ; i++){ 
                        for (int j = 0; j < data.cant ; j++){
                            if (Repetidos(data.arreglo[i],data.arreglo[j]) && (i != j)){
                                printf("\nEl apellido ya existe, se eliminara la primera ocurrencia del mismo\n");
                                Suprimir(&data,data.arreglo[i]);
                            }
                        }
                    }
                }    
            break;

            case 2: 
                if (Vacia(&data) == true){
                    printf("\nNo hay apellidos en la lista\n");
                }else{
                    // si la lista no esta vacia, leo el apellido ingresado.
                    do{
                        // ciclo que asegura los 30 caracteres del apellido y que este exista en la lista.
                        printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a dar de baja: ");
                        scanf("%s", apellido);
                        if (strlen(apellido) > 30){
                            printf("\nEl apellido debe tener como maximo 30 caracteres. Ingrese el apellido nuevamente\n");
                        }
                    } while (strlen(apellido) > 30  );
                    // verifico que el apellido existe usando la funcion Encontrar().
                    if (Encontrar(&data, apellido) != -1){
                        Suprimir(&data, apellido); 
                    }else{
                        printf("\nEl apellido no existe en la lista\n");
                    }
                }
            break;

            case 3:
                if (Vacia(&data) == true){
                    printf("\nNo hay apellidos en la lista\n");
                }else{
                    // si la lista no esta vacia, leo el apellido a modificar.
                    do{
                        // ciclo que asegura los 30 caracteres del apellido y que este exista en la lista.
                        printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a modificar: ");
                        scanf("%s", apellido);
                        if (strlen(apellido) > 30 || Encontrar(&data, apellido) == -1){
                            printf("\nEl apellido debe tener como maximo 30 caracteres y debe existir en la lista. Ingrese el apellido nuevamente\n");
                        }
                    } while (strlen(apellido) > 30 && Encontrar(&data, apellido) == -1);
                    // verifico que el apellido existe usando la funcion Encontrar().
                    if (Encontrar(&data, apellido) != -1){
                        Modificar(&data, apellido);
                    }else{
                        printf("\nEl apellido no existe en la lista\n");
                    }
                    // elimina todos los apellidos repetidos.
                    for (int i = 0; i < data.cant ; i++){ 
                        for (int j = 0; j < data.cant ; j++){
                            if (Repetidos(data.arreglo[i],data.arreglo[j]) && (i != j)){
                                printf("\nEl apellido ya existe, se eliminara la primera ocurrencia del mismo\n");
                                Suprimir(&data,data.arreglo[i]);
                            }   
                        }   
                    }   
                }
            break;

            case 4: 
                if (Vacia(&data) == true){
                    printf("\nNo hay apellidos en la lista\n");
                }else{
                    Mostrar(&data);
                }
            break;

            case 5:
                if (Vacia(&data) == true){
                    printf("\nNo hay apellidos en la lista\n");
                }else{
                    do{
                        // ciclo que asegura los 30 caracteres del apellido y que este exista en la lista.
                        printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a buscar: ");
                        scanf("%s", apellido);
                        if (strlen(apellido) > 30){
                            printf("\nEl apellido debe tener como maximo 30 caracteres. Ingrese el apellido nuevamente\n");
                        }
                    } while (strlen(apellido) > 30);
                    // verifico que el apellido existe usando la funcion Encontrar().
                    if (Encontrar(&data, apellido) == -1){
                        printf("\nEl apellido no existe en la lista\n");
                    }else{
                        printf("\nEl apellido %s se encuentra en la posicion %d\n", apellido, Encontrar(&data, apellido));
                    } 
                }
            break;

            case 6:
                return 0;
            break;            
        }
        // condicional que verifica que el numero ingresado esta entre 1 y 6.
        if (num < 1 || num > 6){
            printf("\nEl numero ingresado debe estar entre 1 y 6\n");
        }
    } while (num != 9999);
}

// cuerpo de las funciones y acciones.
bool Vacia(TData* data){
    // si la cantidad de elementos del arreglo es 0, devuelve verdadero.
    if ((*data).cant == 0){
        return true;
    }else{
        return false;
    }
}

bool Llena(TData* data){
    // si la cantidad de elementos del arrelgo es igual a NMAX, devuelve verdadero.
    if ((*data).cant == NMAX){
        return true;
    }else{
        return false;
    }
}

void Insertar(TData* data, char apellido[31]){
    // inserto el apellido ingresado por el usuario en el lugar correcto
    strcpy((*data).arreglo[(*data).cant], apellido);
    printf("\nSe ha registrado el nuevo empleado exitosamente\n");
    (*data).cant++; 
}

void Suprimir(TData* data,char apellido[31]){
    // muevo un lugar para atras todos los apellidos, pisando el apellido que queria borrar.
    for (int j = Encontrar(data,apellido); j < (*data).cant; j++){
        strcpy((*data).arreglo[j], (*data).arreglo[j + 1]);
    }
    printf("\nEl empleado fue dado de baja exitosamente\n");
    (*data).cant--;
}

void Modificar(TData* data, char apellido[31]){
    char apellidoM[31];
    
    printf("\nIngrese apellido modificado: ");
    scanf("%s", apellidoM);
    // uso la funcion Encontrar() para localizar el apellido a modificar
    Encontrar(data, apellido);
    // una vez encontrado, pongo el nuevo apellido en el lugar del antiguo apellido.
    strcpy((*data).arreglo[Encontrar(data, apellido)], apellidoM);
    printf("\nEl apellido ha sido modificado exitosamente\n");
}

void Mostrar(TData* data){
    // recorro el arreglo mostrando cada apellido.
    for (int i = 0; i < (*data).cant; i++){
        printf("- %s\n", (*data).arreglo[i]);
    }
}

int Encontrar(TData* data, char apellido[31]){
    // recorro el arreglo hasta que encuentro el apellido, luego devuelvo el indice en donde se encuentra.
    for (int i = 0; i < (*data).cant; i++){
        if(strcmp((*data).arreglo[i], apellido) == 0){
            return i;
        }
    }
    // codigo de error.
    return -1;
}

bool Repetidos(char apellido1[31], char apellido2[31]){
    // si ambos apellidos son iguales, devuelvo verdadero.
    if (strcmp(apellido1, apellido2) == 0){
        return true;
    }else{
        return false;
    }
}