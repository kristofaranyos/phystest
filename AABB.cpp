//
// Created by kristof on 2018.03.03..
//

#include "AABB.h"

AABB::AABB(unsigned int m_entityId, unsigned int createdAt)
	: m_entityId(m_entityId)
	, m_posX(0)
	, m_posY(0)
	, m_width(0)
	, m_height(0)
	, m_velX(0)
	, m_velY(0)
	, m_createdAt(createdAt)
{}

AABB::AABB(unsigned int entityId, int posX, int posY, int width, int height, int velX, int velY, unsigned int createdAt)
	: m_entityId(entityId)
	, m_posX(posX)
	, m_posY(posY)
	, m_width(width)
	, m_height(height)
	, m_velX(velX)
	, m_velY(velY)
	, m_createdAt(createdAt)
{}


void AABB::setPos(std::pair<int, int> position, ParamSelect params) {
	if (params == ParamSelect::First || params == ParamSelect::Both) {
		if (position.first >= 0) {
			this->m_posX = position.first;
		} else {
			//todo throw OutOfBoundsException
		}
	}

	if (params == ParamSelect::Second || params == ParamSelect::Both) {
		if (position.second >= 0) {
			this->m_posY = position.second;
		} else {
			//todo throw OutOfBoundsException
		}
	}
}

std::pair<int, int> AABB::getPos() const {
	return std::pair<int, int>(this->m_posX, this->m_posY);
}


void AABB::setSpeed(std::pair<int, int> speed, ParamSelect params){
	if (params == ParamSelect::First || params == ParamSelect::Both) {
		if (speed.first >= 0) {
			this->m_velX = speed.first;
		} else {
			//todo throw OutOfBoundsException
		}
	}

	if (params == ParamSelect::Second || params == ParamSelect::Both) {
		if (speed.second >= 0) {
			this->m_velY = speed.second;
		} else {
			//todo throw OutOfBoundsException
		}
	}
}

std::pair<int, int> AABB::getSpeed() const {
	return std::pair<int, int>(this->m_velX, this->m_velY);
}

