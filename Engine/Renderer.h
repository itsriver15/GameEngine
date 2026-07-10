#pragma once
#include <SDL3/SDL.h>
class Renderer
{
public:
	void Initialize(int, int);
	void Shutdown();

	void Clear() const;
	void Present() const;

	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
	void SetColor(float r, float g, float b, float = 1.0f) const;


	void DrawPoint(float x, float y) const;
	void DrawLine(float x1, float y1, float x2, float y2) const;
	void DrawFillRect(float x, float y, float w, float h) const;
	void DrawRect(float x, float y, float w, float h) const;
	
	
	
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
};