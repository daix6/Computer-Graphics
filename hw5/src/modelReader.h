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

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

#define OFF 0
#define PLY 1
#define OBJ 2

class modelReader {
  public:
    modelReader(string filename);
    void handleModel();
    
    void offModelReader(ifstream& model);
    void plyModelReader(ifstream& model);
    void objModelReader(ifstream& model);
    GLfloat getCenter();
  private:
    int mode;
    string file;
    GLfloat highY, lowY;
    GLfloat highZ, lowZ;
    
};

GLfloat* normalize(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]);