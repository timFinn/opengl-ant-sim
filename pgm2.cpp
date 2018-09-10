//	CS 445/545 Prog 2 for Timothy Finnegan

/****

	Software Architecture Statement
	
	This application is designed to 

****/

#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "my_setup_3D_18.h"

#define canvas_Width 480
#define canvas_Height 480
#define canvas_Name "CS 445 - Program 2"
#define PI 3.14159265359

int x_offset;
bool start_flag;

void drawGoose(int init_x, int init_y)
{
    glBegin(GL_LINE_LOOP);
      glColor3f(0.0, 0.0, 0.0);
      glVertex2i(init_x, init_y);
      glVertex2i(init_x + 60, init_y); // head
      glVertex2i(init_x, init_y);
      glVertex2i(init_x - 40, init_y + 40); // top wing
      glVertex2i(init_x, init_y);
      glVertex2i(init_x - 40, init_y - 40); // bottom wing
      glVertex2i(init_x, init_y);
      glVertex2i(init_x - 40, init_y); // tail
    glEnd();
}

void DisplayEventHandler()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGoose(100 + x_offset, canvas_Height - 50);
    drawGoose(100 + x_offset, canvas_Height  - 150);
    drawGoose(240 + x_offset, canvas_Height -75);

    drawCloud((canvas_Width - 50) - (x_offset/2), 100, 20);
    drawCloud((canvas_Width - 150) - (x_offset/3), 200, 20);
    drawCloud((canvas_Width - 175) - (x_offset/3), 50, 20);
    drawCloud((canvas_Width - 200) - (x_offset/2), 150, 20);

    glFlush();
}

void TimerEventHandler(int ID)
{
    x_offset += 10;

    if (x_offset == 50 || x_offset == 150 || x_offset == 250 || x_offset == 350)
    {
    	display_func2();
    }
    else
    {
    	display_func();
    }
    
    glutTimerFunc(100, timer_func, 1);
}

void KeyboardEventHandler(unsigned char key, int x, int y)
{    
	if (start_flag == false)
	{
		glutTimerFunc(100, timer_func, 1);
		start_flag = true;
	}    
    else
    {
    	if (key == 'r')
    	{
    		x_offset = 0;
    	}    	
    }
}

void initRendering()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);	// set background to white
    glLineWidth(1.0);					// set line width to 1
}

int main (int argc, char ** argv)
{
    x_offset = 0;
    start_flag = false;

    glutInit(&argc, argv);    
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    initRendering();   

    glutDisplayFunc(DisplayEventHandler);
    glutKeyboardFunc(KeyboardEventHandler);

    std::cout << "Any Key Click Will Start." << std::endl;
    std::cout << "Press R to reset the flock." << std::endl;

    glutMainLoop();

    return 0;
}
