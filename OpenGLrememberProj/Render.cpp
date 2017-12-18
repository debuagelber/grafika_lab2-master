#include "Render.h"
#include <windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "MyOGL.h"

#include "Camera.h"
#include "Light.h"
#include "Primitives.h"
#include <cmath>


bool textureMode = true;
bool lightMode = true;
bool alphamode = false;
bool print_mode = false;

double a = 0;



//расчет нормалей
void norm(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3,int i){
	double Xa, Ya, Za, Xb, Yb, Zb;
	double Nx, Ny, Nz;
	Xa = x3-x2;
	Ya =y3-y2;
	Za =z3-z2;
	Xb =x1-x2;
	Yb =y1-y2;
	Zb =z1-z2;
	Nx = (Ya*Zb-Yb*Za);
	Ny = 0-(Xa*Zb-Xb*Za);
	Nz =(Xa*Yb-Xb*Ya);
	if(i==0)
	glNormal3d(Nx,Ny,Nz);
	else
	glNormal3d(-Nx,-Ny,-Nz);
}


//Кнопка 
void button_stand(double x, double y, const unsigned char c, double x1, double y1) {

	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);


	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0,0+x,1.11+y,0,1.11+x,0+y,0,1);

	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11+y, 0.0);
	glVertex3d(1.11+x, 1.11+y, 0.0);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	

	norm(0.17+x,0.17+y,0.3,0.94+x,0.94+y,0.3, 0.94+x,0.17+y,0.3,1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+52)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.94+y, 0.3);

	glTexCoord2d((x1+52)/1024, 1-(y1+51)/1024);
	glVertex3d(0.94+x, 0.94+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+51)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glEnd();
	





	norm(0.0+x,0.0+y,0.0,0.17+x,0.17+y,0.3,0.94+x,0.17+y,0.3,1);

	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	
	norm(0.0+x,0.0+y,0.0,0.17+x,0.17+y,0.3, 0.17+x,0.94+y,0.3, 0);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 0.94+y, 0.3);
	glVertex3d(0.0+x, 1.11+y, 0.0);

	glEnd();

	

	norm(0.0+x,1.11+y,0.0,   0.17+x,0.94+y,0.3,   0.94+x,0.94+y,0.3, 0);

	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11+y, 0.0);
	glVertex3d(0.17+x, 0.94+y, 0.3);
	glVertex3d(0.94+x, 0.94+y, 0.3);
	glVertex3d(1.11+x, 1.11+y, 0);

	glEnd();

	
	norm(1.11+x,1.11+y,0.0,   0.94+x,0.94+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glBegin(GL_POLYGON);

	glVertex3d(1.11+x, 1.11+y, 0.0);
	glVertex3d(0.94+x, 0.94+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ



	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43+y, 0.0);
	glVertex3d(0.43+x, 0.43+y, -0.3);
	glVertex3d(0.69+x, 0.43+y, -0.3);
	glVertex3d(0.69+x, 0.43+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43+y, 0.0);
	glVertex3d(0.69+x, 0.43+y, -0.3);
	glVertex3d(0.69+x, 0.69+y, -0.3);
	glVertex3d(0.69+x, 0.69+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69+y, 0.0);
	glVertex3d(0.69+x, 0.69+y, -0.3);
	glVertex3d(0.43+x, 0.69+y, -0.3);
	glVertex3d(0.43+x, 0.69+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69+y, 0.0);
	glVertex3d(0.43+x, 0.69+y, -0.3);
	glVertex3d(0.43+x, 0.43+y, -0.3);
	glVertex3d(0.43+x, 0.43+y, 0.0);

	glEnd();

}

