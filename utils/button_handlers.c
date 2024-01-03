#include "../graphics/renderer.h"
#include "button_handlers.h"
#include "../timer/timer.h"
#include "button_utils.h"
#include "../game/game.h"


void onPressInt0() {
	if (game.status == WAITING) {		/* Game has to start */
		/* Game initialization */
		game.status = STARTED;
		game.turn = 1;
		game.countdown = COUNTDOWN_TIME_S;
		/* Highlights Player possibile moves */
		highlightSquares();
		/* Start countdown */
		reset_timer(0);
		enable_timer(0);
	}
}

void onPressKey1() {
}

void onPressKey2() {
}
