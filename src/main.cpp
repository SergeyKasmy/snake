#include "controller.hpp"
#include "settings.hpp"

Point Settings::field_size = {18, 35};
bool Settings::enable_walls = false;

int main()
{
	Controller controller;
	controller.game_start();
	return 0;
}
