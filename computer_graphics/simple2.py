from OpenGL.GL import *
from OpenGL.GLUT import *

def display():
	# 把窗口背景设置为当前颜色
	# glClear(GL_COLOR_BUFFER_BIT)
	# GL_POLYGON参数：绘制一个凸多边形
	glBegin(GL_POLYGON)
	''' 确定多边形顶点坐标 '''
	glVertex2f(-0.3, -0.5)
	glVertex2f(-0.5, 0.5)
	glVertex2f(0.5, 1)
	glVertex2f(0.5, -0.5)
	# 命令结束
	glEnd()
	# glClearColor(1.0, 0.5, 0.0, 0.5)
	# 立即执行前面的OpenGL命令
	glFlush()


def init():
	# 设置背景颜色RGBA
	glClearColor(1.0, 0.5, 0.0, 0.5)
	# 设置当前色(R, G, B)
	glColor3f(0.3, 0.7, 0.9)
	# 将当前矩阵设置为投影矩阵
	glMatrixMode(GL_PROJECTION)
	# 把矩阵设置为单位矩阵
	glLoadIdentity()
	# 设置视景体
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)

def main():
	# 初始化GLUT库
	glutInit()
	# 设置显示方式，GLUT_SINGLE表示使用单缓冲，GLUT_RGB表示使用RGB颜色
	glutInitDisplayMode (GLUT_SINGLE or GLUT_RGB)
	# 设置窗口大小
	glutInitWindowSize(300,300)
	# 设置窗口位置
	glutInitWindowPosition(100,200)
	# 设置窗口名称
	glutCreateWindow("simple")
	init()
	# 调用display绘图函数
	glutDisplayFunc(display)
	# 执行GLUT程序
	glutMainLoop()

main()