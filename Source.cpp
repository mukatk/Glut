#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <fstream>
#include "Camera.h"
#include "OBJReader.h"
#include "Mesh.h"
#include "Material.h";

using namespace std;

int width = 800;
int height = 600;
float v = 0.6f;
int hv = 1.0f;

int objA = 0;

int selectedGroup = 0;

Camera *cam;

Mesh* m = new Mesh();
vector<Material*> mat;

void applyTexture() {
	// Create one OpenGL texture

	for (int l = 0; l < mat.size(); l++)
	{
		if (mat[l]->hasTexture()) {
			GLuint textureID;
			glGenTextures(1, &textureID);
			mat[l]->textureID = textureID;
			glBindTexture(GL_TEXTURE_2D, mat[l]->textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mat[l]->img->getWidth(), mat[l]->img->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, mat[l]->img->getPixels());
		}
	}	
}

void DrawObject() {
	for (int i = 0; i < m->groups.size(); i++)
	{
		if (!m->groups[i]->visible) continue;

		int selectedMaterial = -1;

		for (int l = 0; l < mat.size(); l++)
		{
			if (mat[l]->name == m->groups[i]->material) {
				selectedMaterial = l;
				break;
			}
		}

		if (selectedMaterial > -1 && mat[selectedMaterial]->hasTexture())
		{
			glBindTexture(GL_TEXTURE_2D, mat[selectedMaterial]->textureID);
		}

		if (selectedMaterial > -1) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat[selectedMaterial]->Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat[selectedMaterial]->Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat[selectedMaterial]->Ks);
			glMaterialf(GL_FRONT, GL_SHININESS, mat[selectedMaterial]->Ns);
		}

		for (int j = 0; j < m->groups[i]->faces.size(); j++)
		{
			glBegin(GL_POLYGON);
			for (int k = 0; k < m->groups[i]->faces[j]->refPoints.size(); k++)
			{
				Vertex* vx = m->allVertex[m->groups[i]->faces[j]->refPoints[k]];
				if (m->groups[i]->faces[j]->normalPoints.size() > 0) {
					Vertex* vn = m->allNormals[m->groups[i]->faces[j]->normalPoints[k]];
					glNormal3f(vn->coords[0], vn->coords[1], vn->coords[2]);
				}

				if (m->groups[i]->faces[j]->textPoints.size() > 0) {
					TextureMapping* vt = m->allTextures[m->groups[i]->faces[j]->textPoints[k]];
					glTexCoord2f(vt->u, vt->v);
				}

				glVertex3f(vx->coords[0], vx->coords[1], vx->coords[2]);
			}
			glEnd();
		}
	}
	
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float) w / (float) h, 1.0, 10000);
	glViewport(0, 0, width = w, height = h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);
}

void display(void)
{
/*  clear all pixels  */
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawObject();

/*  don't wait!  
 *  start processing buffered OpenGL routines 
 */
	glutSwapBuffers ();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w') {
		int c = (cos(cam->rad) * v + cam->ex); 
		int l = (sin(cam->rad) * v + cam->ez);

		cam->move(v);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);

		glutPostRedisplay();
	}

	if (key == 's') {
		int c = (cos(cam->rad) * -v + cam->ex); 
		int l = (sin(cam->rad) * -v + cam->ez);

		cam->move(-v);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);

		glutPostRedisplay();
	}

	if (key == 'd') {
		cam->rotate(hv);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);
		glutPostRedisplay();
	}

	if (key == 'a') {
		cam->rotate(-1 * hv);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);
		glutPostRedisplay();
	}

	if (key == 'u') {
		cam->upDownCam(v);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);
		glutPostRedisplay();
	}

	if (key == 'j') {
		cam->upDownCam(-v);
		glLoadIdentity();
		gluLookAt(cam->ex, cam->ey, cam->ez, cam->dx, cam->dy, cam->dz, cam->ux, cam->uy, cam->uz);
		glutPostRedisplay();
	}
	
	if (key == 'm') {
		selectedGroup = (selectedGroup++) % (m->groups.size() - 1);
		glutPostRedisplay();
	}

	if (key == 'b') {
		if (selectedGroup > -1) {
			m->groups[selectedGroup]->changeVisibility();
			glutPostRedisplay();
		}
	}

	if (key == 'n') {
		if (selectedGroup > 0) {
			selectedGroup--;
			glutPostRedisplay();
		}
	}

	if (key == 'q' || key == 'Q') {
		exit(0);
	}
}

void init (void) 
{
/*  select clearing (background) color       */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	cam = new Camera(0, 1, 0);
	OBJReader* reader = new OBJReader();
	reader->readObj("Sonic/Sonic.obj", m, mat);
	//reader->readObj("Deadpool/dead 123456.obj", m, mat);
	//reader->readObj("moon.obj", m, mat);
	//reader->readObj("tie-intercept.obj", m, mat);
	//reader->readObj("Millennium_Falcon/millenium-falcon.obj", m, mat);
	applyTexture();
	//reader->readObj("bb8.obj", m, mat);
}


/* 
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (width, height); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");

    init ();
    glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}