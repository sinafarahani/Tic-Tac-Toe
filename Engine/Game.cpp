#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ai(aiSym)
{
	std::random_device rr;
	std::mt19937_64 rnd(rr());
	std::uniform_int_distribution<int> brdSymbol(0,1);
	aiSym = brdSymbol(rnd) == 0 ? board::place::X : board::place::O;
	huSym = aiSym == board::place::O ? board::place::X : board::place::O;
	turn = aiSym == board::place::X ? players::ai : players::human;
}

void Game::Go()
{
	gfx.BeginFrame();
	if (!gameover) {
		UpdateModel();
	}
	ComposeFrame();
	gfx.EndFrame();	
}

void Game::UpdateModel()
{
	if (turn == players::ai) {
		if (brd.setPlace(ai.run(brd), aiSym)) {
			turn = players::human;
		}
	}
	if (turn == players::human) {
		while (!wnd.mouse.IsEmpty()) {
			const auto evt = wnd.mouse.Read();
			if (evt.GetType() == Mouse::Event::Type::LPress) {
				if (brd.setPlace(std::make_pair(wnd.mouse.GetPosY() / 240, wnd.mouse.GetPosX() / 240), huSym)) {
					turn = players::ai;
				}
			}
		}
	}
	gameResult = brd.getResult();

	if (gameResult != board::place::MPT) {
		if (gameResult == aiSym) {
			wnd.ShowMessageBox(L"result", L"GG WP but you've lost");
			gameover = true;
		}
		if (gameResult == huSym) {
			wnd.ShowMessageBox(L"result", L"congrats, you could win my AI");
			gameover = true;
		}
	}
	if (brd.IsFull()) {
		wnd.ShowMessageBox(L"result", L"Draw as always");
		gameover = true;
	}
}


void Game::ComposeFrame()
{
	brd.show(gfx);
}