void button_f(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);



	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0,  0+x,1.11+y,0,  0.62+x,0+y,0,1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11+y, 0.0);
	glVertex3d(0.62+x, 1.11+y, 0.0);
	glVertex3d(0.62+x, 0.0+y, 0.0);

	glEnd();
	

	norm(0.17+x,0.17+y,0.3,  0.45+x,0.94+y,0.3, 0.45+x,0.17+y,0.3,  1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);


	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	
	glTexCoord2d((x1+56)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.94+y, 0.3);


	glTexCoord2d((x1+56)/1024, 1-(y1+26)/1024);
	glVertex3d(0.45+x, 0.94+y, 0.3);

	
	glTexCoord2d(x1/1024, 1-(y1+26)/1024);
	glVertex3d(0.45+x, 0.17+y, 0.3);

	glEnd();
	

	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.45+x,0.17+y,0.3, 1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glTexCoord2d(0.1, 0.1);
	glVertex3d(0.45+x, 0.17+y, 0.3);
	glVertex3d(0.62+x, 0.0+y, 0.0);

	glEnd();

	
	norm(0.0+x,0.0+y,0.0,   0.17+x,0.17+y,0.3,   0.17+x,0.94+y,0.3,  0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 0.94+y, 0.3);
	glVertex3d(0.0+x, 1.11+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11+y,0.0,   0.17+x,0.94+y,0.3,   0.45+x,0.94+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);

	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11+y, 0.0);
	glVertex3d(0.17+x, 0.94+y, 0.3);
	glVertex3d(0.45+x, 0.94+y, 0.3);
	glVertex3d(0.62+x, 1.11+y, 0);

	glEnd();

	
	norm(0.62+x,1.11+y,0.0,   0.45+x,0.94+y,0.3,   0.45+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);

	glVertex3d(0.62+x, 1.11+y, 0.0);
	glVertex3d(0.45+x, 0.94+y, 0.3);
	glVertex3d(0.45+x, 0.17+y, 0.3);
	glVertex3d(0.62+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.20+x, 0.43+y, 0.0);
	glVertex3d(0.20+x, 0.43+y, -0.3);
	glVertex3d(0.42+x, 0.43+y, -0.3);
	glVertex3d(0.42+x, 0.43+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.42+x, 0.43+y, 0.0);
	glVertex3d(0.42+x, 0.43+y, -0.3);
	glVertex3d(0.42+x, 0.69+y, -0.3);
	glVertex3d(0.42+x, 0.69+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.42+x, 0.69+y, 0.0);
	glVertex3d(0.42+x, 0.69+y, -0.3);
	glVertex3d(0.20+x, 0.69+y, -0.3);
	glVertex3d(0.20+x, 0.69+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.20+x, 0.69+y, 0.0);
	glVertex3d(0.20+x, 0.69+y, -0.3);
	glVertex3d(0.20+x, 0.43+y, -0.3);
	glVertex3d(0.20+x, 0.43+y, 0.0);

	glEnd();

}


void button_up_down(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0,  0+x,1.11+y,0,  0.62+x,0+y,0,1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	
	
	glVertex3d(0.0+x, 1.11+y, 0.0);

	
	glVertex3d(0.5+x, 1.11+y, 0.0);

	
	glVertex3d(0.5+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.1+x,0.17+y,0.3,  0.4+x,0.94+y,0.3, 0.4+x,0.17+y,0.3,  1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.1+x, 0.17+y, 0.3);

	glTexCoord2d((x1+53)/1024, 1-y1/1024);
	glVertex3d(0.1+x, 0.94+y, 0.3);

	glTexCoord2d((x1+53)/1024, 1-(y1+20)/1024);
	glVertex3d(0.4+x, 0.94+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+20)/1024);  
	glVertex3d(0.4+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.1+x,0.17+y,0.3,  0.4+x,0.17+y,0.3, 1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.1+x, 0.17+y, 0.3);
	glTexCoord2d(0.1, 0.1);
	glVertex3d(0.4+x, 0.17+y, 0.3);


	glVertex3d(0.5+x, 0.0+y, 0.0);

	glEnd();

	
	norm(0.0+x,0.0+y,0.0,   0.1+x,0.17+y,0.3,   0.1+x,0.94+y,0.3,  0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.1+x, 0.17+y, 0.3);
	glVertex3d(0.1+x, 0.94+y, 0.3);
	glVertex3d(0.0+x, 1.11+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11+y,0.0,   0.1+x,0.94+y,0.3,   0.4+x,0.94+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11+y, 0.0);
	glVertex3d(0.1+x, 0.94+y, 0.3);
	glVertex3d(0.4+x, 0.94+y, 0.3);
	glVertex3d(0.5+x, 1.11+y, 0);


	glEnd();

	
	norm(0.5+x,1.11+y,0.0,   0.4+x,0.94+y,0.3,   0.4+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(0.5+x, 1.11+y, 0.0);
	glVertex3d(0.4+x, 0.94+y, 0.3);
	glVertex3d(0.4+x, 0.17+y, 0.3);
	glVertex3d(0.5+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.14+x, 0.43+y, 0.0);
	glVertex3d(0.14+x, 0.43+y, -0.3);
	glVertex3d(0.35+x, 0.43+y, -0.3);
	glVertex3d(0.35+x, 0.43+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.35+x, 0.43+y, 0.0);
	glVertex3d(0.35+x, 0.43+y, -0.3);
	glVertex3d(0.35+x, 0.69+y, -0.3);
	glVertex3d(0.35+x, 0.69+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.35+x, 0.69+y, 0.0);
	glVertex3d(0.35+x, 0.69+y, -0.3);
	glVertex3d(0.14+x, 0.69+y, -0.3);
	glVertex3d(0.14+x, 0.69+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.14+x, 0.69+y, 0.0);
	glVertex3d(0.14+x, 0.69+y, -0.3);
	glVertex3d(0.14+x, 0.43+y, -0.3);
	glVertex3d(0.14+x, 0.43+y, 0.0);

	glEnd();

}

