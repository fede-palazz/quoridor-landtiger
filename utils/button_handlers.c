#include "button_handlers.h"
#include "button_utils.h"
#include "../graphics/renderer.h"


void onPressInt0() {
	LCD_Clear(WHITE);
}

void onPressKey1() {
	GUI_Text(40, 100, (uint8_t *) "Key1 funziona", BLUE, WHITE);
}

void onPressKey2() {
	GUI_Text(40, 200, (uint8_t *) "Key2 pure", BLUE, WHITE);
}
