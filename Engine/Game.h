#pragma once

#include "MainWindow.h"
#include "Graphics.h"
#include "Board.h"
#include "AI.h"

using namespace std;

class Game
{
	enum class boolshits {
		GameOver = 0b00000001,
		Started = 0b00000010,
		setting = 0b00000100,
		paused = 0b00001000
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
	bool gameover = false;

	/********************************/
};