#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <windows.h>
#include <mmsystem.h>



using namespace std;
int move_size[1000],current_move=0;
int numarLinii = 4;
int numarColoane = 4;
int sus, stanga;
bool endgame;
bool turaprimuluijucator = 1;
int scor;
int maxim = 0;
int scor1 = 0;
int scor2 = 0;
#define FUNDAL YELLOW
int P = 4;
int Q = 4;
int w,h;
#define FONT SIMPLEX_FONT
#define FONT_SIZE 1
#define MAX_BOARD_SIZE 25
#define MIN_BOARD_SIZE 4

struct cerc {
    int x;
    int y;
    int i;
    int j;
};

void selectColor(int color) {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
}


int isMouseInside(int xi, int yi, int xf, int yf)
{
    int x=mousex();
    int y=mousey();
    return (x>=xi && x<=xf && y>=yi && y<=yf);
}

bool tabla[16][16];


cerc selecteazaCerc() {
    clearmouseclick(WM_LBUTTONDOWN);
    int x = mousex();
    int y = mousey();
    int selecti = round((y - sus)/(float)100);
    int selectj = round((x - stanga)/(float)100);
    int xNou = sus + selectj*100;
    int yNou = stanga + selecti*100;
    cerc c;
    c.x = xNou;
    c.y = yNou;
    c.i = selecti;
    c.j = selectj;
    return c;
}
cerc selecteazaCercAI(bool primulSelectat,int x, int y )
{
int i, j;
cerc c1;
if(!primulSelectat)
{for(i = 1; i < 4; i++)
    for(j = 1; j < 4; j++)
    {if((tabla[4 * i + j][4*(i-1) + j] == 0 and i != 0) or (tabla[4*i + j][4*(i+1) +j]== 0 and i !=3) or (tabla[4*i +j][4*i+j+1] == 0 and j!=3) or (tabla[4*i+j][4*i+j-1] == 0 and j != 0))
    {

        c1.i = i;
        c1.j = j;
        c1.x = i*100+ sus;
        c1.y = j*100+ stanga;
        return c1;
    }
    }
}
else
    {
if(tabla[4*(x) + y][4*(x-1) + y] ==false )
   {
        c1.i = x-1;
        c1.j = y;
        c1.x = (x-1)*100 + sus;
        c1.y = y*100+ stanga;
        return c1;
   }
if(tabla[4*(x) + y][4*(x+1) + y] == false and x <3)
{
        c1.i = x+1;
        c1.j = y;
        c1.x = (x+1)*100 + sus;
        c1.y = y*100+ stanga;
        return c1;
}
if(tabla[4*(x)+y][4*(x) +y+1] == false and  y<3)
{
        c1.i = x;
        c1.j = y+1;
        c1.x = (x)*100 + sus;
        c1.y = (y+1)*100+ stanga;
        return c1;
}
if(tabla[4*(x)+y][4*(x) +y-1] == false and  y>0)
{
        c1.i = x;
        c1.j = y-1;
        c1.x = (x)*100 + sus;
        c1.y = (y-1)*100+ stanga;
        return c1;
}
}

}

