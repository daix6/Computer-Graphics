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
GLfloat lastX, lastY;
GLfloat translate_x = 0, translate_y = 0;
bool horizontal = true;
int thetaX = 0, thetaY = 0;
int rotateX_x = 0.0, rotateX_y = 1.0, rotateX_z = 0.0;
int rotateY_x = 1.0, rotateY_y = 0.0, rotateY_z = 0.0;

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
  glEnable(GL_DEPTH_TEST);

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
  gluPerspective(90, WIDTH * 1.0 / HEIGHT, depthZ * 0.5, depthZ * 5);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(centerX, centerY, depthZ * 2, centerX, centerY, centerZ, 0, 1, 0);
}

void render() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  view();

  glPushMatrix();
  glTranslated(translate_x, translate_y, 0.0f);
  glRotated(thetaX, rotateX_x, rotateX_y, rotateX_z);
  glRotated(thetaY, rotateY_x, rotateY_y, rotateY_z);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  reader.drawModel();
  glPopMatrix();

  glFlush();
}

void reshape(int w, int h) {
    h = h == 0 ? 1 : h;  // width can't be zero
    float ratio =  w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    view();
}

void click(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    lastX = x;
    lastY = y;
  }
}

void motion(int x, int y) {
  float vec_x = x - lastX, vec_y = y - lastY;
  lastX = x;
  lastY = y;
  translate_x += (vec_x / WIDTH) * (reader.getMaxX() - reader.getMinX());
  translate_y += (-vec_y / HEIGHT) * (reader.getMaxY() - reader.getMinY());

  glutPostRedisplay();
}

void rotate(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      thetaY -= 2;
      horizontal = false;
      glutPostRedisplay();
      break;
    case 's':
      thetaY += 2;
      horizontal = false;
      glutPostRedisplay();
      break;
    case 'a':
      thetaX += 2;
      horizontal = true;
      glutPostRedisplay();
      break;
    case 'd':
      thetaX -= 2;
      horizontal = true;
      glutPostRedisplay();
      break;
    default:
      break;
  }
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

    glutMouseFunc(click);
    glutMotionFunc(motion);
    glutKeyboardFunc(rotate);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}