#pragma once
#include "Food.h"
const int tail_max = 255;

struct Snake {
	V2 pos;
	V2 vel;
	V2 acc;

	V2 tail[tail_max];
	int tail_start, tail_end;
	int tail_len = 20;
	int score = 0;

	uint32_t accumulator;
	Window* window;

	int* r;
	int* g;
	int* b;

	void update(uint32_t delta_time, struct Food& food)
	{
		
		accumulator += delta_time;
		if (accumulator > 100 - (tail_len)) {
			accumulator = 0;

			vel = acc;
			
			tail[tail_end % tail_max] = pos;

			tail_start++;
			tail_end++;

			pos.x += vel.x;
			pos.y += vel.y;

			pos.x = (pos.x + 50) % 50;
			pos.y = (pos.y + 50) % 50;

			if (pos.x == food.x && pos.y == food.y) {
				tail_len += 1;
				tail_start -= 1;
				food.move();
				if (score < 50 * tail_len)
					score =50* tail_len;
				
				
				
				std::cout << "Your score is: " << score << std::endl;
				

				
			}

			for (int i = 0; i < tail_len; i++) {
				V2& tail_pos = tail[(tail_start + i) % tail_max];
				if (tail_pos.x == pos.x && tail_pos.y == pos.y) {
					
					tail_len = 0;
					tail_start = tail_end;
				}
			}
		}
	}

	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, *r, *g, *b, 255);

		for (int i = 0; i < tail_len; i++) {
			V2& tail_pos = tail[(tail_start + i) % tail_max];
			SDL_Rect r{ 16 * tail_pos.x, 16 * tail_pos.y, 16, 16 };
			SDL_RenderFillRect(renderer, &r);
		}

		SDL_Rect r{ 16 * pos.x, 16 * pos.y, 16, 16 };
		SDL_RenderFillRect(renderer, &r);
	}
};