bool verificare(cerc c1, cerc c2, bool turaprimuluijucator)
{
bool ok = false;
    if(c1.i == c2.i)
        {if(c1.i != 3 and tabla[4*(c1.i) +c1.j][4*(c1.i+1) + c1.j] == true and tabla[4*(c2.i) + c2.j][4*(c2.i+1) + c2.j] == true and tabla[4*(c1.i+1) +c1.j][4*(c2.i+1) + c2.j] == true)
    {
        ok = true;
        if(turaprimuluijucator)
            scor1++;
        else
            scor2++;
    }
       if(c1.i != 0 and tabla[4*(c1.i) +c1.j][4*(c1.i -1) + c1.j] == true and tabla[4*(c2.i) + c2.j][4*(c2.i -1) + c2.j] == true and tabla[4*(c1.i-1) +c1.j][4*(c2.i-1) + c2.j] == true)
            {
                ok = true;
            if(turaprimuluijucator)
                scor1++;
            else
                scor2++;
            }
        }
        else
            if(c1.j == c2.j)
        {
            if(c1.j != 0 and tabla[4*(c1.i) +c1.j][4*(c1.i) + c1.j-1] == true and tabla[4*(c2.i) + c2.j][4*(c2.i) + c2.j-1] == true and tabla[4*(c1.i) +c1.j-1][4*(c2.i) + c2.j-1] == true)
            {
                ok = true;
            if(turaprimuluijucator)
                scor1++;
                else
                scor2++;
            }
            if(c1.j != 3 and tabla[4*(c1.i) +c1.j][4*(c1.i) + c1.j+1] == true and tabla[4*(c2.i) + c2.j][4*(c2.i) + c2.j+1] == true and tabla[4*(c1.i) +c1.j+1][4*(c2.i) + c2.j+1] == true)
                 {
                ok = true;
            if(turaprimuluijucator)
                scor1++;
                else
                scor2++;
                 }
        }

return ok;


}
void startGame()
{
PlaySound(TEXT("lord.wav"), NULL, SND_ASYNC);
ofstream out("istoric.in");
    initwindow(400, 600);
    sus = 40;
    stanga = 40;
    int marimeTabla = 100;
    int x;
    int y;
    setbkcolor(FUNDAL);
    clearviewport();
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    for (int i = 0; i < numarLinii; i++)
    {
        for (int j=0; j < numarColoane; j++)
        {
            x = sus + j*100;
            y = stanga + i*100;
            fillellipse(x, y, 15, 15);
        }
    }
       setcolor(RED);
    settextstyle(4, 4,  2);
    outtextxy( 130,  530, "Jucator 1");
    outtextxy( 80,  560, "0");
    setcolor(BLUE);
    outtextxy(370, 530, "Jucator 2");
    outtextxy(310, 560, "0");
    bool primulSelectat = false;
    bool alDoileaSelectat = false;
    cerc c1, c2;
    while(!endgame)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            if (!primulSelectat)
            {
                c1 = selecteazaCerc();
                primulSelectat = true;
                continue;
            }
        if (primulSelectat && !alDoileaSelectat)
                {
                c2 = selecteazaCerc();
                 if(c1.y <410 and c2.y <410 and (abs(c1.i - c2.i) <=1 and abs(c1.j - c2.j) <= 1) and (c1.i == c2.i or c1.j == c2.j ) and tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] == false and (c1.i != c2.i or c1.j != c2.j))
                {
    if (turaprimuluijucator)
    {
        selectColor(RED);
    }
    else
    {
        selectColor(BLUE);
    }
    fillellipse(c1.x, c1.y, 15, 15);
    fillellipse(c2.x, c2.y, 15, 15);
                line(c1.x, c1.y, c2.x, c2.y);
                out << "Jucatorul "<<!turaprimuluijucator +1<<" a tras linie de la "<<c1.i<<"-"<<c1.j<<" la "<<c2.i <<"-"<<c2.j<<endl;
                maxim++;

               tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] = true;
                tabla[4*(c2.i) + c2.j][4*(c1.i) + c1.j] = true;
               if(verificare(c1,c2, turaprimuluijucator))
                    {
                        out <<"Jucatorul "<<!turaprimuluijucator +1<<" a inchis un patrat!"<<endl;
                        char q[2];
                        char z[2];
                        z[0] = '0' + scor2;
                        q[0]='0'+scor1;
                        q[1]=NULL;
                        z[1] = NULL;
                        if(turaprimuluijucator)
                        {
                            setcolor(RED);
                            outtextxy(80, 560, q);
                        }
                        else
                        {
                            setcolor(BLUE);
                            outtextxy( 310, 560,z );

                        }
                        primulSelectat = false;
                        alDoileaSelectat = false;
                        continue;
                    }
                }
                else
                {
                    primulSelectat = false;
                    alDoileaSelectat = false;
                    continue;
                }
                }
                primulSelectat = false;
                turaprimuluijucator = !turaprimuluijucator;
        }
        if(maxim == 24)
        {
        endgame = true;
        cleardevice();
        settextstyle(FONT,0,FONT_SIZE);
        if(scor1 > scor2)
        {
        if(scor1 == 5)
             outtextxy(310, 250,"Jucatorul 1 castiga cu 5 la 4 !");
        if(scor1 == 6)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 6 la 3 !");
        if(scor1 == 7)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 7 la 2 !");
        if(scor1 == 8)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 8 la 1 !");
        if(scor1 == 9)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 9 la 0 !");
         }
        else
        {
        if(scor2 == 5)
             outtextxy(310, 250,"Jucatorul 2 castiga cu 5 la 4 !");
        if(scor2 == 6)
             outtextxy(310, 250,"Jucatorul 2 castiga cu 6 la 3 !");
        if(scor2 == 7)
            outtextxy(310, 250,"Jucatorul 2 castiga cu 7 la 2 !");
        if(scor2 == 8)
            outtextxy(310, 250,"Jucatorul 2 castiga cu 8 la 1 !");
        if(scor2 == 9)
            outtextxy(310, 250,"Jucatorul 2 castiga cu 9 la 0 !");
        }
        outtextxy(310, 360, "Press any character to close...");
        PlaySound(TEXT("ending.wav"), NULL, SND_ASYNC);
        getch();
        out << "Joc terminat";
        closegraph();
         }
    }
}


