#pragma once
#include "pch.h"
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "MathUtils.h"
#include "Transform.h"
#include "Actor.h"
#include "Player.h"
#include <iostream>
#include <vector>

namespace nu {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }

		Time& GetTime() { return m_time; }
	private:
		Input m_input;
		Renderer m_renderer;

		Time m_time;
	};
	extern Engine engine;
}


