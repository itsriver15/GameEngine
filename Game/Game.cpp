#include <SDL3/SDL.h>
#include "../Engine/Engine.h"
using namespace nu;
using namespace std;


int main(int argc, char* argv[]) {

    //INITIALIZATION
    Renderer renderer;
    renderer.Initialize(1280, 1024);

    Input input;
    input.Initialize();

    Time time;

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity(0.0f, 0.0f);
    float speed = 800.0f;

    Transform transform{ position, 0.0f, 50.0f };

    Actor player{ transform };
    
    vector<Vector2> points;

	//MAIN LOOP
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
               quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }

        }
        //ENGINE
        
        input.Update();
        time.Tick();

       

        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) cout << "released\n";

        //if (input.GetButtonPressed(Input::MouseButton::Left)) cout << "button pressed\n";
        //if (input.GetButtonDown(Input::MouseButton::Left)) cout << "button down\n";
        //if (input.GetButtonReleased(Input::MouseButton::Left)) cout << "button released\n";
        
        /*if (input.GetButtonPressed(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }*/


        if (input.GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());
            }
            else {
                Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 30.0f) {
                    points.push_back(input.GetMousePosition());
                }
            }
        }

        //undo points

        if (input.GetButtonPressed(Input::MouseButton::Right)) {
            
            if(!points.empty()) points.pop_back();
        }



        Vector2 force(0.0f, 0.0f); 

        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;


        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

       /* velocity += (force * time.GetDeltaTime());

        position += (velocity * time.GetDeltaTime());

        position.x = Wrap(0.0f, 1280.0f, position.x);
        position.y = Wrap(0.0f, 1024.0f, position.y);*/


        //RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();
        // unsigned int (0) - 1 = MAX_NUMBER
        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }
        //character
        player.Draw(renderer);
        /*renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);*/

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}