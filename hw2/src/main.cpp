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

void render1(void) {
  // Clear screen and z-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.5, 0);
    glVertex3f(0.5, 0.5, 0);
    glVertex3f(0.5, -0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
  glEnd();
  
  glutSwapBuffers();
}

void render2() {
  
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(500, 500);
    glutCreateWindow("First");

    // Register callbacks
    glutDisplayFunc(render1);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}