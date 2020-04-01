#include <chrono>
#include <thread>

#include "controller.hpp"

#include "point.hpp"
#include "settings.hpp"

void Controller::start()
{
	Ui ui;
	// TODO: Move GameUi logic to the Ui class
	m_ui = new GameUi();
	std::vector<std::string> main_menu_items = {{"New Game",
						"Settings",
						"Exit"}};

	switch(ui.display_menu(main_menu_items, true))
	{
		case 0:
			new_game();
		case -1:
			return;
		default:
			//TODO
			break;
	}

	// TODO
	delete(m_ui);
}

void Controller::new_game()
{
	m_ui->set_field(&m_field);
	// prepare the ui for a new game
	m_ui->game_start();
	if(Settings::enable_walls) m_field.add_walls();
	m_field.place_food();
	m_ui->draw_static_elements();

	int go_on = 0;
	while(true)
	{
		go_on = tick();
		if(go_on != 0) break;
	}
}

int Controller::tick()
{
	m_player.set_facing(m_ui->get_input());
	Point desirable_pos = m_player.get();
	switch(m_field.get(desirable_pos))
	{
		case Object::food:
		{
			m_field.set(desirable_pos, Object::player);
			m_field.place_food();
			m_player.lengthen();
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
	
	m_field.update_player(&m_player);
	m_player.move(m_field.m_field_size);
	m_ui->update(m_player.length() - 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(145));
	return 0;
}
