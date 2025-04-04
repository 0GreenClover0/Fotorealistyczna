#include "Sphere.h"

#include "MathHelpers.h"

Sphere::Sphere(const Vector& p, float radius, std::shared_ptr<Material> const& mat) : center(p), radius(radius)
{
    material = mat;
}

void Sphere::hit(const Ray& ray, HitResult& hitResult)
{
    Vector originCenter = ray.origin - center;
    float a = ray.direction.lengthSquared();
    float b = 2.0f * ray.direction.dot(originCenter);
    float c = originCenter.lengthSquared() - radius * radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f)
    {
        return; // No intersection
    }

    // Compute both possible intersection distances
    float sqrtDiscriminant = std::sqrt(discriminant);
    float a2 = 2.0f * a;
    float root1 = (-b - sqrtDiscriminant) / a2;
    float root2 = (-b + sqrtDiscriminant) / a2;

    // Ensure t1 is the smaller value
    if (root1 > root2) std::swap(root1, root2);

    // If both intersections are behind the ray origin, return false
    if (root2 < 0)
    {
        return;
    }

    // Choose the closest valid intersection
    float root = root1 >= 0 ? root1 : root2; // If root1 is negative, use root2 (ray starts inside sphere)

    // Compute intersection point

    hitResult.hitPoint = ray.origin + ray.direction * root;
    hitResult.material = getMaterial();
}
