#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
  FILE * fp = fopen("formula","w");

  int row, col;
  int board[101][101];

  //Check size
/*
  row = 0;
  col = 0;
  char line[300];
  int i = 0;

  while(getline(line) != NULL){

    while(line[i] != '\n'){
        if(line[i] != ' ')
          col++;
    }
    row++;
  }
*/
  row = 6;
  col = 6;
  int max;
  max = row * col;
/*
  char line[300];
  char* box;
  box = malloc(sizeof(char));

  while(gets(line) != NULL){

    box = strtok(line,' ');
    while(box != NULL){
      col++;
      box = strtok(NULL,' ');
    }
    row++;
  }
*/

  //Store number

  int n,m;
  char temp[10];
  for(n = 1; n <= row; n++)
    for(m = 1; m <= col; m++){

      scanf("%s",temp);

      if(temp != 63)
        board[n][m] = atoi(temp);
      else
        board[n][m] = 0;
    }

  //Declare
  for(n = 1; n <= row; n++)
    for(m = 1; m <= col; m++)
      fprintf(fp, "(declare-const a%d%d Int)\n",n,m);

  //1.Distinct
  fprintf(fp, "(assert (distinct ");
  for(n = 1; n <= row; n++)
    for(m = 1; m <= col; m++)
      fprintf(fp, "a%d%d ",n,m);
  fprintf(fp, "))\n");

  //2.
  int i;
  for (n = 1 ; n <= row ; n++)
    for (m = 1 ; m <= col ; m++){
      i = 1;
      fprintf(fp, "(assert(or  ");

      while(i <= max ){
      fprintf(fp,"(= a%d%d %d )",n,m,i);
      i++;
      }

      fprintf(fp,"))\n");
    }

  //3. fixed numbers
  for(n = 1; n <= row; n++)
    for(m = 1; m <= col; m++){
      if(board[n][m] != 0)
        fprintf(fp,"(assert (= a%d%d %d))\n",n,m,board[n][m]);
    }

  //4.Check continous number

  for(n = 1; n <= row; n++){
    for(m = 1; m <= col; m++){
      fprintf(fp, "(assert (and ");

      if((n == 1) && (m == 1)){
      fprintf(fp,"(or (= a11 1) (= (- a11 a12) 1) (= (- a11 a21) 1)) (or (= a11 %d) (= (- a11 a12) -1) (= (- a11 a21) -1))",max);
      }

      if((n == 1) && (m == row)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d %d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n+1,m,n,m,n,m-1,n,m,max,n,m,n+1,m,n,m,n,m-1);
      }

       if((n == col) && (m == 1)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n-1,m,n,m,n,m+1,n,m,max,n,m,n-1,m,n,m,n,m+1);
      }

      if((n == row) && (m == col)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n,m-1,n,m,n-1,m,n,m,max,n,m,n,m-1,n,m,n-1,m);
      }


      if((1 < n) && (n < row) && (m == 1)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n-1,m,n,m,n,m+1,n,m,n+1,m,n,m,max,n,m,n-1,m,n,m,n,m+1,n,m,n+1,m);
      }

      if((n == 1) && (1 < m) && (m < col)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n,m-1,n,m,n+1,m,n,m,n,m+1,n,m,max,n,m,n,m-1,n,m,n+1,m,n,m,n,m+1);
      }

      if((1 < n) && (n < row) && (m == col)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n-1,m,n,m,n,m-1,n,m,n+1,m,n,m,max,n,m,n-1,m,n,m,n,m-1,n,m,n+1,m);
      }

      if((n == row) && (1 < m) && (m < col)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n,m-1,n,m,n-1,m,n,m,n,m+1,n,m,max,n,m,n,m-1,n,m,n-1,m,n,m,n,m+1);
      }

      if((1 < n) && (n < row ) && (1 < m) && (m < col)){
      fprintf(fp,"(or (= a%d%d 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1) (= (- a%d%d a%d%d) 1)) (or (= a%d%d %d) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1) (= (- a%d%d a%d%d) -1)) ",n,m,n,m,n,m-1,n,m,n-1,m,n,m,n,m+1,n,m,n+1,m,n,m,max,n,m,n,m-1,n,m,n-1,m,n,m,n,m+1,n,m,n+1,m);
      }


      fprintf(fp," ))\n");
    }
  }

  fprintf(fp, "(check-sat)\n(get-model)\n");
  fclose(fp);

  return 0;



}
