#pragma once

#include <exception>

#include "field.hpp"

class GameUI;
class Player;

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
		Game(GameUI *p_ui);
		~Game();

		void start();
};