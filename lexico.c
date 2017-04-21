#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estructura nodo
typedef struct nodo{
    char caracter;
    struct nodo * sig;
}Nodo;

//Estructura Cola
typedef struct cola{
  struct nodo * first;
  struct nodo * last;
}Cola;


//Matrices que representan a los automatas que reconocen ENTEROS, STRINGS, OPERADORES: ASIGNACION, ARITMETICO, LOGICO, RELACIONAL
int FLOAT[6][4];
int ENTERO[2][3];
int STRING[4][3];
int ASIGNACION[3][3];
int ARITMETICO[3][2];
int LOGICO[8][7];
int RELACIONAL[5][4];

/*
RESUMEN: Funcion encargada de inicializar un nodo con un caracter
ENTRADA: new_caracter = Numero en represntacion ascii del caracter
SALIDA: un puntero a la estructura inicializada
*/
struct nodo * crearNodo(char new_caracter){
  struct nodo * new = (struct nodo *)malloc(sizeof(struct nodo));
  new->caracter = new_caracter;
  new->sig = NULL;
  return new;
}

/*
RESUMEN: Funcion encargada de inicializar una cola vacía
ENTRADA: sin argumentos
SALIDA: un puntero a la estructura inicializada
*/
struct cola * crearCola(){
  struct cola * new = (struct cola *)malloc(sizeof(struct cola));
  new->first=NULL;
  new->last=NULL;
  return new;
}

/*
RESUMEN: Funcion encargada de determinar si una cola esta vacía
ENTRADA: C = Un puntero a una estructura cola
SALIDA: Retorna 1 si la cola está vacía y un 0 si no lo está
*/
int isEmpty(struct cola * C){
  if(C==NULL){
    return 1;
  }else{
    if(C->first==NULL && C->last==NULL){
      return 1;
    }else{
      return 0;
    }
  }
}

/*
RESUMEN: Funcion encargada de agregar un caracter al final de una cola, encolar
ENTRADA: C = Un puntero a una estructura cola
          new_caracter = valor ascii del caracter
SALIDA: un puntero a la estructura cola modificada
*/
struct cola * encolar(struct cola * C, char new_caracter){
  if(isEmpty(C)==1){
    struct nodo * nuevo = crearNodo(new_caracter);
    C->last = nuevo;
    C->first = nuevo;
    return C;
  }else{
    C->last->sig = crearNodo(new_caracter);
    C->last = C->last->sig;
    return C;
  }
}

/*
RESUMEN: Función encargada de eliminar o desencolar un caracter del inicio de una cola.
ENTRADA: C = Un puntero a una estructura cola
SALIDA: el valor ascii del caracter extraido
*/
char desencolar(struct cola * C ){
  if(isEmpty(C)==1){
    return -1;
  }else{
    struct nodo * aux = C->first;
    char first_caracter = C->first->caracter;
    if(aux->sig == NULL){
      C->first = NULL;
      C->last = NULL;
      free(aux);
    }else{
        C->first = C->first->sig;
        free(aux);
    }
    return first_caracter;
  }
}

/*
RESUMEN: Función encargada de sacar o vaciar todos los caracteres de una cola
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna 0 como reflejo del exito de la operacion
*/
int vaciar_cola(struct cola* C){
  while(isEmpty(C)==0){
    desencolar(C);
  }
  return 0;
}

/*
RESUMEN: Función encargada de mostrar por consola una cola, o más bien una palabra.
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna 0 como reflejo del exito de la operacion
*/
int show_cola(struct cola * C){
  if(isEmpty(C)==1){
    printf("Empty query\n" );
  }else{
    struct nodo * aux = C->first;
    while(aux!= NULL){
      printf("%c", aux->caracter);
      aux = aux->sig;
    }
    printf("\n" );
  }
  return 0;
}

