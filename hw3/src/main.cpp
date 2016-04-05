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

#define ROTATION 100
#define ROTATION_R 68
#define REVOLUTION 121
#define REVOLUTION_R 89

int rotation = 0;
int revolution = 0;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, WIDHT * 1.0f / HEIGHT, 0.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.2f, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glutWireSphere(0.5f, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glRotatef(revolution, 0.0, 1.0, 0.0);
    glTranslatef(-0.7f, 0.0, 0.0);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    glutWireSphere(0.1f, 10, 10);
    glPopMatrix();

    glutSwapBuffers();
}

void rotate(unsigned char key, int x, int y) {
    switch(key) {
        case ROTATION:
            rotation = (rotation + 10) % 360;
            glutPostRedisplay();
            break;
        case ROTATION_R:
            rotation = (rotation - 10) % 360;
            glutPostRedisplay();
            break;
        case REVOLUTION:
            revolution = (revolution + 10) % 360;
            glutPostRedisplay();
            break;
        case REVOLUTION_R:
            revolution = (revolution - 10) % 360;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void reshape(int w, int h) {
    h = h == 0 ? 1 : h;  // width can't be zero
    float ratio =  w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 0.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.2f, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(WIDHT, HEIGHT);
    glutCreateWindow("Computer Graphics HW3");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(rotate);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}