#define NO_TRANSLATE 0
#define TRANSLATE_R 1
#define TRANSLATE_L -1

#define OBS 1
#define COIN 3
#define HEALTH 7
#define LIFE 8
#define DIAMOND 9
#define APPLE 10

#define MENU -1
#define PLAY 0
#define INPUT -2
#define APPLE 10

typedef unsigned int uint;
const double pi=acos(-1.0);
const double acc=1e-8;
const int unit=10;
const int sc_width=1280;
const int sc_height=704;
const int N_F = 15 ; ///Number of frames
short grid[sc_width*N_F+1][sc_height] = {0} ;
int mid=sc_width/2.0;
int cur_f=0;  /// current frame, used in iDraw() to draw obstacles
int mode=0;
int gamemode = -1;
int temp_gamemode;
double g=-0.5; /// the global gravitational acceleration ..
clock_t collision_detected;

typedef struct{
    double x,y,width,height;
} Rect;

typedef struct{
    double x,y,width,height;
    double dx,dy;
    int state; // for dead or alive, state 0 for alive and 1 for dead :( for avatar the direction of motion. 0 for right
    float HP;
    float F_HP;
}  character;

typedef struct{
    char name[10];
    int score;
}  Player_info;
typedef struct{
    int *pixels;
    int height;
    int width;
}  img;




int SS_COUNT,stillcounter,life=3;
uint c_stats = 0;
int points;
int prev_height; /// this var lets to stand if UP_ARROW is pressed while ducking
character c = {2*sc_width+50,300,50,80,0,0,0,500.0,500.0}; /// attributes of the character
double ax;

const int shuriken_length = 200;
character shuriken;
img _shuriken[4];
int shuriken_ss_counter=0;

float energy;
float m_energy=500.0;
character blast;
img blast_l,blast_r;
const int blast_length = 200;

Player_info players[6];


