from OpenGL.GL import *
from OpenGL.GLUT import *
import random

wh = 300
ww = 300
size = 5.0

def drawSquare(x, y):

	y=wh-y
	glColor3ub(random.randint(1, 256), random.randint(1, 256), random.randint(1, 256))
	glBegin(GL_POLYGON)
	glVertex2f(x+size, y+size)
	glVertex2f(x-size, y+size)
	glVertex2f(x-size, y-size)
	glVertex2f(x+size, y-size)
	glEnd()
	glFlush()


def myReshape(w, h):

	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

	glViewport(0,0,w, h)
	glClearColor (0.0, 0.0, 0.0, 1.0)
	glClear(GL_COLOR_BUFFER_BIT)
	glFlush()
   
	# /* set global size for use by drawing routine */

	ww = w
	wh = h


def myinit():
	#  /* set clear color to black */

    glClearColor(0.0, 0.0, 0.0, 1.0)


def mouse(btn, state, x, y):

	if btn==GLUT_RIGHT_BUTTON and state==GLUT_DOWN:
		exit(0)
	if btn == GLUT_LEFT_BUTTON and state == GLUT_UP:
		drawSquare(x, y)


def mouse_move(x, y):
    	
    drawSquare(x, y)


def keyboard(key, x, y):
    
	if GLUT_ACTIVE_ALT == glutGetModifiers():
    	# ord()转换成字符的ASCII码
		if ord(key) == ord('c'):
			exit(0)


def display():
	pass


def main():

	glutInit()
	glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
	glutInitWindowSize(300, 300)
	glutInitWindowPosition(0, 0)
	glutCreateWindow("square")
	glutDisplayFunc(display)
	glutReshapeFunc(myReshape)
	glutPassiveMotionFunc(mouse_move)
	glutMouseFunc(mouse)
	glutKeyboardFunc(keyboard)
	myinit()
	glutMainLoop()

main()