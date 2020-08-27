#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "image.h" //biblioteka za teksture preuzeta iz materijala sa vezbi

//definisanje imena fajlova tekstura
#define FILENAME0 "wood.bmp"
#define FILENAME1 "wood2.bmp"
#define FILENAME2 "floor.bmp"

//definisu se identifikatori tekstura
static GLuint textureid[3];

//definisu se globalne promenljive
static int interval = 25;

int teapot1 = 0;
int teapot2 = 0;
int teapot3 = 0;
int teapot4 = 0;
int ap1 = 0;
int ap2 = 0;
int ap3 = 0;
int ap4 = 0;

//definisu se display, reshape, timer i keyboard funkcije
static void displayFunction();
static void reshapeFunction(int width, int height);
static void timerFunction(int id);
static void keyFunction(unsigned char key, int x, int y);

//inicijalizacija tekstura
static void initTextures(void);

int main(int argc, char** argv){
    //glut inicijalizacija, postavljanje velicine i pozicije prozora, pozivanje funkcija
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(displayFunction);
    glutReshapeFunc(reshapeFunction);
    glutKeyboardFunc(keyFunction);
    
    //ukljucuju se neophodne osobine
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //definisanje osvetljenja
    float lightPosition[] = {0, 10, 2, 1};
    float lightAmbient[] = {.45f, .45f, .45f, 1};
    float lightDiffuse[] = {.7f, .7f, .7f, 1};
    float lightSpecular[] = {.8f, .8f, .8f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    //ukljucuju se osobine color material i texture2D
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    //definisanje boje pozadine
    glClearColor(0.6, 0.9, 1.0, 0);

    //inicijalizacija tekstura
    initTextures();

    //ulazak u glavnu petlju
    glutMainLoop();
    exit(EXIT_SUCCESS);
}

void initTextures(void){
    //definise se promenljiva u kojoj ce biti tekstura ucitana iz .bmp fajla
    Image* imagebuffer;

    //postavljaju se texture environment parametri
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //inicijalizacija promenljive imagebuffer
    imagebuffer = image_init(0, 0);

    //generisu se identifikatori
    glGenTextures(3, textureid);

    //kreira se prva tekstura iz fajla
    image_read(imagebuffer, FILENAME0);

    glBindTexture(GL_TEXTURE_2D, textureid[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagebuffer->width, imagebuffer->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagebuffer->pixels);

    //kreira se druga tekstura iz fajla
    image_read(imagebuffer, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, textureid[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagebuffer->width, imagebuffer->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagebuffer->pixels);

    //kreira se treca tekstura iz fajla
    image_read(imagebuffer, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, textureid[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagebuffer->width, imagebuffer->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagebuffer->pixels);

    //iskljucuje se aktivna tekstura
    glBindTexture(GL_TEXTURE_2D, 0);

    //oslobadja se imagebuffer
    image_done(imagebuffer);
}

//timer funkcija, potrebna za animacije
void timerFunction(int id){
    switch(id){
        case 0:
            ap1 += 1;
            if(ap1 >= 360){
                ap1 -= 360;
            }
            if(teapot1 == 3){
                glutTimerFunc(interval, timerFunction, 0);
            }
            break;
        case 1:
            ap2 += 1;
            if(ap2 >= 360){
                ap2 -= 360;
            }
            if(teapot2 == 3){
                glutTimerFunc(interval, timerFunction, 1);
            }
            break;
        case 2:
            ap3 += 1;
            if(ap3 >= 360){
                ap3 -= 360;
            }
            if(teapot3 == 3){
                glutTimerFunc(interval, timerFunction, 2);
            }
            break;
            
        case 3:
            ap4 += 1;
            if(ap4 >= 720){
                ap4 -= 360;
            }
            if(teapot4 == 1){
                glutTimerFunc(interval, timerFunction, 3);
            }
            break;

    }
    glutPostRedisplay();
}

//keyboard funkcija, neophodna za interakciju
void keyFunction(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 't':
            if(teapot2 != 3){
                teapot2 = 0;
            }

            if(teapot3 == 2){//ako je teapot3 == 2, teapot1 je ili 0 ili 3
                teapot3 = 3;
                glutTimerFunc(interval, timerFunction, 2);
                if(teapot1 == 3 && teapot2 == 3){
                    teapot4 = 1;
                    glutTimerFunc(interval, timerFunction, 3);
                }
            }else{
                if(teapot1 != 3){//ne vraca se na 0, jer i nizovi "t, t, e, a" i "t, e, t, e, a" imaju odgovarajuci kod u odgovarajucem redosledu
                    teapot1 = 1;//t jeste prvi karakter u kodu "tea", pa se flag moze postaviti na 1 bez obzira da li je bio 0, 1 ili 2
                }
                if(teapot3 != 3){
                    teapot3 = 0;
                }
            }
            break;
        case 'e':
            if(teapot2 != 3){
                teapot2 = 0;
            }

            if(teapot3 != 3){
                teapot3 = 0;
            }

            if(teapot1 == 1){
                teapot1 = 2;
            }else{
                if(teapot1 != 3){
                    teapot1 = 0;
                }
            }

            break;
        case 'a':
            if(teapot2 != 3){
                teapot2 = 0;
            }

            if(teapot3 != 3){
                teapot3 = 0;
            }

            if(teapot1 == 2){
                teapot1 = 3;
                glutTimerFunc(interval, timerFunction, 0);
                if(teapot2 == 3 && teapot3 == 3){
                    teapot4 = 1;
                    glutTimerFunc(interval, timerFunction, 3);
                }
            }else{
                if(teapot1 != 3){
                    teapot1 = 0;
                }
            }

            break;
        case 'p':
            if(teapot1 != 3){
                teapot1 = 0;
            }

            if(teapot2 != 3){
                teapot2 = 0;
            }

            if(teapot3 != 3){//ne vraca se na 0, jer i nizovi "p, p, o, t" i "p, o, p, o, t" imaju odgovarajuci kod u odgovarajucem redosledu
                teapot3 = 1;//p jeste prvi karakter u kodu "pot", pa se flag moze postaviti na 1 bez obzira da li je bio 0, 1 ili 2
            }

            break;
        case 'o':
            if(teapot1 != 3){
                teapot1 = 0;
            }

            if(teapot2 != 3){
                teapot2 = 0;
            }

            if(teapot3 == 1){
                teapot3 = 2;
            }else{
                if(teapot3 != 3){
                    teapot3 = 0;
                }
            }

            break;
        case '4':
            if(teapot1 != 3){
                teapot1 = 0;
            }

            if(teapot3 != 3){
                teapot3 = 0;
            }

            if(teapot2 != 3){//ne vraca se na 0, jer i nizovi "4, 4, 1, 8" i "4, 1, 4, 1, 8" imaju odgovarajuci kod u odgovarajucem redosledu
                teapot2 = 1;//4 jeste prvi karakter u kodu "418", pa se flag moze postaviti na 1, bez obzira da li je bio 0, 1 ili 2
            }

            break;
        case '1':
            if(teapot1 != 3){
                teapot1 = 0;
            }

            if(teapot3 != 3){
                teapot3 = 0;
            }

            if(teapot2 == 1){
                teapot2 = 2;
            }else{
                if(teapot2 != 3){
                    teapot2 = 0;
                }
            }

            break;
        case '8':
            if(teapot1 != 3){
                teapot1 = 0;
            }

            if(teapot3 != 3){
                teapot3 = 0;
            }

            if(teapot2 == 2){
                teapot2 = 3;
                glutTimerFunc(interval, timerFunction, 1);
                if(teapot1 == 3 && teapot3 == 3){
                    teapot4 = 1;
                    glutTimerFunc(interval, timerFunction, 3);
                }
            }else{
                if(teapot2 != 3){
                    teapot2 = 0;
                }
            }

            break;
        case 'r'://resetovanje na pocetak
            teapot1 = 0;
            teapot2 = 0;
            teapot3 = 0;
            teapot4 = 0;
            ap1 = 0;
            ap2 = 0;
            ap3 = 0;
            ap4 = 0;
            glutPostRedisplay();
            break;
        default:
            if(teapot1 != 3){
                teapot1 = 0;
            }
            if(teapot2 != 3){
                teapot2 = 0;
            }
            if(teapot3 != 3){
                teapot3 = 0;
            }
            break;
    }
}

//reshape funkcija
//Kod preuzet iz skeleta zadatka sa osvetljenim drvetom
void reshapeFunction(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 20);
}
//Kraj koda preuzetog iz skeleta zadatka sa osvetljenim drvetom

//display funkcija
void displayFunction(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat t1ambient[] = {0, 0, 0.4, 1};
    GLfloat t1diffuse[] = {0, 0, 0.8, 1};
    GLfloat t1specular[] = {0, 0, 0.9, 1};

    GLfloat t2ambient[] = {0.4, 0, 0, 1};
    GLfloat t2diffuse[] = {0.8, 0, 0, 1};
    GLfloat t2specular[] = {0.9, 0, 0, 1};

    GLfloat t3ambient[] = {0, 0.4, 0, 1};
    GLfloat t3diffuse[] = {0, 0.8, 0, 1};
    GLfloat t3specular[] = {0, 0.9, 0, 1}; 

    GLfloat defaulta[] = {0.2, 0.2, 0.2, 1};
    GLfloat defaultd[] = {0.8, 0.8, 0.8, 1};
    GLfloat defaults[] = {0, 0, 0, 1};

    //postavljaju se pozicija i orjentacija kamere
    gluLookAt(0, 5, 10,
              0, 0, 0,
              0, 1, 0);
    

    //iscrtavaju se pod i zidovi
    glPushMatrix();
        glPushMatrix();

            glBindTexture(GL_TEXTURE_2D, textureid[2]);
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(7, 0);
            glVertex3f(3.5f, -0.5f, -1.0f);
            glTexCoord2f(0, 0);
            glVertex3f(-3.5f, -0.5f, -1.0f);
            glTexCoord2f(0, 7);
            glVertex3f(-3.5f, -0.5f, 3.0f);
            glTexCoord2f(7, 7);
            glVertex3f(3.5f, -0.5f, 3.0f);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
            glBegin(GL_POLYGON); 
            glColor3f(1.0f, 0.7f, 0.1f);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-3.5f, -0.5f, -1.0f);
            glVertex3f(3.5f, -0.5f, -1.0f);
            glVertex3f(3.5f, 1.5f, -1.0f);
            glVertex3f(-3.5f, 1.5f, -1.0f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-3.5f, -0.5f, -1.0f);
            glVertex3f(-3.5f, 1.5f, -1.0f);
            glVertex3f(-3.5f, 1.5f, 3.0f);
            glVertex3f(-3.5f, -0.5f, 3.0f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(3.5f, -0.5f, -1.0f);
            glVertex3f(3.5f, -0.5f, 3.0f);
            glVertex3f(3.5f, 1.5f, 3.0f);
            glVertex3f(3.5f, 1.5f, -1.0f);
            glEnd();
        
        glPopMatrix();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textureid[0]);
    //iscrtava se vitrina, u kojoj je levi cajnik
    glPushMatrix();
        glPushMatrix();
        
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, -0.3f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.3f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.3f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, -0.3f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, -0.3f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.3f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, -0.3f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, -0.3f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, -0.3f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, -0.3f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, -0.3f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.3f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, 1.0f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.0f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, 1.0f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, 1.0f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, 1.0f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, 1.0f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.0f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, 1.0f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.0f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.0f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, 1.0f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, 1.0f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.5f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.7f, 1.2f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, 1.2f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, -0.5f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.7f, -0.5f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.9f, 1.2f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, 1.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.7f, -0.5f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.7f, -0.5f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, -0.5f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, 1.2f, -0.7f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, 1.2f, -0.7f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, 1.2f, -0.7f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-1.5f, -0.5f, -0.7f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-2.9f, 1.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-2.9f, 1.2f, -0.7f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.7f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, 1.2f, -0.7f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, -0.7f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.7f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, 1.2f, -0.7f);
            glEnd();
            glBegin(GL_POLYGON); 
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-1.5f, -0.5f, -0.7f);
            glTexCoord2f(1, 1);
            glVertex3f(-1.5f, -0.5f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-2.9f, -0.5f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-2.9f, -0.5f, -0.7f);
            glEnd();

        glPopMatrix();
    glPopMatrix();

    //iscrtava se polica, na kojoj je srednji cajnik
    glPushMatrix();
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, textureid[0]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[1]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[0]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[1]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[0]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[1]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, textureid[0]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);

            glBegin(GL_POLYGON);
            glColor3f(0.7f, 0.7f, 0.7f);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, 1.25f, -0.5f);
            glVertex3f(0.45f, 1.25f, -0.5f);
            glVertex3f(0.45f, 1.25f, -0.45f);
            glVertex3f(0.5f, 1.25f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 1.25f, -0.45f);
            glVertex3f(0.45f, 1.25f, -0.45f);
            glVertex3f(0.45f, -0.5f, -0.45f);
            glVertex3f(0.5f, -0.5f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 1.25f, -0.5f);
            glVertex3f(0.5f, 1.25f, -0.45f);
            glVertex3f(0.5f, -0.5f, -0.45f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(0.45f, 1.25f, -0.45f);
            glVertex3f(0.45f, 1.25f, -0.5f);
            glVertex3f(0.45f, -0.5f, -0.5f);
            glVertex3f(0.45f, -0.5f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(0.45f, 1.25f, -0.5f);
            glVertex3f(0.5f, 1.25f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.45f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.45f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.45f);
            glVertex3f(0.45f, -0.5f, -0.45f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, 1.25f, 0.45f);
            glVertex3f(0.45f, 1.25f, 0.45f);
            glVertex3f(0.45f, 1.25f, 0.5f);
            glVertex3f(0.5f, 1.25f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 1.25f, 0.5f);
            glVertex3f(0.45f, 1.25f, 0.5f);
            glVertex3f(0.45f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 1.25f, 0.45f);
            glVertex3f(0.5f, 1.25f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(0.45f, 1.25f, 0.5f);
            glVertex3f(0.45f, 1.25f, 0.45f);
            glVertex3f(0.45f, -0.5f, 0.45f);
            glVertex3f(0.45f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(0.45f, 1.25f, 0.45f);
            glVertex3f(0.5f, 1.25f, 0.45f);
            glVertex3f(0.5f, -0.5f, 0.45f);
            glVertex3f(0.45f, -0.5f, 0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.45f, -0.5f, 0.45f);
            glVertex3f(0.5f, -0.5f, 0.45f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.45f, -0.5f, 0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.45f, 1.25f, -0.5f);
            glVertex3f(-0.5f, 1.25f, -0.5f);
            glVertex3f(-0.5f, 1.25f, -0.45f);
            glVertex3f(-0.45f, 1.25f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.45f, 1.25f, -0.45f);
            glVertex3f(-0.5f, 1.25f, -0.45f);
            glVertex3f(-0.5f, -0.5f, -0.45f);
            glVertex3f(-0.45f, -0.5f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.45f, 1.25f, -0.5f);
            glVertex3f(-0.45f, 1.25f, -0.45f);
            glVertex3f(-0.45f, -0.5f, -0.45f);
            glVertex3f(-0.45f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 1.25f, -0.45f);
            glVertex3f(-0.5f, 1.25f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, 1.25f, -0.5f);
            glVertex3f(-0.45f, 1.25f, -0.5f);
            glVertex3f(-0.45f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.45f, -0.5f, -0.5f);
            glVertex3f(-0.45f, -0.5f, -0.45f);
            glVertex3f(-0.5f, -0.5f, -0.45f);
            glEnd();
            
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.45f, 1.25f, 0.45f);
            glVertex3f(-0.5f, 1.25f, 0.45f);
            glVertex3f(-0.5f, 1.25f, 0.5f);
            glVertex3f(-0.45f, 1.25f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.45f, 1.25f, 0.5f);
            glVertex3f(-0.5f, 1.25f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.45f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.45f, 1.25f, 0.45f);
            glVertex3f(-0.45f, 1.25f, 0.5f);
            glVertex3f(-0.45f, -0.5f, 0.5f);
            glVertex3f(-0.45f, -0.5f, 0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 1.25f, 0.5f);
            glVertex3f(-0.5f, 1.25f, 0.45f);
            glVertex3f(-0.5f, -0.5f, 0.45f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, 1.25f, 0.45f);
            glVertex3f(-0.45f, 1.25f, 0.45f);
            glVertex3f(-0.45f, -0.5f, 0.45f);
            glVertex3f(-0.5f, -0.5f, 0.45f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.45f);
            glVertex3f(-0.45f, -0.5f, 0.45f);
            glVertex3f(-0.45f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
            glEnd();

        glPopMatrix();
    glPopMatrix();

    //iscrtava se sto, na kome je desni cajnik
    glPushMatrix();
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, textureid[1]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(0, 1);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glTexCoord2f(1, 1);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glTexCoord2f(0, 1);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glTexCoord2f(0, 0);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glTexCoord2f(1, 0);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, -0.5f, 0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, -0.5f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, -0.5f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, -0.5f, -0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, -0.5f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, -0.5f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, -0.5f, -0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, -0.5f, -0.4f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glTexCoord2f(1, 1);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, -0.5f, 0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(3.1f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glTexCoord2f(1, 1);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.1f, -0.5f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.1f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, -0.5f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, -0.5f, -0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(3.1f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.1f, -0.5f, 0.4f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, -0.5f, 0.4f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, -0.5f, -0.4f);
            glTexCoord2f(1, 0);
            glVertex3f(3.1f, -0.5f, -0.4f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glTexCoord2f(0, 1);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glTexCoord2f(1, 0);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glTexCoord2f(0, 1);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glTexCoord2f(0, 0);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glTexCoord2f(1, 0);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glEnd();

        glPopMatrix();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    //iscrtava se elipsoid na kome je zicani cajnik
    glPushMatrix();
        glPushMatrix();
            glColor3f(0.2f, 0.0f, 0.4f);
            glTranslatef(0, -0.5, 2.2);
            glScalef(1, 0.2, 1);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
    glPopMatrix();

    //iscrtavaju se cajnici
    glPushMatrix();
        glPushMatrix();
            glColor3f(0.0f, 0.0f, 1.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, t1ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t1diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, t1specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
            glTranslatef(-2.2, 0, 0);
            glRotatef(ap1, 0, 1, 0);

            if(teapot1 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glColor3f(1.0f, 0.0f, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, t2ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t2diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, t2specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40);
            glTranslatef(0, 0.7, 0);
            glRotatef(ap2, 0, 1, 0);

            if(teapot2 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glColor3f(0.0f, 1.0f, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, t3ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t3diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, t3specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70);
            glTranslatef(2.2, 0.5, 0);
            glRotatef(ap3, 0, 1, 0);
            
            if(teapot3 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glColor3f(0.1f, 0.1f, 0.1f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, defaulta);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defaultd);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaults);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
            glTranslatef(0, -0.1, 2.2);
            glRotatef(-ap4, 0, 1, 0);

            if(teapot4 == 1)
                glutWireTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}
