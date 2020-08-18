void GamePlay(){

    iSetColor(0,0,0); ///background color
   // iFilledRectangle(0,0,sc_width,sc_height);
    renderImage(0,0,&background);

    shuriken.state+=10;
    if(shuriken.state>shuriken_length)
        shuriken.state=shuriken_length;

    blast.state+=10;
    if(blast.state>blast_length)
        blast.state=blast_length;

    stillcounter++;
    if(stillcounter>15)
        if(c.state==0)SS_COUNT=6;
        else SS_COUNT=7;

    iSetColor(100,100,100);
    if(mode==NO_TRANSLATE){
        for(int i=st_obs[cur_f];i<en_obs[cur_f];++i){
            for(int j=obs[i].x-cur_f*sc_width;j<obs[i].x+obs[i].width-cur_f*sc_width;j=j+brick.width)  /// No translation here
                for(int k=obs[i].y;k<obs[i].y+obs[i].height;k=k+brick.height){
                    renderImage(j,k,&brick);
                }

        }

        for(int i=st_flames[cur_f];i<en_flames[cur_f];++i){
            for(int j=flames[i].x-cur_f*sc_width;j<flames[i].x+flames[i].width-cur_f*sc_width;j=j+flame[flame_ss_count].width)  /// No translation here
                for(int k=flames[i].y;k<flames[i].y+flames[i].height;k=k+flame[flame_ss_count].height){
                    renderImage(j,k,flame+flame_ss_count);
                }

        }

        for(int i=st_mobs[cur_f];i<en_mobs[cur_f];i++)
            if(movobs[i].HP>0){
                renderImage(movobs[i].x-cur_f*sc_width,movobs[i].y, ghost+movobs[i].type);
                iSetColor(255,0,0);
                iFilledRectangle( movobs[i].x-cur_f*sc_width, movobs[i].y+movobs[i].height+8, movobs[i].width*(movobs[i].HP/movobs[i].F_HP), 4);
                iSetColor(0,255,255);
                iRectangle( movobs[i].x-cur_f*sc_width, movobs[i].y+movobs[i].height+8, movobs[i].width, 4);
            }
        for(int i=st_collectable[cur_f];i<en_collectable[cur_f];++i)
            if( grid[collectable[i].x][collectable[i].y] != 0)
                renderImage(collectable[i].x-cur_f*sc_width,collectable[i].y,collectable[i].ss+collectable_ss_count);




        if(collision_detected==NULL) renderImage(c.x-cur_f*sc_width, c.y, SS+SS_COUNT);
        else if( (clock()-collision_detected) % 10 == 0 )
            renderImage(c.x-cur_f*sc_width, c.y, SS+SS_COUNT);




        if(shuriken.state<shuriken_length)
        {
            shuriken_ss_counter=(shuriken_ss_counter+1)%4;
            if(shuriken.width==1) renderImage( shuriken.x+shuriken.state-cur_f*sc_width, shuriken.y+10,  _shuriken+shuriken_ss_counter);
            else renderImage(shuriken.x-shuriken.state-cur_f*sc_width,shuriken.y+10, _shuriken+shuriken_ss_counter);
           //renderImage( shuriken.x+shuriken.state-cur_f*sc_width, shuriken.y+10, shuriken+shuriken_ss_counter);
        }

        if(blast.state<blast_length)
        {
            if(blast.width==1) renderImage( blast.x+blast.state-cur_f*sc_width, blast.y+10,  &blast_r);
            else renderImage(blast.x-blast.state-cur_f*sc_width,blast.y+10, &blast_l);
           //renderImage( shuriken.x+shuriken.state-cur_f*sc_width, shuriken.y+10, shuriken+shuriken_ss_counter);
        }

    }
    else{
        int start = (mode == 1) ? cur_f : cur_f+mode ;
        int _end = (mode == 1) ? cur_f+mode : cur_f ;
        for(int i=st_obs[start];i<en_obs[_end];++i)
            for(int j=obs[i].x+mid-c.x; j<obs[i].x+obs[i].width+mid-c.x ; j=j+brick.width)
                for(int k=obs[i].y;k<obs[i].y+obs[i].height;k=k+brick.height){
                    renderImage(j,k,&brick);
                }

        for(int i=st_flames[start];i<en_flames[_end];++i){
            for(int j=flames[i].x+mid-c.x;j<flames[i].x+flames[i].width+mid-c.x;j=j+flame[flame_ss_count].width)  /// No translation here
                for(int k=flames[i].y;k<flames[i].y+flames[i].height;k=k+flame[flame_ss_count].height){
                    renderImage(j,k,flame+flame_ss_count);
                }

        }

        for(int i=st_mobs[start];i<en_mobs[_end];i++)
            if(movobs[i].HP>0){
                renderImage( movobs[i].x+mid-c.x,movobs[i].y, ghost+movobs[i].type);
                iSetColor(255,0,0);
                iFilledRectangle( movobs[i].x+mid-c.x, movobs[i].y+movobs[i].height+8, movobs[i].width*(movobs[i].HP/movobs[i].F_HP), 4);
                iSetColor(0,255,255);
                iRectangle( movobs[i].x+mid-c.x, movobs[i].y+movobs[i].height+8, movobs[i].width, 4);
            }

        for(int i=st_collectable[start];i<en_collectable[_end];++i)
            if( grid[collectable[i].x][collectable[i].y] != 0 )
                renderImage(collectable[i].x+mid-c.x, collectable[i].y,collectable[i].ss+collectable_ss_count);


        if(collision_detected==NULL) renderImage(mid, c.y, SS+SS_COUNT);
        else if( (clock()-collision_detected) % 10 == 0 )
            renderImage(mid, c.y, SS+SS_COUNT);



        if(shuriken.state<shuriken_length) {
             shuriken_ss_counter=(shuriken_ss_counter+1)%4;
            if(shuriken.width==1) renderImage(mid+shuriken.state,shuriken.y+10, _shuriken+shuriken_ss_counter);
            else renderImage(mid-shuriken.state,shuriken.y+10,_shuriken+shuriken_ss_counter);
        }
        if(blast.state<blast_length) {
            if(blast.width==1) renderImage(mid+blast.state,blast.y+10, &blast_r);
            else renderImage(mid-blast.state,blast.y+10,&blast_l);
        }


    }

    iSetColor(0,0,0);
    iFilledRectangle(0,0,64,sc_height);
    iFilledRectangle(sc_width-64,0,64,sc_height);

    iSetColor(255,255,255);
    iShowBMP2(40,80,"pause.bmp",0);
    iText(50,670,str,GLUT_BITMAP_9_BY_15);
    char num[10],num2[10];
    itoa(points,num,10);
    iText(130,670,num,GLUT_BITMAP_9_BY_15);
    iText(50,650,"Life   x",GLUT_BITMAP_9_BY_15);
    itoa(life,num2,10);
    iText(130,650,num2,GLUT_BITMAP_9_BY_15);
    if(2*c.HP<=c.F_HP)iSetColor(255,0,0);
    else iSetColor(0,255,0);
    iFilledRectangle(50,610,192*(c.HP/c.F_HP),16); // xx
    iSetColor(0,255,0);
    iRectangle(50,610,192,16);


    iSetColor(0,0,255);
    iFilledRectangle(50,590,192*(energy/m_energy),16); // xx
    iSetColor(0,255,0);
    iRectangle(50,590,192,16);

}


