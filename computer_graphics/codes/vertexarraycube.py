
from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

vertices = np.array([[-1.0, -1.0, 1.0],[-1.0,1.0,1.0],
	[1.0,1.0,1.0],[1.0,-1.0,1.0],[-1.0,-1.0,-1.0],     
	[-1.0,1.0,-1.0], [1.0,1.0,-1.0], [1.0,-1.0,-1.0]])

colors = np.array([[0.0,0.0,0.0], [1.0,0.0,0.0], 
	[1.0,1.0,0.0],[0.0,1.0,0.0], [0.0,0.0,1.0],
	[1.0,0.0,1.0], [1.0,1.0,1.0],[0.0,1.0,1.0]])

cubeIndices = np.array([0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4])


def display():

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0)

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices)
    glutSwapBuffers() 


def myReshape(w, h):

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if w <= h:
        glOrtho(-4.0, 4.0, -3.0 *  h /  w,
            5.0 *  h /  w, -10.0, 10.0)
    else:
        glOrtho(-4.0 *  w /  h,
            4.0 *  w /  h, -3.0, 5.0, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)


def main():

    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(500, 500)
    glutCreateWindow("colorcube")
    glutReshapeFunc(myReshape)
    glutDisplayFunc(display)

    glEnable(GL_DEPTH_TEST)
    glEnableClientState(GL_COLOR_ARRAY) 
    glEnableClientState(GL_VERTEX_ARRAY)
    glVertexPointer(3, GL_DOUBLE, 0, vertices)
    glColorPointer(3,GL_DOUBLE, 0, colors)

    # //glShadeModel(GL_SMOOTH)
    glShadeModel(GL_FLAT)

    glClearColor(0.0,0.0,0.0,1.0)

    glutMainLoop()

main()