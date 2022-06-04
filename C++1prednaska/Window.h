#pragma once
#include "SDL.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();
	void Destroy (){ this->~Window(); }
	inline bool isClosed() const {return  _closed; }
	void clear() const;

	void pollEvents();
	bool is_menu = false;
	bool snake = false;
	bool is_option = false;
	bool is_leaderBoard = false;
	bool is_MapLoader = false;

	using Funkce = void(*)();
	Funkce menu;
	Funkce option;
	Funkce leaderBoard;
	Funkce MapLoader;
	void(*play)(int ,int ,int);
	void(*load)(std::string, std::vector <char>*);


	std::vector <char>* mapa;

	std::string _title;
	int _width = 800, _height = 800;
	bool _closed = false;

	bool init();
	SDL_Window* _window = nullptr;

	SDL_Renderer* _renderer = nullptr;

	bool RedRect= false, GreenRect= false, BlueRect = false;
	int* snakeR;
	int* snakeG;
	int* snakeB;


	int* bgR;
	int* bgB;
	int* bgG;

	int* fR;
	int* fG;
	int* fB;

	void setBgColor(int r, int g, int b) {
		*bgR = r;
		*bgG = g;
		*bgB = b;
	}

	void setSnakeColor(int r, int g, int b) {
		*snakeR = r;
		*snakeG = g;
		*snakeB = b;
	}

	void setFruitColor(int r, int g, int b) {
		*fR = r;
		*fG = g;
		*fB = b;
	}

};
