#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLdouble width = 1080, height = 720;

float x_rotation = 0;
float y_rotation = 0;
void resetTransform() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
}



short light = 0;
void initLights() {
    glEnable(GL_LIGHTING);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    //light 0
    GLfloat ambient_0[] = { 0.4,    0.4,    0.4,    1.0 };
    GLfloat diffuse_0[] = { 1.0,    1.0,    1.0,    1.0 };
    GLfloat specular_0[] = { 1.0,    1.0,    1.0,    1.0 };
    GLfloat position_0[] = { 1.0,    1.0,    0.0,    0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_0);
    glLightfv(GL_LIGHT0, GL_POSITION, position_0);



    //light 1
    GLfloat ambient_1[] = { 0.0,    0.4,    0.4,    1.0 };
    GLfloat diffuse_1[] = { 0.0,    1.0,    1.0,    1.0 };
    GLfloat specular_1[] = { 0.0,    1.0,    1.0,    1.0 };
    GLfloat position_1[] = { 0.0,    1.5,    0.0,    1.0 };
    const GLfloat
        linear_attenuation_1 = 0.8f;

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_1);
    glLightfv(GL_LIGHT1, GL_POSITION, position_1);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &linear_attenuation_1);

    //light 2
    GLfloat ambient_2[] = { 0.4,    0.4,    0.4,    1.0 };
    GLfloat diffuse_2[] = { 4.0,    1.0,    1.0,    1.0 };
    GLfloat specular_2[] = { 4.0,    1.0,    1.0,    1.0 };
    GLfloat position_2[] = { 1.5,   -1.5,    0.0,    1.0 };
    const GLfloat
        linear_attenuation_2 = 0.2;

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular_2);
    glLightfv(GL_LIGHT2, GL_POSITION, position_2);
    glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, &linear_attenuation_2);
}

void Init() {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();

    gluPerspective(60.0f, width / height, 1.0f, 200.0f);

    resetTransform();
    initLights();
}




void makePlane() {
    GLfloat ambient[] = { 0.0,   0.0,    0.4,    1.0 };
    GLfloat diffuse[] = { 0.0,   0.0,    0.6,    1.0 };
    GLfloat specular[] = { 0.0,   0.0,    1.0,    1.0 };
    GLfloat const shine = 100.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);

    glNormal3f(0, 1, 0);

    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glEnd();
}
void makePot() {
    GLfloat ambient_diffuse[] = { 0.4,    0.4,    0.0,    1.0 };
    GLfloat specular[] = { 0.0,    1.0,    1.0,    1.0 };
    GLfloat const shine = 100.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
    glutSolidTeapot(1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);


    glRotatef(x_rotation, 1, 0, 0);
    glRotatef(y_rotation, 0, 1, 0);

    //lighting
    glEnable(GL_LIGHT0);
    if (light == 1)
    {
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
    else if (light == 2) {
        glEnable(GL_LIGHT2);
        glDisable(GL_LIGHT1);
    }

    //geometry
    makePlane();
    makePot();

    glutSwapBuffers();
}




void handleRotateInput(int key, int x, int y)
{
    resetTransform();
    switch (key)
    {
    case GLUT_KEY_UP:
        //do something here
        //glRotatef(anglex,1,0,0);
        x_rotation++;
        break;
    case GLUT_KEY_DOWN:
        //do something here
        //glRotatef(anglex, -1, 0, 0);
        x_rotation--;

        break;
    case GLUT_KEY_LEFT:
        //do something here
        //glRotatef(angley, 0, 1, 0);
        y_rotation++;

        break;
    case GLUT_KEY_RIGHT:
        //do something here
        //glRotatef(angley, 0, -1, 0);
        y_rotation--;

        break;
    }

    display();
}
void handleLightToggle(unsigned char key, int x, int y) {
    resetTransform();
    switch (key)
    {

    case 'l':
        if (light == 1) {
            light = 2;
        }
        else {
            light = 1;
        }
        cout << light << endl;
        break;
    default:
        break;
    }
    display();

}


void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Pot");

    glutDisplayFunc(display);

    glutKeyboardFunc(handleLightToggle);
    glutSpecialFunc(handleRotateInput);

    Init();
    glutMainLoop();
}
