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
				startNewTurn();
				enable_timer(0);
			}
			enableInputDetection();
		}
		else if (game.status == PLACING && game.countdown > 0) {
			/* Confirm barrier placement and end turn */
			disableInputDetection();
			disable_timer(0);
			reset_timer(0);
			placeBarrier();			/* Place barrier and start new turn */
			game.countdown = COUNTDOWN_TIME_S;
			enable_timer(0);
			enableInputDetection();
		}
		if (game.countdown == COUNTDOWN_TIME_S) {
			/* A new turn has started	*/
			// TODO: Substitute WHITE with BG_COLOR
			if (game.turn == 1)						/* Override P2 timer */
				GUI_Text(LAT_PADDING + 162, LAT_PADDING + 22, (uint8_t *) "     ", WHITE, WHITE);
			else
				GUI_Text(LAT_PADDING + 30, LAT_PADDING + 22, (uint8_t *) "     ", WHITE, WHITE);
		}
}
