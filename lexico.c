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
      printf("%i-", aux->caracter);
      aux = aux->sig;
    }
  }
}


int ES_ENTERO(struct cola * C){
  int e_actual = 0;
  char c;
  while(isEmpty(C)==0){
    //show_cola(C);
    c = desencolar(C);
    printf("%c\n", c);
    if (c == 43 || c == 45){
      e_actual = ENTERO[e_actual][0];
    }else if (c>=48 && c<=57) {
      e_actual = ENTERO[e_actual][1];
    }else{
      printf("entre aca\n" );
      return 0;
    }
  }

  printf("Estado actual post analisis %d\n", e_actual);
  if (ENTERO[e_actual][2]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

int ES_FLOAT(struct cola * C){
  int e_actual = 0;
  char c;
  while(isEmpty(C)==0){
    c = desencolar(C);
    if (c == 43 || c==45){
      e_actual = FLOAT[e_actual][0];
    }else if (c == 46) {
      e_actual = FLOAT[e_actual][1];
    }else if (c>=48 && c<=57) {
      e_actual = FLOAT[e_actual][2];
    }else{
      return 0;
    }
  }
  if (FLOAT[e_actual][3]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
}

int ES_STRING(struct cola * C){
  
  int e_actual = 0;
  char c;
  while(isEmpty(C)==0){
    c = desencolar(C);
    if (c == 34){
      e_actual = STRING[e_actual][0];
    }else if ((c>=97 && c<=122) || (c>=65 && c<=90) || ()) {
      e_actual = FLOAT[e_actual][2];
    }else{
      return 0;
    }
  }
  if (FLOAT[e_actual][3]==2){
    return 1;
  }else{
    return 0;
  }
  return 0;
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

  return 1;
}

int procesar(FILE * entrada, FILE * salida){
  int contador_palabras_procesadas =0;
  struct cola * C = crearCola();
  char caracter_actual = fgetc(entrada);
  while(caracter_actual != EOF){
    if(caracter_actual==32){
      printf("_SEPARADOR_");
      contador_palabras_procesadas++;
      show_cola(C);
    }else{
      C = encolar(C,caracter_actual);
      //printf("%c", caracter_actual);
    }
    caracter_actual = fgetc(entrada);
    printf("Se procesaron %d palabras\n", contador_palabras_procesadas);
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
        int i=0;
        for (i = 0; i < 6; i++) {
          printf("{ %d | %d | %d | %d }\n", FLOAT[i][0], FLOAT[i][1],FLOAT[i][2],FLOAT[i][3]);
        }
        struct cola * C = crearCola();
        C = encolar(C,43);
        C = encolar(C,49);
        //C = encolar(C,46);
        C = encolar(C,48);
        C = encolar(C,50);
        if(ES_ENTERO(C)){
          printf("Palabra es ENTERO\n" );
        }else{
          printf("Palabra NO ENTERO\n" );
        }
        //procesar(input,output);
        printf("\n");
        fclose(input);
        fclose(output);
        exit(0);
      }
    }
    exit(0);
}
