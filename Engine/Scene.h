#pragma once
#include "Actor.h"

#include <vector>
#include <string>
using namespace std;

namespace nu {
	class Actor;
	class Scene {
	public:

		void AddActor(Actor* actor);
		void RemoveAllActors();

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T = Actor>
		T* GetActorByName(const string& name);

		void SetGame(class Game* game) {
			m_game = game;
		}

		class Game* GetGame() { return m_game; }


	private:
		void UpdateCollisions();


	private:
		vector<Actor*> m_actors;
		vector<Actor*> m_pendingActors;

		class Game* m_game = nullptr;
	};
	template<typename T>
	inline T* Scene::GetActorByName(const string& name) {
		for (auto actor : m_actors) {
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name) return actorT;
		}
		return nullptr;
	}
}