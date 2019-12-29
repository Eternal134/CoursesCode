from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
import time

angle = 0.0
# axis1为x轴，2为y轴。3为z轴
axis = 0
# status为1时代表按下ctrl键
status = 0
vertices = np.array([[-1.0, -1.0, 1.0],[-1.0,1.0,1.0],
			[1.0,1.0,1.0], [1.0,-1.0,1.0],[-1.0,-1.0,-1.0],     
			[-1.0,1.0,-1.0], [1.0,1.0,-1.0], [1.0,-1.0,-1.0]])
# 颜色数组
colors = np.array([[0.0,0.0,0.0], [1.0,0.0,0.0], 
	[1.0,1.0,0.0],[0.0,1.0,0.0], [0.0,0.0,1.0],
	[1.0,0.0,1.0], [1.0,1.0,1.0],[0.0,1.0,1.0]])


def polygon(a, b, c , d):
	''' 绘制正方体的一个面 '''
	glBegin(GL_QUADS)
	glColor3dv(colors[a])
	glVertex3dv(vertices[a])
	glColor3dv(colors[b])
	glVertex3dv(vertices[b])
	glColor3dv(colors[c])
	glVertex3dv(vertices[c])
	glColor3dv(colors[d])
	glVertex3dv(vertices[d])
	glEnd()
																										

def colorcube():
	''' 绘制正方体的六个面 '''
	polygon(0,3,2,1)
	polygon(2,3,7,6)
	polygon(0,4,7,3)
	polygon(1,2,6,5)
	polygon(4,5,6,7)
	polygon(0,1,5,4)


def display():

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    # 定义摄像机位置
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    if axis == 1:
        glRotatef(angle, 1.0, 0.0, 0.0)
    elif axis == 2:
        glRotatef(angle, 0.0, 1.0, 0.0)
    elif axis == 3:
        glRotatef(angle, 0.0, 0.0, 1.0)
    # 绘图
    colorcube()
    # 交换缓存区内容
    glutSwapBuffers()


def myReshape(w, h):

	glViewport(0, 0, w, h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	if w <= h:
		glOrtho(-2.0, 2.0, -2.0 * h / w,
			2.0 * h / w, -10.0, 10.0)
	else:
		glOrtho(-2.0 *  w / h,
			2.0 *  w / h, -2.0, 2.0, -10.0, 10.0)

	glMatrixMode(GL_MODELVIEW)
 
 
def rotate():
     
    global angle
    
    angle += 10.0
    if angle > 360:
        angle = angle -360
    time.sleep(0.3)
    glutPostRedisplay()

 
def mouse(button, state, x, y):
     
    global axis
    global status
    
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        axis = 1
        
    if glutGetModifiers() == GLUT_ACTIVE_ALT and button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        axis = 2
        
    if button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        axis = 3
        
    glutIdleFunc(rotate)
    
    if (button == GLUT_LEFT_BUTTON or button == GLUT_RIGHT_BUTTON) and state == GLUT_UP:
        glutIdleFunc(None)


def main():

    glutInit()

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(500, 500)
    glutCreateWindow("colorcube")
    glClearColor(0.0,0.0,0.0,0.0)
    # 设置明暗处理模式
    glShadeModel(GL_SMOOTH)
    # 注册当前窗口的形状变化回调函数
    glutReshapeFunc(myReshape)
    glutDisplayFunc(display)
    glutMouseFunc(mouse)
    glutMainLoop()

main()