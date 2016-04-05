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

#define WIDHT 500
#define HEIGHT 500

static const GLfloat cube[][3] = {
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  -0.5f, 0.5f, -0.5f,
  0.5f, 0.5f, -0.5f,
  -0.5f, -0.5f, 0.5f,
  0.5f, -0.5f, 0.5f,
  -0.5f, 0.5f, 0.5f,
  0.5f, 0.5f, 0.5f,
};

static const GLint cubeSurface[][4] = {
  4, 5, 7, 6, // front
  0, 2, 3, 1, // back
  0, 4, 6, 2, // left
  1, 3, 7, 5, // right
  2, 6, 7, 3, // top
  0, 1, 5, 4 // bottom
};

void drawCube() {
  int i, j;
  glBegin(GL_QUADS);
    for (i = 0; i < 6; ++i)
      for (j = 0; j < 4; ++j)
        glVertex3fv(cube[cubeSurface[i][j]]);
  glEnd();
}

void render1() {
  int i;
  // Clear screen and z-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    for (i = 0; i < 4; ++i)
      glVertex3fv(cube[cubeSurface[0][i]]);
  glEnd();
  
  glFlush();
}

void reshape1(int width, int height) {
    height = height == 0 ? 1 : height;  // width can't be zero
    float ratio =  width * 1.0f / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_MODELVIEW);
}

void render2() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();  
  gluPerspective(60.0, 1.0f, 0, 5.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-1.0f, .0, 2.0f, 0, 0, 0, .5f, .8f, 0);  

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(0, 1.0f, 0); // Green
  drawCube();

  glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(-1, -1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(5.0f);
  glColor3f(0, 0, 0);
  drawCube();
  glDisable(GL_POLYGON_OFFSET_LINE);

  glFlush(); // No need to swap buffer
}

void reshape2(int width, int height) {
  height = height == 0 ? 1 : height;  // width can't be zero
  float ratio =  width * 1.0f / height;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, width, height);
  gluPerspective(60.0, 1.0f, 0, 5.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-1.0f, .0, 2.0f, 0, 0, 0, .5f, .8f, 0);  
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(WIDHT, HEIGHT);
    glutCreateWindow("Computer Graphics HW2");

    // Register callbacks
    // glutDisplayFunc(render1);
    // glutReshapeFunc(reshape1);
    
    glutDisplayFunc(render2);
    glutReshapeFunc(reshape2);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}