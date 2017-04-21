#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct nodo{
    char caracter;
    struct nodo * sig;
}Nodo;

typedef struct cola{
  struct nodo * first;
  struct nodo * last;
}Cola;

int FLOAT[6][4];
int ENTERO[2][3];
int STRING[4][3];
int ASIGNACION[3][3];
int ARITMETICO[3][2];
int LOGICO[8][7];
int RELACIONAL[5][4];

struct nodo * crearNodo(char new_caracter){
  struct nodo * new = (struct nodo *)malloc(sizeof(struct nodo));
  new->caracter = new_caracter;
  new->sig = NULL;
  return new;
}

struct cola * crearCola(){
  struct cola * new = (struct cola *)malloc(sizeof(struct cola));
  new->first=NULL;
  new->last=NULL;
  return new;
}

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

char desencolar(struct cola * C ){
  if(isEmpty(C)==1){
    return -1;
  }else{
    //printf("Al desencolar se tiene C->first %c\n", C->first->caracter);
    //printf("Al desencolar se tiene C->last %c\n", C->last->caracter);
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

int vaciar_cola(struct cola* C){
  while(isEmpty(C)==0){
    desencolar(C);
  }
  return 1;
}

char show_cola(struct cola * C){
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
}

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

int escribirArchivo(FILE * file, struct cola * C){
  struct cola * cp = copy_cola(C);
  char c;
  while(isEmpty(cp)==0){
    c = desencolar(cp);
    fputc(c,file);
  }
}

int preprocesar(){
  //Matriz de AFD para FLOAT
  /*
  A INICIAL
  A=0   +-= 0
  B=1   . = 1
  C=2   [0-9]= 2
  D=3   FINAL = 3
  E=4
  F=5
  */
  FLOAT[0][0]=1;
  FLOAT[0][1]=2;
  FLOAT[0][2]=3;
  FLOAT[0][3]=1;
  FLOAT[1][0]=-1;
  FLOAT[1][1]=2;
  FLOAT[1][2]=3;
  FLOAT[1][3]=0;
  FLOAT[2][0]=-1;
  FLOAT[2][1]=-1;
  FLOAT[2][2]=4;
  FLOAT[2][3]=0;
  FLOAT[3][0]=-1;
  FLOAT[3][1]=5;
  FLOAT[3][2]=3;
  FLOAT[3][3]=0;
  FLOAT[4][0]=-1;
  FLOAT[4][1]=-1;
  FLOAT[4][2]=4;
  FLOAT[4][3]=2;
  FLOAT[5][0]=-1;
  FLOAT[5][1]=-1;
  FLOAT[5][2]=4;
  FLOAT[5][3]=2;

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

  return 1;
}

int procesar(FILE * entrada, FILE * salida){
  struct cola * COLA_NORMAL = crearCola();
  struct cola * COLA_STRING = crearCola();
  char caracter_actual = fgetc(entrada);
  char caracter_previo_palabra;
  caracter_previo_palabra = caracter_actual;
  int contador_comillas = 0;
  while(caracter_actual != EOF){
    if (contador_comillas == 0 && caracter_actual != 32 && caracter_actual != 10 && caracter_actual != 9){
      COLA_NORMAL = encolar(COLA_NORMAL,caracter_actual);
    }else if(contador_comillas == 0 && (caracter_actual== 32 || caracter_actual == 10 || caracter_actual == 9)){
      if(ES_ENTERO(COLA_NORMAL)){
        //show_cola(COLA_NORMAL);
        fprintf(salida,"ENTERO%c",caracter_actual);
        vaciar_cola(COLA_NORMAL);
      }else if (ES_ASIGNACION(COLA_NORMAL)) {
        //show_cola(COLA_NORMAL);
        fprintf(salida, "ASIGNACION%c",caracter_actual);
        vaciar_cola(COLA_NORMAL);
      }else if (ES_RELACIONAL(COLA_NORMAL)) {
        //show_cola(COLA_NORMAL);
        fprintf(salida,"RELACIONAL%c",caracter_actual);
        vaciar_cola(COLA_NORMAL);
      }else if (ES_LOGICO(COLA_NORMAL)) {
        //show_cola(COLA_NORMAL);
        fprintf(salida,"LOGICO%c",caracter_actual);
        vaciar_cola(COLA_NORMAL);
      }else if (ES_ARITMETICO(COLA_NORMAL)) {
        //show_cola(COLA_NORMAL);
        fprintf(salida,"ARITMETICO%c",caracter_actual);
        vaciar_cola(COLA_NORMAL);
      }else if (ES_STRING(COLA_NORMAL)){
        //printf("STRING" );
        fprintf(salida, "STRING%c",caracter_actual );
        vaciar_cola(COLA_NORMAL);
      }else{
        COLA_NORMAL = encolar(COLA_NORMAL,caracter_actual);
        escribirArchivo(salida,COLA_NORMAL);
        vaciar_cola(COLA_NORMAL);
      }

    }
    //show_cola(COLA_STRING);
    show_cola(COLA_NORMAL);
    caracter_actual = fgetc(entrada);
    }
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
        printf("Analizando texto %s, copiando a %s\n",argv[1],argv[2] );
        preprocesar();
        procesar(input,output);
        fclose(input);
        fclose(output);
        exit(0);
      }
    }
    exit(0);
}
