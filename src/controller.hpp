#pragma once

#include "game.hpp"
#include "ui.hpp"

class Controller
{
	private:
		MainMenu m_menu;
		GameUI m_ui;
		Game m_game;

	public:
		Controller() : m_game(&m_ui) {}
		void game_start();
};
