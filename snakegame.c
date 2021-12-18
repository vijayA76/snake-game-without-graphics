#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"conio.h"
#include"time.h"
#include"windows.h"


const char player[10];
int height=20,width=60;
int x,y,foodX,foodY,score;
int input,exist;
int tailX[100],tailY[100];
int lengthtail;


//-----------------------> time delay in printing <---------------------------//
void timedelay()
{
    int m,n;
    for(m=0;m<10000;m++)
            for(n=0;n<15000;n++){}
}
//--------------------------> hiding the blinking cursor <--------------------//
void hidecursor()
{
    CONSOLE_CURSOR_INFO blinkcur;

    blinkcur.dwSize = 100;
    //if()
    blinkcur.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&blinkcur);
}
//---------------------------------> Welcome page <---------------------------//
void welcome()
{
    printf("\n\t------------> Welcome to Snake Game <-----------\n");
    printf("\n                             . ***.*.*");
    printf("\n                           * ***X***  ****");
    printf("\n  __                      * **** * *       *");
    printf("\n |  |     |\\    |       /| *                *      /\\      |  /  |-----");
    printf("\n  \\       | \\   |      / | *                *     /  \\     | /   |");
    printf("\n   \\      |  \\  |           *               *    /____\\    |/    |---");
    printf("\n |  |     |   \\ |            *             *    /      \\   | \\   |");
    printf("\n  --      |    \\|             *           *    /        \\  |  \\  |_____");
    printf("\n                               *        *");
    printf("\n                               *......*");
    printf("\n                              *.....*");
    printf("\n                             *....*.*.*..*.");
    printf("\n                            *....*......... **.*.*");
    printf("\n                           *....** * * * ..........*****");
    printf("\n                           *.....**       *.****.* .......*");
    printf("\n                             *.* *            *.*  ****....*");
    printf("\n                                            *.......****...*");
    printf("\n                                           *....**........*");
    printf("\n                               *.*.*       *...*    ****");
    printf("\n                             *.......*     *...*");
    printf("\n                           *...*  *....*..*....*");
    printf("\n                         *..*        **.......*");
    printf("\n                       *.*              **.**");
    printf("\n                     **");
    printf("\n                    *");
    printf("\nPress any key to continue..........");
    getch();
    system("cls");
}
//--------------------------------------> rule page---------------------------//
void rule()
{
    printf("\t\t\t----> GAME INSTRUCTION <----\n");
    printf("\n> Use 'a','w','s','d' key to move the snake.");
    printf("\n> You will be provided foods at the several coordinates of screen which you have to eat.");
    printf("\n> Every time you eat a food the length of the snake will get increased by 1 element.");
    printf("\n> Increase in length gives +5 points");
    printf("\n> To exit press 'X' key.");
    printf("\n\nPress any key to start the Game.......");
    getch();
    system("cls");
}
//-------------------------------------> loading page <------------------------//
void coordinate(int x,int y)
{
    COORD axis;

    axis.X=x;
    axis.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),axis);
}
void loading()
{
    int i,z;

    coordinate(23,10);
    printf("loading....");

    coordinate(18,11);
    for(i=1;i<=20;i++)
    {
        for(z=0;z<=100000000;z++);    //to display the character slowly
        printf("%c",177);
    }
    system("cls");

}
//-------------------------------------> player information <------------------//
void playerinfo()
{
    printf("\nEnter the Player name: ");
    scanf(" %s",&player);
    printf("\n\nPress any key to Play the Game......");
    getch();
    system("cls");
}
//------------------------------------> initial setup <------------------------//
void setup()
{
    exist=0;
    score=0;
    lengthtail=0;

    x=width/2;
    y=height/2;

    foodX=rand()%(width-1)+1;
    foodY=rand()%(height-1)+1;
}
//--------------------------------------> play board <-------------------------//
void playboard()
{
    int l,b,t;
    for(l=0;l<=height;l++)
    {
        for(b=0;b<=width;b++)
        {
            if(l==0 || l==height || b==0||b==width)
                printf("|");
            else
            {
                if(l==y && b==x)
                    printf("O");
                else if(l==foodY&&b==foodX)
                    printf("X");
                else
                {
                    int m=0;
                    for(t=0;t<lengthtail;t++)
                    {
                        if(b==tailX[t] && l==tailY[t])
                        {
                            printf("o");
                            m=1;
                        }
                    }
                    if(m==0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }

}
//------------------------------------> User Instruction <---------------------//
void instruc()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a'://RIGHT
                input=1;
                break;
            case 's'://DOWN
                input=2;
                break;
            case 'w'://UP
                input=3;
                break;
            case 'd'://LEFT
                input=4;
                break;
            case 'x'://EXIT
                exist=1;
                break;
        }
    }
}
//-------------------------> Moving directions of snake logic <-----------------//
void move()
{
    switch(input)
    {
        case 1:
            x--;
            break;
        case 2:
            y++;
            break;
        case 3:
            y--;
            break;
        case 4:
            x++;
            break;
        default:
            break;
    }
    if(x<0||x>=width||y<0||y>=height)
        exist=1;
}
//--------------------------------> food <--------------------------------------//
void food()
{
    if(x==foodX && y==foodY)
    {
        score+=5;
        srand(time(NULL));
        foodX = rand()%(width-1)+1;
        srand(time(NULL));
        foodY = rand()%(height-1)+1;
        lengthtail++;
    }
}
//--------------------------------> length of snake <---------------------------//
void length()
{
    int i;
    int prevX=tailX[0],prevY=tailY[0];
    int prev2X,prev2Y;

    tailX[0]=x;
    tailY[0]=y;

    for(i=1;i<lengthtail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
}
//------------------------------> Head of snake <-------------------------------//
void head()
{
    int i;
    for(i=0;i<lengthtail;i++)
    {
        if(x==tailX[i] && y==tailY[i])
            exist=1;

    }
}
//--------------------------------> Save Record <-------------------------------//
void record()
{
    int i;

    FILE *data;
    data=fopen("recordSnakeGame.txt","a+");
    time_t mytime;
    mytime=time(NULL);

    fprintf(data,"Player Name :%s",player);
    fprintf(data,"\nPlayed Date/Time: %s",ctime(&mytime));
    fprintf(data,"score : %d\n",score);

    for(i=0;i<=45;i++)
        fprintf(data,"%c",'-');

    fprintf(data,"\n");
    fclose(data);


    fclose(data);
}
//-------------------------> display previous records <-------------------------//
void disrecord()
{
    char ch,c;

    FILE *data;
    data=fopen("recordSnakeGame.txt","r");

    printf("\n\tDo you want to see the last record???");
    printf("\n\t\tPress 'y/Y' to see....");
    ch=getch();

    system("cls");

    if(ch=='y' || ch=='y')
    {
        data=fopen("recordSnakeGame.txt","r");
        do
            putchar(c=getc(data));
        while(c!=EOF);
    }
    fclose(data);
}
////////////////////////////////// MAIN FUNCTION /////////////////////////////////
int main()
{
    char playagain;
    welcome();
    rule();
    loading();
    playerinfo();

    label:

    setup();
    hidecursor();
    while(!exist)
    {
        system("cls");

        printf("\t\t     --> Snake Game <--\n");
        playboard();
        printf("\nPLAYER NAME: %s\t\t\t\tScore = %d",player,score);

        timedelay();

        length();
        instruc();
        move();
        food();
        head();
    }
    printf("\n\n\t    >>>>>>>>>>> GameOver <<<<<<<<<<<<");
    record();

    printf("\n\tDo you want to play again??? Press y/Y....");
    playagain=getch();

    if(playagain=='y'||playagain=='Y')
        goto label;
    else
        disrecord();
}














