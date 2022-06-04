#pragma once
#include "Snake.h"

#include <string>
#include <fstream>
#include "DrawText.h"

using namespace std;







void MapLoader();
void Options();
void Menu();
void LeaderBoards();
void LoadFile(string, vector <char>*);

class Game {
public:
	static int SnakeR ;
	static int SnakeG ;
	static int SnakeB ;

	static int bgColR;
	static int bgColG;
	static int bgColB;

	static int FoodR ;
	static int FoodG ;
	static int FoodB ;

	static vector <int> vysledky;
	static vector <char> mapa;
};

vector <int> Game::vysledky = {};
vector <char> Game::mapa = {};
int Game::SnakeR = 0;
int Game::SnakeG = 128;
int Game::SnakeB = 128;

int Game::bgColR = 0;
int Game::bgColG = 255;
int Game::bgColB = 0;

int Game::FoodR = 0;
int Game::FoodG = 0;
int Game::FoodB = 255;

void drawLet(Window* window, char letter, int  x, int y, int r = 255, int g = 255, int b = 255) {


	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++)
		{

			if (MujText8na8[(int)letter][i] & (1 << (j)))
			{
				SDL_SetRenderDrawColor(window->_renderer, r, g, b, 255);
				SDL_Rect r{ x + j, y + i, 1, 1 };
				SDL_RenderFillRect(window->_renderer, &r);
			}


		}

	}

}
void drawSentence(Window* window, string sentence, int  x, int y, int r = 255, int g = 255, int b = 255) {

	for (int i = 0; i < sentence.size(); i++) {
		drawLet(window, sentence[i], x + 7 * i, y, r, g, b);
	}
}

