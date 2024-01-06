#include "joystick_handlers.h"


void onJoystickLeft() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_LEFT)
			selectSquare(MOV_LEFT);							/* Move current player left */
	}
}

void onJoystickUp() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_UP)
			selectSquare(MOV_UP);								/* Move current player up */
	}
}
	
void onJoystickDown() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_DOWN)
			selectSquare(MOV_DOWN);							/* Move current player down */
	}
}
	
void onJoystickRight() {
	if (game.status == MOVING && game.countdown > 0) {
		if (selectedSquare != MOV_RIGHT)
			selectSquare(MOV_RIGHT);						/* Move current player right */
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
			enable_timer(0);
			startNewTurn();
		}
		enableInputDetection();
	}
}
