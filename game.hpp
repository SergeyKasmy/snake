#pragma once

#include "field.hpp"

class GameUI;
class Player;

const static Point FIELD_SIZE = {18, 35};

class Game
{
	private:
		GameUI *m_ui;
		Field *m_field;
		Player *m_player;

		void tick();
		void update();
	public:
		Game(GameUI *p_ui, Point p_field_size = FIELD_SIZE);
		~Game();

		int start();
};