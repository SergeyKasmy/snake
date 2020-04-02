#pragma once

#include "ui.hpp"
#include "player.hpp"
#include "field.hpp"

class Controller
{
	private:
		Ui m_ui;
		Player *m_player = nullptr;
		Field *m_field = nullptr;
		void new_game();
		int tick();
	public:
		void start();
};