/*
RESUMEN: Función encargada de copiar los caracteres de una pila original a una nueva
ENTRADA: C = Un puntero a una estructura cola
SALIDA: un puntero a la estructura copiada
*/
struct cola * copy_cola(struct cola * original){
  struct nodo * aux = NULL;
  struct cola * copia = crearCola();
  aux = original->first;
  while(aux!=NULL){
    copia = encolar(copia, aux->caracter);
    aux = aux->sig;
  }
  return copia;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un ENTERO
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es ENTERO, o un 0 en el caso de no serlo
*/
int ES_ENTERO(struct cola * C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 43 || c == 45){
      e_actual = ENTERO[e_actual][0];
    }else if (c>=48 && c<=57) {
      e_actual = ENTERO[e_actual][1];
    }else{
      return 0;
    }
  }
  if (ENTERO[e_actual][2]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un STRING
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es STRING, o un 0 en el caso de no serlo
*/
int ES_STRING(struct cola * C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 34){
      e_actual = STRING[e_actual][0];
    }else if ((c>=32 && c<=33) || (c>=35 && c<=126)) {
      e_actual = STRING[e_actual][1];
    }else{
      return 0;
    }

  }
  if (STRING[e_actual][2]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un ASIGNACION
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es ASIGNACION, o un 0 en el caso de no serlo
*/
int ES_ASIGNACION(struct cola * C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 61){
      e_actual = ASIGNACION[e_actual][1];
    }else if (c == 60 || c == 62) {
      e_actual = ASIGNACION[e_actual][0];
    }else{
      return 0;
    }
  }
  if (ASIGNACION[e_actual][2]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un ARITMETICO
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es ARITMETICO, o un 0 en el caso de no serlo
*/
int ES_ARITMETICO(struct cola * C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 42 || c==43 || c==45 || c ==47){
      e_actual = ARITMETICO[e_actual][0];
    }else{
      return 0;
    }

  }
  if (ARITMETICO[e_actual][1]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un RELACIONAL
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es RELACIONAL, o un 0 en el caso de no serlo
*/
int ES_RELACIONAL(struct cola * C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 61){
      e_actual = RELACIONAL[e_actual][0];
    }else if ( c == 60 ) {
      e_actual = RELACIONAL[e_actual][1];
    }else if ( c == 62 ) {
      e_actual = RELACIONAL[e_actual][2];
    }
  }
  if (RELACIONAL[e_actual][3]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de determinar si la palabra en la cola es un LOGICO
ENTRADA: C = Un puntero a una estructura cola
SALIDA: retorna un 1 si la palabra es LOGICO, o un 0 en el caso de no serlo
*/
int ES_LOGICO(struct cola *C){
  int e_actual = 0;
  char c;
  struct cola * copia = copy_cola(C);
  while(isEmpty(copia)==0){
    c = desencolar(copia);
    if (c == 78){
      e_actual = LOGICO[e_actual][0];
    }else if ( c==79 ) {
      e_actual = LOGICO[e_actual][1];
    }else if ( c==84 ) {
      e_actual = LOGICO[e_actual][2];
    }else if (c==68) {
      e_actual = LOGICO[e_actual][3];
    }else if (c==82) {
      e_actual = LOGICO[e_actual][4];
    }else if (c==65) {
      e_actual = LOGICO[e_actual][5];
    }
  }
  if (LOGICO[e_actual][6]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

/*
RESUMEN: Función encargada de escribir en un archivo, los caracteres de una cola
ENTRADA:file = puntero al archivo en formato escritura
        C = Un puntero a una estructura cola
SALIDA: retorna 1 como reflejo del exito de la operacion
*/
int escribirArchivo(FILE * file, struct cola * C){
  struct cola * cp = copy_cola(C);
  char c;
  while(isEmpty(cp)==0){
    c = desencolar(cp);
    fputc(c,file);
  }
  return 0;
}

/*
RESUMEN: Función encargada de preprocesar los datos necesarios en los automatas para aceptar las palabras de este programa
  esta información se obtuvo en base a la creación de estos automatas usando la teoría enseñada en clases, con AFD
ENTRADA: sin argumentos
SALIDA: retorna 0 como reflejo del exito de la operacion
*/
int preprocesar(){
  //Matriz de AFD para ENTERO
  /*
  A INICIAL
  A=0   +-= 0
  B=1   [0-9]= 1
        FINAL = 2
  */
  ENTERO[0][0]=1;
  ENTERO[0][1]=1;
  ENTERO[0][2]=1;
  ENTERO[1][0]=1;
  ENTERO[1][1]=1;
  ENTERO[1][2]=2;

  //Matriz de AFD para STRING
  /*
  A INICIAL
  A=0   " = 0
  B=1   [a-zA-Z0-9]= 1
  C=2      FINAL = 2
  D=3
  E=4
  */
  STRING[0][0]=1;
  STRING[0][1]=3;
  STRING[0][2]=1;
  STRING[1][0]=2;
  STRING[1][1]=1;
  STRING[1][2]=0;
  STRING[2][0]=3;
  STRING[2][1]=3;
  STRING[2][2]=2;
  STRING[3][0]=3;
  STRING[3][1]=3;
  STRING[3][2]=0;

  //Matriz de AFD para ASIGNACION
  /*
  A INICIAL
  A=0   <> = 0
  B=1   = = 1
  C=2
  */
  ASIGNACION[0][0]=2;
  ASIGNACION[0][1]=1;
  ASIGNACION[0][2]=1;
  ASIGNACION[1][0]=1;
  ASIGNACION[1][1]=2;
  ASIGNACION[1][2]=2;
  ASIGNACION[2][0]=2;
  ASIGNACION[2][1]=2;
  ASIGNACION[2][2]=0;

  //Matriz de AFD para ARITMETICO
  /*
  A INICIAL
  A=0   +,-,/,* = 0
  B=1   FINAL = 2

  */
  ARITMETICO[0][0]=1;
  ARITMETICO[0][1]=1;
  ARITMETICO[1][0]=1;
  ARITMETICO[1][1]=2;
  ARITMETICO[2][0]=2;
  ARITMETICO[2][1]=0;

  //Matriz de AFD para RELACIONAL
  /*
  A INICIAL
  A=0   = = 0
  B=1   < = 1
  C=2   > = 2
  D=3   FINAL = 2
  E=4

  */
  RELACIONAL[0][0]=3;
  RELACIONAL[0][1]=2;
  RELACIONAL[0][2]=1;
  RELACIONAL[0][3]=1;
  RELACIONAL[1][0]=3;
  RELACIONAL[1][1]=4;
  RELACIONAL[1][2]=4;
  RELACIONAL[1][3]=2;
  RELACIONAL[2][0]=3;
  RELACIONAL[2][1]=4;
  RELACIONAL[2][2]=3;
  RELACIONAL[2][3]=2;
  RELACIONAL[3][0]=4;
  RELACIONAL[3][1]=4;
  RELACIONAL[3][2]=4;
  RELACIONAL[3][3]=2;
  RELACIONAL[4][0]=4;
  RELACIONAL[4][1]=4;
  RELACIONAL[4][2]=4;
  RELACIONAL[4][3]=0;

  //Matriz de AFD para LOGICO
  /*
  A INICIAL
  A=0   N = 0
  B=1   O = 1
  C=2   T = 2
  D=3   D = 3
  E=4   R = 4
  F=5   A = 5
  G=6   FINAL = 2


  */
  LOGICO[0][0]=1;
  LOGICO[0][1]=6;
  LOGICO[0][2]=7;
  LOGICO[0][3]=7;
  LOGICO[0][4]=7;
  LOGICO[0][5]=4;
  LOGICO[0][6]=1;
  LOGICO[1][0]=7;
  LOGICO[1][1]=2;
  LOGICO[1][2]=7;
  LOGICO[1][3]=7;
  LOGICO[1][4]=7;
  LOGICO[1][5]=7;
  LOGICO[1][6]=0;
  LOGICO[2][0]=7;
  LOGICO[2][1]=7;
  LOGICO[2][2]=3;
  LOGICO[2][3]=7;
  LOGICO[2][4]=7;
  LOGICO[2][5]=7;
  LOGICO[2][6]=0;
  LOGICO[3][0]=7;
  LOGICO[3][1]=7;
  LOGICO[3][2]=7;
  LOGICO[3][3]=7;
  LOGICO[3][4]=7;
  LOGICO[3][5]=7;
  LOGICO[3][6]=2;
  LOGICO[4][0]=5;
  LOGICO[4][1]=7;
  LOGICO[4][2]=7;
  LOGICO[4][3]=7;
  LOGICO[4][4]=7;
  LOGICO[4][5]=7;
  LOGICO[4][6]=0;
  LOGICO[5][0]=7;
  LOGICO[5][1]=7;
  LOGICO[5][2]=7;
  LOGICO[5][3]=3;
  LOGICO[5][4]=7;
  LOGICO[5][5]=7;
  LOGICO[5][6]=0;
  LOGICO[6][0]=7;
  LOGICO[6][1]=7;
  LOGICO[6][2]=7;
  LOGICO[6][3]=7;
  LOGICO[6][4]=3;
  LOGICO[6][5]=7;
  LOGICO[6][6]=0;
  LOGICO[7][0]=7;
  LOGICO[7][1]=7;
  LOGICO[7][2]=7;
  LOGICO[7][3]=7;
  LOGICO[7][4]=7;
  LOGICO[7][5]=7;
  LOGICO[7][6]=0;

  return 0;
}

/*
RESUMEN: Función encargada de procesar el texto de entrada para copiarlo al texto de salida,
  aplicando las funciones antes mencionadas e intercambiando los lexemas por sus correspondientes componentes léxicos
ENTRADA:  entrada = puntero al archivo de entrada
          salida = puntero al archivo de salida
SALIDA: retorna un 0 como reflejo del exito de la operacion
*/
int procesar(FILE * entrada, FILE * salida){
  //Cola que almacena los caracteres de una palabra separada por espacios, tabulaciones o saltos de linea
  struct cola * COLA_NORMAL = crearCola();
  //En caso de abrirse una comilla esta cola almacena los caracteres del posible string antes de pasarlo por el automata y revisarlo
  struct cola * COLA_STRING = crearCola();
  char caracter_actual = fgetc(entrada);
  //Este contador ayuda a tener la referencia de la apertura y cierre de comillas para los strings
  int contador_comillas = 0;
  //Lectura del archivo caracter por caracter
  while(caracter_actual != EOF){
    if (caracter_actual != 32 && caracter_actual != 10 && caracter_actual != 9){
      COLA_NORMAL = encolar(COLA_NORMAL,caracter_actual);
      if(caracter_actual == 34){
        contador_comillas++;
        //Agrega la comilla inicial
        COLA_STRING = encolar(COLA_STRING,caracter_actual);
      }
      if(contador_comillas==1){
        //Agrega los caracteres dentro de las comillas
        COLA_STRING = encolar(COLA_STRING,caracter_actual);
      }
      if (contador_comillas ==2) {
        contador_comillas = 0;
        //Agrega la comilla final
        COLA_STRING = encolar(COLA_STRING,caracter_actual);
        if (ES_STRING(COLA_STRING)){
          fprintf(salida, "STRING%c",caracter_actual );
          vaciar_cola(COLA_STRING);
          vaciar_cola(COLA_NORMAL);
        }
      }
    }else if((caracter_actual== 32 || caracter_actual == 10 || caracter_actual == 9)){
      if(contador_comillas == 1 && caracter_actual == 32){
        //Agrega los caracteres ESPACIO dentro de las comillas
        COLA_STRING = encolar(COLA_STRING,caracter_actual);
      }else if (contador_comillas == 0 ){
        //Palabras no son string, FUERA DE COMILLAS
        if(ES_ENTERO(COLA_NORMAL)){
          fprintf(salida,"ENTERO%c",caracter_actual);
          vaciar_cola(COLA_NORMAL);
        }else if (ES_ASIGNACION(COLA_NORMAL)) {
          fprintf(salida, "ASIGNACION%c",caracter_actual);
          vaciar_cola(COLA_NORMAL);
        }else if (ES_RELACIONAL(COLA_NORMAL)) {
          fprintf(salida,"RELACIONAL%c",caracter_actual);
          vaciar_cola(COLA_NORMAL);
        }else if (ES_LOGICO(COLA_NORMAL)) {
          fprintf(salida,"LOGICO%c",caracter_actual);
          vaciar_cola(COLA_NORMAL);
        }else if (ES_ARITMETICO(COLA_NORMAL)) {
          fprintf(salida,"ARITMETICO%c",caracter_actual);
          vaciar_cola(COLA_NORMAL);
        }else if (ES_STRING(COLA_NORMAL)){
          fprintf(salida, "STRING%c",caracter_actual );
          vaciar_cola(COLA_NORMAL);
        }else{
          COLA_NORMAL = encolar(COLA_NORMAL,caracter_actual);
          escribirArchivo(salida,COLA_NORMAL);
          vaciar_cola(COLA_NORMAL);
        }
      }
    }
    caracter_actual = fgetc(entrada);
    }
    return 0;
}



int main(int  argc, char * argv[]){
    FILE * input = NULL;
    FILE * output = NULL;
    char * uso ="Uso: lexico.exe archivo_entrada archivo_salida\n";
    char * faltan_parametros = "Error: Faltan parametros en la linea de comandos.\n";
    char * demasiados_parametros = "Error: Demasiados parametros en la linea de comandos.\n";
    char * out_ya_existe = "Error: El archivo de salida ya existe.\n";
    char * in_no_existe= "Error: El archivo de entrada no existe.\n";
    if (argc <= 2){
      printf("%s\n", faltan_parametros);
      printf("%s\n", uso);
      exit(1);
    }else if (argc > 3) {
      printf("%s\n", demasiados_parametros);
      printf("%s\n", uso);
      exit(1);
    } else {
      input = fopen(argv[1],"r");
      output = fopen(argv[2],"r");
      if(input == NULL){
        //Archivo de entrada no existe
        printf("%s", in_no_existe);
        fclose(output);
        fclose(input);
        exit(1);
      }else if (output != NULL) {
        //Archivo de salida ya existe
        printf("%s\n", out_ya_existe);
        fclose(output);
        fclose(input);
        exit(1);
      }else{
        //Ejecución de proceso de análisis
        output = fopen(argv[2],"w");
        preprocesar();
        procesar(input,output);
        fclose(input);
        fclose(output);
        exit(0);
      }
    }
    exit(0);
}