const int N_MOBS=60;
int st_mobs[N_F] = {0};//{0,4,6,9};
int en_mobs[N_F] = {0};//{4,6,9,12};
img ghost[3];
struct {
    double x,y,width,height;
    double dx,dy;
    int state; // for dead or alive, state 0 for alive and 1 for dead :( for avatar the direction of motion. 0 for right
    float HP;
    float F_HP;
    int type;
}
movobs[N_MOBS]={

                    {320,576,50,60,2,0,0,200,200,0},
                    {384,320,50,60,2,0,0,200,200,0},
                    {384,576,50,60,2,0,0,200,200,0},
                    {384,128,50,60,2,0,0,200,200,0},
                    {896,256,50,60,2,0,0,200,200,0},

                    {sc_width+100,600,50,60,2,0,0,200,200,0},
                    {sc_width+400,300,50,60,2,0,0,200,200,0},
                    {sc_width+400,600,50,60,2,0,0,200,200,0},
                    {sc_width+704,448,50,60,2,0,0,200,200,0},
                    {sc_width+1024,192,50,60,2,0,0,300,300,1},


                    {sc_width*2+100,600,50,60,2,0,0,200,200,0},
                    {sc_width*2+400,300,50,60,2,0,0,200,200,0},
                    {sc_width*2+400,600,50,60,2,0,0,300,300,1},
                    {2*sc_width+832, 576,50,60,2,0,0,200,200,0},
                    {2*sc_width+832, 128,50,60,2,0,0,300,300,1},


                    {sc_width*3+100,600,50,60,2,0,0,200,200,0},
                    {sc_width*3+400,300,50,60,2,0,0,200,200,0},
                    {sc_width*3+400,600,50,60,2,0,0,200,200,0},
                    {3*sc_width+832, 512,50,60,2,0,0,200,200,0},
                    {3*sc_width+1088, 256,50,60,2,0,0,300,300,1},

                    {4*sc_width+896, 128,50,60,2,0,0,200,200,0},
                    {4*sc_width+256, 384,50,60,2,0,0,200,200,0},
                    {4*sc_width+832, 576,50,60,2,0,0,300,300,1},
                    {4*sc_width+256, 128,50,60,2,0,0,300,300,1},


                    {5*sc_width+256, 320,50,60,2,0,0,200,200,0},
                    {5*sc_width+704, 320,50,60,2,0,0,200,200,0},
                    {5*sc_width+960, 384,50,60,2,0,0,200,200,0},
                    {5*sc_width+1088, 192,50,60,2,0,0,300,300,1},
                    {5*sc_width+384, 448,50,60,2,0,0,200,200,0},

                    {6*sc_width+320, 0,50,60,2,0,0,200,200,0},
                    {6*sc_width+640, 0,50,60,2,0,0,200,200,0},
                    {6*sc_width+896, 128,50,60,2,0,0,200,200,0},
                    {6*sc_width+448, 384,50,60,2,0,0,200,200,0},
                    {6*sc_width+960, 576,50,60,2,0,0,200,200,0},


                    {8*sc_width+448, 64,50,60,2,0,0,200,200,0},
                    {8*sc_width+512, 576,50,60,2,0,0,200,200,0},
                    {8*sc_width+960, 64,50,60,2,0,0,200,200,0},
                    {8*sc_width+832, 384,50,60,2,0,0,200,200,0},


                    {9*sc_width+256, 192,50,60,2,0,0,200,200,0},
                    {9*sc_width+384, 384,50,60,2,0,0,200,200,0},
                    {9*sc_width+832, 256,50,60,2,0,0,200,200,0},
                    {9*sc_width+1024, 384,50,60,2,0,0,200,200,0},


                    {10*sc_width+576, 448,50,60,2,0,0,200,200,0},
                    {10*sc_width+960, 384,50,60,2,0,0,200,200,0},
                    {10*sc_width+576, 128,50,60,2,0,0,200,200,0},
                    {10*sc_width+256, 128,50,60,2,0,0,200,200,0},
                    {10*sc_width+128, 448,50,60,2,0,0,200,200,0},


                    {11*sc_width+576, 512,50,60,2,0,0,200,200,0},
                    {11*sc_width+832, 256,50,60,2,0,0,200,200,0},
                    {11*sc_width+512, 128,50,60,2,0,0,200,200,0},
                    {11*sc_width+256, 256,50,60,2,0,0,200,200,0},

                    {12*sc_width+256, 384,50,60,2,0,0,200,200,0},
                    {12*sc_width+640, 512,50,60,2,0,0,200,200,0},
                    {12*sc_width+1024,192,50,60,2,0,0,200,200,0},

                    {13*sc_width+640, 384,50,60,2,0,0,200,200,0},

                    {14*sc_width+384, 384,50,60,2,0,0,200,200,0},
                    {14*sc_width+576, 384,50,60,2,0,0,200,200,0},
                    {14*sc_width+896, 384,50,60,2,0,0,200,200,0},
                    {14*sc_width+832, 384,50,60,2,0,0,200,200,0},
                    {14*sc_width+640, 320,75,90,4,0,0,1000,1000,2}



};


const int n_flames = 12;
const int n_flame_ss = 3;
int flame_ss_count = 0;
int st_flames[N_F] = {0};
int en_flames[N_F] = {0};
img flame[3];
Rect flames[n_flames] = {{512,0,128,128},
                        {sc_width+128,0,320,128},
                        {sc_width+576,0,sc_width-512+192,128},
                        {4*sc_width+192,0,704,128},
                        {5*sc_width+64,0,1216,128},
                        {6*sc_width+320,0,576,128},
                        {7*sc_width+0,0,sc_width+256,128},
                        {9*sc_width+640,0,640,128},
                        {10*sc_width+320,0,256,128},
                        {11*sc_width+512,0,320,128},
                        {12*sc_width+640,0,192,128},
                        {13*sc_width,0,sc_width,128}
    } ;

