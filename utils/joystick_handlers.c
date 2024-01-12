#include "joystick_handlers.h"


void onJoystickLeft() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_LEFT)
			selectSquare(MOV_LEFT);							/* Move current player left */
	}
	else if (game.status == PLACING && game.countdown > 0) {
		moveBarrier(MOV_LEFT);
	}
}

void onJoystickUp() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_UP)
			selectSquare(MOV_UP);								/* Move current player up */
	}
	else if (game.status == PLACING && game.countdown > 0) {
		moveBarrier(MOV_UP);
	}
}
	
void onJoystickDown() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_DOWN)
			selectSquare(MOV_DOWN);							/* Move current player down */
	}
	else if (game.status == PLACING && game.countdown > 0) {
		moveBarrier(MOV_DOWN);
	}
}
	
void onJoystickRight() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_RIGHT)
			selectSquare(MOV_RIGHT);						/* Move current player right */
	}
	else if (game.status == PLACING && game.countdown > 0) {
		moveBarrier(MOV_RIGHT);
	}
}
	
void onJoystickSelect() {
  	if (game.status == MOVING && game.countdown > 0) {
			disableInputDetection();
			/* Check if player needs to be moved*/
			if (selectedSquare != -1) {
				clearHighlightedSquares();	
				movePlayer();								/* Update coordinates and draw player in new position */
				disable_timer(0);
				reset_timer(0);
				game.countdown = COUNTDOWN_TIME_S;
				/* Save last move */
				saveLastMove(game.turn-1, 0, 0, currentPlayer->pos.y, currentPlayer->pos.x);
				/* Check if player won the game */
				if (checkWinningCondition()) {
					game.status = FINISHED;
				}
				else {
					startNewTurn();
					/* A new turn has started	*/
					if (game.turn == 1)						/* Override P2 timer */
						GUI_Text(COUNT2_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
					else
						GUI_Text(COUNT1_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
					enable_timer(0);
				}
			}
			enableInputDetection();
		}
		else if (game.status == PLACING && game.countdown > 0) {
			uint8_t barrierPlaced;
			/* Confirm barrier placement and end turn */
			disableInputDetection();
			disable_timer(0);
			reset_timer(0);
			barrierPlaced = placeBarrier();			/* Try to place barrier and return operation result */
			if (barrierPlaced) {
				game.countdown = COUNTDOWN_TIME_S;
				/* Save last move */
				saveLastMove(game.turn-1, 1, barrier.direction, currentPlayer->pos.y, currentPlayer->pos.x);
				/* A new turn has started	*/
				if (game.turn == 1)						/* Override P2 timer */
					GUI_Text(COUNT2_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
				else
					GUI_Text(COUNT1_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
			}
			enable_timer(0);
			enableInputDetection();
		}
}
