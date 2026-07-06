#include <SDL3/SDL.h>
#include <iostream>
#include "../Engine/Engine.h"
#include <vector>
using namespace nu;
using namespace std;


int main(int argc, char* argv[]) {

    //INITIALIZATION
    Renderer renderer;
    SDL_Init(SDL_INIT_VIDEO);
    renderer.CreateWindow(1280, 1024);
    renderer.CreateRenderer();
    Vector2 val(0.5f, 0.5f);

    vector<Vector2> v;


    for (int i = 0; i < 300; i++) {
        Vector2 vec(RandomFloat(1280), RandomFloat(1024));
        v.push_back(vec);
	}

    bool quit = false;
	//MAIN LOOP
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
               quit = true;
            }

        }
        //RENDER

        renderer.SetColor(0, 0, 0, 255);
        renderer.ClearScreen();
        int i = 0;
            // Draw rectangles - I have it only do one since the number of triangles was unspecified.
            for (i; i < 3; i++) {
                renderer.SetColor(RandomInt(256), RandomInt(256), RandomInt(256), 255);

                int width = rand() % 100 + 20;
                int height = rand() % 100 + 20;

                renderer.DrawRectangle(RandomInt(1280 - width), RandomInt(1024 - height), width, height );
            }


      
            i = 0;
            // Draw all lines
            for (i; i < 10; i++)
            {
                renderer.SetColor(RandomInt(256), RandomInt(256), RandomInt(256), 255);

                renderer.DrawLine(RandomInt(1280), RandomInt(1024), RandomInt(1280), RandomInt(1024));
                
            }

        
            i = 0;
            // Draw all points
            for (i; i < v.size(); i++)
            {
                renderer.SetColor(RandomInt(256), RandomInt(256), RandomInt(256), 255);

                v[i] = v[i] + val;
                renderer.DrawPoint(v[i].x, v[i].y);
            }
       

        renderer.PresentScreen();
    }
    return 0;
}