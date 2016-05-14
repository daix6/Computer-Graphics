#include "modelReader.h"
#include <stdexcept>
#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

GLfloat* normalize(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]) {
  GLfloat vc1[3],vc2[3];
  GLfloat a, b, c;
  GLfloat* nor = new GLfloat[3];

  GLdouble r;
  vc1[0]= v2[0] - v1[0]; vc1[1]= v2[1] - v1[1]; vc1[2]= v2[2] - v1[2];
  vc2[0]= v3[0] - v1[0]; vc2[1]= v3[1] - v1[1]; vc2[2]= v3[2] - v1[2];
  a = vc1[1] * vc2[2] - vc2[1] * vc1[2];
  b = vc2[0] * vc1[2] - vc1[0] * vc2[2];
  c = vc1[0] * vc2[1] - vc2[0] * vc1[1];
  r = sqrt( a * a + b * b + c * c);
  nor[0] = a / r;
  nor[1] = b / r;
  nor[2] = c / r;

  return nor;
}

modelReader::modelReader(string filename) : file(filename), highY(0xFF), lowY(-0xFF), highZ(0xFF), lowZ(-0xFF) {
  int where = file.rfind('.');
  string posfix = file.substr(where + 1);

  if (posfix == "off")
    mode = OFF;
  else if (posfix == "ply")
    mode = PLY;
  else if (posfix == "obj")
    mode = OBJ;
  else
    throw std::invalid_argument("Wrong file type.");
}

// Reference : http://shape.cs.princeton.edu/benchmark/documentation/off_format.html
void modelReader::handleModel() {
  ifstream model(this->file.c_str());

  if (model.fail()) {
    throw std::runtime_error("Wrong when read the file");
    return;
  } 

  switch(this->mode) {
    case OFF:
      offModelReader(model);
      break;
    case PLY:
      plyModelReader(model);
      break;
    case OBJ:
      objModelReader(model);
      break;
    default:
      break;
  }

  model.close();
}

void modelReader::offModelReader(ifstream& model) {
  string s;
  int vertex = 0, face = 0, edge = 0;

  getline(model, s); // 1st line: OFF
  model >> vertex >> face >> edge;

  GLfloat (*vertices)[3] = new GLfloat[vertex][3]; 

  // VERTEX
  GLfloat x = 0, y = 0, z = 0;
  for (int i = 0; i < vertex; ++i) {
    model >> x >> y >> z;
    vertices[i][0] = x;
    vertices[i][1] = y;
    vertices[i][2] = z;
    if (highY < y) highY = y;
    if (lowY > y) lowY = y;
    if (highZ < z) highZ = z;
    if (lowZ > z) lowZ = z;
  }

  // SURFACE
  int points = 0, which = 0;
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  for (int i = 0; i < face; ++i) {
    model >> points;
    GLfloat (*faces)[3] = new GLfloat[points][3];
    glBegin(GL_POLYGON);
    for (int j = 0; j < points; ++j) {
      model >> which;
      // for (int k = 0; k < 3; ++k)
      //   faces[j][k] = vertices[which][k];
      glVertex3fv(vertices[which]);
    }
    glEnd();
    // glBegin(GL_POLYGON);
    // glNormal3fv(normalize(faces[0], faces[1], faces[2]));
    // for (int j = 0; j < points; ++j)
    //   glVertex3fv(faces[j]);
    // glEnd();
  }
}

// Reference: http://paulbourke.net/dataformats/ply/
void modelReader::plyModelReader(ifstream& model) {}

// Reference: http://www.fileformat.info/format/wavefrontobj/egff.htm
void modelReader::objModelReader(ifstream& model) {}

GLfloat modelReader::getCenter() {
  return (highY + lowY) / 2;
}