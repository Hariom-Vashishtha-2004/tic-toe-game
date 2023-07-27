#include<bits/stdc++.h>
using namespace std;

# define COMPUTER 1
# define HUMAN 2

# define SIDE 3

# define COMPUTERMOVE 'O'
# define HUMANMOVE 'X'


void showBoard(char board[][SIDE])
{

    printf("\t\t\t %c | %c | %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t ------------\n");
    printf("\t\t\t %c | %c | %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t ------------\n");
    printf("\t\t\t %c | %c | %c  \n", board[2][0], board[2][1], board[2][2]);
}


void showInstruction()
{
    printf("\n Choose a cell number from 1 to 9 as below and play \n \n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t ----- \n");
    printf("\t\t\t 4 | 5 | 6 \n ");
    printf("\t\t ----- \n");
    printf("\t\t\t 7 | 8 | 9 \n \n");

}


void intialise(char board[][SIDE])
{
     // intilalise the board to * as said
     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
             board[i][j]='*';   
     }
}

void declareWinner(int whoseTurn)
{
     if(whoseTurn==COMPUTER)
         printf("COMPUTER HAS WON \n");
     else
         printf("HUMAN HAS WON \n");
}

bool rowCrossed(char board[][SIDE])
{
     for(int i=0;i<3;i++)
     {
         if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*')
            return true;
     }
     return false;
}



bool columnCrossed(char board[][SIDE])
{
     for(int i=0;i<3;i++)
     {
          if(board[0][i] ==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
             return true;
     }
      return false;
}



bool diagnolCrossed(char board[][SIDE])
{
     if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*')
     {
         return true;
     }
     if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='*')
     {
         return true;
     }
     return false;
     
}



bool gameOver(char board[][SIDE])
{
     return rowCrossed(board) || columnCrossed(board) || diagnolCrossed(board);
}


int minimax(char board[][SIDE], int depth, bool isAI)
{
     int score=0;
     int bestscore=0;
     if(gameOver(board)==true)
     {
         if(isAI==true)
              return -10;
         if(isAI==false)
             return 10;
         
     }
     else
     {
         if(depth<9)
         {
             if(isAI==true)
             {
                  bestscore=-999;
                  for(int i=0;i<3;i++)
                  {
                     for(int j=0;j<3;j++)
                     {
                        if(board[i][j]=='*')
                        {
                              board[i][j]=COMPUTERMOVE;
                              score=minimax(board, depth+1, false);
                              board[i][j]='*';
                              if(score>bestscore)
                              {
                                 bestscore=score;
                              }   
                        }
                     }
                  }
                  return bestscore;

             }
             else
             {
                 bestscore=999;
                 for(int i=0;i<3;i++)
                 {
                     for(int j=0;j<3;j++)
                     {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=HUMANMOVE;
                            score=minimax(board, depth+1, true);
                            board[i][j]='*';
                            if(score<bestscore)
                            {
                                 bestscore=score;
                            }
                        }
                         
                     }
                 }
                 return bestscore;
             }
         }
            else
            {
                return 0;  
            }
    }   
}

int bestMove(char board[][3], int moveindex)
{
     int  x=-1; int  y=-1;
     int score=0, bestscore=-999;
     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
         {
             if(board[i][j]=='*')
             {
                 board[i][j]=COMPUTERMOVE;
                 score=minimax(board, moveindex+1, false);
                 board[i][j]='*';
                 if(score>bestscore)
                 {
                     bestscore=score;x=i; y=j;
                 }
             }
         }
     }
     return 3*x+y;
}

//A function to play tic toe game
void playTicTacToe(int whoseTurn)
{
    char board[3][3];
    int moveindex=0; int x=0;int y=0;

    intialise(board);
    showInstruction();


    while(gameOver(board)==false && moveindex!=3*3)
    {
        int n;
        if(whoseTurn==COMPUTER)
        {
             n=bestMove(board, moveindex);
             x=n/3;
             y=n%3;
             board[x][y]=COMPUTERMOVE;
             printf("COMPUTER has a put a %c in cell %d \n\n ", COMPUTERMOVE, n+1);
             showBoard(board);
             moveindex++;
             whoseTurn=HUMAN;
        }
        else if(whoseTurn==HUMAN)
        {
             printf("You can insert in the following positions : ");
             for(int i=0;i<3;i++)
             { 
                 for(int j=0;j<3;j++)
                 {
                     if(board[i][j]=='*')
                        printf("%d ", (i*3+j)+1);

                 }
             }
             printf("\n\n Enter the position =");
             scanf("%d", &n);
             n--;
             x=n/3; y=n%3;
             if(board[x][y]=='*' && n<9 && n>=0)
             {
                 board[x][y]=HUMANMOVE;
                 printf("\n HUMAN HAS PUT A %c in cell %d \n\n",HUMANMOVE, n+1);
                 showBoard(board);
                 moveindex++;
                 whoseTurn=COMPUTER;

             }
             else if(board[x][y]!='*' && n>=0 && n<9)
             {
                   printf("\n Position is occupied, select any one place from the available places\n\n");
             }
             else if(n<0 || n>=9)
             {
                 printf("invalid positions \n\n");
             }

        }
    }
    if(gameOver(board)==false && moveindex==3*3)
    {
         printf("\n It is an draw \n");

    }
    else
    {
         if(whoseTurn==COMPUTER)
         {
            whoseTurn=HUMAN;
         }
         else if(whoseTurn==HUMAN)
         {
             whoseTurn=COMPUTER;
         }
         declareWinner(whoseTurn);
    }

}

int main()
{
     printf("\n ***********************\n\n");
     printf("\t\t\t Tic-Tac-Toe \n");
     printf("\n *******************************\n\n");
     char cont='y';
     do
     {
        char choice;
        printf(" Do you want to start first (y/n): ");
        scanf("%c",&choice);
        if(choice=='n')
        {
             playTicTacToe(COMPUTER);

        }
        else if(choice=='y')
        {
             playTicTacToe(HUMAN);
        }
        else
        {
             printf("Invalid Choice\n");
        }
        printf("\n Do you want to quite(y/n) : ");
        scanf("%c",&cont);

    
     } while(cont=='n');
     return 0;

     
}




