const int N_OBS =89; ///Number of obstacles
int en_obs[N_F] = {0};//= {8,14,21,28,35,42,49,56,63,70,77,84,91,98,105}; //ending index
int st_obs[N_F] = {0};//= {0,8,14,21,28,35,42,49,56,63,70,77,84,91,98}; //starting index
Rect obs[N_OBS] ={
                    {0.0,0,512,128},  /// here goes the description of the obstacles
                    {320.0,256,256,64},
                    {576.0,448,192,64},
                    {832.0,192,256,64},
                    {640.0, 0, 64, 256},
                    {704.0, 0, sc_width-704, 64},
                    {1152.0+64.0,64, 64, 256},
                    {1152.0+64.0,448, 64, 256},

                    {1*sc_width,0, 128, 256+64},
                    {1*sc_width,448, 128, 256},
                    {1*sc_width+128,256,128,64},
                    {1*sc_width+448,0,128,256},
                    {1*sc_width+448, 576, 128, 128},
                    {1*sc_width+704,384,192,64},
                    {1*sc_width+1024,128,320,64},
                    {1*sc_width+1152,192, 128, 128},

                    {2*sc_width+256,0,sc_width-256,128},
                    {2*sc_width+1152,128,128,128},
                    {2*sc_width+576,256,512,64},
                    {2*sc_width+640,320,384,64},
                    {2*sc_width+704,384,256,64},
                    {2*sc_width+768,448,128,64},

                    {3*sc_width,0,sc_width,128},
                    {3*sc_width+0,128,64,128},
                    {3*sc_width+256,192,sc_width-256,64},
                    {3*sc_width+448,256,sc_width-448-192,64},
                    {3*sc_width+576,320,sc_width-576-192,64},
                    {3*sc_width+704,384,sc_width-704,64},
                    {3*sc_width+832,448,sc_width-832-192,64},

                    {4*sc_width,0,192,128},
                    {4*sc_width+896,0,sc_width-896,128},
                    {4*sc_width+256,320,448,64},
                    {4*sc_width+1152,128,128,192},
                    {4*sc_width+1152,448,128,256},


                    {5*sc_width,0,64,320},
                    {5*sc_width,448,64,256},
                    {5*sc_width+256, 256, 64, 64},
                    {5*sc_width+384, 384, 64, 64},
                    {5*sc_width+512, 448, 64, 64},
                    {5*sc_width+704, 256, 64, 64},
                    {5*sc_width+1024, 320, 64, 64},
                    {5*sc_width+1152, 128, 64, 64},
                    {5*sc_width+448, 640, 192, 64},

                    {6*sc_width, 0, 320, 64},
                    {6*sc_width+896, 0, sc_width-896, 128},
                    {6*sc_width+448, 320, 320, 64},
                    {6*sc_width+960, 512, 384, 64},
                    {6*sc_width+1152, 576, 128, 192},

                    {7*sc_width,256,64,64},
                    {7*sc_width+448,128,640,64},
                    {7*sc_width+512,192,512,64},
                    {7*sc_width+576,256,384,64},
                    {7*sc_width+640,320,256,64},
                    {7*sc_width+704,384,128,64},
                    {7*sc_width+1152,384,256,64},

                    {8*sc_width+320, 0, 128, 512},
                    {8*sc_width+448, 0, sc_width-448, 64},
                    {8*sc_width+768, 256, 192, 64},
                    {8*sc_width+832, 320, 64, 64},


                    {9*sc_width, 0, 640, 128},
                    {9*sc_width+256, 128, 128, 64},
                    {9*sc_width+384, 128, 128, 256},
                    {9*sc_width,448, 256, 256},
                    {9*sc_width+832, 192, 320, 64},
                    {9*sc_width+1024, 320, 320, 64},


                    {10*sc_width, 0, 320, 128},
                    {10*sc_width+128, 128, 128, 320},
                    {10*sc_width+576, 0, sc_width-576, 128},
                    {10*sc_width+384, 256, 320, 64},
                    {10*sc_width+576, 256, 128, 192},
                    {10*sc_width+960, 128, 128, 64},
                    {10*sc_width+960, 256, 192, 128},
                    {10*sc_width+1152, 128, 128, 256},

                    {11*sc_width,0,512,256},
                    {11*sc_width,576,512,256},
                    {11*sc_width+640,384,192,128},
                    {11*sc_width+832,0,448,256},
                    {11*sc_width+896,448,512,256},
                   // {11*sc_width+576, 128, 128, 192},
                   // {11*sc_width+640, 192, 128, 128},

                    {12*sc_width,0,640,192},
                    {12*sc_width+832,0,sc_width-832,192},
                   // {12*sc_width+64,256,256,128},
                 //   {12*sc_width+128,384,192,128},
                    {12*sc_width+sc_width-256,sc_height-192,192,192},
                    {12*sc_width+512, 192, 128, 192},
                    {12*sc_width+832, 192, 128, 192},
                    {12*sc_width+832, 256, 128, 128},

                    {13*sc_width+0,512,sc_width,192},
                    {13*sc_width+320,192,832,64},
                   // {13*sc_width+128,384,192,128},
                   // {13*sc_width+sc_width-256,sc_height-256,192,192},
                   // {13*sc_width+384, 192, 128, 128},
                   // {13*sc_width+576, 192, 128, 128},
                   // {13*sc_width+576, 256, 128, 128},




                    {14*sc_width,0,sc_width,256},
                    {14*sc_width,512,sc_width,128},
                    {14*sc_width,256,64,64},
                   // {14*sc_width+64,384,192,128},
                   // {14*sc_width+sc_width-384,sc_height-192,256,192},
                   // {14*sc_width+512, 192, 128, 192},
                   // {14*sc_width+640, 192, 128, 192},
                   // {14*sc_width+832, 256, 128, 128},

             } ;

