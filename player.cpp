#include <stdexcept>
#include "player.hpp"

void Player::move(point p_field_size)
{
	switch (facing)
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
			throw std::invalid_argument("The player has wrong Facing");
		}
	}

	if(m_position.size() > m_length) m_position.pop_back();
}