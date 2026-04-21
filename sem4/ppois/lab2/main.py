import pygame
import sys

# Initialise Pygame
pygame.init()

# Set up the display window
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("My Top-Down Shooter")

# Main game loop
running = True
while running:
    # Check for events (like quitting the game)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the screen with a colour (here, black)
    screen.fill((0, 0, 0))

    pygame.display.flip()

pygame.quit()
sys.exit()
