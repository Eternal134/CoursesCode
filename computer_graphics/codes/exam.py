#-*- coding: UTF-8-*-
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import numpy as np
import time

my_x = -0.25
my_y = 0
status = 0

def myDisplay():

    glClear(GL_COLOR_BUFFER_BIT)
    # 机头
    glBegin(GL_TRIANGLES)
    glColor3f(0.98, 0.04, 0.7)
    glVertex3f(-0.25, 0., 1.0)
    glVertex3f(-0.4, 0.1, -1.0)
    glVertex3f(-0.4, -0.1, -1.0)
    glEnd()
    # 机身
    glBegin(GL_POLYGON)
    glVertex3f(-0.4, 0.1, 1.0)
    glVertex3f(-0.8, 0.1, 1.0)
    glVertex3f(-0.8, -0.1, -1.0)
    glVertex3f(-0.4, -0.1, -1.0)
    glEnd()
    # 机翼
    glBegin(GL_POLYGON)
    glColor3f(0.0, 1.0, 1.0)
    glVertex3f(-0.6, 0.275, 1.0)
    glVertex3f(-0.7, 0.275, 1.0)
    glVertex3f(-0.65, 0.1, -1.0)
    glVertex3f(-0.55, 0.1, -1.0)
    glEnd()
    glBegin(GL_POLYGON)
    glColor3f(0.0, 1.0, 1.0)
    glVertex3f(-0.6, -0.275, 1.0)
    glVertex3f(-0.7, -0.275, 1.0)
    glVertex3f(-0.65, -0.1, -1.0)
    glVertex3f(-0.55, -0.1, -1.0)
    glEnd()
    # 机尾
    glBegin(GL_POLYGON)
    glColor3f(0.98, 0.625, 0.12)
    glVertex3f(-0.8, 0.175, 1.0)
    glVertex3f(-0.9, 0.175, 1.0)
    glVertex3f(-0.9, -0.175, -1.0)
    glVertex3f(-0.8, -0.175, -1.0)
    glEnd()
    glutSwapBuffers()

def translate():
    
    glTranslate(0.001, 0.0, 0.0)
    myDisplay()
    
def turn():
    
    glLoadIdentity()
    glRotate(180, 0, 0, 1)
    glTranslate(0.0, (-1)*my_y, 0.0)
    myDisplay()
    
    
def keyboard(key, x, y):
    global status
    global my_x
    global my_y
    if ord(key) == ord('d'):
    
        while status == 0:
            translate()
            my_x += 0.001
            if my_x > 1 and status == 0:
                time.sleep(0.2)
                turn()
                my_x = 0.25
                status = 1
                break
        
    if ord(key) == ord('a'):
        
        while status == 1: 
            translate()
            my_x += -0.001
            if my_x < -1 and status == 1:
                time.sleep(0.2)
                glLoadIdentity()
                glTranslate(0.0, my_y, 0.0)
                myDisplay()
                my_x = -0.25
                status = 0
                break
            
    if ord(key) == ord('w'):
        
        if my_y < 0.6:
            
            glTranslate(0.0, 0.1, 0.0)
            myDisplay()
            my_y += 0.1
            
    if ord(key) == ord('s'):
        
        if my_y > -0.6:
            
            glTranslate(0.0, -0.1, 0.0)
            myDisplay()
            my_y += -0.1
        
    
    if ord(key) == ord('p'):
        exit()

def main():

    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutCreateWindow("simple")
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
    # gluLookAt(-1.0, -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glutDisplayFunc(myDisplay)
    glutKeyboardFunc(keyboard)
    glutMainLoop()

main()