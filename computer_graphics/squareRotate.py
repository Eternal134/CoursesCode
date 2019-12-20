from OpenGL.GL import *
from OpenGL.GLUT import *
from math import *

theta = 0.0

DEGREES_TO_RADIANS = 3.14159 / 180.0


def display():

    glClear(GL_COLOR_BUFFER_BIT)
    glBegin(GL_POLYGON)
    glVertex2f(cos(theta * DEGREES_TO_RADIANS),
               sin(theta * DEGREES_TO_RADIANS))
    glVertex2f(cos(pi / 3 + theta * DEGREES_TO_RADIANS),
               sin(pi / 3 + theta * DEGREES_TO_RADIANS))
    glVertex2f(cos(2 * pi / 3 + theta * DEGREES_TO_RADIANS),
               sin(2 * pi / 3 + theta * DEGREES_TO_RADIANS))
    glVertex2f(cos(2 * pi / 3 + theta * DEGREES_TO_RADIANS),
               sin(2 * pi / 3 + theta * DEGREES_TO_RADIANS))
    glVertex2f(-cos(theta * DEGREES_TO_RADIANS),
               -sin(theta * DEGREES_TO_RADIANS))
    glVertex2f(cos(-2 * pi / 3 + theta * DEGREES_TO_RADIANS),
               sin(-2 * pi / 3 + theta * DEGREES_TO_RADIANS))
    glVertex2f(cos( -1 * pi / 3 + theta * DEGREES_TO_RADIANS),
               sin( -1 * pi / 3 + theta * DEGREES_TO_RADIANS))
    glEnd()
    glutSwapBuffers()


def idle():

    global theta
    theta += 2.0
    if theta > 360.0:
        theta -= 360.0
    glutPostRedisplay()


def myinit():

    glClearColor(0.0, 0.0, 0.0, 1.0)
    glColor3f(1.0, 1.0, 1.0)
    glShadeModel(GL_FLAT)


def mouse(btn, state, x, y):

    if btn == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        glutIdleFunc(idle)
    if glutGetModifiers(
    ) == GLUT_ACTIVE_CTRL and btn == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        glutIdleFunc(NULL)


def mykey(key, x, y):

    if (key == 'Q' or key == 'q'):
        exit(0)


def myReshape(w, h):

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if w <= h:
        glOrtho(-2.0, 2.0, -2.0 * h / w, 2.0 * h / w, -1.0, 1.0)
    else:
        glOrtho(-2.0 * w / h, 2.0 * w / h, -2.0, 2.0, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def main():

    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE or GLUT_RGB)
    glutInitWindowPosition(500, 0)
    glutCreateWindow("double buffered")
    myinit()
    glutDisplayFunc(display)
    glutReshapeFunc(myReshape)
    glutIdleFunc(idle)
    glutMouseFunc(mouse)
    glutKeyboardFunc(mykey)
    glutMainLoop()


main()