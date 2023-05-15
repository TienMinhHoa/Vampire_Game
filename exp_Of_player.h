#pragma once
#include"Components.h"
#include "Game.h"
#include"TextureManager.h"

class exp_Of_player : public Component
{
private:
	int exp;
	int lv;
	SDL_Rect srcRect, destRect;
	std::string path;
	SDL_Texture* tex;
	TransformComponent* transform;
public:
	bool lvup = 0;
	exp_Of_player(std::string path)
	{
		this->path = path;
		exp = 0;
		lv = 1;
	}
	void init() override
	{
		tex = texturemanager::LoadTexture(path.c_str());
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.x = 0;
		destRect.y = 0;
		transform = &entity->getComponent<TransformComponent>();

	}
	void up()
	{
		std::cout << 1;
		exp += 50;
		if (exp == 100* lv)
		{
			lv += 1;
			exp = 0;
			lvup = 1;
		}
		
	}
	void update() override
	{
		destRect.w = exp*10/(lv*2);
		destRect.h = 32;
	}
	void draw() override
	{
		texturemanager::Draw(tex, srcRect, destRect);
		int a = (Game::clock / 1000) % 60;
		int b = 0;
		if (a == 0) b++;
		std::string tmp = std::to_string(b) + " : " + std::to_string(a);
		SDL_Rect dest = { 650,100,60,25 };
		SDL_Color color = { 255,255,255 };
		SDL_Texture* tex = texturemanager::LoadTextureFromFont("fonts/KO.ttf", color, tmp.c_str());
		texturemanager::write(tex, dest);
		SDL_DestroyTexture(tex);
	}

	int getlv()
	{
		return lv;
	}
};