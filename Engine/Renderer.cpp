#include "pch.h"
#include "Renderer.h"
#include <iostream>
#include <string>
#include <SDL3/SDL.h>

void Renderer::CreateWindow(int width, int height)
{
	window = SDL_CreateWindow("SDL3 Project", width, height, 0);

	if (window == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}

void Renderer::CreateRenderer()
{
	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
	{
		std::cerr << "SDL_CreateRenderer Error: "
			<< SDL_GetError() << std::endl;

		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}


void Renderer::ClearScreen() {
	SDL_RenderClear(renderer);
}

void Renderer::SetColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::DrawRectangle(float x, float y, float sideA, float sideB)
{
	SDL_FRect rect{ x, y, sideA, sideB };
	SDL_RenderFillRect(renderer, &rect);
}

// Overloaded function to draw a square
void Renderer::DrawRectangle(float x, float y, float side)
{
	SDL_FRect rect{ x, y, side, side };
	SDL_RenderFillRect(renderer, &rect);
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
	SDL_RenderLine(renderer, x1, y1, x2, y2);
}

void Renderer::DrawPoint(float x, float y)
{
	SDL_RenderPoint(renderer, x, y);
}
void Renderer::PresentScreen()
{
	SDL_RenderPresent(renderer);
}	

Renderer::~Renderer() {
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}
