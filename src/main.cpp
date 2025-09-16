#include <Arduino.h>
#include <esp_display_panel.hpp>

using namespace esp_panel::drivers;
using namespace esp_panel::board;

IRAM_ATTR static bool onTouchInterruptCallback(void *user_data)
{
	esp_rom_printf("Touch interrupt callback\n");

	return false;
}

void setup()
{

	Board *board = new Board();
	ESP_LOGI("Setup", "Board init");
	board->init();

	auto lcd = board->getLCD();
	auto backlight = board->getBacklight();
	auto touch = board->getTouch();
	auto expander = board->getIO_Expander()->getBase();

	ESP_LOGI("Setup", "Board begin");

	board->begin();
	backlight->off();
	touch->attachInterruptCallback(onTouchInterruptCallback, NULL);

	delay(1000);

	// Specific to this display
	lcd->invertColor(true); // There is a PR ongoing in the library for this, can be removed once the PR has been approved

	ESP_LOGI("Setup", "Set backlight to 50%");
	backlight->setBrightness(50);

	ESP_LOGI("Setup", "Print IO Expander state");
	expander->printStatus();

	ESP_LOGI("Setup", "Perform color bar test");
	lcd->colorBarTest(lcd->getFrameWidth(), lcd->getFrameHeight());

	ESP_LOGI("Setup", "Setup finished");
}

void loop()
{
	delay(5);
}
