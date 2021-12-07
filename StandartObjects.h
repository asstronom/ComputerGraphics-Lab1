#pragma once

#include "Mesh.h"




class Cube : public Mesh {
public:
	Cube();
};

class Octaedr : public Mesh {
public:
	Octaedr();
};

class Torus : public Mesh {
public: 
	Torus(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};

Torus BuildTorus(GLfloat radius_XY = 2.0f, GLfloat radius_YZ = 1.0f);

Mesh BuildGraph(double (*func)(double, double), double LimitX, double LimitY, double h);

Mesh GenerateAxis(double limitXY, double limitZ);