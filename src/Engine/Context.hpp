#pragma once
#include "ResourceManager.hpp"

namespace Engine {

class Context {
public:
	Context();
	~Context();

	ResourceManager resource_manager;

private:

};
} // Engine
