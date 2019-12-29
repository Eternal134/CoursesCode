from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
# 顶点数组
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


def main():

	glutInit()

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
	glutInitWindowSize(500, 500)
	glutCreateWindow("colorcube")
	glClearColor(0.0,0.0,0.0,0.0)
	# 设置明暗处理模式
	glShadeModel(GL_FLAT)
 	# 注册当前窗口的形状变化回调函数
	glutReshapeFunc(myReshape)
	glutDisplayFunc(display)
	glutMainLoop()

main()
