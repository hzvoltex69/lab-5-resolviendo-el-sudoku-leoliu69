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
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k, p;
  int check[10];

  for(i = 0; i < 9; i++){
    for(j = 0; j < 10; j++) check[j] = 0;
    for(j = 0; j < 9; j++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(check[num] == 1) return 0;
        check[num] = 1;
      }
    }
  }

  for(j = 0; j < 9; j++){
    for(i = 0; i < 10; i++) check[i] = 0;
    for(i = 0; i < 9; i++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(check[num] == 1) return 0;
        check[num] = 1;
      }
    }
  }

  for(k = 0; k < 9; k++){
    for(i = 0; i < 10; i++) check[i] = 0;
    for(p = 0; p < 9; p++){
        int row = 3*(k/3) + (p/3);
        int col = 3*(k%3) + (p%3);
        int num = n->sudo[row][col];
        if(num != 0){
        if(check[num] == 1) return 0;
        check[num] = 1;
      }  
    }
  } 
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j;
    int found = 0;

    for(i = 0; i < 9 && !found; i++){
      for(j = 0; j < 9 && !found; j++){
        if(n->sudo[i][j] == 0){
          found = 1;
          int num;
          for(num = 1; num <= 9; num++){
            Node* adj = copy(n);
            adj->sudo[i][j] = num;
            if(is_valid(adj)){
              pushBack(list, adj);
            } 
            else{
              free(adj);
            }  
          }    
        }      
      }    
    }    
    return list;
}


int is_final(Node* n){
  int i, j;
  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
    return 1;
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
}
  */