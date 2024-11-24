// EllipsoidInOpenGL.c

#include <windows.h> //Windows-specific headers
#include <GL/glut.h> //OpenGL Utility Toolkit header
#include <stdio.h> // Standard input/output header
#include <stdlib.h> // Standard Library header
#include <math.h> // Math functions


#define PI 3.142857

// Define normalization factors
#define X .525731112119133606
#define Z .850650808352039932


// Define vertex coordinates for an icosahedron
static GLfloat vdata[12][3] = {
  { -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
  { 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
  { Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
};

// Define triangle indices for the icosahedron faces (manually create 20 points from vdata)
/*
static GLuint tindices[20][3] = {
{ , ,  }, { , ,  }, { , ,  }, { , ,  }, { , ,  },
 { , , }, { , ,  }, { , ,  }, { , ,  }, { , ,  },
 { , ,  }, { , ,  }, { , ,  }, { , ,  }, { , ,  },
 { , , }, { , ,  }, { , ,  }, { , ,  }, { , ,  },
};
*/


// Define a rotation angle for animation
GLfloat angle = 0;



void myinit(void)
{
	// Clear the screen with a specific color and transparency
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // Enable depth testing
	glEnable(GL_NORMALIZE); // Enable normalization

	//Select the Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8, 8, -8, 8, -8, 8); // Set orthographic projection

    gluLookAt(1, 0, 0, 0, 0, 0, 0, 0, 1); // Set the camera position

}

void setMaterial(float ambientR, float ambientG, float ambientB,
	float diffuseR, float diffuseG, float diffuseB,
	float specularR, float specularG, float specularB, float shine)
{
    // Set material properties for the object
	GLfloat ambient[] = { ambientR, ambientG, ambientB };
	GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
	GLfloat specular[] = { specularR, specularG, specularB };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void animate()
{
    // Update the rotation angle and trigger a redisplay
	angle = angle + 0.5;
	Sleep(10);
	glutPostRedisplay();
}


//draws triangle at the specified coordinate and material properties
void drawtriangle(float v1[3], float v2[3], float v3[3], float rx, float ry, float rz) {

	setMaterial(0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 0.5, 0.5, 128);

	glBegin(GL_TRIANGLES);
	glNormal3f(v1[0]/rx, v1[1]/ry, v1[2]/rz);
	glVertex3f(v1[0]*rx, v1[1]*ry, v1[2]*rz);
	glNormal3f(v2[0]/rx, v2[1]/ry, v2[2]/rz);
	glVertex3f(v2[0]*rx, v2[1]*ry, v2[2]*rz);
	glNormal3f(v3[0]/rx, v3[1]/ry, v3[2]/rz);
	glVertex3f(v3[0]*rx, v3[1]*ry, v3[2]*rz);
	glEnd();
}

// Normalize a vector to unit length
void normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		printf("zero length vector\n");
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

// Recursively subdivide triangles to create smoother shapes
void subdivide(float v1[3], float v2[3], float v3[3],float rx, float ry, float rz, long depth) {
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	//end recursion
	if (depth == 0) {
		drawtriangle(v1, v2, v3, rx, ry, rz);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}

	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31,rx, ry, rz, depth - 1);
	subdivide(v2, v23, v12, rx, ry, rz, depth - 1);
	subdivide(v3, v31, v23, rx, ry, rz, depth - 1);
	subdivide(v12, v23, v31, rx, ry, rz, depth - 1);
}
void display(void) {
    // Clear buffers and set shading model
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);

    // Rotate and draw the ellipsoid
	glPushMatrix();
    glRotatef(angle, 0.5, 1.0, 0.5);
    glColor3f(0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	setMaterial(0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 0.5, 0.5, 58);

	int subdivisionDepth = 4; //Increased depth for smoother ellipsoid

	for (int i = 0; i < 20; i++) {
		subdivide(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]],2, 4, 8, subdivisionDepth);
		setMaterial(0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 0.5, 0.5, 50);
	}
	glPopMatrix();

	glFlush();
}


void initLight()
{
	// Set up default lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat ambient[] = { 0.3, 0.3, 0.3 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.5 };
	GLfloat specular[] = { 1, 1, 1 };
	GLfloat position1[] = { -2,0.5,4,1 };
	GLfloat position2[] = { 0,0.5,-4,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, position2);

	glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
	//Step1: Initilize the GLUT using command line parameters
	glutInit(&argc, argv);

	//Step2: Used for setting up openGL window
	// and setting the size of this window
	glutInitWindowSize(640, 480);

	//Step3: Setting up the position of the window on our screen
	glutInitWindowPosition(10, 10);

	//setup the display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);


	//Step4: Give a name to your window.
	glutCreateWindow("My First OpenGL Project");

	glEnable(GL_DEPTH_TEST);

	//set the projection window
	myinit();

	//setup light
	initLight();

	// register the display callback.
	glutDisplayFunc(display);

	//register a timer callback function
	glutIdleFunc(animate);

	//trigger the display callback
	glutMainLoop();

	return 0;
}
