#pragma once

#include "ScreenState.h"
#include "GameState.h"
#include <vector>
#include "Button.h"
using namespace std;

class ScoreState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { play, exit };
	int score = 0;
	string message = "";

public:
	ScoreState() {}
	void setScore(int sc) {
		this->score = sc;
	}
	int getScore() {
		return score;
	}
	void setMessage(string msg) {
		this->message = msg;
	}
	string getMessage() {
		return message;
	}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};