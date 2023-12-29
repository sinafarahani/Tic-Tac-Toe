#pragma once

#include "MainWindow.h"
#include "Graphics.h"
#include "Board.h"
#include "AI.h"
#include "minimaxAI.h";
#include "Font.h"

using namespace std;

class Game
{
	enum class opponents {
		OpAi = 0b00000001,
		minimax = 0b00000010,
		human = 0b00000100
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void restart();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	enum class players
	{
		ai,
		human
	};
	board::place aiSym;
	board::place huSym;
	board::place gameResult;
	players turn;
	board brd;
	ai ai;
	minimaxAi AI;
	opponents opponent = opponents::OpAi;
	Font F = "Images\\Fixedsys16x28.bmp";
	bool started = false;
	bool gameover = false;
	/********************************/
};