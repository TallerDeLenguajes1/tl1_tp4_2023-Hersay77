#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct {
    Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;

//funciones
Nodo *CrearListaVacia();
Nodo * CrearNodo(int *id, char *buff);
void InsertarNodo(Nodo ** Start , Nodo *nodo);
void MostrarNodos(Nodo **Start);
Nodo * BuscarNodo(Nodo ** Start,int ID); //FUNCION BUSCAR TAREA POR ID
void EliminarNodo(Nodo **Start, int ID); //FUNCION ELIMNAR TAREA POR ID
void DesvincularNodo(Nodo **Start, int ID);//FUNCION DESVINCULAR NODO DE LISTA
void mostrarUnNodo(Nodo * nodo);
Nodo * BuscarNodoPorPalabra(Nodo ** Start, char * palabra); //FUNCION BUSCAR NODO POR PALABRA CLAVE

int main(){
    int opcion, continuar, id=1000, idAux;
    Nodo *NodoAux = (Nodo *)malloc(sizeof(Nodo)); //creo un puntero auxiliar a un nodo para usarlo en opciones de eliminar, marcar como realizada

    char * buff = (char *)malloc(sizeof(char) * 100);

    srand(time(NULL)); //para numeros aleatorios

    //Creacion de listas vacias de pendientes y realizadas
    Nodo *TareasPendientes = CrearListaVacia(); 
    Nodo *TareasRealizadas = CrearListaVacia(); 
    
    //menu
    do
    {
        printf("\n****MENU INTERACTIVO****\n");
        printf("Opcion 1 -> Cargar Una Tarea Pendiente\n"); //1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes
        printf("Opcion 2 -> Borrar Una Tarea Pendiente\n"); 
        printf("Opcion 3 -> Marcar una Tarea Pendiente como realizada\n");//2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser transferidas a la lista de tareas realizadas.
        printf("Opcion 4 -> Borrar una Tarea Realizada\n");
        printf("Opcion 5 -> Mostrar Tareas Pendientes y Realizadas\n"); //3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.
        printf("Opcion 6 -> Buscar una tarea por palabra"); //4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.
        printf("\nOpcion 7 -> Salir");
        printf("\nIngrese opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            do
            {
                printf("\n***Cargando Tarea***");
                Nodo * NuevaTarea =  CrearNodo(&id, buff); //creo nodo, el id es argumento como puntero asi poder editarlo cada vez que se crea una nueva tarea
                InsertarNodo(&TareasPendientes, NuevaTarea); //envio el puntero al inicio de la lista y el nuevo nodo (tarea)
                printf("\nDesea cargar otra tarea? ingrese '1' para continuar: ");
                scanf("%d", &continuar);

            } while (continuar == 1);
            opcion = 0;
            break;
        case 2:
            do
            {
                printf("\n***Borrando Tarea***");
                
                if (TareasPendientes)
                {
                    printf("\n****Lista de Tareas Pendientes*****\n");
                    MostrarNodos(&TareasPendientes);

                    printf("\nIngrese ID de Tarea a borrar: ");
                    scanf("%d", &idAux);

                    NodoAux = BuscarNodo(&TareasPendientes,idAux);
                    if (NodoAux)
                    {
                        printf("\nEliminar la tarea: %s? ingrese '1' para si: ", NodoAux->T.Descripcion);
                        scanf("%d", &opcion);
                        if (opcion == 1)
                        {
                            EliminarNodo(&TareasPendientes, idAux);
                            printf("\nTarea Eliminada");
                        }
                        else
                        {
                            printf("\nCancelado");
                        }
                    }
                    else
                    {
                        printf("\nTarea no encontrada");
                    }               

                    printf("\n****Lista de Tareas Pendientes*****\n");
                    MostrarNodos(&TareasPendientes);

                    printf("\nDesea borrar otra tarea ? ingrese '1' para continuar borrando: ");
                    scanf("%d", &continuar);
                }
                else
                {
                    printf("\nNo hay tareas para eliminar");
                    continuar = 0;
                }

            } while (continuar == 1);
            opcion = 0;
            break;
        case 3:
            do
            {
                printf("\n***Marcar Tarea como realizada***");
                
                if (TareasPendientes)
                {
                    printf("\n****Lista de Tareas Pendientes*****\n");
                    MostrarNodos(&TareasPendientes);

                    printf("\nIngrese ID de Tarea a marcar como realizada: ");
                    scanf("%d", &idAux);

                    NodoAux = BuscarNodo(&TareasPendientes,idAux);
                    if (NodoAux)
                    {
                        printf("\nMarcar la tarea: %s como realizada? ingrese '1' para si: ", NodoAux->T.Descripcion);
                        scanf("%d", &opcion);
                        if (opcion == 1)
                        {
                            DesvincularNodo(&TareasPendientes, idAux);
                            InsertarNodo(&TareasRealizadas , NodoAux);
                            printf("\nTarea marcada como Realizada");
                        }
                        else
                        {
                            printf("\nCancelado");
                        }
                    }
                    else
                    {
                        printf("\nTarea no encontrada");
                    }               

                    printf("\n****Lista de Tareas Pendientes*****\n");
                    MostrarNodos(&TareasPendientes);
                    printf("\n****Lista de Tareas Realizadas*****\n");
                    MostrarNodos(&TareasRealizadas);

                    printf("\nDesea marcar otra tarea? ingrese '1' para continuar marcando: ");
                    scanf("%d", &continuar);
                }
                else
                {
                    printf("\nNo hay tareas para marcar");
                    continuar = 0;
                }

            } while (continuar == 1);
            opcion = 0;
            break;
        case 4:
            do
            {
                printf("\n***Borrando Tarea***");
                if (TareasRealizadas)
                {
                    printf("\n****Lista de Tareas Realizadas*****\n");
                    MostrarNodos(&TareasRealizadas);

                    printf("\nIngrese ID de Tarea a borrar: ");
                    scanf("%d", &idAux);

                    NodoAux = BuscarNodo(&TareasRealizadas,idAux);
                    if (NodoAux)
                    {
                        printf("\nEliminar la tarea: %s? ingrese '1' para si: ", NodoAux->T.Descripcion);
                        scanf("%d", &opcion);
                        if (opcion == 1)
                        {
                            EliminarNodo(&TareasRealizadas, idAux);
                            printf("\nTarea Eliminada");
                        }
                        else
                        {
                            printf("\nCancelado");
                        }
                    }
                    else
                    {
                        printf("\nTarea no encontrada");
                    }               

                    printf("\n****Lista de Tareas Realizadas*****\n");
                    MostrarNodos(&TareasRealizadas);

                    printf("\nDesea borrar otra tarea ? ingrese '1' para continuar borrando: ");
                    scanf("%d", &continuar);
                }
                else
                {
                    printf("\nNo hay tareas para eliminar");
                    continuar = 0;
                }

            } while (continuar == 1);
            opcion = 0;
            break;
        case 5:
            printf("\n****Lista de Tareas Pendientes*****\n");
            MostrarNodos(&TareasPendientes);
            printf("\n****Lista de Tareas Realizadas*****\n");
            MostrarNodos(&TareasRealizadas);   
            opcion = 0;
            break;
        case 6:
            do
            {
                if (TareasPendientes || TareasRealizadas)
                {
                    printf("\n****Busqueda de Tarea por palabra clave o Id****");
                    printf("\nIngrese 1 para buscar por Id o ingrese 2 para buscar por Palabra clave: ");
                    scanf("%d", &opcion);
                    switch (opcion)
                    {
                    case 1:
                        printf("\nIngrese id a buscar: ");
                        scanf("%d", &idAux);
                        NodoAux = BuscarNodo(&TareasPendientes, idAux);
                        if (NodoAux)
                        {
                            printf("\nTarea encontrada en Tareas Pendientes: ");
                            mostrarUnNodo(NodoAux);
                        }
                        else
                        {
                            NodoAux = BuscarNodo(&TareasRealizadas, idAux);
                            if (NodoAux)
                            {
                                printf("\nTarea encontrada en Tareas Realizadas: ");
                                mostrarUnNodo(NodoAux);
                            }
                            else
                            {
                                printf("\nTarea no encontrada");
                            }
                        }
                        break;
                    case 2:
                        printf("\nIngrese palabra clave a buscar: ");
                        fflush(stdin);
                        gets(buff);
                        fflush(stdin);
                        NodoAux = BuscarNodoPorPalabra(&TareasPendientes, buff);
                        if (NodoAux)
                        {
                            printf("\nTarea encontrada en Tareas Pendientes: ");
                            mostrarUnNodo(NodoAux);
                        }
                        else
                        {
                            NodoAux = BuscarNodoPorPalabra(&TareasRealizadas, buff);
                            if (NodoAux)
                            {
                                printf("\nTarea encontrada en Tareas Realizadas: ");
                                mostrarUnNodo(NodoAux);
                            }
                            else
                            {
                                printf("\nTarea no encontrada");
                            }
                        }
                        break;
                    default:
                        printf("\nOpcion ingresada incorrecta");
                        break;
                    }
                    
                }
                else
                {
                    printf("\nLas listas se enuentran Vacias");
                }

                printf("\nDesea continuar buscando? ingrese '1' para si: ");  
                scanf("%d", &continuar);              
                
            } while (continuar == 1);
            opcion = 0;
            break;
        case 7:
            opcion= 7; //sale del bulcle
            break;
        default:
            break;
        }      

    } while (opcion <1 || opcion > 7);
    
    free(buff);
    free(NodoAux);
    return 0;
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(int *id,char *buff)
{
  Nodo * nodo = (Nodo *) malloc(sizeof(Nodo));
  nodo->T.TareaID = (*id)++; //id autoincremental comenzando desde 1000
  nodo->T.Duracion = rand()% (91) + 10;  // duracion entre 100 y 10
  printf("\nIngrese una descripcion de la Tarea: ");
  fflush(stdin);
  gets(buff); //la descripcion se recibe en el buff 
  nodo->T.Descripcion = (char *)malloc(sizeof(char)*(strlen(buff))+1); //a descripcion se le asigna memoria segun la longitud del buff
  strcpy(nodo->T.Descripcion, buff); //copio lo del buff en descripcion
  return nodo;
}

void InsertarNodo(Nodo ** Start , Nodo *nodo){
    nodo->Siguiente = *Start; //el nuevo nodo ahora apunta al nodo que estaba al inicio
    *Start  = nodo ; //el inicio ahora apunta al nuevo nodo
}

void MostrarNodos(Nodo **Start)
{
    Nodo * Aux = * Start; //CREO PUNTERO AUXILIAR PARA RECORRER LISTA, RECIBE EL PUNTERO AL INICIO DE LA LISTA *Star 
    if (Aux == NULL)
    {
        printf("\nLista Vacia\n");
    }
    else
    {
        while(Aux) //mientras la direccion que contiene aux no es null
        {
            printf("\nTarea ID: %d\n", Aux->T.TareaID);
            printf("Descripcion: %s\n", Aux->T.Descripcion);
            printf("Duracion: %d\n", Aux->T.Duracion);
            Aux = Aux->Siguiente; //muevo al siguiente nodo
        };
    }
    
};

Nodo * BuscarNodo(Nodo ** Start,int ID)
{
  Nodo * Aux = *Start;
  while (Aux && Aux->T.TareaID != ID)
  {
    Aux = Aux->Siguiente;
  }
  return Aux;
}

void EliminarNodo(Nodo **Start, int ID) {
    Nodo ** aux = Start;  // Usamos un puntero doble para apuntar al puntero actual.
    
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
    while (*aux != NULL && (*aux)->T.TareaID != ID) {
        aux = &(*aux)->Siguiente;
    }

    // Si encontramos el nodo con el dato especificado, lo eliminamos.
    if (*aux) {
        Nodo *temp = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
        free(temp);  // Liberamos la memoria ocupada por el nodo.
    }
}

void DesvincularNodo(Nodo **Start, int ID) {
    Nodo ** aux = Start;  // Usamos un puntero doble para apuntar al puntero actual.
    
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
    while (*aux != NULL && (*aux)->T.TareaID != ID) {
        aux = &(*aux)->Siguiente;
    }

    // Si encontramos el nodo con el dato especificado, lo eliminamos.
    if (*aux) {
        *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
    }
}

void mostrarUnNodo(Nodo * nodo){
    printf("\nTarea ID: %d" , nodo->T.TareaID);
    printf("\nDescripcion: %s",nodo->T.Descripcion);
    printf("\nDuracion: %d\n", nodo->T.Duracion);
}

Nodo * BuscarNodoPorPalabra(Nodo ** Start, char * palabra){
    Nodo * Aux = *Start;
    while (Aux && strcmp(Aux->T.Descripcion, palabra) != 0)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}
