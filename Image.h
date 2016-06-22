#include <math.h>
#include <fstream>

using namespace std;

class Image {
public:
	Image(int w, int h) {
		width = w; height = h;
		pixels = new int[w*h * 3];
	}

	Image() {
		Image(1600, 724);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				setPixel(0, 255, 0, 255, j, i);
			}
		}
	}

	Image(string path) {
		ifstream arg(path);
		if (!arg.is_open()) {
			exit(EXIT_FAILURE);
		}

		char word[10];

		//Reading type
		arg >> word;

		//Reading width
		int argWidth;
		arg >> word;
		argWidth = atoi(word);

		//Reading height
		int argHeight;
		arg >> word;
		argHeight = atoi(word);

		//Reading max
		arg >> word;

		//Creating an image with arg size
		width = argWidth;
		height = argHeight;

		pixels = new int[argWidth * argHeight * 3];

		int a, r, g, b;
		for (int i = argHeight-1; i > 0; i--) {
			for (int j = 0; j < argWidth; j++) {
				arg >> word;
				a = atoi(word);
				arg >> word;
				r = atoi(word);
				arg >> word;
				g = atoi(word);
				arg >> word;
				b = atoi(word);
				setPixel(a, r, g, b, j, i);
			}
		}

		arg.close();
		//End of reading
	}

	~Image() {
		delete[] pixels;
	}

	void setPixel(int a, int r, int g, int b, int x, int y) {
		pixels[x + y * width] = (a << 24) | (r << 16) | (g << 8) | b;
	}

	int getPixel(int x, int y) {
		return pixels[x + y*width];
	}
	int getWidth() { return width; }

	int getHeight() { return height; }

	int* getPixels() {
		return pixels;
	}

private:
	int *pixels; // alternativamente char *pixels – 1 byte por canal
				 // neste caso, pixels = new char[w*h*3];
	int width, height;
};