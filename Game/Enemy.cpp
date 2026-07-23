#include "Enemy.h"
#include "Player.h"
#include "../Engine/Engine.h" 

void Enemy::Update(float dt) {
	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();

		m_transform.rotation = rotation * RadToDeg;

		Vector2 forward{ 1,0 };
		forward = forward.Rotate(m_transform.rotation * DegToRad);
		AddVelocity(forward * m_speed * dt);

		float thrust = 0.0f;
		float rotate = 0.0f;

		forward = { 1.0f, 0.0f };
		Vector2 velocitiy = forward.Rotate(m_transform.rotation * DegToRad) * thrust;
		AddVelocity(velocitiy * dt);

		Actor::Update(dt);
	}
}