const int n_collectable = 137;
int collectable_ss_count;
const int collectable_length = 64;
int st_collectable[N_F] = {0};//,10,12,18} ;
int en_collectable[N_F] = {0};//10,12,18,24} ;
img coin[10],heart[10],diamond[10],apple[10];
struct {
   int x,y;
   char type;
   img *ss;
} collectable[n_collectable] = {
                        {320, 320,COIN,coin},
                        {384, 320,APPLE,apple},
                        {448, 320,COIN,coin},
                        {512, 320,COIN,coin},
                        {576, 512,COIN,coin},
                        {640, 512,APPLE,apple},
                        {704, 512,COIN,coin},
                        {960, 576,COIN,coin},
                        {128, 512,LIFE,heart},
                        {832, 256,DIAMOND,diamond},

                        {sc_width+64,320,COIN,coin},
                        {sc_width+128,320,COIN,coin},
                        {sc_width+128,512,DIAMOND,diamond},
                        {sc_width+192,320,COIN,coin},
                        {sc_width+192,576,COIN,coin},
                        {sc_width+256,192,DIAMOND,diamond},
                        {sc_width+448,256,COIN,coin},
                        {sc_width+512,256,DIAMOND,diamond},
                        {sc_width+576,256,COIN,coin},
                        {sc_width+704,448,COIN,coin},
                        {sc_width+1024,512,COIN,coin},
                        {sc_width+768,448,DIAMOND,diamond},
                        {sc_width+1088,576,DIAMOND,diamond},
                        {sc_width+1024,192,APPLE,apple},
                        {sc_width+768,128,LIFE,heart},


                        {2*sc_width+556,320,COIN,coin},
                        {2*sc_width+620,384,COIN,coin},
                        {2*sc_width+684,448,COIN,coin},
                        {2*sc_width+896,448,COIN,coin},
                        {2*sc_width+960,384,COIN,coin},
                        {2*sc_width+1024,320,COIN,coin},
                        {2*sc_width+768,512,DIAMOND,diamond},
                        {2*sc_width+832,512,APPLE,apple},

                        {3*sc_width+1088,320,LIFE,heart},
                        {3*sc_width+768,448,COIN,coin},
                        {3*sc_width+448,384,COIN,coin},
                        {3*sc_width+896,512,APPLE,apple},
                        {3*sc_width+1088,256,APPLE,apple},
                        {3*sc_width+576,384,DIAMOND,diamond},


                        {4*sc_width+256,384,COIN,coin},
                        {4*sc_width+448,384,COIN,coin},
                        {4*sc_width+640,384,COIN,coin},
                        {4*sc_width+1152,384,DIAMOND,diamond},
                        {4*sc_width+320, 384,DIAMOND,diamond},
                        {4*sc_width+512, 384,DIAMOND,diamond},
                        {4*sc_width+320, 448,COIN,coin},
                        {4*sc_width+448, 448,APPLE,apple},
                        {4*sc_width+512, 448,APPLE,apple},
                        {4*sc_width+384, 512,COIN,coin},

                        {5*sc_width+1152,256,COIN,coin},
                        {5*sc_width+1024,448,COIN,coin},
                        {5*sc_width+704,320,COIN,coin},
                        {5*sc_width+512,576,COIN,coin},
                        {5*sc_width+384,448,COIN,coin},
                        {5*sc_width+256,320,COIN,coin},
                        {5*sc_width+512,512,APPLE,apple},
                        {5*sc_width+1024,384,APPLE,apple},
                        {5*sc_width+1152,192,DIAMOND,diamond},


                        {6*sc_width+448,384,COIN,coin},
                        {6*sc_width+704,384,COIN,coin},
                        {6*sc_width+1088,640,LIFE,heart},
                        {6*sc_width+512, 384,COIN,coin},
                        {6*sc_width+576, 384,DIAMOND,diamond},
                        {6*sc_width+640, 384,COIN,coin},
                        {6*sc_width+1088, 576,APPLE,apple},




                        {7*sc_width+896,320,COIN,coin},
                        {7*sc_width+576,320,COIN,coin},
                        {7*sc_width+1024,192,COIN,coin},
                        {7*sc_width+448,192,COIN,coin},
                        {7*sc_width+704,448,DIAMOND,diamond},
                        {7*sc_width+768,448,APPLE,apple},
                        {7*sc_width+1088,448,COIN,coin},
                        {7*sc_width+1216,448,COIN,coin},


                        {8*sc_width+768,320,COIN,coin},
                        {8*sc_width+896,320,COIN,coin},
                        {8*sc_width+832,384,DIAMOND,diamond},
                        {8*sc_width+320,512,COIN,coin},
                        {8*sc_width+384,512,COIN,coin},

                        {9*sc_width+1088,256,LIFE,heart},
                        {9*sc_width+512,128,COIN,coin},
                        {9*sc_width+320, 192,COIN,coin},
                        {9*sc_width+320, 384,COIN,coin},
                        {9*sc_width+384, 384,COIN,coin},
                        {9*sc_width+832, 256,DIAMOND,diamond},
                        {9*sc_width+1024, 256,APPLE,apple},
                        {9*sc_width+1024, 384,COIN,coin},

                        {10*sc_width+1088,128,LIFE,heart},
                        {10*sc_width+512,320,COIN,coin},
                        {10*sc_width+960,192,COIN,coin},
                        {10*sc_width+512,448,COIN,coin},
                        {10*sc_width+640,448,COIN,coin},
                        {10*sc_width+896,384,COIN,coin},
                        {10*sc_width+1024,384,COIN,coin},
                        {10*sc_width+128, 448,DIAMOND,diamond},
                        {10*sc_width+384, 320,APPLE,apple},






                        {11*sc_width+0,256,COIN,coin},
                        {11*sc_width+1216,256,COIN,coin},
                        {11*sc_width+640,128,COIN,coin},
                        {11*sc_width+640, 512,LIFE,heart},
                        {11*sc_width+704, 512,APPLE,apple},
                        {11*sc_width+768, 512,APPLE,apple},
                        {11*sc_width+832, 256,DIAMOND,diamond},
                        {11*sc_width+896, 256,DIAMOND,diamond},
                        {11*sc_width+960, 256,APPLE,apple},







                        {12*sc_width+192,576,COIN,coin},
                        {12*sc_width+832,384,COIN,coin},
                        {12*sc_width+512,448,COIN,coin},
                        {12*sc_width+704, 320,APPLE,apple},
                        {12*sc_width+896, 384,APPLE,apple},
                        {12*sc_width+1024, 192,COIN,coin},
                        {12*sc_width+1024, 256,DIAMOND,diamond},


                        {13*sc_width+320,256,COIN,coin},
                        {13*sc_width+384, 256,COIN,coin},
                        {13*sc_width+448, 256,COIN,coin},
                        {13*sc_width+512, 256,COIN,coin},
                        {13*sc_width+576, 256,DIAMOND,diamond},
                        {13*sc_width+704, 256,COIN,coin},
                        {13*sc_width+768, 256,APPLE,apple},
                        {13*sc_width+896, 256,DIAMOND,diamond},
                        {13*sc_width+960, 256,COIN,coin},
                        {13*sc_width+1024, 256,COIN,coin},
                        {13*sc_width+1088, 256,COIN,coin},



                       {14*sc_width+256,256,DIAMOND,diamond},
                        {14*sc_width+320, 256,DIAMOND,diamond},
                        {14*sc_width+384, 256,DIAMOND,diamond},

                        {14*sc_width+448, 256,COIN,coin},
                        {14*sc_width+512, 256,DIAMOND,diamond},
                        {14*sc_width+576, 256,COIN,coin},
                        {14*sc_width+640, 256,DIAMOND,diamond},
                        {14*sc_width+704, 256,APPLE,apple},
                        {14*sc_width+768, 256,DIAMOND,diamond},
                        {14*sc_width+832, 256,DIAMOND,diamond},
                        {14*sc_width+832, 256,DIAMOND,diamond},
                        {14*sc_width+896, 256,DIAMOND,diamond},
                        {14*sc_width+960, 256,DIAMOND,diamond},
                        {14*sc_width+1088, 256,DIAMOND,diamond},
                        {14*sc_width+1152, 256,COIN,coin},
                    };

