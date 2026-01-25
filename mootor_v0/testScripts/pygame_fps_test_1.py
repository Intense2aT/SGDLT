# Example file showing a basic pygame "game loop"
import pygame
import random

# pygame setup
screen_dims = (1280, 720)

image = pygame.image.load('C:/Users/laur/Pictures/lerninPixelArt/simpleCandle1.jpg')
image_dims = 100
scaled_image = pygame.transform.scale(image, (image_dims, image_dims))
image_map_size = [25, 25]
image_data_array:list[tuple[int, int]] = []

j = 0
n = 0
appendable = [0, 0]
while j < image_map_size[1]:
    image_data_array.append((appendable[0], appendable[1]))
    while n < image_map_size[0]:
        appendable[0] += image_dims
        image_data_array.append((appendable[0], appendable[1]))
        n += 1
    n = 0
    appendable[0] = 0
    appendable[1] += image_dims
    j += 1

blit_seq = []
for i in image_data_array:
    blit_seq.append((scaled_image, i))

#print(image_data_array)
results:list[int] = []
repeatamount = 5
for i in range(repeatamount):
    pygame.init()
    screen = pygame.display.set_mode(screen_dims)
    #clock = pygame.time.Clock()
    pygame.display.set_caption("test_1")

    ticks = 50000
    i = 0
    startTime = pygame.time.get_ticks()

    while i <= ticks:
        # poll for events
        # pygame.QUIT event means the user clicked X to close your window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # fill the screen with a color to wipe away anything from last frame
        screen.fill("blue")

        # RENDER YOUR GAME HERE
        #for x in image_data_array:
            #screen.blit(scaled_image, (x[0], x[1]))
        
        screen.blits(blit_sequence=blit_seq, doreturn=0)

        # flip() the display to put your work on screen
        pygame.display.flip()

        i += 1

    endTime = pygame.time.get_ticks()

    avg_fps = ticks / ((endTime - startTime) / 1000)

    pygame.quit()

    #print(avg_fps)
    results.append(avg_fps)

print(results)
print(sum(results) / repeatamount)