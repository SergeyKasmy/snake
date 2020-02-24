#pragma once

#include <exception>

#include "ui.hpp"

class Field;
class Player;

struct GameEndDeath : std::exception {};
struct GameEndQuit : std::exception {};

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
