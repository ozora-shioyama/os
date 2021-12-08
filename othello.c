#include<stdio.h>
#include<stdlib.h>
#define EMPTY -1
#define WHITE 0
#define BLACK 1
#define OUT -2

int board[20][20];

void make_board(int SIZE)
{
    int i,j;
    for(i=0;i<=SIZE+1;i++)
    {
        for(j=0;j<=SIZE+1;j++)
        {
            board[i][j]=OUT;
        }
    }
    for(i=1;i<=SIZE;i++)
    {
        for(j=1;j<=SIZE;j++)
        {
            board[i][j]=EMPTY;
        }
    }
}
void view_board(int SIZE)
{
    int t;
    int i,j;
    printf("    ");
    for(t=1;t<=SIZE;t++)
    {
        printf("%d   ",t);
    }
    printf("\n");

    printf("   ");
    for(t=1;t<=SIZE;t++)
    {
        printf("----");
    }
    printf("\n");
    for(i=1;i<=SIZE;i++)
    {
        printf("%d ",i);
        for(j=1;j<=SIZE;j++)
        {
            if(board[i][j]==WHITE)
            {
                printf("| ● ");
            }
            if(board[i][j]==BLACK)
            {
                printf("| o ");
            }
            if(board[i][j]==EMPTY) //elseなんでだめか?
            {
                printf("|   ");
            }
        }
        printf("|\n");
     
     printf("   ");
    for(t=1;t<=SIZE;t++)
    {
        printf("----");
    }
    printf("\n");
    }    
}
void start_board(int SIZE)
{
    int i,j;

    board[SIZE/2][SIZE/2]=WHITE;
    board[SIZE/2][(SIZE/2)+1]=BLACK;
    board[(SIZE/2)+1][SIZE/2]=BLACK;
    board[(SIZE/2)+1][(SIZE/2)+1]=WHITE;

    view_board(SIZE);
}

