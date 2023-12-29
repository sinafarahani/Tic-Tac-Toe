#include "minimaxAI.h"

#define NOMINMAX

minimaxAi::minimaxAi(const board::place& aiSymbol, const board::place& huSymbol)
	:
	aiSymbol(aiSymbol),
	huSymbol(huSymbol)
{
}

std::pair<int, int> minimaxAi::run(board& b)
{
	return minimax_optimization(b, aiSymbol, 0, -1000, 1000).second;
}

std::pair<int, std::pair<int, int>> minimaxAi::minimax_optimization(board b, const board::place marker, int depth, int alpha, int beta)
{
	std::pair<int, int> best_move = std::make_pair(-1, -1);
	int best_score = (marker == aiSymbol) ? -1000 : 1000;

	auto legalMoves = b.getEmptyPlaces();
	if (legalMoves.size() > 8) {
		return std::make_pair(0, std::make_pair(1, 1));
	}
	auto r = b.getResult();
	if (legalMoves.size() == 0 || r != board::place::MPT)
	{
		if (b.getResult() == aiSymbol) {
			best_score = 1000;
		}
		else if (b.getResult() == huSymbol) {
			best_score = -1000;
		}
		else {
			best_score = 0;
		}
		return std::make_pair(best_score, best_move);
	}

	for (const auto& move :legalMoves) {
		std::pair<int, int> curr_move = move;
		b.setPlace(move, marker);

		if (marker == aiSymbol)
		{
			int score = minimax_optimization(b, huSymbol, depth + 1, alpha, beta).first;
			
			if (best_score < score)
			{
				best_score = score - depth * 10;
				best_move = curr_move;

				alpha = (std::max)(alpha, best_score);
				b.unsetPlace(move);
				if (beta <= alpha)
				{
					break;
				}
			}

		}
		else
		{
			int score = minimax_optimization(b, aiSymbol, depth + 1, alpha, beta).first;

			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = curr_move;

				beta = (std::min)(beta, best_score);
				b.unsetPlace(move);
				if (beta <= alpha)
				{
					break;
				}
			}

		}

		b.unsetPlace(move);
	}

	return std::make_pair(best_score, best_move);
}
