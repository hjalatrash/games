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

# initialize screen
pygame.init()
screen = pygame.display.set_mode((1024, 768))
pygame.display.set_caption('Murad\'s game')
screen.fill('black')
clock = pygame.time.Clock()

rocket = pygame.image.load("rocket.png")


# initialize values
x = 0
y = 20

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()
    if keys[pygame.K_UP]:
        y -= STEP_SIZE * DT
    if keys[pygame.K_DOWN]:
        y += STEP_SIZE * DT
    if keys[pygame.K_LEFT]:
        x -= STEP_SIZE * DT
    if keys[pygame.K_RIGHT]:
        x += STEP_SIZE * DT



    screen.fill('black')
    screen.blit(rocket, (x,y))
    #keys = pygame.key.get_pressed()
    #print(key)

    for i in range(0,64):
        for j in range(0, 48):
            pygame.draw.rect(screen, GREEN, (i*SQUARE_WIDTH,j*SQUARE_WIDTH,SQUARE_WIDTH-1,SQUARE_WIDTH-1), width=BORDER_WIDTH)

    # x += 1
    # if(x>63):
    #     x -=63
    # pygame.draw.rect(screen, RED, (x*SQUARE_WIDTH,y*SQUARE_WIDTH,SQUARE_WIDTH-1,SQUARE_WIDTH-1), width=BORDER_WIDTH)


    pygame.display.update()
    clock.tick(FPS)