void takehighscore();
void updatescore();
void take_name();
void _exit();
void show_score();

img brick,SS[10],background;

img imageLoader(const char *path, int ignoreColor=-1){
    img temp;
    AUX_RGBImageRec *Image = auxDIBImageLoad(path);
    int i,j;
    temp.width = Image->sizeX;
    temp.height = Image->sizeY;
    int nPixels = temp.width * temp.height;
    temp.pixels = (int*)malloc(nPixels*sizeof(int) );

    for (i = j = 0; i < nPixels; i++, j += 3)
    {
        int rgb = 0;
        for(int k = 2; k >= 0; k--)
        {
            rgb = ((rgb << 8) | Image->data[j+k]);
        }

        temp.pixels[i] = (rgb == ignoreColor) ? 0 : 255;
        temp.pixels[i] = ( (temp.pixels[i] << 24) | rgb);
    }
    free(Image->data);  /// releases the allocated memory
    free(Image); /// releases the allocated memory
    return temp;
}

void renderImage(double posX,double posY, img *I)
{
    glRasterPos2f(posX, posY) ;
    glDrawPixels(I->width, I->height, GL_RGBA, GL_UNSIGNED_BYTE, I->pixels);
    glEnd();
}



/** load_level_info() : sets the pixels of obstacle to 1 ...so that HITting condition can be checked,
                here integer n is for which set to draw.. i.e current screen */

