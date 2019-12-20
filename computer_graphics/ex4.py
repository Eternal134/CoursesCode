from OpenGL.GL import *
from OpenGL.GLUT import *

size = 1
color_mode = 0
shape_mode = 0

def display():

    glClearColor(0.0, 0.0, 0.0, 1)
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()


def process_menu_events(value):

    if value == 0:
        exit()


def draw_figure(value):

    global shape_mode
    shape_mode = value
    if color_mode == 1:
        glColor3ub(255, 48, 48)
    elif color_mode == 2:
        glColor3ub(255, 182, 193)
    elif color_mode == 3:
        glColor3ub(0, 191, 255)

    if value == 1:

        glClear(GL_COLOR_BUFFER_BIT)
        glLineWidth(5)
        glBegin(GL_LINES)
        glVertex2f(-0.5, 0.0)
        glVertex2f(0.5, 0.0)
        glEnd()

        glFlush()

    if value == 2:

        glClear(GL_COLOR_BUFFER_BIT)
        glShadeModel(GL_SMOOTH)
        glBegin(GL_TRIANGLES)
        glVertex2f(-0.25, -0.144)
        glVertex2f(0.25, -0.144)
        glVertex2f(0.0, 0.289)
        glEnd()

        glFlush()

    if value == 3:

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

    global color_mode
    color_mode = value
    draw_figure(shape_mode)


def figure_resize(value):

    pass


def creat_menu():

    shape_menu = glutCreateMenu(draw_figure)
    glutAddMenuEntry('LINE', 1)
    glutAddMenuEntry('TRANGLE', 2)
    glutAddMenuEntry('QUADS', 3)

    color_menu = glutCreateMenu(figure_color_change)
    glutAddMenuEntry('RED', 1)
    glutAddMenuEntry('PINK', 2)
    glutAddMenuEntry('BLUE', 3)

    resize_menu = glutCreateMenu(figure_resize)
    glutAddMenuEntry('half times big', 1)
    glutAddMenuEntry('twice big', 2)

    main_menu = glutCreateMenu(process_menu_events)
    
    glutAddSubMenu('shape', shape_menu)
    glutAddSubMenu('color', color_menu)
    glutAddSubMenu('resize', resize_menu)
    glutAddMenuEntry('move', 3)
    glutAddMenuEntry('rotate', 4)
    glutAddMenuEntry('exit', 0)
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