void play_snake(int pozadiR = 0, int pozadiG = 0, int pozadiB = 0) {

	Window window("Snake", 800, 800);
	window.snake = true;
	SDL_Event e;

	bool running = true;
	Snake snake = {};
	snake.r = &Game::SnakeR;
	snake.g = &Game::SnakeG;
	snake.b = &Game::SnakeB;

	Food food = {};
	food.Cr = Game::FoodR;
	food.Cg = Game::FoodG;
	food.Cb = Game::FoodB;
	food.mapa = Game::mapa;

	food.move();

	uint32_t current_time = 0, previous_time, delta_time;

	while (running) {

		previous_time = current_time;
		current_time = SDL_GetTicks();
		delta_time = current_time - previous_time;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w: if (snake.vel.y != 1) snake.acc = { 0, -1 }; break;
				case SDLK_s: if (snake.vel.y != -1) snake.acc = { 0, 1 }; break;
				case SDLK_a: if (snake.vel.x != 1) snake.acc = { -1, 0 }; break;
				case SDLK_d: if (snake.vel.x != -1) snake.acc = { 1, 0 }; break;
				case SDLK_b:  Game::vysledky.push_back(snake.score); running = false; Menu();   window.~Window(); break;

				}
			}
		}





		snake.update(delta_time, food);

		SDL_SetRenderDrawColor(window._renderer, Game::bgColR, Game::bgColG, Game::bgColB, 255);
		SDL_RenderClear(window._renderer);
		for (size_t i = 0; i < Game::mapa.size(); i++)
		{
			if (Game::mapa[i] == '1') {
				//cout << "Ctverecek " << endl;
				SDL_Rect rect{ 16 * (int)(i % 50) , 16 * (int)(i / 50) , 16, 16 };
				SDL_SetRenderDrawColor(window._renderer, 0, 0, 0, 255);

				SDL_RenderFillRect(window._renderer, &rect);

				if ((int)(i % 50) == snake.pos.x && ((int)(i / 50)) == snake.pos.y) {
					cout << "Colision \r";

					snake.tail_len = 0;
					snake.tail_start = snake.tail_end;
				}


			}

		}
		snake.draw(window._renderer);
		food.draw(window._renderer);

		SDL_RenderPresent(window._renderer);
	}


}
void Menu() {
	Window window("Menu", 400, 300);
	window.play = play_snake;
	window.is_menu = true;
	window.option = Options;
	window.menu = Menu;
	window.leaderBoard = LeaderBoards;
	window.MapLoader = MapLoader;

	while (!window.isClosed()) {

		drawSentence(&window, "Main menu", 150, 30,255,0,0);
		//drawSentence(&window, "Ahoj", 50, 50);
		drawSentence(&window, "Play", 150, 100);
		drawSentence(&window, "Options", 150, 130);
		drawSentence(&window, "Leader boards", 150, 160);
		drawSentence(&window, "Map Loader", 150, 190);
		window.pollEvents();
		window.clear();
	}
}
void Options() {
	Window window("Option", 400, 300);
	window.is_option = true;
	window.menu = Menu;
	window.option = Options;
	window.play = play_snake;

	window.snakeR = &Game::SnakeR;
	window.snakeG = &Game::SnakeG;
	window.snakeB = &Game::SnakeB;

	window.bgR = &Game::bgColR;
	window.bgG = &Game::bgColG;
	window.bgB = &Game::bgColB;

	window.fR = &Game::FoodR;
	window.fG = &Game::FoodG;
	window.fB = &Game::FoodB;


	while (!window.isClosed()) {

		// red
		SDL_SetRenderDrawColor(window._renderer, 255, 0, 0, 255);
		SDL_Rect rR{ 50 , 50, 20, 20 };
		SDL_RenderFillRect(window._renderer, &rR);
		//green
		SDL_SetRenderDrawColor(window._renderer, 0, 255, 0, 255);
		SDL_Rect rG{ 50 , 100, 20, 20 };
		SDL_RenderFillRect(window._renderer, &rG);
		//blue
		SDL_SetRenderDrawColor(window._renderer, 0, 0, 255, 255);
		SDL_Rect rB{ 50 , 150, 20, 20 };
		SDL_RenderFillRect(window._renderer, &rB);

		drawSentence(&window, "Options", 150, 30);

		drawSentence(&window, "Backgroud color", 150, 110, Game::bgColR, Game::bgColG, Game::bgColB);
		drawSentence(&window, "Snake color", 150, 130, Game::SnakeR, Game::SnakeG, Game::SnakeB);
		drawSentence(&window, "Fruit color", 150, 150, Game::FoodR, Game::FoodG, Game::FoodB);
		drawSentence(&window, "Back", 200, 220);
		window.pollEvents();
		window.clear();
	}
}
void LeaderBoards() {
	Window window("Leader Board", 400, 300);
	window.play = play_snake;
	window.is_leaderBoard = true;
	window.option = Options;
	window.menu = Menu;

	while (!window.isClosed()) {

		if (Game::vysledky.size() == 0) {
			drawSentence(&window, "Empty so far", 150, 10, 255, 255, 255);
		}
		for (int i = 0; i < Game::vysledky.size(); i++)
		{

			std::string intStr = "Hrac cislo " + std::to_string(i + 1) + " ma score " + std::to_string(Game::vysledky[i]);


			drawSentence(&window, intStr, 100, 30 + 20 * i, 255, 255, 255);

		}

		drawSentence(&window, "Back", 200, 220);
		window.pollEvents();
		window.clear();
	}
}
void MapLoader() {
	Window window("Map Loader", 400, 300);
	window.play = play_snake;
	window.is_MapLoader = true;
	window.option = Options;
	window.menu = Menu;
	window.leaderBoard = LeaderBoards;
	window.mapa = &Game::mapa;
	window.load = LoadFile;
	while (!window.isClosed()) {

		drawSentence(&window, "Map Loader", 150, 30);
		//drawSentence(&window, "Ahoj", 50, 50);
		drawSentence(&window, "Map 1", 150, 100);
		drawSentence(&window, "Map 2", 150, 130);
		drawSentence(&window, "Map 3", 150, 160);
		drawSentence(&window, "Back", 200, 220);
		window.pollEvents();
		window.clear();
	}
}
void LoadFile(string file, vector <char>* mapa) {
	ifstream MyFile(file);
	string text;
	mapa->clear();
	while (getline(MyFile, text)) {
		// Output the text from the file
		//cout << text << endl;
		for (char ch : text) {
			if (ch == '1' || ch == '0')
				mapa->push_back(ch);
		}
	}
}