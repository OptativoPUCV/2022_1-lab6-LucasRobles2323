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
      if (n->sudo[i][j] != 0;)
      {
        vectorNum[n->sudo[i][j]]++;
      }
      if (vectorNum[n->sudo[i][j]] > 1)
      {
        return 0;
      }
    }
    free(vectorNum);
    int *vectorNum = (int*)calloc(10, sizeof(int));
  }

  
  
  // Comprobar columnas

  // Comprobar cuadrantes
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
  return 0;
}

Node* DFS(Node* initial, int* cont){
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