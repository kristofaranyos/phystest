#include "MoveModule.hpp"

void MoveModule::runFrame(PhysicsEntity &entity) {
	int tPosX, tPosY;
	float tSpeedY, tTime;

	tTime = (SDL_GetTicks() - entity.getCreatedAt()) * TO_SEC;
	tSpeedY = entity.getVel().second + GRAVITY * tTime;
	tPosX = (int)std::round(entity.getPos().first + entity.getVel().first * tTime);
	tPosY = (int)std::round(entity.getPos().second + entity.getVel().second * tTime + GRAVITY / 2.f * tTime * tTime);

	//X bounds
	if (tPosX < 0) {
		entity.setPos(std::pair<int, int>(0, 0), PhysicsEntity::ParamSelect::First);
		entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), PhysicsEntity::ParamSelect::First);
	} else if (tPosX > SCREEN_WIDTH - entity.getSize().first) {
		entity.setPos(std::pair<int, int>(SCREEN_WIDTH - entity.getSize().first, 0), PhysicsEntity::ParamSelect::First);
		entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), PhysicsEntity::ParamSelect::First);
	} else {
		entity.setPos(std::pair<int, int>(tPosX, 0), PhysicsEntity::ParamSelect::First);
	}

	//Y bounds
	if (tPosY < SCREEN_HEIGHT - entity.getSize().first) {
		entity.setPos(std::pair<int, int>(0, tPosY), PhysicsEntity::ParamSelect::Second);
		entity.setVel(std::pair<float, float>(0.f, tSpeedY), PhysicsEntity::ParamSelect::Second);
	} else {
		entity.setPos(std::pair<int, int>(0, SCREEN_HEIGHT - entity.getSize().second), PhysicsEntity::ParamSelect::Second);
		entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::Second);
	}

	//friction
	if (tPosY >= SCREEN_HEIGHT - entity.getSize().first) {
		if (entity.getVel().first > 0) {
			if (entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime > 0) {
				float newVelX = entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime;
				entity.setVel(std::pair<int, int>(newVelX, 0), PhysicsEntity::ParamSelect::First);

				int newX = entity.getPos().first - (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
				entity.setPos(std::pair<int, int>(newX, 0), PhysicsEntity::ParamSelect::First);
			} else {
				entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::First);
			}
		} else if (entity.getVel().first < 0) {
			if (entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime < 0) {
				float newVelX = entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime;
				entity.setVel(std::pair<int, int>(newVelX, 0), PhysicsEntity::ParamSelect::First);

				int newX = entity.getPos().first + (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
				entity.setPos(std::pair<int, int>(newX, 0), PhysicsEntity::ParamSelect::First);
			} else {
				entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::First);
			}
		}
	}
}