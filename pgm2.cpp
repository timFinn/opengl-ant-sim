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

float x_offset;
float y_offset;
bool start_flag;

void DrawAnt(float init_x, float init_y, float init_z)		// Ant is drawn from the center of its thorax
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();											// Body segment 1 - Abdomen
		glTranslated(init_x-60.0, init_y, init_z);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);									// Abdomen leg segment
    	glVertex3f(init_x-100.0, init_y+30.0, init_z);
    	glVertex3f(init_x-60.0, init_y, init_z);
    	glVertex3f(init_x-100.0, init_y-30.0, init_z);
    glEnd();

    glBegin(GL_LINES);										// Joining segment
    	glVertex3f(init_x-25.0, init_y, init_z);
    	glVertex3f(init_x-35.0, init_y, init_z);
    glEnd();

	glPushMatrix();											// Body segment 2 - Thorax
		glTranslated(init_x, init_y, init_z);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);									// Thorax leg segment
    	glVertex3f(init_x, init_y+55.0, init_z);
    	glVertex3f(init_x, init_y, init_z);
    	glVertex3f(init_x, init_y-55.0, init_z);
    glEnd();

    glBegin(GL_LINES);										// Joining segment
    	glVertex3f(init_x+25.0, init_y, init_z);
    	glVertex3f(init_x+35.0, init_y, init_z);
    glEnd();

    glPushMatrix();											// Body segment 3 - Head
		glTranslated(init_x+60.0, init_y, init_z);
    	glutWireSphere(25.0, 10, 10);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);									// Head leg segment
    	glVertex3f(init_x+100.0, init_y+30.0, init_z);
    	glVertex3f(init_x+60.0, init_y, init_z);
    	glVertex3f(init_x+100.0, init_y-30.0, init_z);
    glEnd();
}

void DrawFood(float init_x, float init_y, float init_z)
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();											// FOOD Cube
		glTranslated(init_x, init_y, init_z);
    	glutSolidCube(40.0);
    glPopMatrix();
}

void DisplayEventHandler()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawAnt((canvas_Width-100.0) + x_offset, canvas_Height/2 + y_offset, -200.0);

	DrawFood(50.0, canvas_Height/2, -180.0);    

    glFlush();
}

void TimerEventHandler(int ID)
{
    DisplayEventHandler();
}

void KeyboardEventHandler(unsigned char key, int x, int y)
{    
	if (key == 'h')
	{
		x_offset -= 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		x_offset -= 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
	}    	
	else if (key == 'j')
	{
		x_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		x_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
	}
	else if (key == 'u')
	{
		y_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		y_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
	}
	else if (key == 'n')
	{
		y_offset -= 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		y_offset -= 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
	}
}

void InitRendering()
{
    glClearColor(0.5, 1.0, 0.5, 1.0);	// set background to light green
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

    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    glutMainLoop();

    return 0;
}
