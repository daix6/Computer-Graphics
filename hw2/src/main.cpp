#ifdef __APPLE__ // In macosx
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// #include <GL/gl.h>
// #include <GL/glu.h>

// #ifdef _WIN32
// #include <windows.h>
// #endif

static const GLfloat cube[][3] = {
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  -0.5f,   0.5f, -0.5f,
  0.5f,   0.5f, -0.5f,
  -0.5f, -0.5f,   0.5f,
  0.5f, -0.5f,   0.5f,
  -0.5f,   0.5f,   0.5f,
  0.5f,   0.5f,   0.5f,
};

static const GLint cubeSurface[][4] = {
  4, 5, 7, 6, // front
  0, 2, 3, 1, // back
  0, 4, 6, 2, // left
  1, 3, 7, 5, // right
  2, 6, 7, 3, // top
  0, 1, 5, 4 // bottom
};

void render1(void) {
  int i;
  // Clear screen and z-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glBegin(GL_QUADS);
    for (i = 0; i < 4; ++i)
      glVertex3fv(cube[cubeSurface[0][i]]);
  glEnd();

  glutSwapBuffers();
}

void render2() {
  int i, j;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();  
  gluPerspective(60.0, 1.0f, .1f, 5.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-1.0f, .0, 2.0f, .0, .0, .0, .5f, .8f, .0);  

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_QUADS);
    glColor3f(0, 1.0f, 0); // Green
    for (i = 0; i < 6; ++i)
      for (j = 0; j < 4; ++j)
        glVertex3fv(cube[cubeSurface[i][j]]);
  glEnd();

  glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(-1, -1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(5.0f);
  glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f); // Black border
    for (i = 0; i < 6; ++i)
      for (j = 0; j < 4; ++j)
        glVertex3fv(cube[cubeSurface[i][j]]);
  glEnd();
  glDisable(GL_POLYGON_OFFSET_LINE);

  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Computer Graphics HW2");

    // Register callbacks
    glutDisplayFunc(render2);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}