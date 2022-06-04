#include "Window.h"

Window::Window(const std::string& title, int width, int height) : _title(title) , _width(width), _height(height)
{
	
	_closed = !init();
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
	SDL_DestroyRenderer(_renderer);
}

void Window::clear() const
{ 
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0 , 0, 0 ,255);
	SDL_RenderClear(_renderer);

}

void Window::pollEvents()
{
	SDL_Event event;
	
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_closed = true;
			break;
		case SDL_MOUSEBUTTONUP  :	
			if (is_menu == true) {
				if (event.motion.x >= 150 && event.motion.x <= 190 && event.motion.y >= 100 && event.motion.y <= 110) {
					std::cout << "Play " << std::endl;
					_closed = true;
					Destroy();
					play(0,0,0);

				}

				else if (event.motion.x >= 150 && event.motion.x <= 230 && event.motion.y >= 130 && event.motion.y <= 140) {
					std::cout << "Options " << std::endl;

					_closed = true;
					Destroy();
					option();

				}


				else if (event.motion.x >= 150 && event.motion.x <= 260 && event.motion.y >= 160 && event.motion.y <= 170) {
					std::cout << "LeaderBoard " << std::endl;

					_closed = true;
					Destroy();
					leaderBoard();

				}

				else if (event.motion.x >= 150 && event.motion.x <= 260 && event.motion.y >= 190 && event.motion.y <= 200) {
					std::cout << "LeaderBoard " << std::endl;

					_closed = true;
					Destroy();
					MapLoader();

				}
			}
			else if (is_option || is_leaderBoard || is_MapLoader) {
				if (event.motion.x >= 200 && event.motion.x <= 260 && event.motion.y >= 220 && event.motion.y <= 230) {
					std::cout << "Back " << std::endl;

					_closed = true;
					Destroy();
					menu();

				}
			}

			if (is_MapLoader) {
				if (event.motion.x >= 150 && event.motion.x <= 200 && event.motion.y >= 100 && event.motion.y <= 120) {

					load("map1.txt", mapa);
					std::cout << "Map 1 loaded" << std::endl;
				}
				else if (event.motion.x >= 150 && event.motion.x <= 200 && event.motion.y >= 130 && event.motion.y <= 150) {

					load("map2.txt", mapa);
					std::cout << "Map 2 loaded" << std::endl;
				}
				else if (event.motion.x >= 150 && event.motion.x <= 200 && event.motion.y >= 160 && event.motion.y <= 180) {

					load("map3.txt", mapa);
					std::cout << "Map 3 loaded" << std::endl;
				}
			}
			if (is_option) {
				if (event.motion.x >= 150 && event.motion.x <= 240 && event.motion.y >= 110 && event.motion.y <= 130) {
					std::cout << "BackGround color " << std::endl;
					if (RedRect) {
						setBgColor(255, 0, 0);
					}
					else if (GreenRect) {
						setBgColor(0,255, 0);
					}
					else if (BlueRect) {
						setBgColor(0,0,255);
					}


				}

				if (event.motion.x >= 150 && event.motion.x <= 230 && event.motion.y >= 150 && event.motion.y <= 160) {
					std::cout << "Fruit color " << std::endl;
					if (RedRect) {
						setFruitColor(255, 0, 0);
					}
					else if (GreenRect) {
						setFruitColor(0,255, 0);
					}
					else if (BlueRect) {
						setFruitColor(0, 0, 255);
					}


				}


				if (event.motion.x >= 150 && event.motion.x <= 200 && event.motion.y >= 130 && event.motion.y <= 140) {
					std::cout << "Snake Color " << std::endl;
					if (RedRect) {
						 setSnakeColor(255, 0, 0);

					}
					else if (GreenRect) {
						setSnakeColor(0, 255, 0);
					}
					else if (BlueRect) {
						setSnakeColor(0,0,255);
					}
					

				}

				if (event.motion.x >= 50 && event.motion.x <= 70 && event.motion.y >= 50 && event.motion.y <= 70) {
					std::cout << "Red rect" << std::endl;
					RedRect = true;
					GreenRect = false;
					BlueRect = false;
				}

				else if (event.motion.x >= 50 && event.motion.x <= 70 && event.motion.y >= 100 && event.motion.y <= 120) {
					std::cout << "Green rect " << std::endl;
					RedRect = false;
					GreenRect = true;
					BlueRect = false;

				}

				else if (event.motion.x >= 50 && event.motion.x <= 70 && event.motion.y >= 150 && event.motion.y <= 170) {
					std::cout << "Blue rect " << std::endl;
					RedRect = false;
					GreenRect = false;
					BlueRect = true;


				}
				
			}
			
			
			std::cout << event.motion.x	  << " " << event.motion.y << std::endl;
			
			
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				
				case 97:
					std::cout << "a";
					break;
				case SDLK_w:
					std::cout << "w";
					break;
				case SDLK_d:
					std::cout << "d";
					break;
				case SDLK_s:
					std::cout << "s";
					break;
				case SDLK_ESCAPE:
					_closed = true;
					break;
				
					break;
				default:
					break;
			}
			break;
		default:
			break;
		}
	}
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Bad inicialization" << std::endl;
		return false;
	}
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height , 0);

	if (_window == nullptr) {
		std::cerr << "Failed to create window" << std::endl;
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1 , SDL_RENDERER_ACCELERATED );

	if (_renderer == nullptr) {
		std::cerr << "Failed to create renderer!\n";
		return 0;
	}
	return true;
}