void button_tab_delete(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0.0,  0+x,1.11*1.6+y,  0,1.11+x,0+y,0.0, 1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11*1.6+y, 0.0);
	glVertex3d(1.11+x, 1.11*1.6+y, 0.0);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.17+x,0.17+y,0.3,  0.94+x,1.6+y,0.3, 0.94+x,0.17+y,0.3,1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+86)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 1.6+y, 0.3);

	glTexCoord2d((x1+86)/1024, 1-(y1+50)/1024);
	glVertex3d(0.94+x, 1.6+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+50)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);


	glEnd();

	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.17+x,1.6+y,0.3, 0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 1.6+y, 0.3);
	glVertex3d(0.0+x, 1.11*1.6+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11*1.6+y,0.0,   0.17+x,1.6+y,0.3,   0.94+x,1.6+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11*1.6+y, 0.0);
	glVertex3d(0.17+x, 1.6+y, 0.3);
	glVertex3d(0.94+x, 1.6+y, 0.3);
	glVertex3d(1.11+x, 1.11*1.6+y, 0);


	glEnd();

	
	norm(1.11+x,1.11*1.6+y,0.0,   0.94+x,1.6+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(1.11+x, 1.11*1.6+y, 0.0);
	glVertex3d(0.94+x, 1.6+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43*1.6+y, 0.0);
	glVertex3d(0.43+x, 0.43*1.6+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.6+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.6+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43*1.6+y, 0.0);
	glVertex3d(0.69+x, 0.43*1.6+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.6+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.6+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69*1.6+y, 0.0);
	glVertex3d(0.69+x, 0.69*1.6+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.6+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.6+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69*1.6+y, 0.0);
	glVertex3d(0.43+x, 0.69*1.6+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.6+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.6+y, 0.0);

	glEnd();

}

void button_caps_enter(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0.0,  0+x,1.11*1.8+y,  0,1.11+x,0+y,0.0, 1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11*1.8+y, 0.0);
	glVertex3d(1.11+x, 1.11*1.8+y, 0.0);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.17+x,0.17+y,0.3,  0.94+x,1.8+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+105)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 1.8+y, 0.3);

	glTexCoord2d((x1+105)/1024, 1-(y1+50)/1024);
	glVertex3d(0.94+x, 1.8+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+50)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);


	glEnd();

	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.17+x,1.8+y,0.3, 0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 1.8+y, 0.3);
	glVertex3d(0.0+x, 1.11*1.8+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11*1.8+y,0.0,   0.17+x,1.8+y,0.3,   0.94+x,1.8+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11*1.8+y, 0.0);
	glVertex3d(0.17+x, 1.8+y, 0.3);
	glVertex3d(0.94+x, 1.8+y, 0.3);
	glVertex3d(1.11+x, 1.11*1.8+y, 0);


	glEnd();

	
	norm(1.11+x,1.11*1.8+y,0.0,   0.94+x,1.8+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(1.11+x, 1.11*1.8+y, 0.0);
	glVertex3d(0.94+x, 1.8+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43*1.8+y, 0.0);
	glVertex3d(0.43+x, 0.43*1.8+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.8+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.8+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43*1.8+y, 0.0);
	glVertex3d(0.69+x, 0.43*1.8+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.8+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.8+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69*1.8+y, 0.0);
	glVertex3d(0.69+x, 0.69*1.8+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.8+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.8+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69*1.8+y, 0.0);
	glVertex3d(0.43+x, 0.69*1.8+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.8+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.8+y, 0.0);

	glEnd();

}

