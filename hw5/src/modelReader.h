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

#define WIREFRAME 3
#define FLAT 4
#define FLAT_LINE 5

typedef vector<int> Face;

class modelReader {
  public:
    modelReader();
    modelReader(string filename);
    ~modelReader();
    void setFile(string filename);
    void setStyle(int style);

    void readModel();
    void drawModel();
    void drawModel(int style);

    GLfloat getMaxX();
    GLfloat getMaxY();
    GLfloat getMaxZ();
    GLfloat getMinX();
    GLfloat getMinY();
    GLfloat getMinZ();
  private:
    void offModelReader(ifstream& model);
    void plyModelReader(ifstream& model);
    void objModelReader(ifstream& model);
    void adjustRange(GLfloat x, GLfloat y, GLfloat z);
    void drawNormalize(Face face);

    int mode, style;
    string file;
    vector<Point> vertices;
    vector<Face> faces;

    GLfloat highX, lowX;
    GLfloat highY, lowY;
    GLfloat highZ, lowZ;
};
