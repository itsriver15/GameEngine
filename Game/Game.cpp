#include <SDL3/SDL.h>
#include "../Engine/Engine.h"

using namespace nu;
using namespace std;

int main(int argc, char* argv[])
{
    
    engine.Initialize();

    Mesh mesh{ {{0,1},{2,0},{0,-1},{.5,0},{0,1}}, {1.0f,1.0f,1.0f} };

    Transform transform{{640.0f,512.0f}, 0.0f, 50.0f };

    float speed = 800.0f;

    Player player{ speed, transform, vector<Mesh>{mesh} };

    vector<Vector2> points;

    bool quit = false;

    while (!quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                quit = true;

            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.scancode == SDL_SCANCODE_ESCAPE)
                quit = true;
        }

        engine.Update();

        player.SetRotation(player.GetTransform().rotation + (engine.GetTime().GetDeltaTime() * 360.0f));

        
        player.Update(engine.GetTime().GetDeltaTime());

        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();

                if (v.Length() > 30.0f)
                {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }

        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            if (!points.empty()) {
                points.pop_back();
            }
        }

        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            engine.GetRenderer().SetColor(RandomFloat(), RandomFloat(), RandomFloat());

            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        player.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    }

    engine.Shutdown();

    return 0;
}