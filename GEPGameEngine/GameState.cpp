#include "GameState.h"
#include "Game.h"
#include "ScoreState.h"
#include "MainMenuState.h"
#include "PauseMenuPopupState.h"
void GameState::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	mainSpriteTex = Game::Instance()->LoadTexture("Sprites.png");
	coinSpriteTex = Game::Instance()->LoadTexture("Coins.png");
	lifeSpriteTex = Game::Instance()->LoadTexture("life.gif");
	enemyShipSpriteTex = Game::Instance()->LoadTexture("enemyShip.png");
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	// Asteroid
	SDL_Rect asteroidSrcRect;
	asteroidSrcRect.x = 124;
	asteroidSrcRect.y = 0;
	asteroidSrcRect.w = asteroidSrcRect.h = 66;//66 pixelsx66 pixels is each cell's dimension

	SDL_Rect asteroidDestRect;
	asteroidDestRect.w = asteroidDestRect.h = 66;

	for (int i = 0; i < 5; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);
		asteroidDestRect.x = (rand() % 900) + 1; //generate between 1 and 900
		asteroidDestRect.y = (rand() % 600) + 1;//generate between 1 and 600
		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, r);
		asteroids.push_back(ast);
	}
	for (int i = 0; i < 5; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);
		asteroidDestRect.x = (rand() % 900) + 1; //generate between 1 and 900
		asteroidDestRect.y = (rand() % 700) + 1;//generate between 1 and 700
		asteroidDestRect.w = asteroidDestRect.h = 132;
		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, r);
		ast->setRadius(66);
		asteroids.push_back(ast);
	}

	//Generating Coins
	SDL_Rect coinSrcRect;
	coinSrcRect.x = 0;
	coinSrcRect.y = 0;
	coinSrcRect.w = 30;
	coinSrcRect.h = 32;

	SDL_Rect coinDestRect;
	coinDestRect.w = 30;
	coinDestRect.h = 32;

	for (int i = 0; i < 5; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);
		coinDestRect.x = (rand() % 900) + 1; //generate between 1 and 900
		coinDestRect.y = (rand() % 600) + 1;//generate between 1 and 600
		Coins* coin = new Coins(coinSpriteTex, coinSrcRect, coinDestRect, r);
		coin->setRadius(15);
		coins.push_back(coin);
	}
	//Generating Life
	SDL_Rect lifeSrcRect;
	lifeSrcRect.x = 0;
	lifeSrcRect.y = 0;
	lifeSrcRect.w = lifeSrcRect.h = 16;
	SDL_Rect lifeDestRect;
	lifeDestRect.w = lifeDestRect.h = 32;

	for (int i = 0; i < 2; i++)
	{
		lifeDestRect.x = (rand() % 400) + 1; //generate between 1 and 400
		lifeDestRect.y = (rand() % 700) + 1;//generate between 1 and 700
		Life* lives = new Life(lifeSpriteTex, lifeSrcRect, lifeDestRect);
		lives->setRadius(16);
		life.push_back(lives);
	}
	//Generating Life
	SDL_Rect enemyShipSrcRect;
	enemyShipSrcRect.x = 0;
	enemyShipSrcRect.y = 0;
	enemyShipSrcRect.w = enemyShipSrcRect.h = 30;
	SDL_Rect enemyShipDestRect;
	enemyShipDestRect.w = enemyShipDestRect.h = 40;

	for (int i = 0; i < 5; i++)
	{
		enemyShipDestRect.x = (rand() % 700) + 1; //generate between 1 and 100
		enemyShipDestRect.y = (rand() % 700) + 1;//generate between 1 and 700
		EnemyShip* enemyship = new EnemyShip(enemyShipSpriteTex, enemyShipSrcRect, enemyShipDestRect);
		enemyship->setRadius(20);
		enemyShip.push_back(enemyship);
	}
	player = new Player(mainSpriteTex, bgDestRect.w * 0.5, bgDestRect.h - 100);

	fireSound = Mix_LoadWAV("Fire.wav");
	engineSound = Mix_LoadWAV("Engines.wav");
	coinPick = Mix_LoadWAV("CoinPick.wav");
	lifePick = Mix_LoadWAV("life_pickup.flac");
	Mix_VolumeChunk(fireSound, 40);
	Mix_VolumeChunk(engineSound, 40);
	Mix_VolumeChunk(coinPick, 70);
	Mix_VolumeChunk(lifePick, 70);
}