void load_level_info(){
    /// load indexes for iDraw()
    for(int i=0;i<N_OBS;++i){
        int x = (int)obs[i].x/sc_width ;
        ++en_obs[ x ];
    }
    st_obs[0] = 0;
    for(int i=1;i<N_F;++i){
        en_obs[i] += en_obs[i-1] ;
        st_obs[i] = en_obs[i-1] ;
    }


    for(int i = 0;i<n_collectable;++i){
        int x = (int)(collectable[i].x/sc_width) ;
        ++en_collectable[x];
    }
    st_collectable[0] = 0;
    for(int i=1;i<N_F;++i){
        en_collectable[i] += en_collectable[i-1] ;
        st_collectable[i] = en_collectable[i-1] ;
    }


    for(int i = 0;i<n_flames;++i){
        int x = (int)(flames[i].x/sc_width) ;
        ++en_flames[x];
    }
    st_flames[0] = 0;
    for(int i=1;i<N_F;++i){
        en_flames[i] += en_flames[i-1] ;
        st_flames[i] = en_flames[i-1] ;
    }

    for(int i = 0;i<N_MOBS;++i){
        int x = (int)(movobs[i].x/sc_width) ;
        ++en_mobs[x];
    }
    st_mobs[0] = 0;
    for(int i=1;i<N_F;++i){
        en_mobs[i] += en_mobs[i-1] ;
        st_mobs[i] = en_mobs[i-1] ;
    }
    ///end

    ///make grid
    for(int i=0;i<sc_height;++i) {
        for(int j=0;j<16;++j){
            grid[j][i] = 1;
            grid[N_F*sc_width-j][i] = 1;
        }
    }
    for(int k=0;k<N_OBS;++k)
        for(int i=obs[k].x; i<obs[k].x+obs[k].width; ++i)
            for(int j=obs[k].y; j<obs[k].y+obs[k].height;++j)
                grid[i][j] = 1;

    for(int i=0;i<n_collectable;i++)
        for(int j=collectable[i].x;j<collectable[i].x+collectable_length;++j)
            for(int k=collectable[i].y;k<collectable[i].y+collectable_length;++k)
                grid[j][k] = collectable[i].type;
    ///
}

