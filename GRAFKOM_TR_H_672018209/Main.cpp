#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <Windows.h>
<<<<<<< HEAD
#include "TGA.h"
#include "object.h"

=======
#include <vector>
#include "object.h"
>>>>>>> 82816fbe79487a0eb9107eb39185370cc3fd76f2


Object woman;
Object womans[50];

void display();
void ukuran(int, int);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char, int, int);

float rotx = 0.0f;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
float pos = 0.0f;
float posX = 0.0f;
bool mouseDown = false;
int is_depth;


void initcahaya(void)
{
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "KLIK KIRI" << " = anda menekan LEFT_BUTTON" << std::endl;
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
    display();
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glLoadIdentity();
		

        glRotatef(xrot, 1.0, 0.0, 0.0);
        glRotatef(yrot, 0.0, 1.0, 0.0);
        glutPostRedisplay();
    }
}



void keyboard(unsigned char key, int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << key << " = anda menekan tombol " << key << std::endl;

    switch (key)
    {
    case 'z': //zoom +
    case 'Z':
        glTranslatef(0.0, 0.0, 1.0);
        break;
    case 'x': //zoom -
    case 'X':
        glTranslatef(0.0, 0.0, -1.0);
        break;

    case 'w': //rotasi kebelakang
    case 'W':
        glRotatef(-1.0, 1.0, 0.0, 0.0);
        break;
    case 'd': //rotasi kekanan
    case 'D':
        glRotatef(1.0, 0.0, 1.0, 0.0);
        rotx += 1.0;
        break;
    case 's': //rotasi kedepan
    case 'S':
        glRotatef(1.0, 1.0, 0.0, 0.0);
        break;
    case 'a': //rotasi kiri
    case 'A':
        glRotatef(-1.0, 0.0, 1.0, 0.0);
        rotx += -1.0;
        break;
    case 'n': //putar kekiri
    case 'N':
        glRotatef(1.0, 0.0, 0.0, 1.0);
        break;
    case 'm':
    case 'M': //putar kekanan
        glRotatef(-1.0, 0.0, 0.0, 1.0);
        break;
    case 'p':
    case 'P':
        if (is_depth) {
            is_depth = 0;
            glDisable(GL_DEPTH_TEST);
        }
        else {
            is_depth = 1;
            glEnable(GL_DEPTH_TEST);
        }
    }
    std::cout << "rotx: " << rotx << std::endl;
    display();
}

void onSpecialKeyPressed(int key, int x, int y) {
    std::cout << key << " = anda menekan tombol " << key << std::endl;
    switch (key) {
    case GLUT_KEY_UP:
        glTranslatef(0.0, 3.0, 0.0);
        break;
    case GLUT_KEY_DOWN:
        glTranslatef(0.0, -3.0, 0.0);
        break;
    case GLUT_KEY_LEFT:
        glTranslatef(-3.0, 0.0, 0.0);
        posX += -3.0;
        break;
    case GLUT_KEY_RIGHT:
        glTranslatef(3.0, 0.0, 0.0);
        posX += 3.0;
        break; 
    }
    std::cout << posX << std::endl;
    display();
}



void display() {

    if (is_depth)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-2.0, 0.0,-2.0);
    glVertex3f(2.0, 0.0, -2.0);
    glVertex3f(2.0, 0.0, 2.0);
    glVertex3f(-2.0, 0.0, 2.0);
    glEnd();
	
	woman.draw();

    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
    //glTranslatef(-0.003, 0.0, 0.0);
    posX -= 0.003;

}



void idle() {
	
    if (!mouseDown) {
		woman.idle();
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void ukuran(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1;

	glViewport(0, 0, lebar, tinggi);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(60, lebar / tinggi, 0.02, 100.0);
	
    glTranslatef(0.0, -1.0, -3.0);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 540);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("TR_GRAFKOM_672018209");
	
	woman.setup("./Woman1.nfg", "./Woman1.bmp");
	
    //inisialisasi glut
    glClearColor(1.0, 0.73, 0.27, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glPointSize(1);
    glLineWidth(1);
    is_depth = 1;
    glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); //mengatur penglihatan objek
	glTranslatef(0.0, 0.2, 0.0);
    //initcahaya();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(onSpecialKeyPressed);
    glutReshapeFunc(ukuran);
    glutIdleFunc(display);
		
    glutMainLoop();
    return 0;
}