void GameState::Update()
{
	ScoreState* scoreSt = new ScoreState();
	if (isDefeated) {
		scoreSt->setMessage("Game Over. You got killed.");
		Exit();
		scoreSt->setScore(score);
		Game::Instance()->GetFSM()->PushState(scoreSt);
	}
	else {
		if (asteroids.size() <= 0 && enemyShip.size() <= 0) {
			scoreSt->setMessage("Congratulations!!!");
			Exit();
			scoreSt->setScore(score);
			Game::Instance()->GetFSM()->PushState(scoreSt);
		}
	}

	if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		Game::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update();
	for (int i = 0; i < coins.size(); i++)
		coins[i]->Update();

	if (player) this->CheckCollision();

	if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		//to do:: launch a missile...
		Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
		player->SpawnBullet();
	}
	//Play engine sound....
	if (Game::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		if (!Mix_Playing(15)) //if channel 15 is not playing
			Mix_PlayChannel(15, engineSound, -1);   //-1 because we want to loop the sound...

	}
	if (Game::Instance()->KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250); //250 is in milliseconds.. the time over which the audio will fade out...
			player->SetIdle();

		}

	}
	if (Game::Instance()->KeyDown(SDL_SCANCODE_E))
	{
		//we need to switch to endstate ... 
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}
}


void GameState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Render();
	for (int i = 0; i < coins.size(); i++)
		coins[i]->Render();
	for (int i = 0; i < life.size(); i++)
		life[i]->Render();
	for (int i = 0; i < enemyShip.size(); i++)
		enemyShip[i]->Render();


	string s = "Score: " + to_string(score);

	string l = "Lives: " + to_string(lives);

	RenderFont(true, s.c_str(), 32, 50);
	RenderFont(true, l.c_str(), 32, 80);
	ScreenState::Render();


}


void GameState::Exit()
{
	cout << "Exiting GameState...\n";
	// Removing Asteroids
	for (int i = 0; i < (int)asteroids.size(); i++)
	{
		delete asteroids[i];
		asteroids[i] = nullptr;
	}
	asteroids.clear();
	asteroids.shrink_to_fit();
	// Removing enemyShip
	for (int i = 0; i < (int)enemyShip.size(); i++)
	{
		delete enemyShip[i];
		enemyShip[i] = nullptr;
	}
	enemyShip.clear();
	enemyShip.shrink_to_fit();
	// Removing life
	for (int i = 0; i < (int)life.size(); i++)
	{
		delete life[i];
		life[i] = nullptr;
	}
	life.clear();
	life.shrink_to_fit();
	// Removing coins
	for (int i = 0; i < (int)coins.size(); i++)
	{
		delete coins[i];
		coins[i] = nullptr;
	}
	coins.clear();
	coins.shrink_to_fit();
}

