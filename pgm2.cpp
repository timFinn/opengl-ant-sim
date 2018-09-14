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

float ant_x;
float ant_y;
float ant_z;

float food_x;
float food_y;
float food_z;


void DrawAnt(float x, float y, float z)			// Ant is drawn from the center of its thorax
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();								// Body segment 1 - Abdomen
		glTranslated(x-60.0, y, z);
    	glutWireSphere(25.0, 20, 20);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Abdomen leg segment
    	glVertex3f(x-100.0, y+30.0, z);
    	glVertex3f(x-60.0, y, z);
    	glVertex3f(x-100.0, y-30.0, z);
    glEnd();

    glBegin(GL_LINES);							// Joining segment
    	glVertex3f(x-25.0, y, z);
    	glVertex3f(x-35.0, y, z);
    glEnd();

	glPushMatrix();								// Body segment 2 - Thorax
		glTranslated(x, y, z);
    	glutWireSphere(25.0, 20, 20);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Thorax leg segment
    	glVertex3f(x, y+55.0, z);
    	glVertex3f(x, y, z);
    	glVertex3f(x, y-55.0, z);
    glEnd();
 
    glBegin(GL_LINES);							// Joining segment
    	glVertex3f(x+25.0, y, z);
    	glVertex3f(x+35.0, y, z);
    glEnd();

    glPushMatrix();								// Body segment 3 - Head
		glTranslated(x+60.0, y, z);
    	glutWireSphere(25.0, 20, 20);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Head leg segment
    	glVertex3f(x+100.0, y+30.0, z);
    	glVertex3f(x+60.0, y, z);
    	glVertex3f(x+100.0, y-30.0, z);
    glEnd();    
}

void DrawFood(float x, float y, float z)
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();								// FOOD Cube
		glTranslated(x, y, z);
    	glutWireCube(40.0);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(x-18.0, y, z);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'F');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'O');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'O');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'D');
}

void CheckFood()
{
	if (ant_x + x_offset == food_x && ant_y + y_offset == food_y)
	{
		glColor3f(0.0, 0.0, 0.0);
	    glRasterPos3f(0.0, 0.0, 0.0);
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');
	}
}

void DisplayEventHandler()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawAnt(ant_x + x_offset, ant_y + y_offset, ant_z);

	DrawFood(food_x, food_y, food_z);    

	CheckFood();

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
		// x_offset -= 5.0;
		// glutTimerFunc(30.0, TimerEventHandler, 1);
	}    	
	else if (key == 'j')
	{
		x_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		// x_offset += 5.0;
		// glutTimerFunc(30.0, TimerEventHandler, 1);
	}
	else if (key == 'u')
	{
		y_offset += 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		// y_offset += 5.0;
		// glutTimerFunc(30.0, TimerEventHandler, 1);
	}
	else if (key == 'n')
	{
		y_offset -= 5.0;
		glutTimerFunc(30.0, TimerEventHandler, 1);
		// y_offset -= 5.0;
		// glutTimerFunc(30.0, TimerEventHandler, 1);
	}
}

void InitRendering()
{
    glClearColor(0.5, 1.0, 0.5, 1.0);	// set background to light green
    glLineWidth(1.0);					// set line width to 1
}

int main (int argc, char ** argv)
{
    x_offset = 0.0;
    y_offset = 0.0;

    ant_x = (canvas_Width/2 - 100.0);
    ant_y = 0.0;
    ant_z = -200.0;

    food_x = -canvas_Width/2 + 100.0;
    food_y = 0.0;
    food_z = -220.0;

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
