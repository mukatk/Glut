#pragma once

#include <stdlib.h>
#include <vector>
#include "Face.h"
#include "Material.h"

using namespace std;

class Group
{
public:
	vector<Face*> faces;
	string name;
	bool visible;
	string material;

	Group()
	{
		visible = true;
	}

	void AddFace(Face* f) {
		faces.push_back(f);
	}

	void changeVisibility() {
		visible = !visible;
	}

	~Group()
	{
		for (int i = 0; i < faces.size(); i++)
		{
			delete faces[i];
		}
	}

};