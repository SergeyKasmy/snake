#include "controller.hpp"

#include "ui.hpp"

void Controller::game_start()
{
	m_menu.new_game();
	m_game.start();
}
