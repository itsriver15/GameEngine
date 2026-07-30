#include "pch.h"
#include "ParticleSystem.h"

namespace nu {
	bool ParticleSystem::Initialize(size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particle
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (particle.active == false) continue;

			// reduce particle.lifespan by subtracting delta time
			particle.lifespan -= dt;

			// set active if (particle.lifespan > 0);
			particle.active = particle.lifespan > 0;

			// update position with velocity (multiply by dt)
			// TODO: update position += with particle velocity * delta time
			GetFreeParticle();
		}
	}
	void ParticleSystem::Draw(const Renderer& renderer)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// set particle color and draw point at current position
				// TODO: set color with particle color
				// TODO: draw point with particle position
			}
		}
	}
	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			// TODO: dereference (*) free particle and set it to particle
			// set particle active
			// TODO: set free particle active to true
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			if (particle.active)
				return &particle;
		}

		// no free particles, return nullptr
		return nullptr;
	}
}