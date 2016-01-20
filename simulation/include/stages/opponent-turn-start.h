#ifndef STAGES_OPPONENT_TURN_START_H
#define STAGES_OPPONENT_TURN_START_H

#include <stdexcept>
#include <vector>
#include <string>

#include "stages/common.h"
#include "board.h"

class StageOpponentTurnStart
{
	public:
		static const Stage stage = STAGE_OPPONENT_TURN_START;
		static std::string GetStageStringName() { return "StageOpponentTurnStart"; }

		static void GetNextMoves(const Board &, std::vector<Move> &next_moves)
		{
			return StageCommonUtilities::GetGameFlowMove(next_moves);
		}

		static void ApplyMove(Board &board, const Move &move)
		{
#ifdef DEBUG
			if (move.action != Move::ACTION_GAME_FLOW) throw std::runtime_error("Invalid move");
#endif

			board.opponent_stat.crystal.TurnStart();

			if (board.player_deck.GetCards().empty()) {
				// no any card can draw, take damage
				// TODO
				board.stage = STAGE_LOSS;
				return;
			} else {
				if (board.opponent_cards.GetHandCount() < 10) {
					board.opponent_cards.DrawFromDeckToHand();
				} else {
					// hand can have maximum of 10 cards
					// TODO: distroy card (trigger deathrattle?)
				}
			}
			board.stage = STAGE_OPPONENT_CHOOSE_BOARD_MOVE;
	}
};

#endif
