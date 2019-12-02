#-*- coding: UTF-8-*-
from OpenGL.GL import *
from OpenGL.GLUT import *

def myDisplay():

    glClear(GL_COLOR_BUFFER_BIT)
    glBegin(GL_POLYGON)
    glVertex2d(-0.5, -0.5)
    glVertex2d(-0.5, 0.5)
    glVertex2d(0.5, 0.5)
    glVertex2d(0.5, -0.5)
    glEnd()
    glFlush()

def main():

    glutInit()
    glutCreateWindow("simple")
    glutDisplayFunc(myDisplay)
    glutMainLoop()

main()