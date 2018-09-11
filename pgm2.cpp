//	CS 445/545 Prog 2 for Timothy Finnegan

/****

	Software Architecture Statement
	
	This application is designed to 

****/

#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "my_setup_3D_18.h"

#define canvas_Width 640
#define canvas_Height 640
#define canvas_Name "CS 445 - Program 2"
#define PI 3.14159265359

int x_offset;
int y_offset;
bool start_flag;

void DrawAnt(int init_x, int init_y)			// Ant is drawn from the center of its thorax
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();								// Body segment 1 - Abdomen
		glTranslated(init_x-60.0, init_y, 0.0);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Abdomen leg segment
    	glVertex3f(init_x-100.0, init_y+30.0, 0.0);
    	glVertex3f(init_x-60.0, init_y, 0.0);
    	glVertex3f(init_x-100.0, init_y-30.0, 0.0);
    glEnd();

    glBegin(GL_LINES);							// Joining segment
    	glVertex3f(init_x-25.0, init_y, 0.0);
    	glVertex3f(init_x-35.0, init_y, 0.0);
    glEnd();

	glPushMatrix();								// Body segment 2 - Thorax
		glTranslated(init_x, init_y, 0.0);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);							// Thorax leg segment
    	glVertex3f(init_x, init_y+55.0, 0.0);
    	glVertex3f(init_x, init_y, 0.0);
    	glVertex3f(init_x, init_y-55.0, 0.0);
    glEnd();

    glBegin(GL_LINES);							// Joining segment
    	glVertex3f(init_x+25.0, init_y, 0.0);
    	glVertex3f(init_x+35.0, init_y, 0.0);
    glEnd();

    glPushMatrix();								// Body segment 3 - Head
		glTranslated(init_x+60.0, init_y, 0.0);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Head leg segment
    	glVertex3f(init_x+100.0, init_y+30.0, 0.0);
    	glVertex3f(init_x+60.0, init_y, 0.0);
    	glVertex3f(init_x+100.0, init_y-30.0, 0.0);
    glEnd();
}

void DisplayEventHandler()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawAnt(canvas_Width/2 + x_offset, canvas_Height/2 + y_offset);

    glFlush();
}

void TimerEventHandler(int ID)
{
    DisplayEventHandler();
    
    glutTimerFunc(100, TimerEventHandler, 1);
}

void KeyboardEventHandler(unsigned char key, int x, int y)
{    
	if (start_flag == false)
	{
		glutTimerFunc(100, TimerEventHandler, 1);
		start_flag = true;
	}    
    else
    {
    	if (key == 'h')
    	{
    		x_offset = 0;
    	}    	
    	else if (key == 'j')
    	{
    		x_offset = 0;
    	}
    	else if (key == 'u')
    	{
    		x_offset = 0;
    	}
    	else if (key == 'n')
    	{
    		x_offset = 0;
    	}
    }
}

void InitRendering()
{
    glClearColor(0.5, 1.0, 0.5, 1.0);	// set background to white
    glLineWidth(1.0);					// set line width to 1
}

int main (int argc, char ** argv)
{
    x_offset = 0;
    start_flag = false;

    glutInit(&argc, argv);    
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    InitRendering();   

    glutDisplayFunc(DisplayEventHandler);
    glutKeyboardFunc(KeyboardEventHandler);

    std::cout << "Any Key Click Will Start." << std::endl;
    std::cout << "Press R to reset the flock." << std::endl;

    glutMainLoop();

    return 0;
}
