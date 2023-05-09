# https://www.pygame.org/docs/
# https://replit.com/talk/learn/A-Starter-Guide-to-Pygame/11741

import pygame, sys
from pygame.locals import QUIT

pygame.init()
screen = pygame.display.set_mode((400, 300))
pygame.display.set_caption('Murad\'s game')
clock = pygame.time.Clock()

screen.fill('black')
rocket = pygame.image.load("rocket.png")

i = 0

while True:
    i += 1
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    rocketposition = (i, i)
    screen.blit(rocket, rocketposition)
    #keys = pygame.key.get_pressed()
    #print(key)

    pygame.display.update()
    clock.tick(600)