void startGameAI()
{
    turaprimuluijucator = true;
    PlaySound(TEXT("lord.wav"), NULL, SND_ASYNC);
    ofstream out("istoric.in");
    initwindow(400, 600);
    sus = 40;
    stanga = 40;
    int marimeTabla = 100;
    int x;
    int y;
    setbkcolor(FUNDAL);
    clearviewport();
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    for (int i = 0; i < numarLinii; i++)
    {
        for (int j=0; j < numarColoane; j++)
        {
            x = sus + j*100;
            y = stanga + i*100;
            fillellipse(x, y, 15, 15);
        }
    }
       setcolor(RED);
    settextstyle(4, 4,  2);
    outtextxy( 130,  530, "Jucator 1");
    outtextxy( 80,  560, "0");
    setcolor(BLUE);
    outtextxy(370, 530, "Computer");
    outtextxy(310, 560, "0");
    bool primulSelectat = false;
    bool alDoileaSelectat = false;
    cerc c1, c2;
    while(!endgame)
    {

        while(!turaprimuluijucator)
        {

                selectColor(BLUE);
                primulSelectat = false;
                c1 = selecteazaCercAI(primulSelectat,0,0);
                primulSelectat = true;
                c2 = selecteazaCercAI(primulSelectat, c1.i,c1.j);
                cout << c2.i << " "<< c2.j;
                if(c1.y <410 and c2.y <410 and (abs(c1.i - c2.i) <=1 and abs(c1.j - c2.j) <= 1) and (c1.i == c2.i or c1.j == c2.j ) and tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] == false and (c1.i != c2.i or c1.j != c2.j))
                {

                fillellipse(c1.x, c1.y, 15, 15);
                fillellipse(c2.x, c2.y, 15, 15);
                line(c1.x, c1.y, c2.x, c2.y);
                out << "Computerul "<<" a tras linie de la "<<c1.i<<"-"<<c1.j<<" la "<<c2.i <<"-"<<c2.j<<endl;
               tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] = true;
                tabla[4*(c2.i) + c2.j][4*(c1.i) + c1.j] = true;
               if(verificare(c1,c2, turaprimuluijucator))
                    {
                        turaprimuluijucator = false;
                        out <<"Jucatorul "<<!turaprimuluijucator +1<<" a inchis un patrat!"<<endl;
                        char q[2];
                        char z[2];
                        z[0] = '0' + scor2;
                        q[0]='0'+scor1;
                        q[1]=NULL;
                        z[1] = NULL;
                        outtextxy( 310, 560,z );
                        primulSelectat = false;
                        alDoileaSelectat = false;
                   }
                   else
                    turaprimuluijucator = true;
            }
        }

        if (ismouseclick(WM_LBUTTONDOWN))
        {
         if (!primulSelectat and turaprimuluijucator)
            {
                c1 = selecteazaCerc();
                primulSelectat = true;
                continue;
            }
            if(turaprimuluijucator and primulSelectat and !alDoileaSelectat)
            {
                c2 = selecteazaCerc();
                alDoileaSelectat = true;

            }
        if (primulSelectat && alDoileaSelectat)
                {
                if(c1.y <410 and c2.y <410 and (abs(c1.i - c2.i) <=1 and abs(c1.j - c2.j) <= 1) and (c1.i == c2.i or c1.j == c2.j ) and tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] == false and (c1.i != c2.i or c1.j != c2.j))
                {
                selectColor(RED);
                fillellipse(c1.x, c1.y, 15, 15);
                fillellipse(c2.x, c2.y, 15, 15);
                line(c1.x, c1.y, c2.x, c2.y);
                out << "Jucatorul "<<!turaprimuluijucator +1<<" a tras linie de la "<<c1.i<<"-"<<c1.j<<" la "<<c2.i <<"-"<<c2.j<<endl;
               tabla[4*(c1.i) + c1.j][4*(c2.i) + c2.j] = true;
                tabla[4*(c2.i) + c2.j][4*(c1.i) + c1.j] = true;
               if(verificare(c1,c2, turaprimuluijucator))
                    {
                        out <<"Jucatorul "<<!turaprimuluijucator +1<<" a inchis un patrat!"<<endl;
                        char q[2];
                        char z[2];
                        z[0] = '0' + scor2;
                        q[0]='0'+scor1;
                        q[1]=NULL;
                        z[1] = NULL;
                        if(turaprimuluijucator)
                        {
                            setcolor(RED);
                            outtextxy(80, 560, q);
                        }
                        else
                        {
                            setcolor(BLUE);
                            outtextxy( 310, 560,z );
                        }
                        primulSelectat = false;
                        alDoileaSelectat = false;
                        continue;
                    }
                }
                else
                {
                    primulSelectat = false;
                    alDoileaSelectat = false;
                    continue;
                }
                }
                primulSelectat = false;
                turaprimuluijucator = !turaprimuluijucator;
        }
        if(maxim == 24)
        {
        endgame = true;
        cleardevice();
        settextstyle(FONT,0,FONT_SIZE);
        if(scor1 > scor2)
        {
        if(scor1 == 5)
             outtextxy(310, 250,"Jucatorul 1 castiga cu 5 la 4 !");
        if(scor1 == 6)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 6 la 3 !");
        if(scor1 == 7)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 7 la 2 !");
        if(scor1 == 8)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 8 la 1 !");
        if(scor1 == 9)
            outtextxy(310, 250,"Jucatorul 1 castiga cu 9 la 0 !");
         }
        else
        {
        if(scor2 == 5)
             outtextxy(310, 250,"Computer castiga cu 5 la 4 !");
        if(scor2 == 6)
             outtextxy(310, 250,"Computer castiga cu 6 la 3 !");
        if(scor2 == 7)
            outtextxy(310, 250,"Computer  castiga cu 7 la 2 !");
        if(scor2 == 8)
            outtextxy(310, 250,"Computer castiga cu 8 la 1 !");
        if(scor2 == 9)
            outtextxy(310, 250,"Comouter castiga cu 9 la 0 !");
        }
        outtextxy(310, 360, "Press any character to close...");

        getch();
        closegraph();
         }
    }
}


