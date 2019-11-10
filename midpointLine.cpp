#include "GL/glut.h"
#include "stdio.h"
#include "math.h"

int xs, ys, xe, ye;

void MidpointLine(int x0, int y0, int x1, int y1)
{
	int x = x0, y = y0;
	int a = y0 - y1, b = x1 - x0;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));
	glVertex2i(x, y);

	int dl, d2, d;
	if (-a <= b)		// -1<= k <=1
	{
		d = 2 * a + b;
		dl = 2 * a;
		d2 = 2 * (a + b);
		while (x != x1)
		{
			if (d < 0)
				y += cy, d += d2;
			else
				d += dl;
			x += cx;
			glVertex2i(x, y);
		}
	}
	else				// k>1&&k<-1
	{
		d = 2 * b + a;
		dl = 2 * b;
		d2 = 2 * (a + b);
		while (y != y1)
		{
			if (d < 0)
				d += dl;
			else
				x += cx, d += d2;
			y += cy;
			glVertex2i(x, y);
		}
	}
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	MidpointLine(xs, ys, xe, ye);
	glEnd();
	glFlush();
}

void main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	printf("输入起点和终点坐标（范围为0-500,0-500）");
	scanf_s("%d,%d,%d,%d", &xs, &ys, &xe, &ye);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("中点划线算法");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}
