#include <SDL3/SDL.h>
#include <iostream>
#include "../Engine/Renderer.h"

// I couldn't figure out how to make it not clear every frame, so I just made it so that you can press enter to go to the next stage and see the next set of shapes.

// That means that it looks like there are a lot more shapes then there actually are in each stage, but my for loop demonstrates that the numbers are correct :]
int main(int argc, char* argv[]) {
    int stage = 0;
    Renderer renderer;
    SDL_Init(SDL_INIT_VIDEO);
    renderer.CreateWindow(1280, 1024);
    renderer.CreateRenderer();

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
               quit = true;
            }

            if (e.type == SDL_EVENT_KEY_DOWN &&
                e.key.key == SDLK_RETURN)
            {
                stage++;
                
            }
        }


        renderer.SetColor(0, 0, 0, 255);
        renderer.ClearScreen();
        int i = 0;
        if (stage == 0)
        {
            // Draw rectangles - I have it only do one since the number of triangles was unspecified.
                renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);

                int width = rand() % 100 + 20;
                int height = rand() % 100 + 20;

                renderer.DrawRectangle(rand() % (1280 - width), rand() % (1024 - height), width, height);
        }
        else if (stage == 1)
        {
            i = 0;
            // Draw all lines
            for (i; i < 10; i++)
            {
                renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);

                renderer.DrawLine(rand() % 1280, rand() % 1024, rand() % 1280, rand() % 1024);
            }
        }
        else if (stage == 2)
        {
            i = 0;
            // Draw all points
            for (i; i < 20; i++)
            {
                renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);

                renderer.DrawPoint(rand() % 1280, rand() % 1024);
            }
        }
        else {
            break;
        }

        renderer.PresentScreen();
    }
    return 0;
}