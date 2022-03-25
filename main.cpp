#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <Windows.h>
#include <exception>
#include <fstream>
#include <cmath>
#include <thread>
#include <queue>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define PI 3.14159265359
using namespace std;

ofstream fout("form.txt");
struct vec {
	double x;
	double y;
	double z;
};
const int nr = 21;
int Map[nr][nr];
int wsubwindowsize = 1200, hsubwindowsize = 700;
double sze = 20;
map<int, vec> m;
int k = 0, icnt = 1, jcnt = 1;
double x, y, z;
int rotatey = 0;
int look = 10;
bool bar = true;
float linew = 0.5;
bool figura = false;

void Light(int x, int y, int z) {
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { x, y, z, 1 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void FileOut() {
	fout.clear();
	fout <<"x y z" << endl;
	for (int i = 0; i < nr; ++i) {
		for (int j = 0; j < nr; ++j) {
			fout << m[Map[i][j]].x << " " << m[Map[i][j]].y << " " << m[Map[i][j]].z << "\n";
		}
	}
}

void subinit() {
	m.clear();
	k = 0;
	for (int i = 0; i < nr; ++i) {
		x = (i - nr / 2) * sze + sze/2;
		for (int j = 0; j < nr; ++j) {
			z = (j - nr / 2) * sze + sze / 2;
			Map[i][j] = k;
			m[Map[i][j]].x = x;
			m[Map[i][j]].y = 0;
			m[Map[i][j]].z = z;
			k++;
		}
	}
}

void DrawMap() {
	float cnt = 0;
	
	for (int i = 0; i < nr - 1; ++i) {
		for (int j = 0; j < nr - 1; ++j) {
			if (bar) {
				glColor3d(0.2, 0.2, 0.2);
				glBegin(GL_QUADS);
				glVertex3d(m[Map[i][j]].x, m[Map[i][j]].y, m[Map[i][j]].z);
				glVertex3d(m[Map[i][j + 1]].x, m[Map[i][j + 1]].y, m[Map[i][j + 1]].z);
				glVertex3d(m[Map[i + 1][j + 1]].x, m[Map[i + 1][j + 1]].y, m[Map[i + 1][j + 1]].z);
				glVertex3d(m[Map[i + 1][j]].x, m[Map[i + 1][j]].y, m[Map[i + 1][j]].z);
				glEnd();
			}
			else {
				glColor3d(0.2, 0.2, 0.2);
				glBegin(GL_QUADS);
				glVertex3d(m[Map[i][j]].x + linew, m[Map[i][j]].y, m[Map[i][j]].z + linew);
				glVertex3d(m[Map[i][j + 1]].x + linew, m[Map[i][j + 1]].y, m[Map[i][j + 1]].z - linew);
				glVertex3d(m[Map[i + 1][j + 1]].x - linew, m[Map[i + 1][j + 1]].y, m[Map[i + 1][j + 1]].z - linew);
				glVertex3d(m[Map[i + 1][j]].x - linew, m[Map[i + 1][j]].y, m[Map[i + 1][j]].z + linew);
				glEnd();

				glPointSize(linew);
				glLineWidth(linew * 4);
				glColor3d(0.5, 0.5, 0.5);
				glBegin(GL_LINES);

				glVertex3d(m[Map[i][j]].x, m[Map[i][j]].y + cnt, m[Map[i][j]].z);
				glVertex3d(m[Map[i][j + 1]].x, m[Map[i][j + 1]].y + cnt, m[Map[i][j + 1]].z);

				glVertex3d(m[Map[i][j + 1]].x, m[Map[i][j + 1]].y + cnt, m[Map[i][j + 1]].z);
				glVertex3d(m[Map[i + 1][j + 1]].x, m[Map[i + 1][j + 1]].y + cnt, m[Map[i + 1][j + 1]].z);

				glVertex3d(m[Map[i + 1][j + 1]].x, m[Map[i + 1][j + 1]].y + cnt, m[Map[i + 1][j + 1]].z);
				glVertex3d(m[Map[i + 1][j]].x, m[Map[i + 1][j]].y + cnt, m[Map[i + 1][j]].z);

				glVertex3d(m[Map[i + 1][j]].x, m[Map[i + 1][j]].y + cnt, m[Map[i + 1][j]].z);
				glVertex3d(m[Map[i][j]].x, m[Map[i][j]].y + cnt, m[Map[i][j]].z);
				glEnd();
			}
		}
	}
}





void subdisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	glLoadIdentity();
	gluLookAt(0, hsubwindowsize/4 - look, hsubwindowsize/4, 0, sze , 0, 0, 1, 0);

	


	if (bar) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glutPostRedisplay();
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glutPostRedisplay();
	}

	if (figura) {
		glPushMatrix();
		glTranslated(0, sze * 2, 0);
		glRotated(rotatey, 0, 1, 0);
		glColor3d(0.5, 0.2, 0.1);
		glutSolidTeapot(sze * 4);
		glPopMatrix();
	}

	glPushMatrix();
	Light(sze * nr / 2, sze * nr, -sze * nr / 2);
	glPopMatrix();

	glRotated(rotatey, 0, 1, 0);
	DrawMap();
	glTranslated(m[Map[icnt][jcnt]].x, m[Map[icnt][jcnt]].y, m[Map[icnt][jcnt]].z);
	glColor3d(0, 0, 1);
	glutSolidSphere(3, 20, 20);

	glFlush();
	glutSwapBuffers();
	this_thread::sleep_for(chrono::milliseconds(1000/60));
}