void mov_obs_updater()
{
    int i;
    for(i=st_mobs[cur_f];i<en_mobs[cur_f];i++){
            movobs[i].y+=movobs[i].dy;
            movobs[i].dy+=g;

            int dir;
            if(movobs[i].dx<0) dir=0;
            else dir=1;
            if( grid[ (int)(movobs[i].x+dir*movobs[i].width+movobs[i].dx) ][ (int)(movobs[i].y+4) ] == 1  || grid[ (int)(movobs[i].x+dir*movobs[i].width+movobs[i].dx) ][ (int)(movobs[i].y+movobs[i].height) ] == 1 || movobs[i].y < 0.0){
                movobs[i].dx=-movobs[i].dx;
                movobs[i].dy=15;
                ++movobs[i].y;
            }
            else
                movobs[i].x+=movobs[i].dx;

            if( grid[ (int)movobs[i].x ][ (int)(movobs[i].y) ] == 1 || grid[ (int)(movobs[i].x+movobs[i].width) ][ (int)(movobs[i].y) ] == 1){
                ++movobs[i].y;
                movobs[i].dy = 0;
            }

            if( grid[(int)(movobs[i].x+movobs[i].width)][(int)(movobs[i].y+movobs[i].height)] == 1|| grid[(int)(movobs[i].x)][(int)(movobs[i].y+movobs[i].height)] == 1 ){ ///AN OBSTACLE ABOVE THE CHARACTER
                --movobs[i].y;
                movobs[i].dy = -0.3*movobs[i].dy;
                movobs[i].dx=-movobs[i].dx ;
            }
    }

    if(mode!=NO_TRANSLATE){
        for(i=st_mobs[cur_f+mode];i<en_mobs[cur_f+mode];i++){
            movobs[i].y+=movobs[i].dy;
            movobs[i].dy+=g;
            int dir;
            if(movobs[i].dx<0) dir=0;
            else dir=1;

            if( grid[ (int)(movobs[i].x+dir*movobs[i].width+movobs[i].dx+4) ][ (int)(movobs[i].y+movobs[i].height) ] == 1 || grid[ (int)(movobs[i].x+dir*movobs[i].width+movobs[i].dx) ][ (int)(movobs[i].y+movobs[i].height) ] == 1 || movobs[i].y < 0.0 ){
                movobs[i].dx=-movobs[i].dx;
                movobs[i].dy=15;
                ++movobs[i].y;
            }
            else
                movobs[i].x+=movobs[i].dx;

            if( grid[ (int)movobs[i].x ][ (int)(movobs[i].y) ] == 1|| grid[ (int)(movobs[i].x+movobs[i].width) ][ (int)(movobs[i].y) ] == 1){ /// CHECKS FOR AN OBSTACLE BENEATH THE CHARACTER i.e CHARCTER TOUCHED THE GROUND
                ++movobs[i].y;
                movobs[i].dy = 0;
            }

            if( grid[(int)(movobs[i].x+movobs[i].width)][(int)(movobs[i].y+movobs[i].height)] == 1 || grid[(int)(movobs[i].x)][(int)(movobs[i].y+movobs[i].height)] == 1 ){ /// CHECKS FOR AN OBSTACLE ABOVE THE CHARACTER
                --movobs[i].y;
                movobs[i].dy = -0.3*movobs[i].dy; /// THE DOWNWARDS VELOCITY AFTER HITTING, THERE WILL BE A REDUCTION IN VELOCITY, I ASSUMED IT FOR 40 PERCENT
                movobs[i].dx=-movobs[i].dx ;
            }
        }

    }
}


