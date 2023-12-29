#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ai(aiSym),
	AI(aiSym, huSym)
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
	if (started) {
		if (turn == players::ai) {
			switch (opponent)
			{
			case Game::opponents::OpAi:
				if (brd.setPlace(ai.run(brd), aiSym)) {
					turn = players::human;
				}
				break;
			case Game::opponents::minimax:
				if (brd.setPlace(AI.run(brd), aiSym)) {
					turn = players::human;
				}
				break;
			case Game::opponents::human:
				while (!wnd.mouse.IsEmpty()) {
					const auto evt = wnd.mouse.Read();
					if (evt.GetType() == Mouse::Event::Type::LPress) {
						if (brd.setPlace(std::make_pair(wnd.mouse.GetPosY() / 240, wnd.mouse.GetPosX() / 240), aiSym)) {
							turn = players::human;
						}
					}
				}
				break;
			default:
				break;
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
			gameover = true;
		}
		if (brd.IsFull()) {
			gameover = true;
		}
	}
	else {
		while (!wnd.mouse.IsEmpty()) {
			const auto evt = wnd.mouse.Read();
			if (evt.GetType() == Mouse::Event::Type::LPress) {
				if (wnd.mouse.GetPosX() < 480 && wnd.mouse.GetPosX() > 250 && wnd.mouse.GetPosY() < 200 && wnd.mouse.GetPosY() > 130) {
					opponent = opponents::OpAi;
				}
				else if (wnd.mouse.GetPosX() < 480 && wnd.mouse.GetPosX() > 250 && wnd.mouse.GetPosY() < 300 && wnd.mouse.GetPosY() > 230) {
					opponent = opponents::minimax;
				}
				else if (wnd.mouse.GetPosX() < 480 && wnd.mouse.GetPosX() > 250 && wnd.mouse.GetPosY() < 400 && wnd.mouse.GetPosY() > 330) {
					opponent = opponents::human;
				}
				else if (wnd.mouse.GetPosX() < 480 && wnd.mouse.GetPosX() > 250 && wnd.mouse.GetPosY() < 550 && wnd.mouse.GetPosY() > 480) {
					started = true;
				}
			}
		}
	}
}

void Game::restart()
{
	std::random_device rr;
	std::mt19937_64 rnd(rr());
	std::uniform_int_distribution<int> brdSymbol(0, 1);
	aiSym = brdSymbol(rnd) == 0 ? board::place::X : board::place::O;
	huSym = aiSym == board::place::O ? board::place::X : board::place::O;
	turn = aiSym == board::place::X ? players::ai : players::human;
	brd.reset();
	started = false;
	gameover = false;
	gameResult = brd.getResult();
}


void Game::ComposeFrame()
{
	if (started) {
		brd.show(gfx);
		if (gameover) {
			if (opponent != opponents::human) {
				if (gameResult == aiSym) {
					F.Drawtext("GG WP but you've lost", Vei2(200, gfx.ScreenHeight / 2), Colors::Red, gfx);
				}
				if (gameResult == huSym) {
					F.Drawtext("congrats, you could win my AI", Vei2(140, gfx.ScreenHeight / 2), Colors::Green, gfx);
				}
			}
			else {
				if (gameResult == board::place::X) {
					F.Drawtext("Player 1 is the winner", Vei2(200, gfx.ScreenHeight / 2), Colors::Cyan, gfx);
				}
				if (gameResult == board::place::O) {
					F.Drawtext("Player 2 is the winner", Vei2(200, gfx.ScreenHeight / 2), Colors::Cyan, gfx);
				}
			}
			if (brd.IsFull()) {
				F.Drawtext("Draw as always", Vei2(250, gfx.ScreenHeight / 2), Colors::White, gfx);
			}
			F.Drawtext("Restart", Vei2(300, 500), Colors::Blue, gfx);
			while (!wnd.mouse.IsEmpty()) {
				const auto evt = wnd.mouse.Read();
				if (evt.GetType() == Mouse::Event::Type::LPress) {
					if (wnd.mouse.GetPosX() < 450 && wnd.mouse.GetPosX() > 280 && wnd.mouse.GetPosY() < 550 && wnd.mouse.GetPosY() > 480) {
						restart();
					}
				}
			}
		}
	}
	else {
		F.Drawtext("Choose your opponent: ", Vei2(50, 50), Colors::White, gfx);
		F.Drawtext("Sina0 OP Ai", Vei2(300, 150), Colors::Cyan, gfx);
		F.Drawtext("minimax Ai", Vei2(300, 250), Colors::Yellow, gfx);
		F.Drawtext("a friend", Vei2(300, 350), Colors::Green, gfx);
		switch (opponent)
		{
		case Game::opponents::OpAi:
			F.Drawtext("=>", Vei2(250, 150), Colors::Red, gfx);
			break;
		case Game::opponents::minimax:
			F.Drawtext("=>", Vei2(250, 250), Colors::Red, gfx);
			break;
		case Game::opponents::human:
			F.Drawtext("=>", Vei2(250, 350), Colors::Red, gfx);
			break;
		default:
			break;
		}
		F.Drawtext("Start", Vei2(300, 500), Colors::Blue, gfx);
	}
}
