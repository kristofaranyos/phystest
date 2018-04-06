//
// Created by kristof on 2018.03.31..
//

#ifndef PHYSTEST_MOVEMODULE_HPP
#define PHYSTEST_MOVEMODULE_HPP

#include "PhysicsModule.hpp"
class MoveModule : public PhysicsModule {
public:
	void runFrame(PhysicsEntity &entity);

};


#endif //PHYSTEST_MOVEMODULE_HPP