void cUpdater()
{
    energy=min(energy+1,m_energy);
    if(c.x>(N_F-1)*sc_width+ 1088 && movobs[N_MOBS-1].HP <= 0.0){
        gamemode=6;
    }

    c.y+=c.dy;
    c.dy+=g;
    if(c.dx!=0.0){
        c.dx+=ax;

        if(c.dx>0.0){
            if(grid[ (int)(c.x+c.width+c.dx) ][ (int)(c.y+4) ] == 1 || grid[ (int)(c.x+c.width+c.dx) ][ (int)(c.y+c.height) ] == 1 || grid[ (int)(c.x+c.width+c.dx) ][ (int)(c.y+c.height/2) ] == 1)
                c.dx=0.0;
            c.x+=c.dx;
        }
        else if(c.dx<0.0){
            if(grid[ (int)(c.x+c.dx) ][ (int)(c.y+4) ] == 1 || grid[ (int)(c.x+c.dx) ][ (int)(c.y+c.height) ] == 1 || grid[ (int)(c.x+c.dx) ][ (int)(c.y+c.height/2) ] == 1)
                c.dx=0.0;
            c.x+=c.dx;
        }
    }
    if( grid[ (int)c.x ][ (int)(c.y) ] == 1 || grid[ (int)(c.x+c.width) ][ (int)(c.y) ] == 1 ){ /// CHECKS FOR AN OBSTACLE BENEATH THE CHARACTER i.e CHARCTER TOUCHED THE GROUND
        ++c.y;
        c.dy = 0;
        c_stats = c_stats & ~(1<<1) ; /// TURNS OFF THE JUMP STAT i.e "STAND", AFTER THIS, THE CHARACTER CAN JUMP IF UP_ARROW IS PRESSED
    }
    if( grid[(int)(c.x+c.width)][(int)(c.y+c.height)] == 1|| grid[(int)(c.x)][(int)(c.y+c.height)] == 1){ /// CHECKS FOR AN OBSTACLE ABOVE THE CHARACTER
        --c.y;
        c.dy = -0.6*c.dy; /// THE DOWNWARDS VELOCITY AFTER HITTING, THERE WILL BE A REDUCTION IN VELOCITY, I ASSUMED IT FOR 40 PERCENT
    }




    int CENTER = grid[(int)(c.x+c.width/2)][(int)(c.y+c.height/2)] ;
    if( CENTER > OBS ){
        if(CENTER == COIN)
            points+=10;
        else if(CENTER == DIAMOND)
            points+=50;
        else if(CENTER == APPLE)
            c.HP=min((c.HP+50),c.F_HP);
       else if(CENTER == LIFE)
                ++life ;


        players[5].score=points;
        int x=c.x+c.width/2,y=c.y+c.height/2;
        while( grid[x][y] == CENTER)
            x--;
       ++x;
        while( grid[x][y] == CENTER)
            y--;
        ++y;
        for(int i=x;i<x+collectable_length;++i)
            for(int j=y;j<y+collectable_length;++j)
                grid[i][j] = 0;

    }

}

