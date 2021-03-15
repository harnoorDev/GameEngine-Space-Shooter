#pragma once
#include "Player.h"
#include "Asteroid.h"
#include "Coins.h"
#include "Life.h"
#include "EnemyShip.h"
#include "SDL_mixer.h"

#include "ScreenState.h"

#include <iostream>
using namespace std;

class GameState : public ScreenState
{
private:
	SDL_Texture * mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite texture
	SDL_Texture* coinSpriteTex; //load and store the coin sprite texture
	SDL_Texture* lifeSpriteTex; //load and store the life sprite texture
	SDL_Texture* enemyShipSpriteTex; //load and store the enemy ship sprite texture

	SpriteEx* bg;

	Player* player;
	vector<Asteroid*> asteroids;
	vector<Coins*> coins;
	vector<Life*> life;
	vector<EnemyShip*> enemyShip;

	Mix_Chunk* fireSound;
	Mix_Chunk* engineSound;
	Mix_Chunk* coinPick;
	Mix_Chunk* lifePick;

	int lives = 3;
	int score = 0;
	bool isDefeated = false;


public:
	GameState() {}
	void setIsDefeated(bool defeat) {
		isDefeated = defeat;
	}
	bool getIsDefeated() {
		return isDefeated;
	}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	int getScore() {
		return score;
	}
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}

	void CheckCollision();
};
