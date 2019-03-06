#include <chrono>
#include <exception>
#include <unistd.h>

#include "game.hpp"

#include "player.hpp"
#include "ui.hpp"

struct GameEnd : std::exception {};

void Game::tick()
{
	const static std::chrono::milliseconds TICK_DURATION(225);
	auto last_tick = std::chrono::high_resolution_clock::now();
	Facing input;

	while(true)
	{
		if((input = m_ui->get_input()) != Facing::null) m_player->facing = input;
		
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
			m_field->set(player_head, Object::empty);
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
	m_ui->draw_field();
}


Game::Game(GameUI *p_ui, Point p_field_size) : m_ui(p_ui)
{
	m_field = new Field(p_field_size);
	m_ui->set_field(m_field);

	m_player = new Player();
}

Game::~Game()
{
	delete m_field;
	delete m_player;
}

int Game::start()
{
	m_field->add_walls();
	m_field->place_food();

	try
	{
		tick();
	}
	catch(const GameEnd &)
	{
		return 1;
	}

	return 0;
}