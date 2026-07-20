#include "pch.h"
#include "Enemy.h"
#include "Engine.h" 

void Enemy::Update(float dt) {
    float thrust = 0.0f;
    //if (engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    //if (engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    //if (engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    //if (engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity{ 0,0 };
    velocity = velocity.Rotate(DegToRad * m_transform.rotation) * thrust;

    AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Enemy::Draw(const nu::Renderer& renderer) const
{
    Actor::Draw(renderer);
}