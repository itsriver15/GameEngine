
#include "pch.h"
#include "Engine.h"
#include "framework.h"
#include <iostream>

namespace nu {

	bool Engine::Initialize() {
		m_renderer.Initialize(1280, 1024);
		m_ps.Initialize();
		m_audio.Initialize();
		m_input.Initialize();
		

		return true;
	}
	void Engine::Shutdown() {
		m_input.Shutdown();
		m_audio.Shutdown();
		m_ps.Shutdown();
		m_renderer.Shutdown();
		
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
		m_ps.Update(m_time.GetDeltaTime());
		m_audio.Update();
		
	}
	
}
