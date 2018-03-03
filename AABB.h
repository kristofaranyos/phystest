/**
 * AABB declarations
 *
 * @author kristof
 * @version 1.0.0
 */
#ifndef PHYSTEST_AABB_H
#define PHYSTEST_AABB_H

#include <utility>

#include <SDL2/SDL.h>

class AABB {
private:
    unsigned int m_entityId;
    int m_posX;
    int m_posY;
    int m_width;
    int m_height;
    float m_velX; // positive = right, negative = left
    float m_velY; // positive = down. negative = up
    Uint32 m_createdAt;
public:
    AABB(unsigned int m_entityId, Uint32 createdAt);
	AABB(unsigned int m_entityId, int posX, int posY, int width, int height, float velX, float velY, Uint32 createdAt);

	enum ParamSelect {First, Second, Both};

	void setPos(std::pair<int, int> position, ParamSelect params);
	std::pair<int, int> getPos() const;

	void setSpeed(std::pair<float, float> speed, ParamSelect params);
	std::pair<float, float> getSpeed() const;

	void setSize(std::pair<int, int> position, ParamSelect params);
	std::pair<int, int> getSize() const;

};


#endif //PHYSTEST_AABB_H