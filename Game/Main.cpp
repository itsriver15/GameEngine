#include <SDL3/SDL.h>
#include <fmod.hpp>
#include "../Engine/Engine.h"
#include "Assets.h"
#include "Player.h"
#include "Enemy.h"
#include <map>

using namespace nu;
using namespace std;

int main(int argc, char* argv[])
{
    /*map<string, int> students;
    students["Aiden"] = 16;
    students["Jack"] = 17;
    students["River"] = 15;

    cout << students["Aiden"] << endl;

    if (students.contains("Aiden")) {
        cout << "found" << endl;
    }*/



    //INITALIZE
    Engine::Get().Initialize();
    // create audio system

   
    //TEST FILESYSTEM
        // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

   
    Engine::Get().GetAudio().AddSound("test", "test.wav");


    Scene scene;
   

    PlayerDesc playerDesc;

    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f,512.0f }, 0.0f, 20.0f };
    playerDesc.velocity = Vector2{ 0,0 };
    playerDesc.damping = 4.0f;
    playerDesc.speed = 2000.0f;

    Player* player = new Player{playerDesc};
    scene.AddActor(player);
    Enemy* enemy = new Enemy{ 2000.0f, Transform{Vector2 {RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}}, assets::playerModel};
    for (int i = 0; i < 4; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = assets::playerModel;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.damping = 3.0f;
        enemyDesc.speed = RandomFloat(500.0f, 1000.0f);

        Enemy* enemy = new Enemy{ enemyDesc };
        scene.AddActor(enemy);
    }

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
        Engine::Get().Update();
        


        float dt = Engine::Get().GetTime().GetDeltaTime();

        //player.SetRotation(player.GetTransform().rotation + (Engine::Get().GetTime().GetDeltaTime() * 360.0f));

        
        scene.Update(dt);

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("test");
        }

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();

                if (v.Length() > 30.0f)
                {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            if (!points.empty()) {
                points.pop_back();
            }
        }

        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            Engine::Get().GetRenderer().SetColor(RandomFloat(), RandomFloat(), RandomFloat());

            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        scene.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    //SHUTDOWN

    Engine::Get().Shutdown();

    return 0;
}