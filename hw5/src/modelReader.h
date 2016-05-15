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
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#ifndef _POINT_H_
#define _POINT_H_
#include "Point.h"
#endif

using std::string;
using std::vector;
using std::ifstream;

#define OFF 0
#define PLY 1
#define OBJ 2

typedef vector<int> Face;

class modelReader {
  public:
    modelReader(string filename);
    ~modelReader();
    void readModel();

    void drawModel();

    GLfloat getCenter();
  private:
    void offModelReader(ifstream& model);
    void plyModelReader(ifstream& model);
    void objModelReader(ifstream& model);
    void adjustRange(GLfloat x, GLfloat y, GLfloat z);

    int mode;
    string file;
    vector<Point> vertices;
    vector<Face> faces;

    GLfloat highY, lowY;
    GLfloat highZ, lowZ;
};
