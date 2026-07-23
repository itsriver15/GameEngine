#include "Bullet.h"
#include "../Engine/MathUtils.h"

void Bullet::Update(float dt) {

	nu::Vector2 forward{ 1.0f,1.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad);

	SetVelocity(velocity);


	Actor::Update(dt);
}