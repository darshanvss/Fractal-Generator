//g++ fractals.cpp -lGL -lGLU -lglut -lGLEW -o fr

/*_____KEYBOARD CONTROLS_______
1- SIERPINSKI TRIANGLE GENERATION 
2- SIERPINSKI TRIANGLE ZOOMING
3- T SQUARE GENERATION
4- T SQUARE ZOOMING
5- SIERPINSKI CARPET GENERATION
6- SIERPINSKI CARPET ZOOMING
7-HEIGHWAY DRAGON CURVE GENERATION
8- FLORAL PATTERN WITH DRAGON CURVES
__________________________________________*/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void changeViewPort(int w, int h) // to always have the viewport in the centre of the window in SQUARE SHAPE
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.1, 0.11, 0.12, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
}

struct triangle
{
    float ax, ay;
    float bx, by;
    float cx, cy;
};
struct line
{
    float x1, y1;
    float x2, y2;
};
struct square
{
    float x; //center of square
    float y;
    float l;
};

int x = 0;
int y = 0;
int repeat = 7;

float randColor()
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

void drawSierpinskiTriangle(triangle old, int iteration)
{
    if (iteration > 0)
    {
        //drawing tri

        glBegin(GL_LINE_LOOP);
        glVertex2f(old.ax, old.ay);
        glVertex2f(old.bx, old.by);
        glVertex2f(old.cx, old.cy);
        glEnd();

        //splitting into 4 triangles

        triangle newM; //middle triangle
        //x co-orxinates
        newM.ax = (old.ax + old.bx) / 2;
        newM.bx = (old.bx + old.cx) / 2;
        newM.cx = (old.cx + old.ax) / 2;
        //y co-orxinates
        newM.ay = (old.ay + old.by) / 2;
        newM.by = (old.by + old.cy) / 2;
        newM.cy = (old.cy + old.ay) / 2;

        triangle newA; //Vertex A triangle
        //x co-orxinates
        newA.ax = old.ax;
        newA.bx = (old.ax + old.bx) / 2;
        newA.cx = (old.ax + old.cx) / 2;
        //y co-orxinates
        newA.ay = old.ay;
        newA.by = (old.ay + old.by) / 2;
        newA.cy = (old.ay + old.cy) / 2;

        triangle newB; //Vertex B triangle
        //x co-orxinates
        newB.ax = (old.bx + old.ax) / 2;
        newB.bx = old.bx;
        newB.cx = (old.bx + old.cx) / 2;
        //y co-orxinates
        newB.ay = (old.by + old.ay) / 2;
        newB.by = old.by;
        newB.cy = (old.by + old.cy) / 2;

        triangle newC; //Vertex C triangle
        //x co-orxinates
        newC.ax = (old.cx + old.ax) / 2;
        newC.bx = (old.cx + old.bx) / 2;
        newC.cx = old.cx;
        //y co-orxinates
        newC.ay = (old.cy + old.ay) / 2;
        newC.by = (old.cy + old.by) / 2;
        newC.cy = old.cy;

        iteration -= 1;
        //drawSierpinskiTriangle(newM, iteration);
        bool f1 = true, f2 = true, f3 = true;
        if ((newA.ay >= 0) || (newA.by >= 0) || (newA.cy >= 0))
            drawSierpinskiTriangle(newA, iteration);
        if ((newB.ay >= 0) || (newB.by >= 0) || (newB.cy >= 0))
            drawSierpinskiTriangle(newB, iteration);
        if ((newC.ay >= 0) || (newC.by >= 0) || (newC.cy >= 0))
            drawSierpinskiTriangle(newC, iteration);
    }
}

void f1()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(1);
    glColor3f(0, 1, 1);
    //glColor3f(randColor(),randColor(),randColor());

    triangle Base = {160, 240, 640, 240, 400, 240 + 415.688}; // height of equilateral triangle
    //triangle Base = {0,1  ,  100,1  ,  50,100};
    drawSierpinskiTriangle(Base, x);

    glutSwapBuffers();
}

float zoomx1 = 0, zoomy1 = 0;

void f2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(1);
    glColor3f(0, 1, 1);
    //glColor3f(randColor(),randColor(),randColor());

    triangle Base = {0 - zoomx1, 0 - zoomy1, 800 + zoomx1, 0 - zoomy1, 400, 800 * 0.866}; // height of equilateral triangle
    //triangle Base = {0,1  ,  100,1  ,  50,100};
    drawSierpinskiTriangle(Base, 9);

    glutSwapBuffers();
}

