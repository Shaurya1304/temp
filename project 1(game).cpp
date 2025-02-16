#include <iostream> 
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream inp;  
ofstream outp;

char c[30][21]; 
int n[30][21];  
int highscore;
int contr,tuk=0,score=0,t=0,bt=0,birdx=0,birdy=0; 
bool err; 

void game(); 
void screen();
void pipes();
void bird();
bool gameover();
void checkscore();
void help();
void menu();
void endgame();
void credits();
void checkscore()  
{
    int y;
    for(y=0;y<20;y++)
    {
        if(c[birdx][y]=='|')  
        {
            score++;
            return;
        }
    }
}

bool gameover() 
{
    int x,y,f=0;
    if(birdy>19) 
    {
        c[birdx][19]='*';
        c[birdx][20]='-';
        f=1;           
        goto quit;
    }
    else
    {     
        if(n[birdx][birdy]>0 && (c[birdx][birdy]=='|' || c[birdx][birdy]=='*'))
        {
            c[birdx][birdy]='|';
            c[birdx-1][19]='*';
            f=1;
            goto quit;
        }  
    }
    quit:
    if(f==1) return true;
    else return false;
}

void endgame() 
{
    screen();   
    cout<<""<<endl<<endl;
    cout << "_---------    Game Over    --------_" << endl;
    cout<<""<<endl<<endl;
    cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<"                        H I G H   S C O R E : "<<highscore<<endl;
    cout<<""<<endl<<endl;
}

void menu()  //shows menu
{
    system("cls");
    cout<<""<<endl;
    cout << "----------- Flappy Bird -------------" <<  endl;
    cout<<""<<endl<<endl;
    cout<<"                  High Score:  "<<highscore<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"                  1: Start Game  "<<endl<<endl;
    cout<<"                  2: Help        "<<endl<<endl;
    cout<<"                  3: Credits     "<<endl<<endl;
    cout<<"                  4: Exit        "<<endl<<endl;
}

void credits()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}

void help()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"                 1 - Press any key to fly up.         "<<endl<<endl;
    cout<<"             2 - Dont hit the Pips the pipes.   "<<endl;
    cout<<"             When you pass through the pipes ,you get 1 point.  "<<endl;
    cout<<"                          Are you ready? Go!                  "<<endl<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}

int main()
{
srand(time(0)); 
inp.open("/Program Files/FlappyBird/options.txt");  
if(inp.is_open()) 
{
    inp>>highscore;
    inp.close();
    err=false; 
}
else
{
    highscore=0;
    err=true;
}

int a=0,b;
char sl; 
while(1) {
    if(a==0) goto play; 
    if(a>0) 
    {
        score=0;
        cout<<"Try again? [y/n] ";
        cin>>sl;
        if(sl=='n') goto quit;
        else goto play;
    }
    play:
    menu(); 
    cin>>sl;
    switch(sl)
    {
        case '1':
        {
            game();
            break;
        }
        case '2':
        {
            help(); 
            goto play;
            break;
        }
        case '3':
        {
            credits();
            goto play;
            break;
        }
        case '4':
        {
            goto quit; 
            break;
        }
        default:
        {
            goto play;
            break;
        }
    }
    a++;
}
quit:
{
   cout<<"Thats it.";
}

return 0;
}

void game()  
{
    int x,y;
    char s;
    for(y=0;y<21;y++)  
    {
        for(x=0;x<30;x++)
        {
            if(y<20)
            {
            c[x][y]=' ';
            n[x][y]=0;
            }
            if(y==20)
            {
                c[x][y]='-';
                n[x][y]=2;
            }
        }
    }
    c[10][10]='*';  
    screen();      
    while(1)       
    {
        s='~';  
        Sleep(0.2*1000);  
        t++;              
        if(kbhit()) 
        {
            s=getch();        
            if(s!='~') tuk=1; 
        }
        for(x=0;x<30;x++) 
        {
            c[x][20]='-';
            n[x][20]=2;
        }
        bird();           
        checkscore();     
        if(gameover()==true) goto gameEnd; 
        pipes();                           
        if(score>highscore) highscore=score;
        screen();                           

        if(tuk>0) tuk++;           
        if(tuk==3) tuk=0;          
    }
    gameEnd:  
    {
        if(score>highscore) highscore=score;
        if(err==false)              
        {
            outp.open("/Program Files/FlappyBird/options.txt");
            outp<<highscore;
            outp.close();
        }
        screen();   
        endgame();
        return;
    }
}

void screen()    
{
    int x,y;
    system("cls");    
    for(y=0;y<21;y++) 
    {
        for(x=0;x<30;x++)
        {
            if(x<29) cout<<c[x][y];
            if(x==29) cout<<c[x][y]<<endl;
        }
    }
    cout<<""<<endl;
    cout<<"Your Score: "<<score;
}

void pipes()  
{
    int x,y,r;
    if(t==10)  
    {
        r=(rand()%11)+5;  
        for(y=0;y<20;y++)  
        {
            c[29][y]='|';  
            n[29][y]=2;   
        }
        c[29][r-1]=' ';  
        c[29][r]=' ';
        c[29][r+1]=' ';
        n[29][r-1]=0;
        n[29][r]=0;
        n[29][r+1]=0;
        t=0;
        goto mv; 
    }
    else goto mv;
    mv:                 
    {
        for(y=0;y<20;y++) 
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='|')  
                {
                    if(x>0)
                    {
                        c[x-1][y]='|';
                        n[x-1][y]=2;
                        c[x][y]=' ';
                        n[x][y]=0;
                    } 
                    if(x==0)  
                    {
                        c[x][y]=' ';
                        n[x][y]=0;
                    }
                }
            }
        }
    }
}

void bird()   
{
    int x,y;
    if(tuk>0) 
    {
        bt=0;
        for(y=0;y<20;y++)   
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y>0)
                    {
                    c[x][y-1]='*';  
                    c[x][y]=' ';
                    birdx=x;       
                    birdy=y-1;     
                    return;       
                    }
                }
            }
        }
    }
    else   
    {
        bt++;
        for(y=0;y<20;y++)
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y<20)  
                    {
                        if(bt<3)   
                        {
                            c[x][y+1]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+1;
                            return;
                        }
                        else if(bt>2 && bt<5) 
                        {
                            c[x][y+2]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+2;
                            return;
                        }
                        else if(bt>4)
                        {
                            c[x][y+3]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+3;
                            return;
                        }
                    }
                    else
                    {
                        return;  
                    }
                }
            }
        }
    }
}