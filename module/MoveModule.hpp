#ifndef PHYSTEST_MOVEMODULE_HPP
#define PHYSTEST_MOVEMODULE_HPP


#include "../PhysicsIncludes.hpp"

class MoveModule : public PhysicsModule {
public:
	void runFrame(PhysicsEntity &entity);
};


#endif //PHYSTEST_MOVEMODULE_HPP
