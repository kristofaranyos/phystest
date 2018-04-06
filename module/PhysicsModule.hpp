/*
 * PhysicsModule declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_PHYSICSMODULE_HPP
#define PHYSTEST_PHYSICSMODULE_HPP

#include "../entity/PhysicsEntity.hpp"

class PhysicsModule {
private:

public:
	void runFrame(PhysicsEntity &entity);
};


#endif //PHYSTEST_PHYSICSMODULE_HPP