void button_shift(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0.0,  0+x,1.11*2.3+y,  0,1.11+x,0+y,0.0, 1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11*2.3+y, 0.0);
	glVertex3d(1.11+x, 1.11*2.3+y, 0.0);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.17+x,0.17+y,0.3,  0.94+x,2.383+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+141)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 2.383+y, 0.3);

	glTexCoord2d((x1+141)/1024, 1-(y1+51)/1024);
	glVertex3d(0.94+x, 2.383+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+51)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);


	glEnd();

	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.17+x,2.383+y,0.3, 0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 2.383+y, 0.3);
	glVertex3d(0.0+x, 1.11*2.3+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11*2.3+y,0.0,   0.17+x,2.383+y,0.3,   0.94+x,2.383+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 1.11*2.3+y, 0.0);
	glVertex3d(0.17+x, 2.3+y, 0.3);
	glVertex3d(0.94+x, 2.3+y, 0.3);
	glVertex3d(1.11+x, 1.11*2.3+y, 0);


	glEnd();

	
	norm(1.11+x,1.11*2.3+y,0.0,   0.94+x,2.383+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(1.11+x, 1.11*2.3+y, 0.0);
	glVertex3d(0.94+x, 2.383+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43*2.3+y, 0.0);
	glVertex3d(0.43+x, 0.43*2.3+y, -0.3);
	glVertex3d(0.69+x, 0.43*2.3+y, -0.3);
	glVertex3d(0.69+x, 0.43*2.3+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43*2.3+y, 0.0);
	glVertex3d(0.69+x, 0.43*2.3+y, -0.3);
	glVertex3d(0.69+x, 0.69*2.3+y, -0.3);
	glVertex3d(0.69+x, 0.69*2.3+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69*2.3+y, 0.0);
	glVertex3d(0.69+x, 0.69*2.3+y, -0.3);
	glVertex3d(0.43+x, 0.69*2.3+y, -0.3);
	glVertex3d(0.43+x, 0.69*2.3+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69*2.3+y, 0.0);
	glVertex3d(0.43+x, 0.69*2.3+y, -0.3);
	glVertex3d(0.43+x, 0.43*2.3+y, -0.3);
	glVertex3d(0.43+x, 0.43*2.3+y, 0.0);

	glEnd();

}

void button_space(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0.0,  0+x,1.11*8.7+y,  0,1.11+x,0+y,0.0, 1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11*8.7+y, 0.0);
	glVertex3d(1.11+x, 1.11*8.7+y, 0.0);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.17+x,0.17+y,0.3,  0.94+x,9.487+y,0.3, 0.94+x,0.17+y,0.3,1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+333)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 9.487+y, 0.3);

	glTexCoord2d((x1+333)/1024, 1-(y1+61)/1024);
	glVertex3d(0.94+x, 9.487+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+61)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);


	glEnd();

	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.17+x,9.487+y,0.3, 0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 9.487+y, 0.3);
	glVertex3d(0.0+x, 1.11*8.7+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11*8.7+y,0.0,   0.17+x,9.487+y,0.3,   0.94+x,9.487+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 1.11*8.7+y, 0.0);
	glVertex3d(0.17+x, 9.487+y, 0.3);
	glVertex3d(0.94+x, 9.487+y, 0.3);
	glVertex3d(1.11+x, 1.11*8.7+y, 0);


	glEnd();

	
	norm(1.11+x,1.11*8.7+y,0.0,   0.94+x,9.487+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	
	glVertex3d(1.11+x, 1.11*8.7+y, 0.0);
	glVertex3d(0.94+x, 9.487+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43*8.7+y, 0.0);
	glVertex3d(0.43+x, 0.43*8.7+y, -0.3);
	glVertex3d(0.69+x, 0.43*8.7+y, -0.3);
	glVertex3d(0.69+x, 0.43*8.7+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43*8.7+y, 0.0);
	glVertex3d(0.69+x, 0.43*8.7+y, -0.3);
	glVertex3d(0.69+x, 0.69*8.7+y, -0.3);
	glVertex3d(0.69+x, 0.69*8.7+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69*8.7+y, 0.0);
	glVertex3d(0.69+x, 0.69*8.7+y, -0.3);
	glVertex3d(0.43+x, 0.69*8.7+y, -0.3);
	glVertex3d(0.43+x, 0.69*8.7+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69*8.7+y, 0.0);
	glVertex3d(0.43+x, 0.69*8.7+y, -0.3);
	glVertex3d(0.43+x, 0.43*8.7+y, -0.3);
	glVertex3d(0.43+x, 0.43*8.7+y, 0.0);

	glEnd();

}

