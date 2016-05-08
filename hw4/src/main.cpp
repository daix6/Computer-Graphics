#include <iostream>
#include <vector>
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

#define WIDTH 500
#define HEIGHT 500

struct Point {
  GLfloat x;
  GLfloat y;
};

class Bezier {
    public:
      void addPoint(GLfloat x, GLfloat y) {
        if (points.size() < 4) {
          Point p;
          p.x = x;
          p.y = y;
          points.push_back(p);
        }
      }
      void drawPoints() {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_POINTS);
          for (int i = 0, len = points.size(); i < len; i++)
            glVertex2f(points[i].x, points[i].y);
        glEnd();
      }
      void drawLines() {
        glColor3f(1.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        for (int i = 0, len = points.size() - 1; i < len; i++) {
          glVertex2f(points[i].x, points[i].y);
          glVertex2f(points[i+1].x, points[i+1].y);
        }
        glEnd();
      }
      void drawBezier() {
        Point lastP = points[0], p;
        float a, b, c, d;

        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for (float t = 0.0f, temp = 1.0f; t <= 1.0f ; t += 0.05f, temp = 1 - t) {
          a = temp * temp * temp;
          b = 3 * t * temp * temp;
          c = 3 * t * t * temp;
          d = t * t * t;

          p.x = a * points[0].x + b * points[1].x + c * points[2].x + d * points[3].x;
          p.y = a * points[0].y + b * points[1].y + c * points[2].y + d * points[3].y;
          
          glVertex2f(lastP.x, lastP.y);
          glVertex2f(p.x, p.y);
          lastP = p;
        }
        glEnd();
      }
      void draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        drawPoints();
        if (points.size() >= 4) {
          drawLines();
          drawBezier();
        }
        glFlush();
       }
    private:
      std::vector<Point> points;
};

Bezier bezier;

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Background Color
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WIDTH, 0.0, HEIGHT); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(4.0f);
    glEnable(GL_POINT_SMOOTH);

    bezier.draw();
}

void idle() {
  bezier.draw();
}

void choosePoint(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      bezier.addPoint(x, HEIGHT - y);
}

void reshape(int w, int h) {
    h = h == 0 ? 1 : h;  // width can't be zero
    float ratio =  w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WIDTH, 0.0, HEIGHT); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Computer Graphics HW4 - Bezier Curve");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMouseFunc(choosePoint);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}