#pragma once

#include "SpriteEx.h"

class Life : public SpriteEx
{
public:
	Life(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect)
		: SpriteEx(tex, srcRect, destRect)
	{
		m_X = destRect.x;
		m_Y = destRect.y;
	}

	void setRadius(int r)
	{
		m_dRadius = r;
	}

};