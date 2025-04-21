#pragma once

#include "Light.h"

#include <vector>

class HittableList;

extern std::vector<std::shared_ptr<Light>> lights;

namespace Global
{
    extern std::shared_ptr<HittableList> world;
}
