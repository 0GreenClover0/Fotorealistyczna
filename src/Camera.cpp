#include "Camera.h"

#include "MathHelpers.h"

void Camera::render(const std::shared_ptr<Hittable>& root)
{
    initialize();

    for (int y = 0; y < bitmap->height; y++)
    {
        for (int x = 0; x < bitmap->width; x++)
        {
            Ray ray = getRay(x, y);
            bitmap->data[y][x] = rayGetColor(ray, maxDepth, root);
        }
    }
}

void Camera::initialize()
{
    pixelSamplesScale = 1.0f / static_cast<float>(samplesPerPixel);
    center = lookFrom;

    float focalLength = (lookFrom - lookAt).length();
    float theta = radians(verticalFov);
    float h = tan(theta / 2.0f);
    float viewportHeight = 2.0f * h * focalLength;
    float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / static_cast<float>(imageHeight));

    w = (lookFrom - lookAt).normalize();
    u = vUp.cross(w).normalize();
    v = w.cross(u);

    Vector viewportU = viewportWidth * u;
    Vector viewportV = -viewportHeight * v;

    pixelDeltaU = viewportU / static_cast<float>(imageWidth);
    pixelDeltaV = viewportV / static_cast<float>(imageHeight);

    Vector viewportUpperLeft = center - (focalLength * w) - viewportU / 2.0f - viewportV / 2.0f;
    pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}

Vector Camera::rayGetColor(const Ray& ray, int depth, const std::shared_ptr<Hittable>& root) const
{
    if (root->hit(ray).isInvalid())
    {
        return backgroundColor;
    }

    // TODO: Hit should give us appropriate color instead (or a pointer to the material, and then the material has the color() function)
    return Vector(255.0f, 0.0f, 0.0f);
}

Ray Camera::getRay(int x, int y) const
{
    if (isOrthographic)
    {
        // TODO: Ortographic ray
    }
    else
    {
        Vector offset = Vector(); // Antyaliasing ex. sample_square();
        Vector pixel_sample = pixel00Location + (static_cast<float>(x) + offset.x) * pixelDeltaU + (static_cast<float>(y) + offset.y) * pixelDeltaV;
        Vector ray_origin = center;
        Vector ray_direction = pixel_sample - ray_origin;
        return Ray(ray_origin, ray_direction);
    }
}
