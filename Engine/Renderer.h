#pragma once
#include <SDL3/SDL.h>
class Renderer
{
public:
	void CreateWindow(int, int);
	void CreateRenderer();
	void ClearScreen();
	void SetColor(int, int, int, int);
	void DrawRectangle(float, float, float, float);
	void DrawRectangle(float, float, float);
	void DrawLine(float, float, float, float);
	void DrawPoint(float, float);
	void PresentScreen();
	~Renderer();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
};