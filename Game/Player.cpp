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

    //fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BulletDesc desc;
        desc.name = "PlayerBullet";
        desc.tag = "PlayerBullet";
        desc.model = bulletModel;
        desc.transform = m_transform;
        desc.speed = 100.0f;
        desc.lifespan = 2.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    };

    nu::Particle particle;
particle.position = m_transform.position;
particle.color = { 1.0f, 1.0f, 1.0f };
particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

nu::Engine::Get().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
    if (other->GetName() == "Enemy") {
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}
