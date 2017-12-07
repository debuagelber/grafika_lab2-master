#include "Render.h"

#include <windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "MyOGL.h"

#include "Camera.h"
#include "Light.h"
#include "Primitives.h"
#include "RandomTrash.h"



bool textureMode = true;
bool lightMode = true;

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
		
		if (OpenGL::isKeyPressed('G'))
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
		GLfloat dif[] = { 0.5, 0.5, 0.5, 0 };
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
	if (OpenGL::isKeyPressed('G') && !OpenGL::isKeyPressed(VK_LBUTTON))
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

	if (OpenGL::isKeyPressed('G') && OpenGL::isKeyPressed(VK_LBUTTON))
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
	if (key == 'L')
	{
		lightMode = !lightMode;
	}

	if (key == 'T')
	{
		textureMode = !textureMode;
	}

	if (key == 'R')
	{
		camera.fi1 = 1;
		camera.fi2 = 1;
		camera.camDist = 15;

		light.pos = Vector3(1, 1, 3);
	}

	if (key == 'F')
	{
		light.pos = camera.pos;
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
	OpenGL::LoadBMP("test2.bmp", &texW, &texH, &texarray);
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


	//   задать параметры освещения
	//  параметр GL_LIGHT_MODEL_TWO_SIDE - 
	//                0 -  лицевые и изнаночные рисуются одинаково(по умолчанию), 
	//                1 - лицевые и изнаночные обрабатываются разными режимами       
	//                соответственно лицевым и изнаночным свойствам материалов.    
	//  параметр GL_LIGHT_MODEL_AMBIENT - задать фоновое освещение, 
	//                не зависящее от сточников
	// по умолчанию (0.2, 0.2, 0.2, 1.0)

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}





