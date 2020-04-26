/* 
	Programa para ilustrar os elementos mais basicos do OpenGL e Glut.
	Apresenta os principais recursos do sistema de Janelas GLUT
	Autor: Cesar Tadeu Pozzer
	UFSM - 2020
	pozzer@inf.ufsm.br
	pozzer3@gmail.com
	Referencias GLUT: 
	http://www.opengl.org/documentation/specs/glut/
	http://www.opengl.org/documentation/specs/glut/spec3/node1.html

	Código formatado, métodos convertidos para Pascal Case (para manter a formatação nas classes mais abstratas),  traduzido para inglês e convertido para classe por: Lorenzo Schwertner Kaufmann (23/03/2020)
	Métodos que usavam o valor literal 6.27 ao invés de PI_2 (6.28) para não fechar todos pontos do círculo foram substituídos por loops inteiros que não causam confusão. Itera n-1 vezes
	Parametros de DrawPolygon alterados para uma estrutura que contém x, y
	Original disponível em http://www-usr.inf.ufsm.br/~pozzer/
*/

#include "Canvas2D.h"
#include <GL/glut.h>

constexpr bool IsYBottomUp = true;
constexpr double Tau = 6.28318530717958;

int* Canvas2D::scrWidth;
int* Canvas2D::scrHeight;

void (*Canvas2D::OnKeyDownCallback)(int);
void (*Canvas2D::OnKeyUpCallback)(int);
void (*Canvas2D::OnMouseUpdateCallback)(int, int, int, int, int, int);
void (*Canvas2D::OnRenderCallback)(void);

Canvas2D::Canvas2D(int* h, int* w, std::string title,
	void(OnKeyDownCallback(int)), 
	void(OnKeyUpCallback(int)), 
	void(OnMouseUpdateCallback(int, int, int, int, int, int)),
	void(OnRenderCallback(void)))
{
	int argc = 0;
	glutInit(&argc, NULL);

	scrHeight = h;
	scrWidth = w;
	this->OnKeyDownCallback = OnKeyDownCallback;
	this->OnKeyUpCallback = OnKeyUpCallback;
	this->OnMouseUpdateCallback = OnMouseUpdateCallback;
	this->OnRenderCallback = OnRenderCallback;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(*w, *h);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title.c_str());

	glClearColor(1, 1, 1, 1);
	glPolygonMode(GL_FRONT, GL_FILL);

	glutReshapeFunc(ScreenRedimensionCallback);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyboardDownGlutCallback);
	glutKeyboardUpFunc(OnKeyboardUpGlutCallback);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);

	glutIdleFunc(Display);
	glutMouseFunc(OnMouseClick);
	glutPassiveMotionFunc(OnMouseMotion);
	glutMotionFunc(OnMouseMotion);
	glutMouseWheelFunc(OnMouseWheel);

	printf("GL Version: %s\n", glGetString(GL_VERSION));
	RunCanvas();
}

void Canvas2D::DrawPoint(Float2 point)
{
	glBegin(GL_POINTS);
	glVertex2d(point.x, point.y);
	glEnd();
}

void Canvas2D::DrawLine(Float2 start, Float2 end)
{
	glBegin(GL_LINES);
	glVertex2d(start.x, start.y);
	glVertex2d(end.x, end.y);
	glEnd();
}

void Canvas2D::DrawRect(Float2 bottomLeft, Float2 topRight)
{
	glBegin(GL_LINE_LOOP);
	glVertex2d(bottomLeft.x, bottomLeft.y);
	glVertex2d(topRight.x, topRight.y);
	glVertex2d(topRight.x, topRight.y);
	glVertex2d(topRight.x, bottomLeft.x);
	glEnd();
}

void Canvas2D::DrawFilledRect(Float2 bottomLeft, Float2 topRight)
{
	glBegin(GL_QUADS);
	glVertex2d(bottomLeft.x, bottomLeft.y);
	glVertex2d(topRight.x, topRight.y);
	glVertex2d(topRight.x, topRight.y);
	glVertex2d(topRight.x, bottomLeft.x);
	glEnd();
}

void Canvas2D::DrawPolygon(Float2 vertices[], int elems)
{
	int cont;
	glBegin(GL_LINE_LOOP);
	for (cont = 0; cont < elems; cont++)
	{
		glVertex2d(vertices[cont].x, vertices[cont].y);
	}
	glEnd();
}

void Canvas2D::DrawFilledPolygon(Float2 vertices[], int elems)
{
	int cont;
	glBegin(GL_POLYGON);
	for (cont = 0; cont < elems; cont++)
	{
		glVertex2d(vertices[cont].x, vertices[cont].y);
	}
	glEnd();

}

void Canvas2D::DrawCircle(Float2 pos, float radius, int divisions)
{
	double ang = 0.0;
	double step = Tau / divisions;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < divisions - 1; i++)
	{
		double x1 = (cos(ang) * radius);
		double y1 = (sin(ang) * radius);
		glVertex2d(x1 + pos.x, y1 + pos.y);
		ang += step;
	}
	glEnd();
}

void Canvas2D::DrawFilledCircle(Float2 pos, float radius, int divisions)
{
	double ang = 0.0;
	double step = Tau / divisions;
	glBegin(GL_POLYGON);
	for (int i = 0; i < divisions - 1; i++)
	{
		double x1 = (cos(ang) * radius);
		double y1 = (sin(ang) * radius);
		glVertex2d(x1 + pos.x, y1 + pos.y);
		ang += step;
	}
	glEnd();
}

void Canvas2D::DrawText(Float2 pos, const char* t)
{
	int tam = (int)strlen(t);
	for (int c = 0; c < tam; c++)
	{
		glRasterPos2i((int) pos.x + c * 10, (int) pos.y);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
	}
}


void Canvas2D::SetColor(RGBAFloat color)
{
	glColor3d(color.r, color.g, color.b);
}

void Canvas2D::ClearScreen(RGBAFloat color)
{
	glClearColor(color.r, color.g, color.b, 1);
}

void Canvas2D::OnSpecialKeyDown(int key, int, int)
{
	OnKeyDownCallback(key + 100);
}

void Canvas2D::OnSpecialKeyUp(int key, int, int)
{
	OnKeyUpCallback(key + 100);
}

void Canvas2D::OnKeyboardDownGlutCallback(unsigned char key, int, int)
{
	OnKeyDownCallback(key);
}

void Canvas2D::OnKeyboardUpGlutCallback(unsigned char key, int, int)
{
	OnKeyUpCallback(key);
}

void Canvas2D::OnMouseClick(int button, int state, int x, int y)
{
	ConvertMouseCoord(button, state, -2, -2, x, y);
}

void Canvas2D::OnMouseWheel(int wheel, int direction, int x, int y)
{
	ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void Canvas2D::OnMouseMotion(int x, int y)
{
	ConvertMouseCoord(-2, -2, -2, -2, x, y);
}

void Canvas2D::ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y)
{
	if (IsYBottomUp) 
	{
		y = *scrHeight - y;
	}
	OnMouseUpdateCallback(button, state, wheel, direction, x, y);
}

void Canvas2D::ScreenRedimensionCallback(int w, int h)
{
	*scrHeight = h;
	*scrWidth = w;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (IsYBottomUp) 
	{
		gluOrtho2D(0.0, w, 0.0, h);
	}
	else 
	{

		gluOrtho2D(0.0, w, h, 0.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Canvas2D::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	OnRenderCallback();

	glFlush();
	glutSwapBuffers();
}

void Canvas2D::RunCanvas()
{
	glutMainLoop();
}