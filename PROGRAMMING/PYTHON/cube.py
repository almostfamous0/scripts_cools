#!/usr/bin/env python3
try:
    import pygame
    from pygame.locals import *
    from OpenGL.GL import *
    from OpenGL.GLU import *
except:
    from os import system as sys
    print('\x1b[31m [!!!] VOCE NAO POSSUI ALGUMA DAS BIBLIOTECAS NECESSARIAS!')
    sys('pip3 install pygame && pip3 install pyOpenGL')
    exit(1)

import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

'''
#   CUBO EM SI
verticies = (
    (1, -1, -1),
    (-1, 1, -1),
    (-1, -1, -1),
    (1, 1, 1),
    (1, 1, -1),
    (-1, -1, 1),
    (1, -1, 1),
    (-1, 1, 1)
    )

'''

'''
#   FIGURA MOH DAHORA
verticies = (
    (-1, -1, -1),
    (1, -1, -1),
    (-1, 1, -1),
    (-1, 1, 1),
    (1, -1, 1),
    (1, 1, 1),
    (1, 1, -1),
    (-1, -1, 1)
)
'''

verticies = (
    (-1, -1, -1),
    (1, -1, -1),
    (-1, 1, -1),
    (1, 1, -1),
    (-1, -1, 1),
    (1, -1, 1),
    (-1, 1, 1),
    (1, 1, 1)
)

edges = (
    (0, 1),
    (0, 2),
    (0, 4),
    (1, 3),
    (1, 5),
    (2, 3),
    (2, 6),
    (3, 7),
    (4, 5),
    (4, 6),
    (5, 7),
    (6, 7)
    )


def Cube():
    glBegin(GL_LINES)
    #glColor3f(1.0, 0.0, 0.0)  # Set color to red (example: RGB(255, 0, 0))
    glColor3f(0.0, 1.0, 0.0)  # Set color to red (example: RGB(255, 0, 0))
    for edge in edges:
        for vertex in edge:
            glVertex3fv(verticies[vertex])
    glEnd()


def main():
    pygame.init()
    display = (850,700)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glTranslatef(0.0,0.0, -5)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        glRotatef(1, 3, 1, 1)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        Cube()
        pygame.display.flip()
        pygame.time.wait(10)

main()