void Render(OpenGL *ogl)
{       	
	
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	if (textureMode)
		glEnable(GL_TEXTURE_2D);

	if (lightMode)
		glEnable(GL_LIGHTING);


	////альфаналожение
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//настройка материала
	GLfloat amb[] = { 0.2, 0.2, 0.1, 0.7 };
	GLfloat dif[] = { 0.4, 0.6, 0.8, 1 };
	GLfloat spec[] = { 0.9, 0.8, 0.3, 0.7 };
	GLfloat sh = 0.1f * 256;


	//фоновая
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	//дифузная
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	//зеркальная
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	//размер блика
	glMaterialf(GL_FRONT, GL_SHININESS, sh);

    //чтоб было красиво, без квадратиков (сглаживание освещения)
	glShadeModel(GL_SMOOTH);
	//===================================
	//Прогать тут  
	//Начальные данные
	ThreePoints MyPoints(-7, 6, -3, -1, -8, -6), MyPoints2(-1, 4.8, 3, 6, 5, 3.6);
	ThreePoints tMyPoints((double)101 / 512, (double)396 / 512, (double)188 / 512, (double)271 / 512, (double)82 / 512, (double)143 / 512), tMyPoints2((double)228 / 512, (double)371 / 512, (double)306 / 512, (double)398 / 512, (double)352 / 512, (double)346 / 512);

	double Cx, Cy, r, Cx2, Cy2, r2;
	double tCx, tCy, tr, tCx2, tCy2, tr2;
	std::tie(Cx, Cy, r) = getCircle(MyPoints);
	std::tie(Cx2, Cy2, r2) = getCircle(MyPoints2);
	std::tie(tCx, tCy, tr) = getCircle(tMyPoints);
	std::tie(tCx2, tCy2, tr2) = getCircle(tMyPoints2);
	double angle = Angles::getAngle(MyPoints.X1, MyPoints.Y1, MyPoints.X3, MyPoints.Y3, Cx, Cy), angle2 = Angles::getAngle(MyPoints2.X1, MyPoints2.Y1, MyPoints2.X3, MyPoints2.Y3, Cx2, Cy2) + 2;
	double start = Angles::getStartAngle(MyPoints.X1, MyPoints.Y1, Cx, Cy, r), start2 = -1 * Angles::getStartAngle(MyPoints2.X1, MyPoints2.Y1, Cx2, Cy2, r2) - 1;
	double A[] = {-7, 6, 0}, A1[] = {-7, 6, 3}, B[] = {-3, -1, 0}, B1[] = {-3, -1, 3}, C[] = {-8, -6, 0}, C1[] = {-8, -6, 3}, D[] = {8, -2, 0}, D1[] = {8, -2, 3}, E[] = {8, 3, 0}, E1[] = {8, 3, 3}, F[] = {5, 3.6, 0}, F1[] = {5, 3.6, 3}, G[] = {3, 6, 0}, G1[] = {3, 6, 3}, H[] = {-1, 4.8, 0}, H1[] = {-1, 4.8, 3};
	double tA[] = { (double)101/512, (double)396 / 512 }, tB[] = { (double)188 / 512, (double)271 / 512 }, tC[] = { (double)82 / 512, (double)143 / 512 }, tD[] = { (double)417 / 512, (double)228 / 512 }, tE[] = { (double)417 / 512, (double)333 / 512 }, tF[] = { (double)352 / 512, (double)346 / 512 }, tG[] = { (double)306 / 512, (double)398 / 512 }, tH[] = { (double)228 / 512, (double)371 / 512 };
	double tN1[] = { (double)88 / 512, (double)109 / 512 }, tN2[] = { (double)425 / 512, (double)194 / 512 }, tR1[] = { (double)452 / 512, (double)228 / 512 }, tR2[] = { (double)452 / 512, (double)333 / 512 }, tU1[] = { (double)97 / 512, (double)75 / 512 }, tU2[] = { (double)433 / 512, (double)160 / 512 }, tL1[] = { (double)453 / 512, (double)429 / 512 }, tL2[] = { (double)453 / 512, (double)134 / 512 }, tL3[] = { (double)487 / 512,(double)134 / 512 }, tL4[] = { (double)487 / 512, (double)429 / 512 };
	double tT1[] = { (double)179 / 512, (double)131 / 512 }, tT2[] = { (double)189 / 512, (double)98 / 512 }, tT3[] = { (double)310 / 512, (double)163 / 512 }, tT4[] = { (double)320 / 512, (double)131 / 512 };

	double nX = 0, nY = 0, nZ = 0;
	double q[3], w[3], e[3];
	double centerPoint[] = {G[0], (D[1] + E[1]) / 2, 0}, centerPoint1[] = { G[0], (D[1] + E[1]) / 2, 3 };
	double temp = 0, temp2 = 0;
	//Боковые грани
	glColor4d(0.39, 0.39, 0.38, 0.98);

	//Правая грань
	glBegin(GL_QUADS);
	std::tie(nX, nY, nZ) = getNormal(E, D, D1);
	glNormal3d(nX, nY, nZ);
	glTexCoord2dv(tD);
	glVertex3dv(D1);
	glTexCoord2dv(tR1);
	glVertex3dv(D);
	glTexCoord2dv(tR2);
	glVertex3dv(E);
	glTexCoord2dv(tE);
	glVertex3dv(E1);
	glEnd();

	//Верхняя правая грань
	glBegin(GL_QUADS);
	std::tie(nX, nY, nZ) = getNormal(F, E, E1);
	glNormal3d(nX, nY, nZ);
	glTexCoord2dv(tN1);
	glVertex3dv(E1);
	glTexCoord2dv(tU1);
	glVertex3dv(E);
	glTexCoord2dv(tT2);
	glVertex3dv(F);
	glTexCoord2dv(tT1);
	glVertex3dv(F1);
	glEnd();

	//Верхняя средняя грань
	glBegin(GL_TRIANGLE_STRIP);
	temp = 0;
	temp2 = 0;
	std::tie(nX, nY, nZ) = getNormal(F, E, E1);
	glNormal3d(nX, nY, nZ);
	for (double i = start2 + 1; i < angle2 + start2; i++)
	{
		q[0] = Cx2 + r2 * sinf(i * 3.141592653589793 / 180);
		q[1] = Cy2 + r2 * cosf(i* 3.141592653589793 / 180);
		q[2] = 0;
		w[0] = Cx2 + r2 * sinf(i * 3.141592653589793 / 180);
		w[1] = Cy2 + r2 * cosf(i* 3.141592653589793 / 180);
		w[2] = 3;
		e[0] = Cx2 + r2 * sinf((i + 1) * 3.141592653589793 / 180);
		e[1] = Cy2 + r2 * cosf((i + 1)* 3.141592653589793 / 180);
		e[2] = 0;
		std::tie(nX, nY, nZ) = getNormal(w, q, e);
		glNormal3d(nX, nY, nZ);
		glTexCoord2d(tU1[0] + temp, tU1[1] + temp2);
		glVertex3d(Cx2 + r2 * sinf(i * 3.141592653589793 / 180), Cy2 + r2 * cosf(i* 3.141592653589793 / 180), 0);
		glTexCoord2d(tN1[0] + temp, tN1[1] + temp2);
		glVertex3d(Cx2 + r2 * sinf(i * 3.141592653589793 / 180), Cy2 + r2 * cosf(i* 3.141592653589793 / 180), 3);
		temp += (double)(131 / angle2 / 512) ;
		temp2 += (double)(32.481879 / angle2 / 512);
	}
	glEnd();


	//Верхня левая грань
	glBegin(GL_QUADS);
	std::tie(nX, nY, nZ) = getNormal(A, H, H1);
	glNormal3d(nX, nY, nZ);
	glTexCoord2dv(tT3);
	glVertex3dv(H1);
	glTexCoord2dv(tT4);
	glVertex3dv(H);
	glTexCoord2dv(tU2);
	glVertex3dv(A);
	glTexCoord2dv(tN2);
	glVertex3dv(A1);
	glEnd();

	//Нижняя грань
	glBegin(GL_QUADS);
	std::tie(nX, nY, nZ) = getNormal(D, C, C1);
	glNormal3d(nX, nY, nZ);
	glTexCoord2dv(tC);
	glVertex3dv(C1);
	glTexCoord2dv(tN1);
	glVertex3dv(C);
	glTexCoord2dv(tN2);
	glVertex3dv(D);
	glTexCoord2dv(tD);
	glVertex3dv(D1);
	glEnd();
	
	//Левая впуклая грань
	glBegin(GL_TRIANGLE_STRIP);
	for (double i = start; i < angle + start; i++)
	{
		q[0] = Cx + r * sinf(i * 3.141592653589793 / 180);
		q[1] = Cy + r * cosf(i* 3.141592653589793 / 180);
		q[2] = 0;
		w[0] = Cx + r * sinf(i * 3.141592653589793 / 180);
		w[1] = Cy + r * cosf(i * 3.141592653589793 / 180);
		w[2] = 3;
		e[0] = Cx + r * sinf((i + 1) * 3.141592653589793 / 180);
		e[1] = Cy + r * cosf((i + 1)* 3.141592653589793 / 180);
		e[2] = 0;
		std::tie(nX, nY, nZ) = getNormal(e, q, w);
		glNormal3d(nX, nY, nZ);
		if(i == start)	
			glTexCoord2dv(tL3);
		else if(i == angle + start - 1)	
			glTexCoord2dv(tL4);
		glVertex3d(Cx + r * sinf(i * 3.141592653589793 / 180), Cy + r * cosf(i* 3.141592653589793 / 180), 0);
		if (i == start)	
			glTexCoord2dv(tL2);
		else if (i == angle + start - 1)	
			glTexCoord2dv(tL1);
		glVertex3d(Cx + r * sinf(i * 3.141592653589793 / 180), Cy + r * cosf(i* 3.141592653589793 / 180), 3);
	}
	glEnd();


	
	//Основания
	glColor4d(0.6, 0.61, 0.6, 0.6);
	//Нижнее основание
	glNormal3d(0, 0, -1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2dv(tE);
	glVertex3dv(E);
	temp = 0;
	temp2 = 0;
	for (double i = start; i < angle + start; i++)
	{
		glTexCoord2d(tCx + tr * sinf(i * 3.141592653589793 / 180), tCy + tr * cosf(i* 3.141592653589793 / 180));
		glVertex3d(Cx + r * sinf(i * 3.141592653589793 / 180), Cy + r * cosf(i* 3.141592653589793 / 180), 0);
		glTexCoord2d(tE[0], tE[1] - temp2);
		glVertex3d(E[0], E[1] - temp, 0);
		temp += (double)5 / angle;
		temp2 += (double)(105/angle/512);
	}
	glTexCoord2dv(tD);
	glVertex3dv(D);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2dv(tF);
	glVertex3dv(F);
	for (double i = start2; i < angle2 + start2; i+=1)
	{
		glTexCoord2d(tCx2 + tr2 * sinf(i * 3.141592653589793 / 180), tCy2 + tr2 * cosf(i* 3.141592653589793 / 180));
		glVertex3d(Cx2 + r2 * sinf(i * 3.141592653589793 / 180), Cy2 + r2 * cosf(i* 3.141592653589793 / 180), 0);
	}
	glTexCoord2dv(tH);
	glVertex3dv(H);
	glEnd();

	//Верхнее основание
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glNormal3d(0, 0, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2dv(tE);
	glVertex3dv(E1);
	temp = 0;
	temp2 = 0;
	for (double i = start; i < angle + start; i++)
	{
		glTexCoord2d(tCx + tr * sinf(i * 3.141592653589793 / 180), tCy + tr * cosf(i* 3.141592653589793 / 180));
		glVertex3d(Cx + r * sinf(i * 3.141592653589793 / 180), Cy + r * cosf(i* 3.141592653589793 / 180), 3);
		glTexCoord2d(tE[0], tE[1] - temp2);
		glVertex3d(E1[0], E1[1] - temp, 3);
		temp += 5 / angle;
		temp2 += (double)(105 / angle / 512);
	}
	glTexCoord2dv(tD);
	glVertex3dv(D1);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2dv(tF);
	glVertex3dv(F1);
	for (double i = start2; i < angle2 + start2; i+=1)
	{
		glTexCoord2d(tCx2 + tr2 * sinf(i * 3.141592653589793 / 180), tCy2 + tr2 * cosf(i* 3.141592653589793 / 180));
		glVertex3d(Cx2 + r2 * sinf(i * 3.141592653589793 / 180), Cy2 + r2 * cosf(i* 3.141592653589793 / 180), 3);
	}
	glTexCoord2dv(tH);
	glVertex3dv(H1);
	glEnd();
	/*glDisable(GL_BLEND);*/
	
	//Конец вброса


	////Начало рисования квадратика станкина
	//double A[2] = { -4, -4 };
	//double B[2] = { 4, -4 };
	//double C[2] = { 4, 4 };
	//double D[2] = { -4, 4 };

	
	
	//glBegin(GL_QUADS);

	//glNormal3d(0, 0, 1);
	//glTexCoord2d(0, 0);
	//glVertex2dv(A);
	//glTexCoord2d(1, 0);
	//glVertex2dv(B);
	//glTexCoord2d(1, 1);
	//glVertex2dv(C);
	//glTexCoord2d(0, 1);
	//glVertex2dv(D);

	//glEnd();
	////конец рисования квадратика станкина
    
	
	//текст сообщения вверху слева, если надоест - закоментировать, или заменить =)
	char c[250];  //максимальная длина сообщения
	sprintf_s(c, "(T)Текстуры - %d\n(L)Свет - %d\n\nУправление светом:\n"
		"G - перемещение в горизонтальной плоскости,\nG+ЛКМ+перемещение по вертикальной линии\n"
		"R - установить камеру и свет в начальное положение\n"
		"F - переместить свет в точку камеры", textureMode, lightMode);
	ogl->message = std::string(c);




}   //конец тела функции

