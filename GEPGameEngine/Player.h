#pragma once

#include "SpriteEx.h"
#include "Bullet.h"
#include <vector>
using namespace std;


class Player : public SpriteExAnimated
{
private:

	vector<Bullet*> m_vBullets;
	void UpdateBullets();

	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;

	void MoveForward();
	void UpdatePlayer();

public :
	Player(SDL_Texture *tex, double x, double y);
	~Player();
	void Update();
	void Render();
	void SetIdle();
	void SpawnBullet(); 

	vector<Bullet*>& GetBullets()
	{
		return m_vBullets;
	}

};