char str[100];
int len;

void show_score(){
    if(gamemode>=5/*6*/) updatescore();
    iShowBMP(0,0,"high_score2.bmp");
    int y=500;
    for(int i=0;i<6;i++){
        iSetColor(255,255,255);
        iText(400,y,players[i].name,GLUT_BITMAP_TIMES_ROMAN_24);
        char num[10];
        itoa(players[i].score,num,10);
        iText(500,y,num,GLUT_BITMAP_TIMES_ROMAN_24);
        y-=30;
    }
    if(gamemode==6) iShowBMP(350,500,"congo.bmp");
    if(gamemode==5) iShowBMP(350,500,"over.bmp");
     if(gamemode==1 or gamemode==4)
        iText(10,10,"Press b for menu",GLUT_BITMAP_TIMES_ROMAN_24);
     else if(gamemode>=5/*6*/)
         iText(10,10,"Press enter to exit",GLUT_BITMAP_TIMES_ROMAN_24);
}
void take_name(){
    iPauseTimer(0);
    iPauseTimer(1);
    iPauseTimer(2);
    iPauseTimer(3);
	iSetColor(150, 150, 150);
	iRectangle(500, 400, 200, 40);
    iShowBMP(350,500,"entername.bmp");
    iSetColor(255, 255, 255);
    iText(510, 415, str,GLUT_BITMAP_TIMES_ROMAN_24);
	//iText(10, 10, "Click to activate the box, enter to finish.");
}


void updatescore(){
    for(int i=0;i<6;i++){
        for(int j=i+1;j<6;j++){
            if(players[i].score<players[j].score){
                Player_info temp;
                temp=players[i];
                players[i]=players[j];
                players[j]=temp;

            }
        }
    }
}

void takehighscore(){
    FILE *fptr;
    fptr = fopen("highscore.txt","r");
    for(int i=0;i<5;i++){
        fscanf(fptr,"%s %d",&players[i].name,&players[i].score);
    }
    //strcpy(players[5].name, str);
    for(int i=0;i<8;i++) players[5].name[i]=str[i];
    players[5].name[8]=str[8];
    fclose(fptr);
    updatescore();

}


void _exit(){
       FILE *fptr2;
   // use appropriate location if you are using MacOS or Linux
   fptr2 = fopen("highscore.txt","w");
   for(int i=0;i<5;i++)
        fprintf(fptr2,"%s %d\n",players[i].name,players[i].score);
   fclose(fptr2);
    exit(0);
}

