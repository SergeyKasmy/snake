#include "ui.hpp"
#include "settings.hpp"

Point Settings::field_size = {18, 35};
bool Settings::enable_walls = false;

int main()
{
	MainMenu main_menu;
	main_menu.show();
	return 0;
}