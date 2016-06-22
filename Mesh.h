#pragma once

#include <vector>
#include "Group.h"
#include "Vertex.h"
#include "TextureMapping.h"

using namespace std;

class Mesh
{
public:
	vector<Vertex*> allVertex;
	vector<Vertex*> allNormals;
	vector<TextureMapping*> allTextures;
	vector<Group*> groups;
	vector<float> points;
	vector<float> normalPoints;
	vector<float> texturePoints;
	
	Mesh()
	{

	}

	~Mesh()
	{
	}

	void addGroup(Group* g) {
		groups.push_back(g);
	}

	void addVertex(Vertex* v) {
		allVertex.push_back(v);
	}

	void addNormal(Vertex* v) {
		allNormals.push_back(v);
	}

	void addTexture(TextureMapping* m) {
		allTextures.push_back(m);
	}

	void generatePoints() {
		for (int i = 0; i < groups.size(); i++)
		{
			for (int j = 0; j < groups[i]->faces.size(); j++)
			{
				for (int k = 0; k < groups[i]->faces[j]->refPoints.size(); k++)
				{
					Vertex* vx = allVertex[groups[i]->faces[j]->refPoints[k]];
					if (groups[i]->faces[j]->normalPoints.size() > 0) {
						Vertex* vn = allNormals[groups[i]->faces[j]->normalPoints[k]];
						normalPoints.push_back(vn->coords[0]); 
						normalPoints.push_back(vn->coords[1]); 
						normalPoints.push_back(vn->coords[2]);
					}

					if (groups[i]->faces[j]->textPoints.size() > 0) {
						TextureMapping* vt = allTextures[groups[i]->faces[j]->textPoints[k]];
						texturePoints.push_back(vt->u);
						texturePoints.push_back(vt->v);
					}

					points.push_back(vx->coords[0]);
					points.push_back(vx->coords[1]);
					points.push_back(vx->coords[2]);
				}
			}
		}
	}
};
