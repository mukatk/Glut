#pragma once

#include "Image.h"

class Material
{
public:
	string name;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ns;
	string map_Kd;
	Image* img;
	int textureID;

	Material() {
		
	}

	~Material() {

	}

	bool hasTexture() {
		return map_Kd.size() > 0;
	}

	void loadImg() {
		if (map_Kd.size() > 0) {
			img = new Image(map_Kd);
		} else {
			img = new Image();
		}
	}

private:

};