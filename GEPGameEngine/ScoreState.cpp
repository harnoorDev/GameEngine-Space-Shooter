#include "ScoreState.h"
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
using namespace std;

// Begin PauseState
void ScoreState::Enter()
{
	cout << "Entering Score..." << endl;
	Game::Instance()->SetLeftMouse(false);

	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,350,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,500,400,100 }));
	m_pFont = TTF_OpenFont("Font/Candles.TTF", 50);
}

void ScoreState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::play]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		Game::Instance()->QuitGame();
	}
}


void ScoreState::Render()
{
	//Game::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 62, 39, 35, 128);

	//draw background 
	SDL_Rect rect = { 125, 120, 800, 600 };
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	string c = message;
	string s = "Your  Total  Score  is  " + to_string(score);
	RenderFont(true, c.c_str(), 150, 150);
	RenderFont(true, s.c_str(), 150, 250);
	ScreenState::Render();

}


void ScoreState::Exit()
{

	cout << "Exiting Score..." << endl;

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