void button_ctrl_alt(double x, double y, const char c, double x1, double y1) {
	if(OpenGL::isKeyPressed(c))
		glTranslated(0, 0, -0.3);
	////////////////////////////////////////НЕПОСРЕДСТВЕННО КНОПКА
	norm(0+x,0+y,0.0,  0+x,1.11*1.27+y,  0,1.11+x,0+y,0.0, 1);

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.0+x, 1.11*1.27+y, 0.0);
	glVertex3d(1.11+x, 1.11*1.27+y, 0.0); 
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();
	
	norm(0.17+x,0.17+y,0.3,  0.94+x,1.24+y,0.3, 0.94+x,0.17+y,0.3,1);

	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glTexCoord2d(x1/1024, 1-y1/1024);
	glVertex3d(0.17+x, 0.17+y, 0.3);

	glTexCoord2d((x1+69)/1024, 1-y1/1024);
	glVertex3d(0.17+x, 1.24+y, 0.3);

	glTexCoord2d((x1+69)/1024, 1-(y1+61)/1024);
	glVertex3d(0.94+x, 1.24+y, 0.3);

	glTexCoord2d(x1/1024, 1-(y1+61)/1024);
	glVertex3d(0.94+x, 0.17+y, 0.3);


	glEnd();
	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.94+x,0.17+y,0.3,1);

	glColor4d(0.0, 1.0, 0.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);

	glTexCoord2d(0.1, 0.1);
	glVertex3d(1.11+x, 0.0+y, 0.0);


	glEnd();

	
	norm(0.0+x,0.0+y,0.0,  0.17+x,0.17+y,0.3,  0.17+x,1.24+y,0.3, 0);

	glColor4d(0.0, 0.0, 1.0, 1);


	glBegin(GL_POLYGON);
	
	glVertex3d(0.0+x, 0.0+y, 0.0);
	glVertex3d(0.17+x, 0.17+y, 0.3);
	glVertex3d(0.17+x, 1.24+y, 0.3);
	glVertex3d(0.0+x, 1.11*1.27+y, 0.0);

	glEnd();

	
	norm(0.0+x,1.11*1.27+y,0.0,   0.17+x,1.24+y,0.3,   0.94+x,1.24+y,0.3, 0);

	glColor4d(0.4, 0.1, 0.2, 1);
	glBegin(GL_POLYGON);

	glVertex3d(0.0+x, 1.11*1.27+y, 0.0);
	glVertex3d(0.17+x, 1.24+y, 0.3);
	glVertex3d(0.94+x, 1.24+y, 0.3);
	glVertex3d(1.11+x, 1.11*1.27+y, 0);


	glEnd();

	
	norm(1.11+x,1.11*1.27+y,0.0,   0.94+x,1.24+y,0.3,   0.94+x,0.17+y,0.3, 0);

	glColor4d(0.5, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);

	glVertex3d(1.11+x, 1.11*1.27+y, 0.0);
	glVertex3d(0.94+x, 1.24+y, 0.3);
	glVertex3d(0.94+x, 0.17+y, 0.3);
	glVertex3d(1.11+x, 0.0+y, 0.0);

	glEnd();

	///////////////////////////////////////////////////НОЖКА КНОПКИ

	glColor4d(0.4, 0.0, 1.0, 1);
	

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.43*1.27+y, 0.0);
	glVertex3d(0.43+x, 0.43*1.27+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.27+y, -0.3);
	glVertex3d(0.69+x, 0.43*1.27+y, 0.0);

	glEnd();
	


	glColor4d(1.0, 0.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.43*1.27+y, 0.0);
	glVertex3d(0.69+x, 0.43*1.27+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.27+y, -0.3);
	glVertex3d(0.69+x, 0.69*1.27+y, 0.0);


	glEnd();
	
	
	glColor4d(0.0, 1.0, 0.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.69+x, 0.69*1.27+y, 0.0);
	glVertex3d(0.69+x, 0.69*1.27+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.27+y, -0.3);
	glVertex3d(0.43+x, 0.69*1.27+y, 0.0);

	glEnd();

	glColor4d(0.0, 0.0, 1.0, 1);

	glBegin(GL_POLYGON);

	glVertex3d(0.43+x, 0.69*1.27+y, 0.0);
	glVertex3d(0.43+x, 0.69*1.27+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.27+y, -0.3);
	glVertex3d(0.43+x, 0.43*1.27+y, 0.0);

	glEnd();

}

