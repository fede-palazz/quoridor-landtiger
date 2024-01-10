#include "../graphics/renderer.h"
#include "button_handlers.h"
#include "../utils/input.h"
#include "../timer/timer.h"
#include "button_utils.h"
#include "../game/game.h"


void onPressInt0() {
	if (game.status == WAITING) {		/* Game has to start */
		disableInputDetection();
		/* Game initialization */
		game.status = MOVING;
		game.turn = INITIAL_TURN;
		game.countdown = COUNTDOWN_TIME_S;
		drawCurrentTurnMessage(currentPlayer, game.turn);
		/* Highlights Player possibile moves */
		highlightSquares();
		/* Start countdown */
		reset_timer(0);
		enable_timer(0);
		enableInputDetection();
	}
	else if (game.status == FINISHED) {
		resetGame();
	}
}

void onPressKey1() {
	if (currentPlayer->barrierNum > 0 && game.countdown > 0) {		/* Check remaning barriers */
		if (game.status == MOVING ) {
			disableInputDetection();
			game.status = PLACING;	/* Switch to barrier placing mode */
			disable_timer(0);
			reset_timer(0);
			createNewBarrier();			/* Create new barrier in the centre of the board */
			enable_timer(0);
			enableInputDetection();
		}
		else if (game.status == PLACING) {
			/* Come back to MOVING mode */
			disable_timer(0);
			reset_timer(0);
			switchToMovingMode();
			enable_timer(0);
			enableInputDetection();
		}
	}
	else if (currentPlayer->barrierNum == 0 && game.status == MOVING) {		/* Show a warning message */
		disableInputDetection();
		disable_timer(0);
		reset_timer(0);
		drawNoBarriersMessage();
		isBarrierWarningDisplayed = 1;			/* Check message to be hidden on next turn */
		enable_timer(0);
		enableInputDetection();
	}
}

void onPressKey2() {
	if (game.status == PLACING && game.countdown > 0) {	/* Check if player is placing a barrier */
		disableInputDetection();
		disable_timer(0);
		reset_timer(0);
		rotateBarrier();			/* Rotate current barrier */
		enable_timer(0);
		enableInputDetection();
	}
}
