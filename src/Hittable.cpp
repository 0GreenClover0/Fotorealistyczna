#include "Hittable.h"

std::shared_ptr<Material> Hittable::getMaterial() const
{
    return material;
}
