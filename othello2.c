#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define EMPTY -1
#define WHITE 0
#define BLACK 1
#define OUTSIDE -2

int board[20][20];

int mode()
{
    int m;
    printf("対人戦かコンピュータ戦どちらか選んでください\n 人:1 コンピュータ:2 \n");
    scanf("%d",&m);
    if(m==1)
    {
        printf("対人戦を行います\n");
        return 1;
    }
    else if(m==2)
    {
        printf("コンピュータ戦を行います\n");
        return 2;
    }
    else 
    {
        printf("1,2以外が選択されましたが、対人戦を行います\n");
        return 1;
    }
}
int color()
{
    char c[10];
    printf("先行後攻どちらかを選択してください\n");
    printf("先行:b 後攻:w \n");
    scanf("%s",c);
    if(strcmp(c,"b")==0)
    {
        printf("you: black に決まりました\n");
        return 1;
    }
    else if(strcmp(c,"w")==0)
    {
        printf("you: white に決まりました\n");
        return 0;
    }
    else
    {
        printf("b,w以外が選択されましたが、あなたは先攻(black)とします\n");
        return 1;
    }
}
int strong()
{
    int s;
    printf("コンピュータのレベルを選んでください\n");
    printf("1: 初級　2: 中級　3:上級\n");
    scanf("%d",&s);
    if(s==1)
    {
        printf("コンピュータ: 初級\n");
        return 1;
    }
    else if(s==2)
    {
        printf("コンピュータ: 中級\n");
        return 2;
    }
    else if(s==3)
    {
        printf("コンピュータ: 上級\n");
        return 3;
    }
    else
    {
        printf("1,2以外が選択されましたが、コンピュータの強さを中級に設定しました\n");
        printf("コンピュータ: 中級\n");
        return 2;
    }
    
}
void make_board(int SIZE)
{
    int i,j;
    for(i=0;i<=SIZE+1;i++)
    {
        for(j=0;j<=SIZE+1;j++)
        {
            board[i][j]=OUTSIDE;
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
void view_board(int SIZE,int mode)
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
    if(mode==2)
    {    
     Sleep(2*1000);
    }
}
void start_board(int SIZE,int mode)
{
    int i,j;

    board[SIZE/2][SIZE/2]=WHITE;
    board[SIZE/2][(SIZE/2)+1]=BLACK;
    board[(SIZE/2)+1][SIZE/2]=BLACK;
    board[(SIZE/2)+1][(SIZE/2)+1]=WHITE;

    view_board(SIZE,mode);
}
void computer_1(int *turn,int SIZE)
{
    int x,y;
    int i,j;
    int s,t;
    int count=0;
    srand((unsigned int)time(NULL));
    while(1)
    {
    x=rand()%SIZE+1;
    y=rand()%SIZE+1;
   printf("x,y: %d,%d\n",x,y);

    if(board[x][y]!=EMPTY)
     {
         continue;
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
                     if(board[x+i][y+j]==(*turn+1)%2)
                     {
                         s=1;
                         while(board[x+s*i][y+s*j]==(*turn+1)%2)
                         {
                            s++;
                         }
                         if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
                         {
                             continue;
                         }
                         else if(board[x+s*i][y+s*j]==(*turn)%2)
                         {
                            for(t=1;t<s;t++)
                            {
                                board[x+t*i][y+t*j]=(*turn)%2;
                            }
                            count++;    
                         }
                         
                     }
                     else //探索盤面が違う色が置かれていない
                     {
                         continue;
                     }
                     

                 }
             } //for j
         } //for i
         if(count==0)
         {
            continue;
         }
         else
         {
             board[x][y]=(*turn)%2;
             break;
         }
     }
     }
     
}
void computer_2(int *turn,int SIZE)
{
    int x=1,y=1;
    int i,j;
    int s,t;
    int count=0;
    int point=-1;
    int sub;
    srand((unsigned int)time(NULL));
    while(1)
    {
        point++;
        sub=point-3;
        printf("point:%d sub:%d\n",point,sub);
        if(point==0)
        {
            x=1,y=1;
        }
        else if(point==1)
        {
            x=1;y=SIZE;
        }
        else if(point==2)
        {
            x=SIZE;y=1;
        }
        else if(point==3)
        {
            x=SIZE;y=SIZE;
        }
        else if(sub>=1&&sub<=SIZE-1)
        {
            x--;
        }
        else if(sub>=SIZE&&sub<=2*(SIZE-1))
        {
            y--;
        }
        else if(sub>=2*(SIZE-1)+1&&sub<=3*(SIZE-1))
        {
            x++;
        }
        else if(sub>=3*(SIZE-1)+1&&sub<=4*(SIZE-1))
        {
            y++;
        }
        else
        {
            x=rand()%(SIZE-2)+2;
            y=rand()%(SIZE-2)+2;
        }

   printf("x,y: %d,%d\n",x,y);

    if(board[x][y]!=EMPTY)
     {
         continue;
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
                     if(board[x+i][y+j]==(*turn+1)%2)
                     {
                         s=1;
                         while(board[x+s*i][y+s*j]==(*turn+1)%2)
                         {
                            s++;
                         }
                         if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
                         {
                             continue;
                         }
                         else if(board[x+s*i][y+s*j]==(*turn)%2)
                         {
                            for(t=1;t<s;t++)
                            {
                                board[x+t*i][y+t*j]=(*turn)%2;
                            }
                            count++;    
                         }
                         
                     }
                     else //探索盤面が違う色が置かれていない
                     {
                         continue;
                     }
                     

                 }
             } //for j
         } //for i
         if(count==0)
         {
            continue;
         }
         else
         {
             board[x][y]=(*turn)%2;
             break;
         }
     }
     }
     
}
void computer_3(int *turn,int SIZE)
{
    int x=1,y=1;
    int i,j;
    int s,t;
    int count=0;
    int point=-1;
    int sub;
    srand((unsigned int)time(NULL));
    while(1)
    {
     struct max_xy
     {
        int key;
        int x;
        int y;
     };
     
   printf("x,y: %d,%d\n",x,y);

    if(board[x][y]!=EMPTY)
     {
         continue;
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
                     if(board[x+i][y+j]==(*turn+1)%2)
                     {
                         s=1;
                         while(board[x+s*i][y+s*j]==(*turn+1)%2)
                         {
                            s++;
                         }
                         if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
                         {
                             continue;
                         }
                         else if(board[x+s*i][y+s*j]==(*turn)%2)
                         {
                            for(t=1;t<s;t++)
                            {
                                board[x+t*i][y+t*j]=(*turn)%2;
                            }
                            count++;    
                         }
                         
                     }
                     else //探索盤面が違う色が置かれていない
                     {
                         continue;
                     }
                     

                 }
             } //for j
         } //for i
         if(count==0)
         {
            continue;
         }
         else
         {
             board[x][y]=(*turn)%2;
             break;
         }
     }
     }
     
}

