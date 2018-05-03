/*
 * PhysicsModule declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_PHYSICSMODULE_HPP
#define PHYSTEST_PHYSICSMODULE_HPP


#include <iostream>

#include "../entity/PhysicsEntity.hpp"

class PhysicsModule {
protected:
	std::string m_moduleName;
public:
	PhysicsModule() : m_moduleName("PhysicsModule") {}

	virtual void runFrame(PhysicsEntity &entity) {};

	virtual std::string getName() {};
};


#endif //PHYSTEST_PHYSICSMODULE_HPP