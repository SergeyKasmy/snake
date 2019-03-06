#include <stdexcept>
#include "player.hpp"

void Player::move(Point p_field_size)
{
	switch (m_facing)
	{
		case Facing::right:
		{
			if(m_position[0].x + 1 == p_field_size.x)
				m_position.insert(m_position.begin(), { m_position.front().y, 0 });
			else
				m_position.insert(m_position.begin(), { m_position.front().y, m_position.front().x + 1 });
			break;
		}
		case Facing::down:
		{
			if(m_position[0].y + 1 == p_field_size.y)
				m_position.insert(m_position.begin(), { 0, m_position.front().x });
			else
				m_position.insert(m_position.begin(), { m_position.front().y + 1, m_position.front().x });
			break;
		}
		case Facing::left:
		{
			if(m_position[0].x - 1 == -1)
				m_position.insert(m_position.begin(), { m_position.front().y, p_field_size.x - 1 });
			else
				m_position.insert(m_position.begin(), { m_position.front().y, m_position.front().x - 1 });
			break;
		}
		case Facing::up:
		{
			if(m_position[0].y - 1 == -1)
				m_position.insert(m_position.begin(), { p_field_size.y - 1, m_position.front().x });
			else
				m_position.insert(m_position.begin(), { m_position.front().y - 1, m_position.front().x });
			break;
		}
		default:
		{
			throw std::invalid_argument("Player has wrong Facing");
		}
	}

	if(m_position.size() > m_length) m_position.pop_back();
}

void Player::set_facing(Facing p_facing)
{
	switch (p_facing)
	{
		case Facing::right:
			if(m_facing != Facing::left) m_facing = p_facing;
			break;
		case Facing::left:
			if(m_facing != Facing::right) m_facing = p_facing;
			break;
		case Facing::down:
			if(m_facing != Facing::up) m_facing = p_facing;
			break;
		case Facing::up:
			if(m_facing != Facing::down) m_facing = p_facing;
			break;
		default:
			break;
	}
}