void GameState::CheckCollision()
{
	//check for the player and asteroid collision
	for (int i = 0; i < (int)asteroids.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			asteroids[i]->GetX(), asteroids[i]->GetY(),
			player->GetRadius(), asteroids[i]->GetRadius()
		)) {
			if (lives > 0) {
				lives = lives - 1;
				delete asteroids[i];
				asteroids[i] = nullptr;
				asteroids.erase(asteroids.begin() + i);
				break;
			}
			//there was a player-asteroid collision!!!
			cout << "Player collided with an asteroid and got killed!!\n";
			//we can delete the player...
			if (lives == 0) {
				delete player;
				isDefeated = true;
				player = nullptr;
				return;
			}
		}
	}
	//check for the player and enemyShip collision
	for (int i = 0; i < (int)enemyShip.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			enemyShip[i]->GetX(), enemyShip[i]->GetY(),
			player->GetRadius(), enemyShip[i]->GetRadius()
		)) {
			if (lives > 0) {
				lives = lives - 1;
				delete enemyShip[i];
				enemyShip[i] = nullptr;
				enemyShip.erase(enemyShip.begin() + i);
				break;
			}
			//there was a player-asteroid collision!!!
			cout << "Player collided with an enemyShip and got killed!!\n";
			//we can delete the player...
			if (lives == 0) {
				delete player;
				isDefeated = true;
				player = nullptr;
				return;
			}
		}
	}
	//check for the player and life collision
	for (int i = 0; i < (int)life.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			life[i]->GetX(), life[i]->GetY(),
			player->GetRadius(), life[i]->GetRadius()
		))
		{
			lives += 1;
			if (!Mix_Playing(4)) //if channel 15 is not playing
				Mix_PlayChannel(5, lifePick, 0);   //-1 because we want to loop the sound...
			delete life[i];
			life[i] = nullptr;
			life.erase(life.begin() + i);
		}

	}
	//check for the player and coin collision
	for (int i = 0; i < (int)coins.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			coins[i]->GetX(), coins[i]->GetY(),
			player->GetRadius(), coins[i]->GetRadius()
		))
		{
			score += 10;
			if (!Mix_Playing(5)) //if channel 15 is not playing
				Mix_PlayChannel(10, coinPick, 0);   //-1 because we want to loop the sound...
			delete coins[i];
			coins[i] = nullptr;
			coins.erase(coins.begin() + i);
		}

	}

	bool isBreakOutOfLoop = false;
	//check for bullet and asteroid collision
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{
		for (int i = 0; i < (int)asteroids.size(); i++)
		{
			Bullet* bullet = player->GetBullets()[b];
			if (CircleCollisionTest(bullet->GetX(), bullet->GetY(),
				asteroids[i]->GetX(), asteroids[i]->GetY(),
				bullet->GetRadius(), asteroids[i]->GetRadius()
			)) {
				cout << "Bullet collided with an asteroid!!\n";
				//may be, add to score here... 
				if (asteroids[i]->GetdstRecth() > 66)
				{
					score += 10;
				}
				else score += 5;
				//cleanup/destroy the bullet
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);
				asteroids[i]->SetdstRecth(asteroids[i]->GetdstRecth() - 33);
				asteroids[i]->SetdstRectw(asteroids[i]->GetdstRectw() - 33);
				asteroids[i]->setRadius(asteroids[i]->GetRadius() - 16);
				if (asteroids[i]->GetdstRecth() <= 0)
				{
					//destroy the asteroid
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);
				}
				isBreakOutOfLoop = true;
			}
			if (isBreakOutOfLoop)	break;
		}
		if (isBreakOutOfLoop)	break;
	}
	//check for bullet and enemyShip collision
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{
		for (int i = 0; i < (int)enemyShip.size(); i++)
		{
			Bullet* bullet = player->GetBullets()[b];
			if (CircleCollisionTest(bullet->GetX(), bullet->GetY(),
				enemyShip[i]->GetX(), enemyShip[i]->GetY(),
				bullet->GetRadius(), enemyShip[i]->GetRadius()
			)) {
				cout << "Bullet collided with an enemyShip!!\n";
				//may be, add to score here... 
				score += 50;
				//cleanup/destroy the bullet
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);
				enemyShip[i]->SetdstRecth(enemyShip[i]->GetdstRecth() - 40);
				enemyShip[i]->SetdstRectw(enemyShip[i]->GetdstRectw() - 40);
				enemyShip[i]->setRadius(enemyShip[i]->GetRadius() - 20);
				if (enemyShip[i]->GetdstRecth() <= 0)
				{
					//destroy the enemyShip
					delete enemyShip[i];
					enemyShip[i] = nullptr;
					enemyShip.erase(enemyShip.begin() + i);
				}
				isBreakOutOfLoop = true;
			}
			if (isBreakOutOfLoop)	break;
		}
		if (isBreakOutOfLoop)	break;
	}
	if (isBreakOutOfLoop)
	{
		player->GetBullets().shrink_to_fit();
		asteroids.shrink_to_fit();
		coins.shrink_to_fit();
		life.shrink_to_fit();
		enemyShip.shrink_to_fit();
	}

}