void turn_board(int *turn,int SIZE,int mode,int color,int strong)
{
    int x,y;
    int i,j;
    int s,t;
    int count=0;

 if(*turn%2!=0) //turn black
 {
     if(mode==2&&color==0)
     {
         if(strong==1)
         {
             computer_1(turn,SIZE);
         }
         else if(strong==2)
         {
            computer_2(turn,SIZE);
         }
         else if(strong==3)
         {
             computer_3(turn,SIZE);
         }

     }
     else
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
                         if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
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
 }
 else  //turn white
 {
     if(mode==2&&color==1)
     {
         if(strong==1)
         {
             computer_1(turn,SIZE);
         }
         else if(strong==2)
         {
             computer_2(turn,SIZE);
         }
         else if(strong==3)
         {
             computer_3(turn,SIZE);
         }
     }
     else
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
                         if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
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
                                    else if(board[x+s*i][y+s*j]==OUTSIDE||board[x+s*i][y+s*j]==EMPTY)
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
void finish_board(int SIZE,int mode,int color)
{
    int w=0,b=0;
    int i,j;
    printf("final board\n");
    view_board(SIZE,mode);
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
        if(color==1)
        {
            printf("You win!!!!!!\n");
        }
        else if(color==0)
        {
            printf("You lose.....\n");
        }
    }
    else if(b==w)
    {
        printf("draw\n");
    }
    else
    {
        printf("winner: white\n");
        if(color==1)
        {
            printf("You lose.....\n");
        }
        else if(color==0)
        {
            printf("You win!!!!!!\n");
        }
    }
}
int main(int argc,char *argv[])
{
    int p;
    int SIZE;
    int i,j;//
    int turn=0;
    int alarm=0;
    int m,c,s;
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
    start_board(SIZE,m);
     m=mode();
            if(m==2)
            {
                s=strong();
                c=color();
            }
    while(1)
    {   
        alarm=0;
        turn++;
        if(flag(&turn,SIZE)==-1)
        {
            if(turn%2==1)
            {
                printf("turn black: 置けるところがないので、パスします\n");
                Sleep(2*1000);
            }
            else
            {
                printf("turn white: 置けるところがないので、パスします\n");
                Sleep(2*1000);
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
            turn_board(&turn,SIZE,m,c,s);
            view_board(SIZE,m);      
    }
    finish_board(SIZE,m,c);
    
}