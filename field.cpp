#include <random>
#include "field.hpp"
#include "player.hpp"
#include "settings.hpp"

Field::Field() : m_field_size(Settings::field_size)
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
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> disty(0, m_field_size.y - 1);
    std::uniform_int_distribution<int> distx(0, m_field_size.x - 1);
    Point location = {disty(rng), distx(rng)};
    while(get(location) != Object::empty)
    {  
        location = {disty(rng), distx(rng)};
    }
    set(location, Object::food);
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
		Point player_point = p_player->get(i);
		m_field[player_point.y][player_point.x] = Object::player;
	}
}