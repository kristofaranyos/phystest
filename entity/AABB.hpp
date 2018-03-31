/*
 * AABB declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_AABB_H
#define PHYSTEST_AABB_H


#include <utility>

#include <SDL2/SDL.h>

class AABB {
private:
    unsigned long m_entityId;
    int m_posX;
    int m_posY;
    int m_width;
    int m_height;
    float m_velX; // positive = right, negative = left
    float m_velY; // positive = down. negative = up
	float m_fricCoeff;
    Uint32 m_createdAt;
public:
    AABB(unsigned long m_entityId, Uint32 createdAt);
	AABB(unsigned long m_entityId, int posX, int posY, int width, int height, float velX, float velY, float fricCoeff, Uint32 createdAt);

	enum class ParamSelect {First, Second, Both};

	void setPos(std::pair<int, int> position, ParamSelect params);
	std::pair<int, int> getPos() const;

	void setVel(std::pair<float, float> speed, ParamSelect params);
	std::pair<float, float> getVel() const;

	void setSize(std::pair<int, int> position, ParamSelect params);
	std::pair<int, int> getSize() const;

	float getFricCoeff() const;
	unsigned long getEntityId() const;
	Uint32 getCreatedAt() const;


	void draw(SDL_Renderer *renderer, SDL_Color color) const;
};


#endif //PHYSTEST_AABB_H