#include <SDL3/SDL.h>
#include "../Engine/Engine.h"

using namespace nu;
using namespace std;

int main(int argc, char* argv[])
{
    //INITALIZE
    engine.Initialize();

    Mesh mesh1{ {{ 0, -1 }, { 1, 0 }, { 0, 1 }, { 3, 0 }, { 0, -1 } }, { 0.694f, 0.0f, 1.0f } };
    Mesh mesh2{ {{ 0, -1 }, { -1, -2 }, { -3, 0 }, { -1, 2 }, { 0, 1 }}, {1.0f, 0.902f, 0.38f} };
    Mesh mesh3{ {{ -1, -1 }, { 0, 0 }, { -1, 1 }, { -2, 0 }, { -1, -1 }}, {0.53f, 1.0f, 0.7f} };
    Model model = vector<Mesh>{ mesh1, mesh2, mesh3};

    Scene scene;
   

    PlayerDesc playerDesc;

    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{ 640.0f,512.0f }, 0.0f, 50.0f };
    playerDesc.velocity = Vector2{ 0,0 };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{playerDesc};
    scene.AddActor(player);
    /*Enemy* enemy = new Enemy{ 2000.0f, Transform{Vector2 {RandomFloat((float)engine.GetRenderer().GetWidth()), RandomFloat((float)engine.GetRenderer().GetHeight())}}, model};
    for (int i = 0; i < 4; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = model;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)engine.GetRenderer().GetWidth()), RandomFloat((float)nu::engine.GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.speed = 2000.0f;
        scene.AddActor(enemy);
    }*/

    vector<Vector2> points;

    bool quit = false;
    //MAIN LOOP
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
        //UPDATE
        engine.Update();

        float dt = engine.GetTime().GetDeltaTime();

        //player.SetRotation(player.GetTransform().rotation + (engine.GetTime().GetDeltaTime() * 360.0f));

        
        scene.Update(dt);

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

        scene.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    }
    //SHUTDOWN

    engine.Shutdown();

    return 0;
}