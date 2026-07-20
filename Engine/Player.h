#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc {
	float speed;
	int ammo;
};
class Player : public nu::Actor {

public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }{
		m_ammo = playerDesc.ammo;
		m_speed = playerDesc.speed;
	}
	Player(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {};
	Player(float speed, const nu::Transform& transform, const Model& model) : Actor{ transform, model }, m_speed{ speed } {};

	void Update(float dt) override;
	void Draw(const Renderer& renderer) const override;

private:
	int m_ammo = 0;
	float m_speed = 0.0f;
};