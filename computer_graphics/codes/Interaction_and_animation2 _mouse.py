from OpenGL.GL import *
from OpenGL.GLUT import *

# 全局变量记录形状选择
shape_mode = 0
# status为0时不绘图，为1时绘图
status = -1
vexs = []

def display():

    glClearColor(0.0, 0.0, 0.0, 1)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-250, 250, -250, 250, -1, 1)
    

def process_menu_events(value):
    ''' 处理部分菜单命令 '''
    global color_mode
    if value == 0:
        
        exit()
        
    if value == 1:
        
        glLoadIdentity()
        glOrtho(-250, 250, -250, 250, -1, 1)
        glColor3f(1.0, 1.0, 1.0)
        draw_figure(vexs)
        
        
def draw_point(x, y):
    ''' 绘制一个点 '''
    glPointSize(10)
    glBegin(GL_POINTS)
    glVertex2f(x, y)
    glEnd()
    glFlush()
    
    
def draw_figure(vexs):
    ''' 根据vexs列表和shape_mode绘制图形 '''
    glClear(GL_COLOR_BUFFER_BIT)
    if shape_mode == 1:
        
        glLineWidth(5)
        glBegin(GL_LINES)
        glVertex2f(vexs[0]['x'], vexs[0]['y'])
        glVertex2f(vexs[1]['x'], vexs[1]['y'])
        
    elif shape_mode == 2:
        
        glBegin(GL_TRIANGLES)
        glVertex2f(vexs[0]['x'], vexs[0]['y'])
        glVertex2f(vexs[1]['x'], vexs[1]['y'])
        glVertex2f(vexs[2]['x'], vexs[2]['y'])
        
    elif shape_mode == 3:
        
        glBegin(GL_QUADS)
        glVertex2f(vexs[0]['x'], vexs[0]['y'])
        glVertex2f(vexs[1]['x'], vexs[0]['y'])
        glVertex2f(vexs[1]['x'], vexs[1]['y'])
        glVertex2f(vexs[0]['x'], vexs[1]['y'])
    
    glEnd()
    glFlush()
        
        
def mouse_process(btn, state, x, y):
    ''' 根据鼠标左键确定图形的顶点 '''
    global vexs
    global status
    x = x - 250
    y = 250 - y
    if btn == GLUT_LEFT_BUTTON and state == GLUT_UP and status:
        
        draw_point(x, y)
        vex = {}
        vex['x'] = x
        vex['y'] = y
        vexs.append(vex)
        if len(vexs) == 2 and (shape_mode == 1 or shape_mode == 3):
            draw_figure(vexs)
            status = 0
            
        elif len(vexs) == 3 and shape_mode == 2:
            draw_figure(vexs)
            status = 0
            
            
def choose_shape_mode(value):
    ''' 选择绘图形状 '''
    global shape_mode
    shape_mode = value
    global status
    status = 1
    vexs.clear()
    glutMouseFunc(mouse_process)


def figure_color_change(value):
    ''' 选择颜色 '''
    global vexs
    if value == 1:
        glColor3ub(255, 48, 48)
        
    elif value == 2:
        glColor3ub(255, 182, 193)
        
    elif value == 3:
        glColor3ub(0, 191, 255)
        
    draw_figure(vexs)


def figure_resize(value):
    ''' 改变图形大小 '''
    if value == 1:
        # 面积缩小为1/2
        glScaled(0.5, 0.5, 0.0)
        draw_figure(vexs)
        
    if value == 2:
        # 面积扩大为2倍
        glScaled(2, 2, 0)
        draw_figure(vexs)
        
        
def figure_move(value):
    ''' 平移图形 '''
    if value == 1:
        # 向左平移0,2单位
        glTranslatef(-50, 0.0, 1.0)
        draw_figure(vexs)
        
    if value == 2:
        # 向右平移50单位
        glTranslatef(50, 0.0, 1.0)
        draw_figure(vexs)

    if value == 3:
        # 向上平移50单位
        glTranslatef(0.0, 50, 1.0)
        draw_figure(vexs)
        
    if value == 4:
        # 向下平移50单位
        glTranslatef(0.0, -50, 1.0)
        draw_figure(vexs)
        

def figure_rotate(value):
    ''' 旋转图形 '''
    if value == 1:
        # 向左旋转30度
        glRotated(30, 0, 0, 1)
        draw_figure(vexs)
        
    if value == 2:
        # 向右旋转30度
        glRotated(-30, 0, 0, 1)
        draw_figure(vexs)
        

def creat_menu():
    ''' 创建菜单 '''
    glClear(GL_COLOR_BUFFER_BIT)
    # 子菜单：选择绘图形状
    shape_menu = glutCreateMenu(choose_shape_mode)
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
    glutAddMenuEntry('50 unit left', 1)
    glutAddMenuEntry('50 unit right', 2)
    glutAddMenuEntry('50 unit up', 3)
    glutAddMenuEntry('50 unit down', 4)
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