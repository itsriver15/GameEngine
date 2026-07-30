#include "../Engine/Engine.h"
#include "SpaceGame.h"
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
 
        //particle system
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        nu::Particle particle;
        particle.position = m_transform.position;
        particle.color = { 1.0f, 1.0f, 1.0f };
        particle.lifespan = RandomFloat(0.5f, 1.5f);
        particle.velocity = { RandomFloat(-200.0f, 200.0f), RandomFloat(-200.0f, 200.0f) };

   
        Engine::Get().GetPS().AddParticle(particle);
    }

    //fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BulletDesc desc;
        desc.name = "PlayerBullet";
        desc.tag = "PlayerBullet";
        desc.model = bulletModel;
        desc.transform = Transform{ m_transform.position, m_transform.rotation, 5.0f };
        desc.speed = 1000.0f;
        desc.lifespan = 3.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    };

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
    if (other->GetName() == "Enemy") {
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}
