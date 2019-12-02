from OpenGL.GL import *
from OpenGL.GLUT import *

def points_display():

    # glViewport(100, 100, 50, 50)
    glClear(GL_COLOR_BUFFER_BIT)

    glPointSize(10)
    glBegin(GL_POINTS)
    glColor3f(255, 165, 0)
    glVertex3f(-0.8, -0.7, 1.0)
    glEnd()

    glPointSize(20)
    glBegin(GL_POINTS)
    glColor3f(0, 255, 0)
    glVertex3f(-0.0, -0.7, 1.0)
    glEnd()

    glPointSize(30)
    glBegin(GL_POINTS)
    glColor3f(255, 0, 255)
    glVertex3f(0.8, -0.7, 1.0)
    glEnd()

    glFlush()

def lines_display():

    glClear(GL_COLOR_BUFFER_BIT)

    glBegin(GL_LINES)
    glColor3f(250, 128, 114)
    glVertex3f(-0.8, -0.5, 1.0)
    glVertex3f(0.6, 0.6, 1.0)
    glEnd()

    glColor3f(255, 215, 0)
    glLineWidth(5)
    glBegin(GL_LINES)
    glVertex3f(-0.5, -0.3, 1.0)
    glVertex3f(0.8, 0.5, 1.0)
    glEnd()

    glColor3f(0, 1.0, 0)
    glEnable(GL_LINE_STIPPLE)
    glLineWidth(2.0)
    glLineStipple(3, 0xcccc)
    glDisable(GL_LINE_STIPPLE)
    glBegin(GL_LINES)
    glVertex3f(-0.8, 0.5, 1.0)
    glVertex3f(0.8, -0.5, 1.0)
    glEnd()

    glFlush()

def polygon_display():

    glClear(GL_COLOR_BUFFER_BIT)

    glPolygonMode(GL_FRONT, GL_FILL)
    glBegin(GL_POLYGON)
    glColor3f(0, 191, 255)
    glVertex3f(-0.8, -0.8, 0.0)
    glColor3f(255, 0, 255)
    glVertex3f(-0.2, -0.8, 0.0)
    glColor3f(255, 255, 0)
    glVertex3f(-0.5, -0.2, 0.0)
    glEnd()

    glPolygonMode(GL_FRONT, GL_FILL)
    glBegin(GL_LINE_STRIP)
    glColor3f(0, 191, 255)
    glVertex3f(0.8, 0.8, 0.0)
    glColor3f(255, 0, 255)
    glVertex3f(0.2, 0.8, 0.0)
    glColor3f(255, 255, 0)
    glVertex3f(0.5, 0.2, 0.0)
    glColor3f(255, 69, 0)
    glVertex3f(0.9, 0.5, 0.0)
    glEnd()

    glFlush()

def ex_questions1_display():

    glClear(GL_COLOR_BUFFER_BIT)

    glShadeModel(GL_FLAT)
    glBegin(GL_LINES)
    glColor3f(1.0, 0.0, 0.0)
    glVertex2f(0.0, 0.5)
    glColor3f(0.0, 0.0, 1.0)
    glVertex2f(0.5, -0.5)
    glEnd()

    glFlush()

def ex_questions2_display():

    glClear(GL_COLOR_BUFFER_BIT)
    glShadeModel(GL_SMOOTH)
    glBegin(GL_QUADS)
    glColor3f(1.0, 0.0, 0.0)
    glVertex2f(-0.5, -0.5)
    glColor3f(0.0, 1.0, 0.0)
    glVertex2f(-0.5, 0.5)
    glColor3f(0.0, 0.0, 1.0)
    glVertex2f(0.5, 0.5)
    glColor3f(1.0, 1.0, 0.0)
    glVertex2f(0.5, -0.5)
    glEnd()

    glFlush()

def ex_questions3_display():

    glClear(GL_COLOR_BUFFER_BIT)
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT)
    glColor3f(1.0, 1.0, 0.0)
    glBegin(GL_POLYGON)
    glVertex2f(-0.5, -0.5)
    glVertex2f(-0.5, 0.5)
    glVertex2f(0.5, 0.5)
    glVertex2f(0.5, -0.5)
    glEnd()

    glFlush()

def ex_questions4_display():

    glClear(GL_COLOR_BUFFER_BIT)

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
    glColor3f(1.0, 1.0, 0.0)
    glBegin(GL_POLYGON)
    glVertex2f(-0.5, -0.5)
    glEdgeFlag(GL_FALSE)
    glVertex2f(-0.5, 0.5)
    glEdgeFlag(GL_TRUE)
    glVertex2f(0.5, 0.5)
    glVertex2f(0.5, -0.5)
    glEnd()

    glFlush()

def triangle():

    glShadeModel(GL_SMOOTH)
    glBegin(GL_TRIANGLES)
    glVertex2f(20.0, 20.0)
    glVertex2f(80.0, 30.0)
    glVertex2f(50.0, 70.0)
    glEnd()

def transfer():

    glOrtho(-100, 100, -100 ,100, -100, 100)
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    glBegin(GL_LINES)
    glVertex2f(-100.0, 0)
    glVertex2f(100.0, 0.0)
    glEnd()
    glBegin(GL_LINES)
    glVertex2f(0.0, 100.0)
    glVertex2f(0.0, -100.0)
    glEnd()

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glColor3f(255, 0, 255)
    triangle()

    glRotatef(200.0, 0.0, 0.0, 1.0)
    glColor3f(255, 69, 0)
    triangle()

    glLoadIdentity()
    glColor3f(0, 255, 80)
    glTranslatef(-100, 0.0, 0.0)
    triangle()

    glFlush()

def init():

    glClearColor(0.0, 0.0, 0.0, 0.5)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    # glOrtho(-10, 10, -10, 10, -10, 10)

def main():

    glutInit()
    glutInitDisplayMode(GLUT_SINGLE or GLUT_RGBA)
    
    glutInitWindowPosition(300, 200)
    glutInitWindowSize(500, 500)
    glutCreateWindow('points')
    init()
    glutDisplayFunc(transfer)
    glutMainLoop()

if __name__ == "__main__":
    main()