void drawing()
{
	glNormal3d(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3d(-0.74-0.5, -0.1, -0.3);
	glVertex3d(6.69, -0.1, -0.3);
	glVertex3d(6.69, 17.13, -0.3);
	glVertex3d(-0.74-0.5, 17.13, -0.3);
	glEnd();

}
//класс для настройки камеры
class CustomCamera : public Camera
{
public:
	//дистанция камеры
	double camDist;
	//углы поворота камеры
	double fi1, fi2;

	
	//значния масеры по умолчанию
	CustomCamera()
	{
		camDist = 15;
		fi1 = 1;
		fi2 = 1;
	}

	
	//считает позицию камеры, исходя из углов поворота, вызывается движком
	void SetUpCamera()
	{
		//отвечает за поворот камеры мышкой
		lookPoint.setCoords(0, 0, 0);

		pos.setCoords(camDist*cos(fi2)*cos(fi1),
			camDist*cos(fi2)*sin(fi1),
			camDist*sin(fi2));

		if (cos(fi2) <= 0)
			normal.setCoords(0, 0, -1);
		else
			normal.setCoords(0, 0, 1);

		LookAt();
	}

	void CustomCamera::LookAt()
	{
		//функция настройки камеры
		gluLookAt(pos.X(), pos.Y(), pos.Z(), lookPoint.X(), lookPoint.Y(), lookPoint.Z(), normal.X(), normal.Y(), normal.Z());
	}



}  camera;   //создаем объект камеры


//Класс для настройки света
class CustomLight : public Light
{
public:
	CustomLight()
	{
		//начальная позиция света
		pos = Vector3(1, 1, 3);
	}

	
	//рисует сферу и линии под источником света, вызывается движком
	void  DrawLightGhismo()
	{
		glDisable(GL_LIGHTING);

		
		glColor3d(0.9, 0.8, 0);
		Sphere s;
		s.pos = pos;
		s.scale = s.scale*0.08;
		s.Show();
		
		if (OpenGL::isKeyPressed('G') && !print_mode)
		{
			glColor3d(0, 0, 0);
			//линия от источника света до окружности
			glBegin(GL_LINES);
			glVertex3d(pos.X(), pos.Y(), pos.Z());
			glVertex3d(pos.X(), pos.Y(), 0);
			glEnd();

			//рисуем окруность
			Circle c;
			c.pos.setCoords(pos.X(), pos.Y(), 0);
			c.scale = c.scale*1.5;
			c.Show();
		}

	}

	void SetUpLight()
	{
		GLfloat amb[] = { 0.2, 0.2, 0.2, 0 };
		GLfloat dif[] = { 1.0, 1.0, 1.0, 0 };
		GLfloat spec[] = { .7, .7, .7, 0 };
		GLfloat position[] = { pos.X(), pos.Y(), pos.Z(), 1. };

		// параметры источника света
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		// характеристики излучаемого света
		// фоновое освещение (рассеянный свет)
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		// диффузная составляющая света
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		// зеркально отражаемая составляющая света
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

		glEnable(GL_LIGHT0);
	}


} light;  //создаем источник света




//старые координаты мыши
int mouseX = 0, mouseY = 0;

void mouseEvent(OpenGL *ogl, int mX, int mY)
{
	int dx = mouseX - mX;
	int dy = mouseY - mY;
	mouseX = mX;
	mouseY = mY;

	//меняем углы камеры при нажатой левой кнопке мыши
	if (OpenGL::isKeyPressed(VK_RBUTTON))
	{
		camera.fi1 += 0.01*dx;
		camera.fi2 += -0.01*dy;
	}

	
	//двигаем свет по плоскости, в точку где мышь
	if (OpenGL::isKeyPressed('G') && !OpenGL::isKeyPressed(VK_LBUTTON) && !print_mode)
	{
		LPPOINT POINT = new tagPOINT();
		GetCursorPos(POINT);
		ScreenToClient(ogl->getHwnd(), POINT);
		POINT->y = ogl->getHeight() - POINT->y;

		Ray r = camera.getLookRay(POINT->x, POINT->y);

		double z = light.pos.Z();

		double k = 0, x = 0, y = 0;
		if (r.direction.Z() == 0)
			k = 0;
		else
			k = (z - r.origin.Z()) / r.direction.Z();

		x = k*r.direction.X() + r.origin.X();
		y = k*r.direction.Y() + r.origin.Y();

		light.pos = Vector3(x, y, z);
	}

	if (OpenGL::isKeyPressed('G') && OpenGL::isKeyPressed(VK_LBUTTON) && !print_mode)
	{
		light.pos = light.pos + Vector3(0, 0, 0.02*dy);
	}

	
}

void mouseWheelEvent(OpenGL *ogl, int delta)
{

	if (delta < 0 && camera.camDist <= 1)
		return;
	if (delta > 0 && camera.camDist >= 100)
		return;

	camera.camDist += 0.01*delta;

}

void keyDownEvent(OpenGL *ogl, int key)
{
	if (key == 'L' && !print_mode)
	{
		lightMode = !lightMode;
	}

	if (key == 'T' && !print_mode)
	{
		textureMode = !textureMode;
	}

	if (key == 'R' && !print_mode)
	{
		camera.fi1 = 1;
		camera.fi2 = 1;
		camera.camDist = 15;

		light.pos = Vector3(1, 1, 3);
	}

	if (key == 'F' && !print_mode)
	{
		light.pos = camera.pos;
	}

	if (key == 'A' && !print_mode)
	{
		alphamode = !alphamode;
	}

	if (key == VK_INSERT)
	{
		print_mode = !print_mode;
	}
}

void keyUpEvent(OpenGL *ogl, int key)
{
	
}




//выполняется перед первым рендером
void initRender(OpenGL *ogl)
{
	//настройка текстур

	//4 байта на хранение пикселя
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//настройка режима наложения текстур
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//включаем текстуры
	glEnable(GL_TEXTURE_2D);
	

	//массив трехбайтных элементов  (R G B)
	RGBTRIPLE *texarray;

	//массив символов, (высота*ширина*4      4, потомучто   выше, мы указали использовать по 4 байта на пиксель текстуры - R G B A)
	char *texCharArray;
	int texW, texH;
	OpenGL::LoadBMP("texture_prism_norm.bmp", &texW, &texH, &texarray);
	OpenGL::RGBtoChar(texarray, texW, texH, &texCharArray);

	
	GLuint texId;
	//генерируем ИД для текстуры
	glGenTextures(1, &texId);
	//биндим айдишник, все что будет происходить с текстурой, будте происходить по этому ИД
	glBindTexture(GL_TEXTURE_2D, texId);

	//загружаем текстуру в видеопямять, в оперативке нам больше  она не нужна
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texCharArray);

	//отчистка памяти
	free(texCharArray);
	free(texarray);

	//наводим шмон
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//камеру и свет привязываем к "движку"
	ogl->mainCamera = &camera;
	ogl->mainLight = &light;

	// нормализация нормалей : их длины будет равна 1
	glEnable(GL_NORMALIZE);

	// устранение ступенчатости для линий
	glEnable(GL_LINE_SMOOTH); 



	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}



