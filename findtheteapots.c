#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //definisanje osvetljenja
    float lightPosition[] = {-2, 10, 0, 1};
    float lightAmbient[] = {.45f, .45f, .45f, 1};
    float lightDiffuse[] = {.7f, .7f, .7f, 1};
    float lightSpecular[] = {.8f, .8f, .8f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    //ukljucuje se osobina color material
    glEnable(GL_COLOR_MATERIAL);

    //definisanje boje pozadine i pokretanje mainloop-a
    glClearColor(0.85, 0.85, 0.85, 0);
    glutMainLoop();
    exit(EXIT_SUCCESS);
}

//timer funkcija, potrebna za animacije
void timerFunction(int id){
    switch(id){
        case 0:
            ap1 += 1;
            if(ap1 >= 720){
                ap1 -= 360;
            }
            if(teapot1 == 3){
                glutTimerFunc(interval, timerFunction, 0);
            }
            break;
        case 1:
            ap2 += 1;
            if(ap2 >= 720){
                ap2 -= 360;
            }
            if(teapot2 == 3){
                glutTimerFunc(interval, timerFunction, 1);
            }
            break;
        case 2:
            ap3 += 1;
            if(ap3 >= 720){
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

    //postavljaju se pozicija i orjentacija kamere
    gluLookAt(0, 5, 10,
              0, 0, 0,
              0, 1, 0);
    

    //iscrtavaju se pod i zidovi
    glPushMatrix();
        glPushMatrix();

        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(3.5f, -0.5f, -1.0f);
        glVertex3f(-3.5f, -0.5f, -1.0f);
        glVertex3f(-3.5f, -0.5f, 3.0f);
        glVertex3f(3.5f, -0.5f, 3.0f);
        glEnd();

        glBegin(GL_POLYGON); 
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

    //iscrtava se vitrina, u kojoj je levi cajnik
    glPushMatrix();
        glPushMatrix();
        
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.7f, -0.3f, -0.5f);
        glVertex3f(-2.7f, -0.3f, -0.5f);
        glVertex3f(-2.7f, -0.3f, 0.5f);
        glVertex3f(-1.7f, -0.3f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.7f, -0.3f, 0.5f);
        glVertex3f(-2.7f, -0.3f, 0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.7f, -0.3f, -0.5f);
        glVertex3f(-1.7f, -0.3f, 0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-2.7f, -0.3f, 0.5f);
        glVertex3f(-2.7f, -0.3f, -0.5f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-1.7f, -0.3f, -0.5f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glVertex3f(-2.7f, -0.3f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glEnd();

        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glVertex3f(-2.7f, 1.0f, 0.5f);
        glVertex3f(-1.7f, 1.0f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glVertex3f(-1.7f, 1.0f, 0.5f);
        glVertex3f(-1.7f, 1.0f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glVertex3f(-2.7f, 1.0f, -0.5f);
        glVertex3f(-2.7f, 1.0f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glVertex3f(-1.7f, 1.0f, -0.5f);
        glVertex3f(-2.7f, 1.0f, -0.5f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.7f, 1.0f, -0.5f);
        glVertex3f(-1.7f, 1.0f, 0.5f);
        glVertex3f(-2.7f, 1.0f, 0.5f);
        glVertex3f(-2.7f, 1.0f, -0.5f);
        glEnd();

        //-1.7, -0.5, 0.5; -1.5, 1.2, -0.5
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glVertex3f(-1.5f, 1.2f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.5f, 1.2f, 0.5f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glVertex3f(-1.5f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glVertex3f(-1.5f, 1.2f, 0.5f);
        glVertex3f(-1.5f, -0.5f, 0.5f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.7f, 1.2f, 0.5f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glVertex3f(-1.7f, 1.2f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glVertex3f(-1.5f, -0.5f, 0.5f);
        glVertex3f(-1.7f, -0.5f, 0.5f);
        glVertex3f(-1.7f, -0.5f, -0.5f);
        glEnd();

        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glVertex3f(-2.9f, 1.2f, 0.5f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glVertex3f(-2.9f, 1.2f, 0.5f);
        glVertex3f(-2.9f, -0.5f, 0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glVertex3f(-2.7f, 1.2f, 0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-2.9f, 1.2f, 0.5f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glVertex3f(-2.9f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-2.7f, 1.2f, -0.5f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-2.7f, -0.5f, -0.5f);
        glVertex3f(-2.7f, -0.5f, 0.5f);
        glVertex3f(-2.9f, -0.5f, 0.5f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glEnd();

        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.5f, 1.2f, -0.7f);
        glVertex3f(-2.9f, 1.2f, -0.7f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.5f, 1.2f, -0.7f);
        glVertex3f(-1.5f, 1.2f, -0.5f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glVertex3f(-1.5f, -0.5f, -0.7f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-2.9f, 1.2f, -0.5f);
        glVertex3f(-2.9f, 1.2f, -0.7f);
        glVertex3f(-2.9f, -0.5f, -0.7f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-1.5f, 1.2f, -0.7f);
        glVertex3f(-1.5f, -0.5f, -0.7f);
        glVertex3f(-2.9f, -0.5f, -0.7f);
        glVertex3f(-2.9f, 1.2f, -0.7f);
        glEnd();
        glBegin(GL_POLYGON); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.5f, -0.5f, -0.7f);
        glVertex3f(-1.5f, -0.5f, -0.5f);
        glVertex3f(-2.9f, -0.5f, -0.5f);
        glVertex3f(-2.9f, -0.5f, -0.7f);
        glEnd();

        glPopMatrix();
    glPopMatrix();

    //iscrtava se polica, na kojoj je srednji cajnik
    glPushMatrix();
        glPushMatrix();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glVertex3f(0.5f, 0.4f, 0.5f);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 0.4f, 0.5f);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, 0.4f, -0.5f);
            glVertex3f(0.5f, 0.4f, -0.5f);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.5f, 0.35f, 0.5f);
            glVertex3f(-0.5f, 0.35f, 0.5f);
            glVertex3f(-0.5f, 0.35f, -0.5f);
            glVertex3f(0.5f, 0.35f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glVertex3f(0.5f, -0.4f, 0.5f);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, -0.4f, 0.5f);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, -0.4f, -0.5f);
            glVertex3f(0.5f, -0.4f, -0.5f);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.5f, -0.45f, 0.5f);
            glVertex3f(-0.5f, -0.45f, 0.5f);
            glVertex3f(-0.5f, -0.45f, -0.5f);
            glVertex3f(0.5f, -0.45f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glVertex3f(0.5f, 1.2f, 0.5f);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 1.2f, 0.5f);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-0.5f, 1.2f, -0.5f);
            glVertex3f(0.5f, 1.2f, -0.5f);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.5f, 1.15f, 0.5f);
            glVertex3f(-0.5f, 1.15f, 0.5f);
            glVertex3f(-0.5f, 1.15f, -0.5f);
            glVertex3f(0.5f, 1.15f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
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
            glEnd();

        glPopMatrix();
    glPopMatrix();

    //iscrtava se sto, na kome je desni cajnik
    glPushMatrix();
        glPushMatrix();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glVertex3f(3.2f, 0.2f, 0.5f);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(1.2f, 0.2f, 0.5f);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(1.2f, 0.2f, -0.5f);
            glVertex3f(3.2f, 0.2f, -0.5f);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(3.2f, 0.15f, 0.5f);
            glVertex3f(1.2f, 0.15f, 0.5f);
            glVertex3f(1.2f, 0.15f, -0.5f);
            glVertex3f(3.2f, 0.15f, -0.5f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glVertex3f(1.3f, -0.5f, 0.4f);
            glVertex3f(1.35f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glVertex3f(1.35f, -0.5f, 0.4f);
            glVertex3f(1.35f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glVertex3f(1.3f, -0.5f, -0.4f);
            glVertex3f(1.3f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glVertex3f(1.3f, -0.5f, -0.4f);
            glVertex3f(1.35f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(1.35f, 0.15f, 0.4f);
            glVertex3f(1.3f, 0.15f, 0.4f);
            glVertex3f(1.3f, 0.15f, -0.4f);
            glVertex3f(1.35f, 0.15f, -0.4f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glVertex3f(3.05f, -0.5f, 0.4f);
            glVertex3f(3.1f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glVertex3f(3.1f, -0.5f, 0.4f);
            glVertex3f(3.1f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glVertex3f(3.05f, -0.5f, -0.4f);
            glVertex3f(3.05f, -0.5f, 0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glVertex3f(3.05f, -0.5f, -0.4f);
            glVertex3f(3.1f, -0.5f, -0.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(3.1f, 0.15f, 0.4f);
            glVertex3f(3.05f, 0.15f, 0.4f);
            glVertex3f(3.05f, 0.15f, -0.4f);
            glVertex3f(3.1f, 0.15f, -0.4f);
            glEnd();

            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glVertex3f(3.05f, 0.0f, 0.35f);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(1.35f, 0.0f, 0.35f);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(1.35f, 0.0f, -0.35f);
            glVertex3f(3.05f, 0.0f, -0.35f);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(3.05f, -0.05f, 0.35f);
            glVertex3f(1.35f, -0.05f, 0.35f);
            glVertex3f(1.35f, -0.05f, -0.35f);
            glVertex3f(3.05f, -0.05f, -0.35f);
            glEnd();

        glPopMatrix();
    glPopMatrix();

    //iscrtava se elipsoid na kome je zicani cajnik
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, -0.5, 2.2);
            glScalef(1, 0.2, 1);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
    glPopMatrix();

    //iscrtavaju se cajnici
    glPushMatrix();
        glPushMatrix();
            glTranslatef(-2.2, 0, 0);
            glRotatef(ap1, 0, 1, 0);

            if(teapot1 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, 0.7, 0);
            glRotatef(ap2, 0, 1, 0);

            if(teapot2 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glTranslatef(2.2, 0.5, 0);
            glRotatef(ap3, 0, 1, 0);
            
            if(teapot3 == 3)
                glutSolidTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, -0.1, 2.2);
            glRotatef(-ap4, 0, 1, 0);

            if(teapot4 == 1)
                glutWireTeapot(0.3);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}
