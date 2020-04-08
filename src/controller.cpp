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
					// TODO: clean up code
					std::vector<std::string> settings_menu_items = {{ 
											std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols",
											std::string("Walls: ") + bool_to_str(Settings::enable_walls) 
											}};

					// TODO: don't close the menu changing an entry
					switch(m_ui.display_menu(settings_menu_items, true, "Settings"))
					{
						// TODO: see if there's a better way to indicate that, e.g. "Field size" was clicked instead of a generic "case 0:"
						case 0:
							switch(Settings::field_size.y) 
							{
								// TODO: see if a better case logic would fit better
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
							// TODO: are the std::to_string()'s really needed here?
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

				//TODO: check if this is really necessary. Will we ever get to this point?
			default:
				break;
		}
	}

}

void Controller::new_game()
{
	// TODO: find a better way to handle new games. Something like shared_ptr/unique_ptr perhaps?
	m_player = new Player();
	m_field = new Field();
	
	// TODO: move all logic out of Field class #1
	if(Settings::enable_walls) m_field->add_walls();
	// prepare the ui for a new game
	m_ui.game_start(*m_field);
	// TODO: move all logic out of Field class #2
	m_field->place_food();

	// TODO: would it be better off without a pointless variable tacking up the stack or does it really hurt readability without it?
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
		// TODO: improve get_input logic
		// TODO: mb move input sanitization out of Ui class
		m_player->set_facing(m_ui.get_input());
	}
	// TODO: try to find a better way to handle loss/death. return values instead of exceptions?
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
			// TODO: same as m_ui.get_input() in Controller::tick()
			//throw GameEndDeath();
			return 1;
		}
		default:
			break;
	}
	
	m_field->update_player(m_player);
	m_player->move(m_field->m_field_size);
	m_ui.update(*m_field, m_player->length() - 1);
	// TODO: check why this might not work in WSL or what else can cause a bug where it skips the sleep
	std::this_thread::sleep_for(std::chrono::milliseconds(145));
	return 0;
}