void drawTSquare(square old, int iteration)
{
    float x = old.x;
    float y = old.y;
    float l = old.l / 2;

    if (iteration > 0)
    {
        //drawing square
        glBegin(GL_POLYGON);
        glVertex2f(x - l, y - l);
        glVertex2f(x + l, y - l);
        glVertex2f(x + l, y + l);
        glVertex2f(x - l, y + l);
        glEnd();

        //New smaller square centers

        square s1 = {x - l, y - l, l};
        square s2 = {x + l, y - l, l};
        square s3 = {x + l, y + l, l};
        square s4 = {x - l, y + l, l};

        iteration -= 1;

        if (s1.x + l > 0 || s1.y + l > 0)
            drawTSquare(s1, iteration);
        if (s2.x + l > 0 || s2.y + l > 0)
            drawTSquare(s2, iteration);
        if (s3.x + l > 0 || s3.y + l > 0)
            drawTSquare(s3, iteration);
        if (s4.x + l > 0 || s4.y + l > 0)
            drawTSquare(s4, iteration);
    }
}

void f3()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.5, 0.4, 0.9);
    //glColor3f(randColor(),randColor(),randColor());
    square Base = {400, 400, 400};

    drawTSquare(Base, x);
    glutSwapBuffers();
}

float zoomx2 = 0, zoomy2 = 0;

void f4()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.5, 0.4, 0.9);
    //glColor3f(randColor(),randColor(),randColor());
    square Base = {400 - zoomx2, 400 - zoomx2, 400 + zoomx2};

    drawTSquare(Base, 10);
    glutSwapBuffers();
}

void drawSierpinskiCarpet(square old, int iteration)
{
    float x = old.x;
    float y = old.y;
    float l = old.l / 6;

    if (iteration > 0)
    {
        //drawing square
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - l, y - l);
        glVertex2f(x + l, y - l);
        glVertex2f(x + l, y + l);
        glVertex2f(x - l, y + l);
        glEnd();

        //making new squares anticlockwise from bottom left

        square s1 = {old.x - old.l / 3, old.y - old.l / 3, old.l / 3}; //bottom left
        square s2 = {old.x, old.y - old.l / 3, old.l / 3};             //bottom mid
        square s3 = {old.x + old.l / 3, old.y - old.l / 3, old.l / 3}; //bottom right
        square s4 = {old.x + old.l / 3, old.y, old.l / 3};             //mid right
        square s5 = {old.x + old.l / 3, old.y + old.l / 3, old.l / 3}; //top right
        square s6 = {old.x, old.y + old.l / 3, old.l / 3};             //top mid
        square s7 = {old.x - old.l / 3, old.y + old.l / 3, old.l / 3}; //top left
        square s8 = {old.x - old.l / 3, old.y, old.l / 3};             //mid left
        square s9 = {old.x, old.y, old.l / 3};                         //middle

        //Recursion
        iteration -= 1;
        if (s1.x + l > 0 || s1.y + l > 0)
            drawSierpinskiCarpet(s1, iteration);
        if (s2.x + l > 0 || s2.y + l > 0)
            drawSierpinskiCarpet(s2, iteration);
        if (s3.x + l > 0 || s3.y + l > 0)
            drawSierpinskiCarpet(s3, iteration);
        if (s4.x + l > 0 || s4.y + l > 0)
            drawSierpinskiCarpet(s4, iteration);
        if (s5.x + l > 0 || s5.y + l > 0)
            drawSierpinskiCarpet(s5, iteration);
        if (s6.x + l > 0 || s6.y + l > 0)
            drawSierpinskiCarpet(s6, iteration);
        if (s7.x + l > 0 || s7.y + l > 0)
            drawSierpinskiCarpet(s7, iteration);
        if (s8.x + l > 0 || s8.y + l > 0)
            drawSierpinskiCarpet(s8, iteration);
        //if (s9.x + l > 0 || s9.y + l > 0)
        //drawSierpinskiCarpet(s9, iteration);
    }
}

void f5()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.5, 1, 0.5);
    //glColor3f(randColor(),randColor(),randColor());
    square Base = {400, 400, 800};

    drawSierpinskiCarpet(Base, x);

    glutSwapBuffers();
}
float zoomx3 = 0;
void f6()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.5, 1, 0.5);
    //glColor3f(randColor(),randColor(),randColor());
    square Base = {400 - zoomx3, 400 - zoomx3, 800 + 2 * zoomx3};

    drawSierpinskiCarpet(Base, 6);

    glutSwapBuffers();
}

