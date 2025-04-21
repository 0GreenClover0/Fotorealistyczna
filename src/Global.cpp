#include "Global.h"

std::vector<std::shared_ptr<Light>> lights = {};

namespace Global
{
   std::shared_ptr<HittableList> world;
}
