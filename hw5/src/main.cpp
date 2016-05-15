#ifndef MODELREADER_H
#define MODELREADER_H
#include "modelReader.h"
#endif

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define WIDTH 750
#define HEIGHT 500

modelReader reader;

void readModel() {
  string filename = "cow.obj";
  int style = -1;
  cout << "Please input filename(Just input filename): ";
  cin >> filename;

  reader.setFile(filename);

  reader.readModel();

  while (style != 0 && style != 1 && style != 2) {
    cout << "Please input style(Wireframe: 0, Flat: 1, Flat lines: 2): ";
    cin >> style;
  }

  reader.setStyle(style + 3);
}

void setLight() {
  GLfloat light_position[] = {1.0f, 2.0f, 3.0f, 0.0f};  
  GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void view() {
  float centerX = (reader.getMaxX() + reader.getMinX()) / 2;
  float centerY = (reader.getMaxY() + reader.getMinY()) / 2;
  float centerZ = (reader.getMaxZ() + reader.getMinZ()) / 2;
  float depthZ = (reader.getMaxZ() - reader.getMinZ());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, WIDTH * 1.0 / HEIGHT, depthZ * 0.5, depthZ * 2);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(centerX, centerY, depthZ * 1.5, centerX, centerY, centerZ, 0, 1, 0);
}

void render() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  view();

  glColor3f(1.0f, 1.0f, 1.0f);
  reader.drawModel();

  glFlush();
}

void reshape(int w, int h) {
    h = h == 0 ? 1 : h;  // width can't be zero
    float ratio =  w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    view();
}

int main(int argc, char *argv[]) {
    readModel();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Computer Graphics HW5 - Mesh");

    setLight();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}