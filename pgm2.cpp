//	CS 445/545 Prog 2 for Timothy Finnegan

/****

	Software Architecture Statement
	
	This application is designed to draw an "ant" and a cube of "food" and provide the
	user with controls to move the ant over to the food so it can eat. The ant is composed
	of three wire spheres and several line segments. Every time the H, J, U, or N keys are
	pressed, the ant will move left, right, up, or down respectively. The position of the
	ant is updated for draw calls by incremented an offset value that is modified by the
	KeyboardEventHandler function. Once the position of the ant plus it's accumulated offset
	matches the position of the food cube, the victory condition is reached and the text
	is drawn on the canvas.

	In order to meet the requirements for the camera space, the glOrtho call in 
	my_setup_3D_18.h was modified to build the world properly.


	EXTRA CREDIT
	(1) I have added the ability to change the color of the ant by creating a global integer
	variable that represents the color to be used in the draw call. Each time the user presses
	'c', the integer is incremented by 1, allowing the user to cycle through each color.



****/

#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "my_setup_3D_18.h"

#define canvas_Width 640
#define canvas_Height 640
#define canvas_Name "CS 445 - Program 2"

float x_offset;									// Additive offset from original x position
float y_offset;									// Additive offset from original y position

float ant_x;									// x component of the ant position
float ant_y;									// y component of the ant position
float ant_z;									// z component of the ant position

int ant_color;									// variable to hold color of ant

float food_x;									// x component of the food position
float food_y;									// y component of the food position
float food_z;									// z component of the food position


void DrawAnt(float x, float y, float z)			// Ant is drawn from the center of its thorax
{
	if (ant_color == 0)
	{
		glColor3f(0.0, 0.0, 0.0);
	}
	else if (ant_color == 1)
	{
		glColor3f(1.0, 0.0, 0.0);
	}	

	glPushMatrix();								// Body segment 1 - Abdomen
		glTranslated(x-60.0, y, z);
    	glutWireSphere(25.0, 20, 20);
    glPopMatrix();

    glBegin(GL_LINE_STRIP);						// Abdomen leg segment
    	glVertex3f(x-110.0, y+20.0, z);
    	glVertex3f(x-60.0, y, z);
    	glVertex3f(x-110.0, y-20.0, z);
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
    	glVertex3f(x+110.0, y+20.0, z);
    	glVertex3f(x+60.0, y, z);
    	glVertex3f(x+110.0, y-20.0, z);
    glEnd();    
}

void DrawFood(float x, float y, float z)
{
	glColor3f(1.0, 1.0, 0.0);					// Set color to "light yellow"
	glPushMatrix();								// Push current matrix to save
		glTranslated(x, y, z);					// Move draw coordinates 
    	glutWireCube(40.0);						// Draw cube with x and y extent of 40
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
	float distance = sqrt((((ant_x + x_offset) - food_x)*((ant_x + x_offset) - food_x)) + 
						(((ant_y + y_offset) - food_y)*((ant_y + y_offset) - food_y)));

	std::cout << distance << std::endl;

	if (distance < 20.0)
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

/*
	The timer event handler is designed to use the timer ID to determine which offset to
	modify in order to move the ant in the desired direction.
*/
void TimerEventHandler(int ID)
{
	if (ID == 1)
	{
		x_offset -= 5.0;
    	DisplayEventHandler();
	}
	else if (ID == 2)
	{
		x_offset += 5.0;
    	DisplayEventHandler();
	}
	else if (ID == 3)
	{
		y_offset += 5.0;
    	DisplayEventHandler();
	}
	else if (ID == 4)
	{
		y_offset -= 5.0;
    	DisplayEventHandler();
	}
	else
	{
		DisplayEventHandler();
	}
}

/*
	The keyboard event handler is designed to identify the correct control inputs
	and based on the key, call the timer twice with a 60ms delay.
*/
void KeyboardEventHandler(unsigned char key, int x, int y)
{    
	if (key == 'h')
	{
		glutTimerFunc(0.0, TimerEventHandler, 1);
		glutTimerFunc(60.0, TimerEventHandler, 1);
	}    	
	else if (key == 'j')
	{
		glutTimerFunc(0.0, TimerEventHandler, 2);
		glutTimerFunc(60.0, TimerEventHandler, 2);
	}
	else if (key == 'u')
	{
		glutTimerFunc(0.0, TimerEventHandler, 3);
		glutTimerFunc(60.0, TimerEventHandler, 3);
	}
	else if (key == 'n')
	{
		glutTimerFunc(0.0, TimerEventHandler, 4);
		glutTimerFunc(60.0, TimerEventHandler, 4);
	}
	else if (key == 'c')
	{
		if(ant_color == 0)
		{
			ant_color++;
			glutTimerFunc(30.0, TimerEventHandler, 1);
		}
		else if (ant_color == 1)
		{
			ant_color--;
			glutTimerFunc(30.0, TimerEventHandler, 1);
		}
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
