#pragma once

#include "ui.hpp"
#include "player.hpp"
#include "field.hpp"

class Controller
{
	private:
		GameUi *m_ui = nullptr;
		Player m_player;
		Field m_field;
		void new_game();
		int tick();
	public:
		void start();
};
