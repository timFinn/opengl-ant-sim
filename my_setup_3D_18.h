
/***********************************************************


   This header file contains initialization function calls and set-ups
for basic 3D CS 445/545 legacy Open GL (Mesa) programs using GLUT/freeglut.
The initializations involve defining a callback handler (my_reshape_function)
that sets viewing parameters for orthographic 3D display.
This file is useful for legacy GLUT 2.1

   TSN 02/2010, updated 08/2018

 ************************************************************/


/* reshape callback handler - defines viewing parameters */

void my_3d_projection(int width, int height)
    {
    GLfloat width_bound, height_bound;

    width_bound = width; height_bound = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // the glOrtho() line may need to be changed 
    glOrtho(-width_bound/2, width_bound/2, -height_bound/2, height_bound/2, 0, 640.0);
    glMatrixMode(GL_MODELVIEW);
    }

#define STRT_X_POS 25
#define STRT_Y_POS 25

void my_setup(int width, int height, char *window_name_str)
    {
    // To get double buffering, uncomment the following line
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    // below code line does single buffering - if above line is uncommented,
    // the single buffering line will have to be commented out
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(width, height);

    glutInitWindowPosition(STRT_X_POS,STRT_Y_POS);

    glutCreateWindow(window_name_str);

    glutReshapeFunc(my_3d_projection);
    }