void mainMenu()
{
    PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);
    int ok=0;
    cleardevice();
    for(int i=0 ; i<=current_move ; i++)
        move_size[i]=0;
    current_move=0;
    cleardevice();
    while(!ok)
    {
        int x= mousex();
        int y= mousey();

            outtextxy(w/2-80,h/10,"JOC ORIENTAL");
            rectangle(w/3,h/4,2*w/3,h/4+50);
            outtextxy(w/2-90,h/4+15,"Player vs Player");
            rectangle(w/3,h/4+100,2*w/3,h/4+155);
            outtextxy(w/2-100,h/4+120,"Player vs Computer");
            rectangle(w/3, h/2+50, 2*w/3, h/2+120);
            outtextxy(w/2-80,h/4+225,"QUIT GAME");

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            bool pressed=true;
            if(ismouseclick(WM_LBUTTONUP))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                clearmouseclick(WM_LBUTTONUP);
                pressed=false;
            }

            if(isMouseInside(w/3,h/4,2*w/3,h/4+50))
                {if(!pressed)
                {
                    ok=1;
                    cleardevice();
                    closegraph();
                    startGame();
                    return;
                }
                }
                if(isMouseInside(w/3 ,h/4+110, 2*w/3, h/4 +130))
                if(!pressed)
                {
                   ok=1;
                   closegraph();
                   startGameAI();
                    return ;

                }
          if(isMouseInside(w/3, h/2+50, 2*w/3, h/2+120))
            {
                if(!pressed)
                {
                    ok=1;
                    cleardevice();
                    closegraph();
                }
            }
    }
}
}

int main()
{

    w=800;
    h=600;
    initwindow(800, 600,"JOC ORIENTAL");
    settextstyle(FONT,0,FONT_SIZE);
    mainMenu();
    return 0;
}
