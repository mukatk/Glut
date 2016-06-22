#include <cmath>

#define PI 3.1415926535898

class Camera {
public:
	float ex, ey, ez;
	float dx, dy, dz;
	float ux, uy, uz;
	float angle, rad;

	Camera(float posx, float posy, float posz){
		ex = posx;
		ey = dy = posy; //mesma altura
		ez = posz;
		ux = uz = 0;
		uy = 1;
		angle = 0;
		setAngle(270.0f);
		dx = ex + cos(rad);
		dz = ez + sin(rad);
	}

	~Camera() {
	}

	void upDownCam(float v) {
		ey += v;
		dy += v;
	}

	void setAngle(float ang) {
		angle += ang;
		rad = angle * PI / 180.0f;
	}

	void move(float v) {
		float ddx = cos(rad) * v;
		float ddz = sin(rad) * v;
		ex += ddx;
		ez += ddz;
		dx += ddx;
		dz += ddz;
	}

	void rotate(float a) {
		setAngle(a);
		float ddx = cos(rad);
		float ddz = sin(rad);
		dx = ex + ddx;
		dz = ez + ddz;
	}
};