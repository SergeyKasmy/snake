#include <random>
#include "field.hpp"
#include "player.hpp"

Field::Field(point p_field_size) : m_field_size(p_field_size)
{
	m_field = new Object*[m_field_size.y];
	for(int row = 0; row < m_field_size.y; row++)
	{
		m_field[row] = new Object[m_field_size.x];
	}

	for(int y = 0; y < m_field_size.y; ++y)
	{
		for(int x = 0; x < m_field_size.x; ++x)
		{
			m_field[y][x] = Object::empty;
		}
	}
	
}

Field::~Field()
{
	for(int row = 0; row < m_field_size.y; row++) delete [] m_field[row];
	delete [] m_field;
}

void Field::place_food()
{
	bool occupied = true;
	while(occupied)
	{  
		// pseudo-random number generator
		static std::mt19937 rng;
		// generate a seed from a random device in the system
		rng.seed(std::random_device()());
		// make a class to distribute the random numbers
		static std::uniform_int_distribution<std::mt19937::result_type> disty(0, m_field_size.y - 1);
		static std::uniform_int_distribution<std::mt19937::result_type> distx(0, m_field_size.x - 1);

		point new_food = {(int) disty(rng), (int) distx(rng)};
		if(m_field[new_food.y][new_food.x] == Object::empty)
		{
			m_field[new_food.y][new_food.x] = Object::food;
			occupied = false;
		}
	}
}

void Field::add_walls()
{
	for(int y = 0; y < m_field_size.y; y++)
	{
		m_field[y][0] = Object::wall;
		m_field[y][m_field_size.x - 1] = Object::wall;
	}

	for(int x = 0; x < m_field_size.x; x++)
	{
		m_field[0][x] = Object::wall;
		m_field[m_field_size.y - 1][x] = Object::wall;
	}
}

void Field::update_player(Player *p_player)
{
	for(int row = 0; row < m_field_size.y; ++row)
	{
		for(int col = 0; col < m_field_size.x; ++col)
		{
			if (m_field[row][col] == Object::player) 
			{
				m_field[row][col] = Object::empty;
			}
		}
	}

	for(int i = 0; i < p_player->size(); ++i)
	{
		point player_point = p_player->get(i);
		m_field[player_point.y][player_point.x] = Object::player;
	}
}