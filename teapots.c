#include <GL/glut.h>
#include "teapots.h"

//funkcija za iscrtavanje plavog cajnika
void drawTeapot1(int flag1, int animationParameter1, float* ambient1, float* diffuse1, float* specular1){
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
        glTranslatef(-2.2, 0, 0);
        glRotatef(animationParameter1, 0, 1, 0);

        if(flag1 == 3)
            glutSolidTeapot(0.3);
    glPopMatrix();
}

//funkcija za iscrtavanje crvenog cajnika
void drawTeapot2(int flag2, int animationParameter2, float* ambient2, float* diffuse2, float* specular2){
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40);
        glTranslatef(0, 0.7, 0);
        glRotatef(animationParameter2, 0, 1, 0);

        if(flag2 == 3)
            glutSolidTeapot(0.3);
    glPopMatrix();
}

//funkcija za iscrtavanje zelenog cajnika
void drawTeapot3(int flag3, int animationParameter3, float* ambient3, float* diffuse3, float* specular3){
    glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70);
        glTranslatef(2.2, 0.5, 0);
        glRotatef(animationParameter3, 0, 1, 0);
        
        if(flag3 == 3)
            glutSolidTeapot(0.3);
    glPopMatrix();
}

//funkcija za iscrtavanje zicanog cajnika
void drawTeapot4(int flag4, int animationParameter4, float* ambient4, float* diffuse4, float* specular4){
    glPushMatrix();
        float tp4color;
        if(animationParameter4 <= 180){
            tp4color = (float)(1.0 - ((0.9*animationParameter4)/180.0));
            glColor3f(tp4color, tp4color, tp4color);
        }else{
            glColor3f(0.1f, 0.1f, 0.1f);
        }
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
        glTranslatef(0, -0.1, 2.2);
        glRotatef(-animationParameter4, 0, 1, 0);
        float tp4scale;
        if(animationParameter4 <= 60){
            tp4scale = 0.5 + (animationParameter4/120.0);
        }else{
            tp4scale = 1;
        }
        glScalef(tp4scale, tp4scale, tp4scale);

        if(flag4 == 1)
            glutWireTeapot(0.3);
    glPopMatrix();
}