bool flag = false;
void Render(OpenGL *ogl)
{       	
	
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	if (textureMode)
		glEnable(GL_TEXTURE_2D);

	if (lightMode)
		glEnable(GL_LIGHTING);


	//альфаналожение
	if (alphamode)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}


	//настройка материала
	GLfloat amb[] = { 0.2, 0.2, 0.1, 1. };
	GLfloat dif[] = { 0.4, 0.65, 0.5, 1. };
	GLfloat spec[] = { 0.9, 0.8, 0.3, 1. };
	GLfloat sh = 0.1f * 256;


	//фоновая
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	//дифузная
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	//зеркальная
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);\
	//размер блика
	glMaterialf(GL_FRONT, GL_SHININESS, sh);

	glShadeModel(GL_SMOOTH);
	

	glTranslated(0, -8, 0);

	glPushMatrix();
    button_f(-1.17/1.6, 0.0, VK_ESCAPE, 11, 11);
	glPopMatrix();
	
	glPushMatrix();
    button_f(-1.17/1.6, 1.5, VK_F1, 84, 11);
	glPopMatrix();
	
	glPushMatrix();
    button_f(-1.17/1.6, 2.67, VK_F2, 157, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 1, VK_F3, 230, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 2, VK_F4, 302, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 3, VK_F5, 375, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 4, VK_F6, 448, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 5, VK_F7, 520, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 6, VK_F8, 593, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 7, VK_F9, 666, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 8, VK_F10, 738, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 9, VK_F11, 811, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 10, VK_F12, 884, 11);
	glPopMatrix();

	glPushMatrix();
    button_f(-1.17/1.6, 2.67+1.17 * 11, VK_DELETE, 957, 11);
	glPopMatrix();
	

	glPushMatrix();
    button_stand(0.0, 0.0, VK_OEM_3, 10, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 1, '1', 80, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 2, '2', 151, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 3, '3', 221, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 4, '4', 291, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 5, '5', 361, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 6, '6', 432, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 7, '7', 502, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 8, '8', 572, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 9, '9', 642, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 10, '0', 712, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 11, VK_OEM_MINUS, 783, 54);
	glPopMatrix();

	glPushMatrix();
	button_stand(0.0, 1.17 * 12, VK_OEM_PLUS, 853, 54);
	glPopMatrix();

	glPushMatrix();
	button_tab_delete(0.0, 1.17*13, VK_BACK, 924, 55);
	glPopMatrix();

	glPushMatrix();
	button_tab_delete(1.17, 0.0, VK_TAB, 11, 123);
	glPopMatrix();
	
	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 0, 'Q', 116, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 1, 'W', 186, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 2, 'E', 256, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 3, 'R', 326, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 4, 'T', 397, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 5, 'Y', 467, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 6, 'U', 537, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 7, 'I', 607, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 8, 'O', 677, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 9, 'P', 747, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 10, VK_OEM_4, 818, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 11, VK_OEM_6, 888, 122);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17, 1.836 + 1.17 * 12, VK_OEM_5, 958, 122);
	glPopMatrix();

	glPushMatrix();
	button_caps_enter(1.17*2, 0.0, VK_CAPITAL, 11, 191);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 0, 'A', 133, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 1, 'S', 203, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 2, 'D', 274, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 3, 'F', 344, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 4, 'G', 414, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 5, 'H', 484, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 6, 'J', 554, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 7, 'K', 625, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 8, 'L', 695, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 9, VK_OEM_1, 765, 190);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*2, 2.1 + 1.17 * 10, VK_OEM_7, 835, 190);
	glPopMatrix();

	glPushMatrix();
	button_caps_enter(1.17*2, 2.1 + 1.17 * 11, VK_RETURN, 907, 191);
	glPopMatrix();

	glPushMatrix();
	button_shift(1.17*3, 0.0, VK_SHIFT, 10, 260);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 0, 'Z', 168, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 1, 'X', 238, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 2, 'C', 309, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 3, 'V', 379, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 4, 'B', 449, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 5, 'N', 519, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 6, 'M', 590, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 7, 188, 660, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 8, 190, 730, 259);
	glPopMatrix();

	glPushMatrix();
	button_stand(1.17*3, 2.653 + 1.17 * 9, 191, 800, 259);
	glPopMatrix();

	glPushMatrix();
	button_shift(1.17*3, 2.653 + 1.17 * 10 + 0.05, VK_SHIFT, 870, 260);
	glPopMatrix();

	glPushMatrix();
	button_ctrl_alt(1.17*4, 0.0, VK_CONTROL, 221, 328);
	glPopMatrix();

	glPushMatrix();
	button_ctrl_alt(1.17*4, 1.47, VK_MENU, 220, 405);
	glPopMatrix();

	glPushMatrix();
	button_space(1.17*4, 1.47*2, VK_SPACE, 309, 327);
	glPopMatrix();
	
	glPushMatrix();
	button_f(1.17*4 + 0.49, 0.82 + 1.47*2 + 9.76, VK_LEFT, 819, 362);
	glPopMatrix();

	glPushMatrix();
	button_up_down(1.17*4, 0.82 + 1.47*2 + 9.76 + 1.17, VK_UP, 889, 328);
	glPopMatrix();

	glPushMatrix();
	button_up_down(1.17*4 + 0.61, 0.82 + 1.47*2 + 9.76 + 1.17, VK_DOWN, 889, 368);
	glPopMatrix();

	glPushMatrix();
	button_f(1.17*4 + 0.49, 0.82 + 1.47*2 + 9.76 + 1.17 * 2, VK_RIGHT, 959, 362);
	glPopMatrix();
	
	drawing();

	//текст сообщения вверху слева
	char c[250];  //максимальная длина сообщения
	sprintf_s(c, "Кнопкой INSERT производится переключение между режимом моделирования печати и режимом управления светом/отключения текстур\nУправление светом аналогичное управлению во второй лабораторной");
	ogl->message = std::string(c);




}   //конец тела функции

