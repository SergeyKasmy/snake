#pragma once

#include "field.hpp"
#include "player.hpp"
#include "ui.hpp"

struct GameEnd : std::exception {};

class Game
{
	private:
		GameUI *m_ui;
		Field *m_field;
		Player *m_player;

		void tick();
		void update();
	public:
		Game(GameUI *p_ui, Point p_field_size = {15, 25});
		~Game();

		int start();
};