void subnkey(unsigned char key, int x, int y) {
	if (key == 27) {
		FileOut();
		exit(0);
	}
	if (key == 'a') {
		rotatey++;
	}
	if (key == 'd') {
		rotatey--;
	}
	if (key == 'w') {
		look++;
	}
	if (key == 's') {
		look--;
	}
	if (key == 'z') {
		m[Map[icnt][jcnt]].y += sze;
	}
	if (key == 'Z') {
		m[Map[icnt][jcnt]].y -= sze;
	}
	if (key == 'D') {
		m[Map[icnt][jcnt]].x += sze;
	}
	if(key == 'A') {
		m[Map[icnt][jcnt]].x -= sze;
	}
	if (key == 'S') {
		m[Map[icnt][jcnt]].z += sze;
	}
	if (key == 'W') {
		m[Map[icnt][jcnt]].z -= sze;
	}
	if (key == 'q') {
		if (bar) {
			bar = false;
		}
		else {
			bar = true;
		}
	}
	if (key == '1') {
		if (figura) figura = false;
		else figura = true;
	}
	glutPostRedisplay();
}

void subskey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		if (jcnt != 0) {
			jcnt--;
		}
	}
	if (key == GLUT_KEY_DOWN) {
		if (jcnt != nr - 1) {
			jcnt++;
		}
	}
	if (key == GLUT_KEY_LEFT) {
		if (icnt != 0) {
			icnt--;
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		if (icnt != nr - 1) {
			icnt++;
		}
	}
	glutPostRedisplay();
}

void subreshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	wsubwindowsize = w;
	hsubwindowsize = h;
	//glOrtho(0, w, h, 0, 0, w);
	if (h == 0) h = 1;
	gluPerspective(100, w / h, 0.1, nr * sze * 2);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);


	subinit();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(wsubwindowsize, hsubwindowsize);
	glutCreateWindow("3D Game");


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//func
	glutDisplayFunc(subdisplay);
	//glutIdleFunc(subdisplay);
	glutReshapeFunc(subreshape);
	glutKeyboardFunc(subnkey);
	glutSpecialFunc(subskey);

	//Light(-1000, 1000, -1000);
	Light(sze * nr/2, sze * nr, -sze * nr/2);
	glutMainLoop();
}
