/**
 * Axis Aligned Bounding Box: basic rectangle-like entity
 *
 * @author kristof
 * @version 1.0.1
 */

#include "AABB.h"

/**
 * Basic ctor for AABB
 *
 * @param m_entityId ID of the entity (so its trackable among multiple instances)
 * @param createdAt Uint32 timestamp of creation returned by SDL_GetTicks()
 */
AABB::AABB(unsigned long m_entityId, Uint32 createdAt)
	: m_entityId(m_entityId)
	, m_posX(0)
	, m_posY(0)
	, m_width(0)
	, m_height(0)
	, m_velX(0)
	, m_velY(0)
	, m_createdAt(createdAt)
{}

/**
 * Full ctor for AABB
 *
 * @param entityId ID of the entity (so its trackable among multiple instances)
 * @param posX X position of the entity (>=0)
 * @param posY Y position of the entity (>=0)
 * @param width Width of entity (>=0)
 * @param height Height of entity (>=0)
 * @param velX X velocity of entity (>=0)
 * @param velY Y velocity of entity (>=0)
 * @param createdAt Uint32 timestamp of creation returned by SDL_GetTicks()
 */
AABB::AABB(unsigned long entityId, int posX, int posY, int width, int height, float velX, float velY, Uint32 createdAt)
	: m_entityId(entityId)
	, m_posX(posX)
	, m_posY(posY)
	, m_width(width)
	, m_height(height)
	, m_velX(velX)
	, m_velY(velY)
	, m_createdAt(createdAt)
{}

/**
 * Sets one or two components of the position of the entity
 *
 * @param position std::pair<int, int> containing x and y positions, unused position can be arbitrary
 * @param params ParamSelect enum defining which position to set
 */
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

/**
 * Returns the current position of the entity
 *
 * @return std::pair<int, int> containing x and y position
 */
std::pair<int, int> AABB::getPos() const {
	return std::pair<int, int>(this->m_posX, this->m_posY);
}

/**
 * Sets one or two components of the speed of the entity
 *
 * @param speed position std::pair<float, float> containing x and y speeds, unused position can be arbitrary
 * @param params ParamSelect enum defining which speed to set
 */
void AABB::setSpeed(std::pair<float, float> speed, ParamSelect params){
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

/**
 * Returns the current speed of the entity
 *
 * @return std::pair<int, int> containing x and y speed
 */
std::pair<float, float> AABB::getSpeed() const {
	return std::pair<int, int>(this->m_velX, this->m_velY);
}

/**
 * Sets one or two components of the size of the entity
 *
 * @param position std::pair<float, float> containing width and height, unused position can be arbitrary
 * @param params ParamSelect enum defining which size to set
 */
void AABB::setSize(std::pair<int, int> size, ParamSelect params) {
	if (params == ParamSelect::First || params == ParamSelect::Both) {
		if (size.first >= 0) {
			this->m_width = size.first;
		} else {
			//todo throw OutOfBoundsException
		}
	}

	if (params == ParamSelect::Second || params == ParamSelect::Both) {
		if (size.second >= 0) {
			this->m_height = size.second;
		} else {
			//todo throw OutOfBoundsException
		}
	}
}

/**
 * Returns the current size of the entity
 *
 * @return std::pair<int, int> containing width and height
 */
std::pair<int, int> AABB::getSize() const {
	return std::pair<int, int>(this->m_width, this->m_height);
}

/**
 * Returns the entity id
 *
 * @return unsigned long m_entityId
 */
unsigned long AABB::getEntityId() const {
	return this->m_entityId;
}

/**
 * Returns the timestamp of creation
 *
 * @return Uint32 m_createdAt
 */

Uint32 AABB::getCreatedAt() const {
	return this->m_createdAt;
}

void AABB::draw(SDL_Renderer *renderer, SDL_Color color) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = 1; i < this->m_width ; ++i) {
		for (int j = 1; j < this->m_height; ++j) {
			SDL_RenderDrawPoint(renderer, this->m_posX + i, this->m_posY + j);
		}
	}
}