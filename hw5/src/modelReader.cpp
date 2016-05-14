#include "modelReader.h"
#include <stdexcept>
#include <iostream>
#include <math.h>
#include <cstdio>

using std::cout;
using std::endl;

int myAtoi(string str) {
  if (str.empty()) return 0;
  int i = 0, sign = 1;
  while (i + 1 < str.size() && isspace(str[i])) ++i;
  long res = 0;
  if (str[i] == '-' || str[i] == '+') sign = 44 - str[i++];
  while (i < str.size()) {
    if (isdigit(str[i])) res = 10 * res + str[i++] - '0';
    else return res * sign;
  }
  return res * sign;
}

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
    glBegin(GL_POLYGON);
    for (int j = 0; j < points; ++j) {
      model >> which;
      glVertex3fv(vertices[which]);
    }
    glEnd();
  }
}

// Reference: http://paulbourke.net/dataformats/ply/
void modelReader::plyModelReader(ifstream& model) {
  string s;
  int vertex = 0, face = 0;

  while (getline(model, s)) {
    if (s.find("end_header") != -1) break;

    int where;
    if ((where = s.find("element vertex")) != -1)
      vertex = myAtoi(s.substr(15));
    else if ((where = s.find("element face")) != -1)
      face = myAtoi(s.substr(13));
  }

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

  int points = 0, which = 0;

  for (int i = 0; i < 5; ++i) {
    model >> points;
    cout << points << " ";
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin(GL_POLYGON);
    for (int j = 0; j < points; ++j) {
      model >> which;
      cout << which << " ";
      glVertex3fv(vertices[which]);
    }
    glEnd();
  }
}

// Reference: http://www.fileformat.info/format/wavefrontobj/egff.htm
void modelReader::objModelReader(ifstream& model) {}

GLfloat modelReader::getCenter() {
  return (highY + lowY) / 2;
}