from OpenGL.GL import *
from OpenGL.GLUT import *

# 全局变量记录颜色选择和形状选择
color_mode = 0
shape_mode = 0

def display():

    glClearColor(0.0, 0.0, 0.0, 1)
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()


def process_menu_events(value):

    global color_mode
    if value == 0:
        
        exit()
        
    if value == 1:
        
        glLoadIdentity()
        color_mode = 0
        draw_figure(shape_mode)


def draw_figure(value):
    ''' 根据选择的图元绘制相应的图形，并记录选择 '''
    global shape_mode
    shape_mode = value
    # 根据全局变量color_mode的值选择不同的颜色
    if color_mode == 1:
        glColor3ub(255, 48, 48)
    elif color_mode == 2:
        glColor3ub(255, 182, 193)
    elif color_mode == 3:
        glColor3ub(0, 191, 255)
    elif color_mode == 0:
        glColor3f(1.0, 1.0, 1.0)

    if value == 1:
        # 线段
        glClear(GL_COLOR_BUFFER_BIT)
        glLineWidth(5)
        glBegin(GL_LINES)
        glVertex2f(-0.5, 0.0)
        glVertex2f(0.5, 0.0)
        glEnd()

        glFlush()

    if value == 2:
        # 三角形
        glClear(GL_COLOR_BUFFER_BIT)
        glShadeModel(GL_SMOOTH)
        glBegin(GL_TRIANGLES)
        glVertex2f(-0.25, -0.144)
        glVertex2f(0.25, -0.144)
        glVertex2f(0.0, 0.289)
        glEnd()

        glFlush()

    if value == 3:
        # 矩形
        glClear(GL_COLOR_BUFFER_BIT)
        glShadeModel(GL_SMOOTH)
        glBegin(GL_POLYGON)
        glVertex2f(-0.5, -0.5)
        glVertex2f(-0.5, 0.5)
        glVertex2f(0.5, 0.5)
        glVertex2f(0.5, -0.5)
        glEnd()

        glFlush()


def figure_color_change(value):
    ''' 选择颜色，将值赋给全局变量color_mode，具体效果在draw_figure函数中体现 '''
    global color_mode
    color_mode = value
    draw_figure(shape_mode)


def figure_resize(value):
    ''' 改变图形大小 '''
    if value == 1:
        # 面积缩小为1/2
        glScaled(0.707, 0.707, 0.707)
        draw_figure(shape_mode)
        
    if value == 2:
        # 面积扩大为2倍
        glScaled(1.414, 1.414, 1.414)
        draw_figure(shape_mode)
        
        
def figure_move(value):
    ''' 平移图形 '''
    if value == 1:
        # 向左平移0,2单位
        glTranslatef(-0.2, 0.0, 0.0)
        draw_figure(shape_mode)
        
    if value == 2:
        # 向右平移0.2单位
        glTranslatef(0.2, 0.0, 0.0)
        draw_figure(shape_mode)

    if value == 3:
        # 向上平移0.2单位
        glTranslatef(0.0, 0.2, 0.0)
        draw_figure(shape_mode)
        
    if value == 4:
        # 向下平移0.2单位
        glTranslatef(0.0, -0.2, 0.0)
        draw_figure(shape_mode)
        

def figure_rotate(value):
    ''' 旋转图形 '''
    if value == 1:
        # 向左旋转30度
        glRotated(30, 0, 0, 1)
        draw_figure(shape_mode)
        
    if value == 2:
        # 向右旋转30度
        glRotated(-30, 0, 0, 1)
        draw_figure(shape_mode)
        

def creat_menu():
    ''' 创建菜单 '''
    # 子菜单：选择绘图形状
    shape_menu = glutCreateMenu(draw_figure)
    glutAddMenuEntry('LINE', 1)
    glutAddMenuEntry('TRANGLE', 2)
    glutAddMenuEntry('QUADS', 3)
    # 子菜单：选择颜色
    color_menu = glutCreateMenu(figure_color_change)
    glutAddMenuEntry('RED', 1)
    glutAddMenuEntry('PINK', 2)
    glutAddMenuEntry('BLUE', 3)
    # 子菜单：缩放
    resize_menu = glutCreateMenu(figure_resize)
    glutAddMenuEntry('half times big', 1)
    glutAddMenuEntry('twice big', 2)
    # 子菜单：平移
    move_menu = glutCreateMenu(figure_move)
    glutAddMenuEntry('0.2 unit left', 1)
    glutAddMenuEntry('0.2 unit right', 2)
    glutAddMenuEntry('0.2 unit up', 3)
    glutAddMenuEntry('0.2 unit down', 4)
    # 子菜单：旋转
    rotate_menu = glutCreateMenu(figure_rotate)
    glutAddMenuEntry('rotate 30 degrees left', 1)
    glutAddMenuEntry('rotate 30 degrees right', 2)
    # 创建主菜单
    main_menu = glutCreateMenu(process_menu_events)
    # 将子菜单与主菜单关联
    glutAddSubMenu('shape', shape_menu)
    glutAddSubMenu('color', color_menu)
    glutAddSubMenu('resize', resize_menu)
    glutAddSubMenu('move', move_menu)
    glutAddSubMenu('rotate', rotate_menu)
    glutAddMenuEntry('reset', 1)
    glutAddMenuEntry('exit', 0)
    # 菜单调出绑定到鼠标右键
    glutAttachMenu(GLUT_RIGHT_BUTTON)


def main():

    glutInit()
    glutInitDisplayMode(GLUT_SINGLE or GLUT_RGBA)
    glutInitWindowPosition(200, 200)
    glutInitWindowSize(500, 500)
    glutCreateWindow("Menu") 
    glutDisplayFunc(display)
    creat_menu()
    glutMainLoop()

main()