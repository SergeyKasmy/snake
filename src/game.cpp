#include <chrono>
#include <thread>

#include "game.hpp"

#include "field.hpp"
#include "point.hpp"
#include "player.hpp"
#include "settings.hpp"
#include "ui.hpp"

void Game::tick()
{
	m_player->set_facing(m_ui->get_input());
	update();
	std::this_thread::sleep_for(std::chrono::milliseconds(145));
}

void Game::update()
{
	Point player_head = m_player->get();
	switch(m_field->get(player_head))
	{
		case Object::food:
		{
			m_field->set(player_head, Object::player);
			m_field->place_food();
			m_player->lengthen();
			break;
		}
		case Object::wall:
		case Object::player:
		{
			throw GameEndDeath();
			break;
		}
		default:
			break;
	}
	
	m_field->update_player(m_player);
	m_player->move(m_field->m_field_size);
	m_ui->update(m_player->length() - 1);
}


Game::Game(GameUI *p_ui)
{
	m_ui = p_ui;
	m_field = new Field();
	m_ui->set_field(m_field);

	m_player = new Player();
}

Game::~Game()
{
	delete m_field;
	delete m_player;
}

void Game::start()
{
	if(Settings::enable_walls) m_field->add_walls();
	m_field->place_food();
	m_ui->draw_static_elements();

	while(true)
	{
		try
		{
			tick();
		}
		catch(const GameEndQuit &)
		{
			// TODO: redraw the field when "No" is clicked
			if(Ui::dialogbox(std::string("Quit?"), std::vector<std::string> {std::string("No"), std::string("Yes")}) == 1) return;
			m_ui->draw_border();
			m_ui->draw_static_elements();
		}
		catch(const GameEndDeath &) 
		{
			Ui::dialogbox(std::string("You died"), std::vector<std::string> {std::string("OK")});
			return;
		}
	}
}
