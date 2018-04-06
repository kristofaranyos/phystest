#ifndef PHYSTEST_MOVEMODULE_HPP
#define PHYSTEST_MOVEMODULE_HPP


#include "PhysicsModule.hpp"

#include "../PhysicsEngine.hpp"

class MoveModule : public PhysicsModule {
public:
	void runFrame(PhysicsEntity &entity);
};


#endif //PHYSTEST_MOVEMODULE_HPP
