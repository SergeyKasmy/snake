#include <chrono>
#include <thread>

#include "controller.hpp"

#include "ui.hpp"
#include "point.hpp"
#include "field.hpp"
#include "settings.hpp"

void Controller::start()
{
	std::vector<std::string> main_menu_items = {{"New Game",
						"Settings",
						"Exit"}};

	while(true)
	{
		switch(m_ui.display_menu(main_menu_items, true))
		{
			case 0:
				new_game();
				break;
			case 1:
				{
					std::vector<std::string> settings_menu_items = {{ 
											std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols",
											std::string("Walls: ") + bool_to_str(Settings::enable_walls) 
											}};
					switch(m_ui.display_menu(settings_menu_items, true, "Settings"))
					{
						case 0:
							switch(Settings::field_size.y) 
							{
								case 18:
									Settings::field_size = {25, 50};
									break;
								case 25:
									Settings::field_size = {10, 20};
									break;
								default:
							 		Settings::field_size = {18, 35};
									break;
							}
							settings_menu_items[0] = std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols";
							break;
						case 1:
							Settings::enable_walls = !Settings::enable_walls;
							settings_menu_items[1] = std::string("Walls: ") + bool_to_str(Settings::enable_walls);
							break;
						default:
							break;
					}
				}
				break;
			case 2:
				return;
			default:
				//TODO
				break;
		}
	}

}

void Controller::new_game()
{
	m_player = new Player();
	m_field = new Field();
	
	// prepare the ui for a new game
	if(Settings::enable_walls) m_field->add_walls();
	m_ui.game_start(*m_field);
	m_field->place_food();

	int go_on = 0;
	while(true)
	{
		go_on = tick();
		if(go_on != 0) break;
	}
	m_ui.game_end();

	delete(m_player);
	delete(m_field);
}

int Controller::tick()
{
	try
	{
		m_player->set_facing(m_ui.get_input());
	}
	catch(GameEndQuit &ex)
	{
		return 2;
	}

	Point desirable_pos = m_player->get();
	switch(m_field->get(desirable_pos))
	{
		case Object::food:
		{
			m_field->set(desirable_pos, Object::player);
			m_field->place_food();
			m_player->lengthen();
			break;
		}
		case Object::wall:
		case Object::player:
		{
			//throw GameEndDeath();
			return 1;
		}
		default:
			break;
	}
	
	m_field->update_player(m_player);
	m_player->move(m_field->m_field_size);
	m_ui.update(*m_field, m_player->length() - 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(145));
	return 0;
}
