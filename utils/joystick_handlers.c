#include "../graphics/renderer.h"
#include "joystick_handlers.h"
#include "../game/game.h"


void onJoystickUp() {
	if (game.status == STARTED && game.countdown > 0) {
		/* Move current player up */
		selectSquare(MOV_UP);
	}
}
	
void onJoystickDown() {
	if (game.status == STARTED && game.countdown > 0) {
		/* Move current player down */
		selectSquare(MOV_DOWN);
	}
}
	
void onJoystickLeft() {
	if (game.status == STARTED && game.countdown > 0) {
		/* Move current player left */
		selectSquare(MOV_LEFT);
	}
}
	
void onJoystickRight() {
	if (game.status == STARTED && game.countdown > 0) {
		/* Move current player right */
		selectSquare(MOV_RIGHT);
	}
}
	
void onJoystickSelect() {
}
