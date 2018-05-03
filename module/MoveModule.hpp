/*
 * MoveModule declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_MOVEMODULE_HPP
#define PHYSTEST_MOVEMODULE_HPP


#include <iostream>

#include "../PhysicsIncludes.hpp"

class MoveModule : public PhysicsModule {
protected:
	std::string m_moduleName;
public:
	MoveModule();

	void runFrame(PhysicsEntity &entity) override;

	std::string getName() override;
};


#endif //PHYSTEST_MOVEMODULE_HPP
