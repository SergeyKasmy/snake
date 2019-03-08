#include <chrono>
#include <exception>
#include <unistd.h>

#include "game.hpp"

#include "player.hpp"
#include "settings.hpp"
#include "ui.hpp"

void Game::tick()
{
	const static std::chrono::milliseconds TICK_DURATION(225);
	auto last_tick = std::chrono::high_resolution_clock::now();

	while(true)
	{
		m_player->set_facing(m_ui->get_input());
		
		// true if the time of the next tick(last tick + tick duration) is in the past
		while((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
		{
			update();
			last_tick += TICK_DURATION;
		}

		// sleep for 25 ms
		usleep(25 * 1000);
	}
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
			throw GameEnd();
			break;
		}
		default:
			break;
	}
	
	m_field->update_player(m_player);
	m_player->move(m_field->m_field_size);
	m_ui->update(m_player->length() - 1);
}


Game::Game(GameUI *p_ui) : m_ui(p_ui)
{
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

	try
	{
		tick();
	}
	catch(const GameEnd &) 
	{
		UIUtils::dialogbox(std::string("Texty"), std::vector<std::string> {std::string("Button1"), std::string("Button2")});
	}
}