void drawFractal6(line old, int rot, int iteration)
{
    if (iteration > 1)
    {
        //glColor3f(randColor(),randColor(),randColor());
        //glLineWidth(rand()%5);
        float r = sqrt(((old.y2 - old.y1) * (old.y2 - old.y1) + (old.x2 - old.x1) * (old.x2 - old.x1)) / 2);
        float a = atan((old.y2 - old.y1) / (old.x2 - old.x1));

        float x, y;

        if (rot == -1)
        {
            if (old.x1 == old.x2) //vertical line
            {
                x = old.x1 + r * cos(a - M_PI / 4);
                y = (old.y1 + old.y2) / 2;
            }
            else if (old.x1 < old.x2)
            {
                x = old.x1 + r * cos(a - M_PI / 4);
                y = old.y1 + r * sin(a - M_PI / 4);
            }
            else
            {
                x = old.x2 + r * cos(a + M_PI / 4);
                y = old.y2 + r * sin(a + M_PI / 4);
            }
        }
        else if (rot == 1)
        {
            if (old.x1 == old.x2) //vertical line
            {
                x = old.x1 - r * cos(a - M_PI / 4);
                y = (old.y1 + old.y2) / 2;
            }
            else if (old.x1 < old.x2)
            {
                x = old.x1 + r * cos(a + M_PI / 4);
                y = old.y1 + r * sin(a + M_PI / 4);
            }
            else
            {
                x = old.x2 + r * cos(a - M_PI / 4);
                y = old.y2 + r * sin(a - M_PI / 4);
            }
        }

        line new1 = {old.x1, old.y1, x, y};
        line new2 = {x, y, old.x2, old.y2};

        iteration -= 1;
        drawFractal6(new1, -1, iteration);
        drawFractal6(new2, 1, iteration);
    }
    else
    {
        glBegin(GL_LINES);
        glVertex2f(old.x1, old.y1);
        glVertex2f(old.x2, old.y2);
        glEnd();
    }
}

void f7()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(1);
    glColor3f(0.3, 0.3, 1);
    //glColor3f(randColor(),randColor(),randColor());
    line Base = {180, 280, 550, 650};
    drawFractal6(Base, -1, y);

    glutSwapBuffers();
}

void f8()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(1);
    glColor3f(0.3, 0.3, 1);
    //glColor3f(randColor(),randColor(),randColor());
    line Base = {160, 400, 400, 400};
    line Base2 = {640, 400, 400, 400};
    line Base3 = {400, 640, 400, 400};
    line Base4 = {400, 160, 400, 400};
    drawFractal6(Base, -1, y);
    drawFractal6(Base2, -1, y);
    drawFractal6(Base3, -1, y);
    drawFractal6(Base4, -1, y);

    glutSwapBuffers();
}

void timer(int);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Sierpinski triangle generation");
    myinit();
    glutDisplayFunc(f1);
    glutReshapeFunc(changeViewPort);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

int FPS = 1000 / 30;
int loop = 0;
void timer(int)
{

    if (loop % FPS == 0) // once a second
    {
        // generation animation
        x++;
        if (x > repeat)
            x = 1;
        y++;
        if (y > 2 * repeat)
            y = 1;
    }
    loop++;
    if (loop >= FPS)
        loop = 0;
    //Sierpinski Triangle zooming Speed
    float sts = 4;
    zoomx1 += sts;
    if (zoomx1 >= 400)
        zoomx1 = 0;
    zoomy1 += sts * 346.41 / 200;
    if (zoomy1 >= 2 * 346.41)
        zoomy1 = 0;
    //T square zooming Speed
    zoomx2 += 8;
    if (zoomx2 >= 3200) //length of smaller fractal
        zoomx2 = 1400;  // lenght/2 shift to loop

    //Sierpinski Carpet zooming Speed
    zoomx3 += 8;
    if (zoomx3 >= 800)
        zoomx3 = 0;

    glutTimerFunc(FPS, timer, 0);
    glutKeyboardFunc(keyboard);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("Sierpinski triangle generation");
        myinit();
        glutDisplayFunc(f1);
        break;
    case '2':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("Sierpinski triangle Zooming ");
        myinit();
        glutDisplayFunc(f2);
        break;
    case '3':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("T Square generation");
        myinit();
        glutDisplayFunc(f3);
        break;
    case '4':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("T Square zooming ");
        myinit();
        glutDisplayFunc(f4);
        break;
    case '5':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("Sierpinski Carpet generation");
        myinit();
        glutDisplayFunc(f5);
        break;
    case '6':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("Sierpinski Carpet zooming");
        myinit();
        glutDisplayFunc(f6);
        break;
    case '7':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("Heighway's Dragon curve generation");
        myinit();
        glutDisplayFunc(f7);
        break;
    case '8':
        glutDestroyWindow(glutGetWindow());
        glutCreateWindow("combination of 4 dragon curves");
        myinit();
        glutDisplayFunc(f8);
        break;

        break;
    }
}