void turn_board(int *turn,int SIZE)
{
    int x,y;
    int i,j;
    int s,t;
    int count=0;

 if(*turn%2!=0) //turn black
 {
     printf("black turn\n");
     printf("何行目に石を置くか入力してください\n");
     scanf("%d",&x);
     printf("何列目に石を置くか入力してください\n");
     scanf("%d",&y);

     if(board[x][y]!=EMPTY)
     {
         printf("既に石が置いてあるので、入力し直してください\n");
         (*turn)--;
     }
     else //石が置いてない
     {
         for(i=-1;i<=1;i++)
         {
             for(j=-1;j<=1;j++)
             {
                 if(i==0&&j==0)
                 {
                     continue;
                 }
                 else //探索盤面が自分自身でない
                 {
                     if(board[x+i][y+j]==WHITE)
                     {
                         s=1;
                         while(board[x+s*i][y+s*j]==WHITE)
                         {
                            s++;
                         }
                         if(board[x+s*i][y+s*j]==OUT||board[x+s*i][y+s*j]==EMPTY)
                         {
                             continue;
                         }
                         else if(board[x+s*i][y+s*j]==BLACK)
                         {
                            for(t=1;t<s;t++)
                            {
                                board[x+t*i][y+t*j]=BLACK;
                            }
                            count++;    
                         }
                         
                     }
                     else //探索盤面が違う色が置かれていない
                     {
                         continue;
                     }
                 }
             } //for
         } //for
         if(count==0)
         {
          printf("挟める石がないので、入力し直してください\n");
         (*turn)--;
         }
         else
         {
             board[x][y]=BLACK;
         }
     }

 }
 else  //turn white
 {
     printf("white turn\n");
     printf("何行目に石を置くか入力してください\n");
     scanf("%d",&x);
     printf("何列目に石を置くか入力してください\n");
     scanf("%d",&y);

     if(board[x][y]!=EMPTY)
     {
         printf("既に石が置いてあるので、入力し直してください\n");
         (*turn)--;
     }
     else //石が置いてない
     {
         for(i=-1;i<=1;i++)
         {
             for(j=-1;j<=1;j++)
             {
                 if(i==0&&j==0)
                 {
                     continue;
                 }
                 else //探索盤面が自分自身でない
                 {
                     if(board[x+i][y+j]==BLACK)
                     {
                         s=1;
                         while(board[x+s*i][y+s*j]==BLACK)
                         {
                            s++;
                         }
                         if(board[x+s*i][y+s*j]==OUT||board[x+s*i][y+s*j]==EMPTY)
                         {
                             continue;
                         }
                         else //端が同じ色
                         {
                            for(t=1;t<s;t++)
                            {
                                board[x+t*i][y+t*j]=WHITE;
                            }
                            count++;    
                         }
                         
                     }
                     else //探索盤面が違う色が置かれていない
                     {
                         continue;
                     }
                 }
             } //for
         } //for
         if(count==0)
         {
          printf("挟める石がないので、入力し直してください\n");
         (*turn)--;
         }
         else
         {
             board[x][y]=WHITE;
         }
     }

 }

}
int flag(int *turn,int SIZE)
{
    int i,j;
    int s,t;
    int x,y;
    int count=0;
    for(x=1;x<=SIZE;x++)
    {
        for(y=1;y<=SIZE;y++)
        {
            if(board[x][y]!=EMPTY) //空でなかったら飛ばす
            {
                continue;
            }
            else
            {
                    for(i=-1;i<=1;i++)
                    {
                        for(j=-1;j<=1;j++)
                        {
                            if(i==0&&j==0)
                            {
                                continue;
                            }
                            else //探索盤面が自分自身でない
                            {
                                if(board[x+i][y+j]==(*turn+1)%2) 
                                {
                                    s=1;
                                    while(board[x+s*i][y+s*j]==(*turn+1)%2)
                                    {
                                        s++;
                                    }
                                   
                                    
                                    if(board[x+s*i][y+s*j]==(*turn)%2)
                                    {
                                        count++;    
                                    }
                                    else if(board[x+s*i][y+s*j]==OUT||board[x+s*i][y+s*j]==EMPTY)
                                    {
                                        continue;
                                    }
                                    
                                }
                                else //探索盤面が違う色が置かれていない
                                {  
                                 continue;
                                }
                             }

                         }
                        }
             }
        }
    }//一番でかいfor
     
    if(count==0)
    {
        return -1;
    }
    else if(count!=0)
    {
        return 1;
    }
   
}
void finish_board(int SIZE)
{
    int w=0,b=0;
    int i,j;
    printf("final board\n");
    view_board(SIZE);
    for(i=1;i<=SIZE;i++)
    {
        for(j=1;j<=SIZE;j++)
        {
            if(board[i][j]==WHITE)
            {
                w++;
            }
            else if(board[i][j]==BLACK)
            {
                b++;
            }
            else
            {
                continue;
            }
        }
    }
    printf("white: %d, black: %d\n",w,b);
    if(b>w)
    {
        printf("winner: black\n");
    }
    else if(b==w)
    {
        printf("draw\n");
    }
    else
    {
        printf("winner: white\n");
    }
}
int main(int argc,char *argv[])
{
    int p;
    int SIZE;
    int i,j;//
    int turn=0;
    int alarm=0;
    if(argc!=2)
    {
        printf("引数の数が違います\n");
        return 1;
    }
    else
    {
        p=atoi(argv[1]);
        if(p<3)
        {
            printf("盤面のサイズについて0以下が入力されたので、サイズを自動で8に設定します\n");
            SIZE=8;
        }
        else if(p>15)
        {
            printf("盤面のサイズが大きすぎるので、サイズを自動で8に設定します\n");
            SIZE=8;
        }
        else
        {
            printf("盤面のサイズを%dに設定します\n",p);
            SIZE=p;
        }
    }
    make_board(SIZE);
    start_board(SIZE);
    while(1)
    {   
        alarm=0;
        turn++;
        if(flag(&turn,SIZE)==-1)
        {
            if(turn%2==1)
            {
                printf("turn black: 置けるところがないので、パスします\n");
            }
            else
            {
                printf("turn white: 置けるところがないので、パスします\n");
            }
            turn++;
            alarm++;
            if(flag(&turn,SIZE)==-1)
            {
                printf("両者とも置けなくなったので、終了します\n");
                alarm++;
            }
        }
        if(alarm==2)
        {
            break;
        }
            turn_board(&turn,SIZE);
            view_board(SIZE);      
    }
    finish_board(SIZE);
    
}