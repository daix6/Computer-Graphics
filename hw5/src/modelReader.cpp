#include "modelReader.h"
#include <math.h>

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

modelReader::modelReader() : highX(-0xFF), lowX(0xff), highY(-0xFF), lowY(0xFF), highZ(-0xFF), lowZ(0xFF) {}

modelReader::modelReader(string filename) : file("data/" + filename) {
  modelReader();
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

modelReader::~modelReader() {
  vertices.clear();
  faces.clear();
}

void modelReader::setFile(string filename) {
  this->file = "data/" + filename;

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

void modelReader::setStyle(int style) {
  this->style = style;
}

void modelReader::readModel() {
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

// Reference : http://shape.cs.princeton.edu/benchmark/documentation/off_format.html
void modelReader::offModelReader(ifstream& model) {
  string s;
  int vertex = 0, face = 0, edge = 0;

  getline(model, s); // 1st line: OFF
  model >> vertex >> face >> edge;

  // VERTEX
  GLfloat x = 0, y = 0, z = 0;
  for (int i = 0; i < vertex; ++i) {
    model >> x >> y >> z;
    vertices.push_back(Point(x, y, z));
    adjustRange(x, y, z);
  }

  // FACE
  int face_size = 0;
  for (int i = 0; i < face; ++i) {
    model >> face_size;

    Face face;
    for (int j = 0; j < face_size; ++j) {
      int which;
      model >> which;
      face.push_back(which);
    }
    faces.push_back(face);
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

  // VERTEX
  GLfloat x = 0, y = 0, z = 0;
  for (int i = 0; i < vertex; ++i) {
    model >> x >> y >> z;
    vertices.push_back(Point(x, y, z));
    adjustRange(x, y, z);
  }

  // FACE
  int face_size = 0;
  for (int i = 0; i < face; ++i) {
    model >> face_size;
    
    Face face;
    for (int j = 0; j < face_size; ++j) {
      int which;
      model >> which;
      face.push_back(which);
    }
    faces.push_back(face);
  }
}

// Reference: http://www.fileformat.info/format/wavefrontobj/egff.htm
void modelReader::objModelReader(ifstream& model) {
  string tag;
  while (model >> tag) {
    if (tag == "v") {
      GLfloat x, y, z;
      model >> x >> y >> z;
      vertices.push_back(Point(x, y, z));
      adjustRange(x, y, z);
    } else if (tag == "f") { // OBJ's face index start from 1
      string s;
      int found, next;
      Face face;
      getline(model, s);
      found = s.find_first_of(" ");
      while (1) {
        next = s.find_first_of(" ", found + 1);
        if (next == string::npos) {
          face.push_back(myAtoi(s.substr(found + 1)) - 1);
          break;
        }
        face.push_back(myAtoi(s.substr(found + 1, next - found - 1)) - 1);
        found = next;
      }
      faces.push_back(face);
    }
  }
}

void modelReader::adjustRange(GLfloat x, GLfloat y, GLfloat z) {
  if (highX < x) highX = x;
  if (lowX > x) lowX = x;
  if (highY < y) highY = y;
  if (lowY > y) lowY = y;
  if (highZ < z) highZ = z;
  if (lowZ > z) lowZ = z;
}

void modelReader::drawModel() {
  drawModel(this->style);
}

void modelReader::drawModel(int style) {
  switch(style) {
    case FLAT_LINE:
      drawModel(FLAT);

      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glColor3f(0.2f, 0.2f, 0.2f);
      for (vector<Face>::const_iterator iter1 = faces.begin(), end1 = faces.end(); iter1 != end1; iter1++) {
        glBegin(GL_POLYGON);

        for (Face::const_iterator iter2 = (*iter1).begin(), end2 = (*iter1).end(); iter2 != end2; iter2++)
          glVertex3fv(vertices[*iter2].getPointVector());

        glEnd();
      }
      glEnable(GL_LIGHTING);

      break;
    case WIREFRAME:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case FLAT:
    default:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
  }

  for (vector<Face>::const_iterator iter1 = faces.begin(), end1 = faces.end(); iter1 != end1; iter1++) {
    glBegin(GL_POLYGON);

    drawNormalize(*iter1);
    for (Face::const_iterator iter2 = (*iter1).begin(), end2 = (*iter1).end(); iter2 != end2; iter2++)
      glVertex3fv(vertices[*iter2].getPointVector());

    glEnd();
  }
}

void modelReader::drawNormalize(Face face) {
  GLfloat* a = vertices[face[0]].getPointVector();
  GLfloat* b = vertices[face[1]].getPointVector();
  GLfloat* c = vertices[face[2]].getPointVector();
  
  GLfloat x1 = b[0] - a[0], y1 = b[1] - a[1], z1 = b[2] - a[2];
  GLfloat x2 = c[0] - a[0], y2 = c[1] - a[1], z2 = c[2] - a[2];

  GLfloat x, y, z;
  // 叉积
  x = y1 * z2 - z1 * y2;
  y = z1 * x2 - x1 * z2;
  z = x1 * y2 - y1 * x2;

  // Normalize
  GLfloat mod = sqrt(x * x + y * y + z * z);
  glNormal3f(x / mod, y / mod, z / mod); 
}

GLfloat modelReader::getMaxX() {
  return highX;
}

GLfloat modelReader::getMaxY() {
  return highY;
}

GLfloat modelReader::getMaxZ() {
  return highZ;
}

GLfloat modelReader::getMinX() {
  return lowX;
}

GLfloat modelReader::getMinY() {
  return lowY;
}

GLfloat modelReader::getMinZ() {
  return lowZ;
}