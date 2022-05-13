#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
  int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(!fscanf (file, "%d", &n->sudo[i][j]))
      {printf("failed to read data!");}
    }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
    {printf("%d ", n->sudo[i][j]);}
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node* n){
  int *vectorNum = (int*)calloc(10, sizeof(int));

  // Comprobar filas
  for(size_t i = 0; i < 9; i++)
  {
    for (size_t j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] != 0)
      {
        vectorNum[n->sudo[i][j]]++;
        if (vectorNum[n->sudo[i][j]] > 1){return 0;}
      }
    }
    free(vectorNum);
    vectorNum = (int*)calloc(10, sizeof(int));
  }
  
  // Comprobar columnas
  for(size_t i = 0; i < 9; i++)
  {
    for (size_t j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] != 0)
      {
        vectorNum[n->sudo[i][j]]++;
        if (vectorNum[n->sudo[i][j]] > 1){return 0;}
      }
    }
    free(vectorNum);
    vectorNum = (int*)calloc(10, sizeof(int));
  }

  // Comprobar cuadrantes
  for (size_t k = 0; k < 9; k++)
  { 
    for(size_t p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      if (n->sudo[i][j] != 0)
      {
        vectorNum[n->sudo[i][j]]++;
        if (vectorNum[n->sudo[i][j]] > 1){return 0;}
      }
    }
    free(vectorNum);
    vectorNum = (int*)calloc(10, sizeof(int));
  }
  
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for (size_t i = 0; i < 9; i++)
  {
    for (size_t j= 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        for (size_t k = 1; k < 10; k++)
        {
          n->sudo[i][j] = k;
          if (is_valid(n))
          {
            Node* adj = copy(n);
            push(list, adj);
          }
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  if (!is_valid(n)){return 0;}
  
  printf("\n\n\n");
  for (size_t i = 0; i < 9; i++){
    printf("\n");
    for (size_t j = 0; j < 9; j++){
      printf("%d ", n->sudo[i][j]);
      if (n->sudo[i][j] == 0){return 0;}
    }  
  }
  printf("\n");printf("\n");
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while (get_size(S) != 0){
    Node* n = top(S); pop(S);

    if (is_final(n) == 1){return n;}
    

    //visitar nodo
    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    while(aux){
      push(S,aux);
      aux=next(adj);
    }
    free(n);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/