#pragma once

#include <cstdlib>

#include <sstream>
#include "Window.h"
#include <vector>
// Things to do:
//   * Make food not spawn in snake
//   * Keep track of score
//   * Walls? Multiple foods?
//   * difficulty curve

struct Food {
	int x, y;
	int Cr, Cg, Cb;
	std::vector <char> mapa;
	void move() {
		x = rand() % (800 / 16);
		y = rand() % (800 / 16);
		for (size_t i = 0; i < mapa.size(); i++)
		{
			if (mapa[i] == '1') {
				if ((int)(i % 50) == x && (int)(i / 50) == y)
				{
					move();
				}

			}
		}


	}

	void draw(SDL_Renderer* renderer) {
		SDL_Rect r{ 16 * x, 16 * y, 16, 16 };
		SDL_SetRenderDrawColor(renderer, Cr, Cg, Cb, 255);
		SDL_RenderFillRect(renderer, &r);
	}
};

struct V2 {
	int x, y;
};
