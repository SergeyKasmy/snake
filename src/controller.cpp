#include "controller.hpp"

#include "ui.hpp"

void Controller::game_start()
{
	MainMenu mm;
	std::vector<MenuItem> main_menu_items = {{ 
						{"New Game", {} },
						{"Settings", {} },
						{"Exit", {} }
						}};

	Ui::display_menu(main_menu_items, 
				[this](menu_item_t p_selected_item)
				{
					switch(p_selected_item)
					{
						// New Game
						case 0:
							m_menu.new_game();
							m_game.start();
							break;
						// Settings
						case 1:
							break;
						case 2:
							//throw GameExit();
							break;
					}
				}, true);
}
