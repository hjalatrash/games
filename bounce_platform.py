# https://www.pygame.org/docs/
# https://replit.com/talk/learn/A-Starter-Guide-to-Pygame/11741

import pygame, sys
from pygame.locals import QUIT

# constants
FPS = 60
DT = 1/FPS
STEP_SIZE = 100

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

SQUARE_WIDTH = 16
BORDER_WIDTH = 8

X_MAX = 60
Y_MAX = 30

# initialize screen
pygame.init()
screen = pygame.display.set_mode(((X_MAX+1)*SQUARE_WIDTH, (Y_MAX+1)*SQUARE_WIDTH))
pygame.display.set_caption('Murad\'s game')
screen.fill('black')
clock = pygame.time.Clock()


# initialize values
# x = int(24)
# y = int(63)

pad_size = 7

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()


    mouse_x, mouse_y = pygame.mouse.get_pos()
    x = mouse_x/SQUARE_WIDTH
    y = Y_MAX #mouse_y/SQUARE_WIDTH

    # keys = pygame.key.get_pressed()
    # if keys[pygame.K_UP]:
    #     if(y>0): y -= 1
    # if keys[pygame.K_DOWN]:
    #     if(y<Y_MAX): y += 1
    # if keys[pygame.K_LEFT]:
    #     if(x>0): x -= 1
    # if keys[pygame.K_RIGHT]:
    #     if(x<X_MAX): x += 1


    screen.fill('black')

    for i in range(int(x-pad_size/2), int(x+pad_size/2)):
        pygame.draw.rect(screen, RED, (i*SQUARE_WIDTH,y*SQUARE_WIDTH,SQUARE_WIDTH-1,SQUARE_WIDTH-1), width=BORDER_WIDTH)


    pygame.display.update()
    clock.tick(FPS)
