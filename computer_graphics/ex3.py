from OpenGL.GL import *
from OpenGL.GLUT import *

wh = 500
ww = 500
size = 5.0
vexs = []

def clear():

    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT)

def drawSquare():
    # 根据vexs数组绘制矩形
    vexs[1] = wh - vexs[1]
    vexs[3] = wh - vexs[3]
    glBegin(GL_QUADS)
    glColor3ub(255, 250, 134)
    glVertex2f(vexs[0], vexs[1])
    glColor3ub(250, 190, 155)
    glVertex2f(vexs[0], vexs[3])
    glColor3ub(241, 120, 180)
    glVertex2f(vexs[2], vexs[3])
    glColor3ub(246, 188, 154)
    glVertex2f(vexs[2], vexs[1])
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


def myinit():
	#  /* set clear color to black */

    glClearColor(0.0, 0.0, 0.0, 1.0)


def draw_point(x, y):
    # 绘制一个点
    y = wh - y
    glPointSize(10)
    glBegin(GL_POINTS)
    glColor3f(1, 1, 1)
    glVertex2f(x, y)
    glEnd()
    glFlush()


def mouse(btn, state, x, y):

    if btn==GLUT_RIGHT_BUTTON and state==GLUT_DOWN:
        exit(0)
    if btn == GLUT_LEFT_BUTTON and state == GLUT_UP:
        ''' 当单击鼠标左键，先绘制一个点，再将鼠标位置的坐标添加到vexs列表中 '''
        draw_point(x, y)
        vexs.append(x)
        vexs.append(y)
        if len(vexs) == 4:
            ''' 当列表的长度为4时，代表这时已保存了两对点，清空屏幕再根据两对点的坐标绘制矩形 '''
            clear()
            drawSquare()
            vexs.clear()


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
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    glutCreateWindow("square")
    glutDisplayFunc(display)
    glutReshapeFunc(myReshape)
    glutMouseFunc(mouse)
    # 实现Alt + c关闭程序
    glutKeyboardFunc(keyboard)
    if len(vexs) == 4:
        glutPostRedisplay(drawSquare)
    myinit()
    glutMainLoop()

main()