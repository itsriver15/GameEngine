#include "../Engine/Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "Player.h"
using namespace assets;

void Player::Update(float dt){
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1.0f,0.0f };
    nu::Vector2 velocity = forward.Rotate((DegToRad * m_transform.rotation)) * thrust;


    AddVelocity(velocity * dt);

    //fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BulletDesc desc;
        desc.name = "bullet";
        desc.tag = "bullet";
        desc.model = bulletModel;
        desc.transform = m_transform;
        desc.speed = 4000.0f;
        desc.lifespan = 2.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    };

    Actor::Update(dt);
}
