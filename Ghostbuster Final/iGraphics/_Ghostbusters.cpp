#include "iGraphics.h"
#include "gl.h"
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#include "declarations.h"
#include "animations.h"


int take=1;
void iDraw()
{
    iClear();
    if (gamemode==-2)       take_name();
    else if(gamemode==-1)   iShowBMP(0,0,"menu3.bmp");
    else if(gamemode==0)    GamePlay();
    else if(gamemode==1 or gamemode>=4/*5,6*/) show_score();
    else if(gamemode==2)    _exit();
    else if(gamemode==3)    iShowBMP(0,0,"resume.bmp");
    else if(gamemode==-3) iShowBMP(0,0,"instruction.bmp");

}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      //  printf("%d, %d, 64-> %d*sc_width+%d, %d\n", mx, my, cur_f, (mx/64)*64, (my/64)*64) ;
        if(gamemode==-1 ){
            if(mx>425 and mx<870 and my>475 and my<580){
                c.x=128; //xxx
                c.y=320;
                for(int i=0;i<4;i++) iResumeTimer(i);
                gamemode=-2;
            }
            else if(mx>425 and mx<870  and my>310 and my<420) gamemode=1;
            else if(mx>425 and mx<870  and my>145 and my<255) gamemode=2;
            else if(mx>15 and mx<15+73 and my>120 and my<193) { temp_gamemode=gamemode; gamemode=-3; }
        }
        else if(gamemode==3){
            if(mx>425 and mx<870 and my>475 and my<580){
                for(int i=0;i<4;i++) iResumeTimer(i);
                gamemode=0;
            }
            else if(mx>425 and mx<870  and my>310 and my<420) gamemode=4;
            else if(mx>425 and mx<870  and my>145 and my<255) gamemode=2;
            else if(mx>15 and mx<15+73 and my>120 and my<193) { temp_gamemode=gamemode; gamemode=-3; }
        }
        else if(gamemode==0){
            if(mx<240 and mx<450 and my>80 and my<150)  for(int i=0;i<4;i++)iPauseTimer(i),gamemode=3;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}

void iKeyboard(unsigned char key)
{
    if(gamemode == -2)
	{
        if(key == '\r')
		{
		    iResumeTimer(0);
		    iResumeTimer(1);
		    iResumeTimer(2);
		    iResumeTimer(3);
		    takehighscore();
			gamemode = 0;
		}
		else if(key == '\b' and len>0) str[--len]='\0';
		else
		{
			str[len] = key;
			len++;
		}
	}
	else if(gamemode==1 and key=='b') gamemode=-1;
	else if(gamemode==4 and key== 'b') gamemode=3;
	else if(gamemode>=5 and key=='\r') gamemode=2;
	else if(gamemode==-3 and key=='b') gamemode=temp_gamemode;
	else{
        if(key == 'p')
    {
        for(int i=0;i<4;i++)
            iPauseTimer(i);
    }
    if(key == 'r')
    {
        for(int i=0;i<4;i++)
            iResumeTimer(i);

    }
    if(key == 'f' )
    {

        shuriken.state=0; shuriken.x=c.x; shuriken.y=c.y+16;
        if(c.state==0) shuriken.width=1,SS_COUNT = 8; else shuriken.width=-1,SS_COUNT = 9;
    }

    if(key == 'b' and energy>=300)
    {
        energy-=300;
        blast.state=0; blast.x=c.x; blast.y=c.y+16;
        if(c.state==0) blast.width=1,SS_COUNT = 8; else blast.width=-1,SS_COUNT = 9;
    }


	}

}

