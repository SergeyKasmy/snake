#include "controller.hpp"

#include "ui.hpp"

void Controller::game_start()
{
	std::vector<std::string> main_menu_items = {{"New Game",
						"Settings",
						"Exit"}};

	switch(Ui::display_menu(main_menu_items, true))
	{
		case 0:
			m_menu.new_game();
			m_game.start();
		case -1:
			return;
		default:
			//TODO
			break;
	}
}
