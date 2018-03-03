//
// Created by kristof on 2018.03.03..
//

#ifndef PHYSTEST_AABB_H
#define PHYSTEST_AABB_H

#include <utility>

class AABB {
private:
    unsigned int m_entityId;
    int m_posX;
    int m_posY;
    int m_width;
    int m_height;
    float m_velX; // positive = right, negative = left
    float m_velY; // positive = down. negative = up
    unsigned int m_createdAt;
public:
    AABB(unsigned int m_entityId, unsigned int createdAt);
	AABB(unsigned int m_entityId, int posX, int posY, int width, int height, int velX, int velY, unsigned int createdAt);

	enum ParamSelect {First, Second, Both};

	void setPos(std::pair<int, int> position, ParamSelect params);
	std::pair<int, int> getPos() const;

	void setSpeed(std::pair<int, int> speed, ParamSelect params);
	std::pair<int, int> getSpeed() const;

};


#endif //PHYSTEST_AABB_H