void getkey(){
    if(GetAsyncKeyState(VK_ESCAPE) )
        exit(0);
    if(GetAsyncKeyState(VK_LEFT) ){
            c.dx=-10.0;
            ax=1;
            SS_COUNT++; stillcounter=0;
            if(SS_COUNT>5 or SS_COUNT<3) SS_COUNT=3;
            c.state=1;
    }
    if(GetAsyncKeyState(VK_RIGHT) ){
            c.dx=10.0;
            ax=-1;
            SS_COUNT++; stillcounter=0;
            if(SS_COUNT>2) SS_COUNT=0;
            c.state=0;
    }
    if(GetAsyncKeyState(VK_UP) ){
        if( (c_stats & 1) == 1){ //checks if the charac is in duck position
            if( !( grid[(int)(c.x+c.width)][(int)(c.y+prev_height)] || grid[(int)(c.x)][(int)(c.y+prev_height)]  ) ){
                c.height=prev_height;
                c_stats = c_stats ^ 1 ; //TOGGLES THE DUCK STAT
            }
        }
        else if( (c_stats & (1<<1)) == 0 ) /// CHECKS "THE JUMP STAT IS OFF"
        {
            c.dy=15; /// jump velocity
            c_stats = c_stats ^ (1<<1) ; /// TOGGLES THE STAT i.e THE CHARACTER WON'T JUMP WHILE JUMPING
         }
    }
    if(GetAsyncKeyState(VK_DOWN) ){
        if( (c_stats & 1) == 0){  /// CHECKS "THE CHARCTER IS STANDING"
            prev_height=c.height;
            c.height -= 0.4*c.height;
            c_stats = c_stats ^ 1 ; /// TOGGLES THE STAT "STAND" TO "DUCK"
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
}




int main()
{
    //PlaySound( (LPCSTR) "The Trooper.mp3", NULL, SND_FILENAME | SND_ASYNC ) ;


    load_level_info();
    takehighscore();
    flame[0] = imageLoader("flame1_violet.bmp",0);
    flame[1] = imageLoader("flame2_violet.bmp",0);
    flame[2] = imageLoader("flame3_violet.bmp",0);
    brick = imageLoader("brick5.bmp");
    background = imageLoader("bg.bmp");
    ghost[0] = imageLoader("ghost2.bmp",0);
    ghost[1] = imageLoader("ghost3.bmp",0);
    ghost[2] = imageLoader("ghost4.bmp",0);

    blast_l=imageLoader("blastl.bmp",0);
    blast_r=imageLoader("blastr.bmp",0);

    _shuriken[0] = imageLoader("shuriken1.bmp",0);
    _shuriken[1] = imageLoader("shuriken2.bmp",0);
    _shuriken[2] = imageLoader("shuriken3.bmp",0);
    _shuriken[3] = imageLoader("shuriken4.bmp",0);

    SS[0] = imageLoader("S1.bmp",0);
    SS[1] = imageLoader("S2.bmp",0);
    SS[2] = imageLoader("S3.bmp",0);
    SS[3] = imageLoader("S4.bmp",0);
    SS[4] = imageLoader("S5.bmp",0);
    SS[5] = imageLoader("S6.bmp",0);
    SS[6] = imageLoader("S10.bmp",0);
    SS[7] = imageLoader("S11.bmp",0);
    SS[8] = imageLoader("S16.bmp",0);
    SS[9] = imageLoader("S17.bmp",0);

    coin[0] = imageLoader("coin1.bmp",0);
    coin[1] = imageLoader("coin2.bmp",0);
    coin[2] = imageLoader("coin3.bmp",0);
    coin[3] = imageLoader("coin4.bmp",0);
    coin[4] = imageLoader("coin5.bmp",0);
    coin[5] = imageLoader("coin6.bmp",0);
    coin[6] = imageLoader("coin7.bmp",0);
    coin[7] = imageLoader("coin8.bmp",0);
    coin[8] = imageLoader("coin9.bmp",0);
    coin[9] = imageLoader("coin10.bmp",0);

    heart[0] = imageLoader("heart1.bmp",0);
    heart[1] = imageLoader("heart2.bmp",0);
    heart[2] = imageLoader("heart3.bmp",0);
    heart[3] = imageLoader("heart4.bmp",0);
    heart[4] = imageLoader("heart5.bmp",0);
    heart[5] = imageLoader("heart6.bmp",0);
    heart[6] = imageLoader("heart7.bmp",0);
    heart[7] = imageLoader("heart8.bmp",0);
    heart[8] = imageLoader("heart9.bmp",0);
    heart[9] = imageLoader("heart10.bmp",0);


    diamond[0] = imageLoader("diamond1.bmp",0);
    diamond[1] = imageLoader("diamond2.bmp",0);
    diamond[2] = imageLoader("diamond3.bmp",0);
    diamond[3] = imageLoader("diamond4.bmp",0);
    diamond[4] = imageLoader("diamond5.bmp",0);
    diamond[5] = imageLoader("diamond6.bmp",0);
    diamond[6] = imageLoader("diamond7.bmp",0);
    diamond[7] = imageLoader("diamond8.bmp",0);
    diamond[8] = imageLoader("diamond9.bmp",0);
    diamond[9] = imageLoader("diamond10.bmp",0);

    for(int i=0;i<10;i++)
        apple[i] = imageLoader("apple.bmp",0);


    iSetTimer(5, cUpdater);
    iSetTimer(5, mov_obs_updater);
    iSetTimer(5, collision);
    iSetTimer(50,story);
    iSetTimer(100,animate_collectables);
    iSetTimer(20,getkey);


    iInitialize(sc_width, sc_height,"GHOST BUSTER");



    for(int i=0;i<10;i++){
        free(diamond[i].pixels);
        free(heart[i].pixels);
        free(coin[i].pixels);
    }

    free(blast_l.pixels);
    free(blast_r.pixels);

    free(flame[0].pixels);
    free(flame[1].pixels);
    free(flame[2].pixels);
    free(background.pixels) ;
    free(brick.pixels);
    free(ghost[0].pixels);
    free(ghost[1].pixels);
    free(ghost[2].pixels);
    for(int i=0;i<4;i++)
    free(_shuriken[i].pixels);

    for(int i=0;i<10;i++)
    free(SS[i].pixels);

    return 0;
}