void collision()
{
//collision between shuriken and my cute ghost
    if(shuriken.state<shuriken_length){
        int pos;
        pos=(int)(shuriken.x+shuriken.state*shuriken.width); //%(int)sc_width; //xxx
        for(int i=st_mobs[cur_f];i<en_mobs[cur_f];i++){
            if(pos>movobs[i].x && pos< movobs[i].x+movobs[i].width && shuriken.y+16>movobs[i].y && shuriken.y+16<movobs[i].y+movobs[i].height){
                if(movobs[i].HP>0){
                    shuriken.state=shuriken_length;

                    if(movobs[i].HP-50 > 0)
                        movobs[i].HP=movobs[i].HP-50;
                    else {
                        movobs[i].HP=0;
                        movobs[i].state=1;
                        points+=50;
                        players[5].score=points;
                    }
                    //movobs[i].state=1;
                }
            }
        }

        if(mode!=NO_TRANSLATE){
            for(int i=st_mobs[cur_f+mode];i<en_mobs[cur_f+mode];i++){
                if(pos>movobs[i].x && pos< movobs[i].x+movobs[i].width && shuriken.y+10>movobs[i].y && shuriken.y+10<movobs[i].y+movobs[i].height){
                        if(movobs[i].HP>0){
                           // movobs[i].HP=(movobs[i].HP-50 > 0) ? movobs[i].HP-50 : 0;
                           // movobs[i].state=1;
                           shuriken.state=shuriken_length;
                            if(movobs[i].HP-50 > 0)
                                movobs[i].HP=movobs[i].HP-50;
                            else {
                                movobs[i].HP=0;
                                movobs[i].state=1;
                                points+=50;
                                players[5].score=points;
                            }
                        }
                }
            }
        }
    }


    //collision between blast and my cute ghost
    if(blast.state<blast_length){
        int pos;
        pos=(int)(blast.x+blast.state*blast.width); //%(int)sc_width; //xxx
        for(int i=st_mobs[cur_f];i<en_mobs[cur_f];i++){
            if(pos>movobs[i].x && pos< movobs[i].x+movobs[i].width && blast.y+16>movobs[i].y && blast.y+16<movobs[i].y+movobs[i].height){
                if(movobs[i].HP>0){
                        blast.state=blast_length;
                    if(movobs[i].HP-500 > 0)
                        movobs[i].HP=movobs[i].HP-50;
                    else {
                        movobs[i].HP=0;
                        movobs[i].state=1;
                        points+=50;
                        players[5].score=points;
                   }
                    //movobs[i].state=1;
                }
            }
        }

        if(mode!=NO_TRANSLATE){
            for(int i=st_mobs[cur_f+mode];i<en_mobs[cur_f+mode];i++){
                if(pos>movobs[i].x && pos< movobs[i].x+movobs[i].width && blast.y+10>movobs[i].y && blast.y+10<movobs[i].y+movobs[i].height){
                        if(movobs[i].HP>0){
                            blast.state=blast_length;
                        if(movobs[i].HP-500 > 0)
                            movobs[i].HP=movobs[i].HP-50;
                        else {
                            movobs[i].HP=0;
                            movobs[i].state=1;
                            points+=50;
                            players[5].score=points;
                   }
                        }
                }
            }
        }
    }

    //collision 0of character and my cute ghost
        for(int i=st_mobs[cur_f];i<en_mobs[cur_f];i++){
            if( (c.x+c.width/2)>movobs[i].x && (c.x+c.width/2)< movobs[i].x+movobs[i].width && (c.y+c.height/2)>movobs[i].y && (c.y+c.height/2)<movobs[i].y+movobs[i].height && movobs[i].state==0){
                //life--;
               // c.x=100;
              //  c.y=600;
              c.HP-=100;
              if(c.HP<=0){
                life--;
                c.HP=500;
                c.x=100;
                c.y=600;
              }
                collision_detected = clock();
                iPauseTimer(2);
                ///Sleep(3000);

            }
          //  else
            //    collision_detected = NULL;
        }

    if(c.y <= 0.0){
        life--;
        c.x=100;
        c.y=600;

    }
    if(life<1){
            updatescore();
            gamemode=5;
            for(int i=0;i<4;i++)
                iPauseTimer(i);
        }


}

void story(){
   if( clock() > collision_detected+3000){
        iResumeTimer(2);
        collision_detected = NULL;
   }

   cur_f = floor(c.x/sc_width);
   int k = floor(c.x/mid);
   // mode = NO_TRANSLATE;
    if(c.x < mid || c.x >= (N_F)*sc_width-mid)
        mode = NO_TRANSLATE;
    else{
        if(k&1) mode = TRANSLATE_R;
        else mode = TRANSLATE_L;
    }
}

void animate_collectables(){
    ++collectable_ss_count;
    if(collectable_ss_count > 9)
        collectable_ss_count = 0;

    ++flame_ss_count;
    if(flame_ss_count == n_flame_ss)
        flame_ss_count = 0;
}
