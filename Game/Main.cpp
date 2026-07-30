#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <SDL3/SDL.h>

#include <fmod.hpp>

#include <iostream>
#include <vector>
#include <map>

using namespace nu;
using namespace std;

int main(int argc, char* argv[])

{
    SetWorkingDirectory("Assets");

    //INITALIZE
    Engine::Get().Initialize();
    SpaceGame game;
    game.Initialize();

    Scene scene;

  
    

    Font* font = new Font();
    font->Load("8-bit-limit/8bitlim.ttf", 20);
    // create audio system

    Text* text = new Text(font);
    text->Create(Engine::Get().GetRenderer(), "Hello World", Color{ 1.0f, 1.0f, 1.0f });

   
    Engine::Get().GetAudio().AddSound("test", "test.wav");

    
    for (int i = 0; i < 4; i++) {
        
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


        game.Update(dt);
        scene.Update(dt);

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) {
            Engine::Get().GetAudio().PlaySound("test");
        }

        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());
        scene.Draw(Engine::Get().GetRenderer());
        text->Draw(Engine::Get().GetRenderer(), 400.0f, 400.0f);
       // Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
       
    }
    //SHUTDOWN

    Engine::Get().Shutdown();

    return 0;
}