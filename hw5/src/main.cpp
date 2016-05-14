#ifndef DATAREADER_H
#define DATAREADER_H
#include "modelReader.h"
#endif

#define WIDTH 1000
#define HEIGHT 500

modelReader reader("data/cactus.ply");

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  // glShadeModel(GL_SMOOTH);
  
  // GLfloat light_ambient_global[] = {0.3, 0.3, 0.3, 1.0}; // Global
  // GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
  // GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
  // GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
  
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  
  // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);
  // glMaterialfv(GL_FRONT, GL_AMBIENT, light_ambient_global);
  // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(90, WIDTH * 1.0 / HEIGHT, 60, 180);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(0, 30, 120, 0, 30, 0, 0, 1, 0);

  glColor3f(1.0f, 1.0f, 1.0f);
  reader.handleModel();

  glFlush();
}

void reshape(int w, int h) {
    h = h == 0 ? 1 : h;  // width can't be zero
    float ratio =  w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, WIDTH * 1.0 / HEIGHT, 60, 180);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 30, 120, 0, 30, 0, 0, 1, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Computer Graphics HW5 - Mesh");

    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}