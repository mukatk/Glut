#pragma once

#include <vector>

using namespace std;

class Vertex
{
public:
	float coords[3];

	Vertex(float x, float y, float z) {
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
	}

	Vertex() {

	}

	~Vertex() {
		delete coords;
	}

};