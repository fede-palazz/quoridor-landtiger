#include "../graphics/renderer.h"
#include "button_handlers.h"
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
		hideInitialMessage();
		/* Highlights Player possibile moves */
		highlightSquares();
		/* Start countdown */
		reset_timer(0);
		enable_timer(0);
		enableInputDetection();
	}
}

void onPressKey1() {
}

void onPressKey2() {
}
