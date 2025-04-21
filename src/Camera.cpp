#include "Camera.h"

#include "Global.h"
#include "Material.h"
#include "MathHelpers.h"

#include <execution>
#include <iostream>
#include <ranges>
#include <vector>

void Camera::render(const std::shared_ptr<HittableList>& world)
{
    initialize();

    auto range = std::views::iota(0, bitmap->height);

    std::for_each(std::execution::par_unseq, range.begin(), range.end(), [&](int const y)
    {
        std::cout << y << "\n";
        for (int x = 0; x < bitmap->width; x++)
        {
            Vector pixelColor = {};

            for (int i = 0; i < samplesPerPixel; i++)
            {
                Ray ray = getRay(x, y);
                pixelColor = pixelColor + rayGetColor(ray, maxDepth, world);
            }

            bitmap->data[y][x] = pixelSamplesScale * pixelColor;
        }
    });
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

    if (isOrthographic)
    {
        Vector viewportUpperLeft = center - w - viewportU / 2.0f - viewportV / 2.0f;
        pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
    }
    else
    {
        Vector viewportUpperLeft = center - (focalLength * w) - viewportU / 2.0f - viewportV / 2.0f;
        pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
    }
}

Vector Camera::rayGetColor(const Ray& ray, int depth, const std::shared_ptr<HittableList>& world) const
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    Vector viewDirection = -ray.direction;
    HitResult hitResult = HitResult();
    world->hit(ray, Interval(0.001f, std::numeric_limits<float>::max()), hitResult);

    // If the ray hits nothing, return the background color.
    if (hitResult.point.isInvalid())
    {
        return backgroundColor;
    }

    Ray scatteredRay;
    Vector attenuation;
    Vector emitted_color = hitResult.material->emitted(0.f, 0.f, {});

    if (!hitResult.material->scatter(ray, hitResult, attenuation, scatteredRay))
    {
        return emitted_color;
    }

    Vector const scattered_color = attenuation * rayGetColor(scatteredRay, depth - 1, world);

    return scattered_color + emitted_color;
}

Ray Camera::getRay(int x, int y) const
{
    if (isOrthographic)
    {
        Vector offset = sampleSquare();
        Vector pixel_sample = pixel00Location + (static_cast<float>(x) + 0.5f + offset.x) * pixelDeltaU + (static_cast<float>(y) + 0.5f + offset.y) * pixelDeltaV;
        Vector ray_origin = pixel_sample;
        Vector ray_direction = (lookAt - lookFrom).normalize();
        return Ray(ray_origin, ray_direction);
    }
    else
    {
        Vector offset = sampleSquare();
        Vector pixel_sample = pixel00Location + (static_cast<float>(x) + 0.5f + offset.x) * pixelDeltaU + (static_cast<float>(y) + 0.5f + offset.y) * pixelDeltaV;
        Vector ray_origin = center;
        Vector ray_direction = (pixel_sample - ray_origin).normalize();
        return Ray(ray_origin, ray_direction);
    }
}

Vector Camera::sampleSquare() const
{
    return { randomFloat(0.0f, 1.0f) - 0.5f, randomFloat(0.0f, 1.0f) - 0.5f, 0.0f };
}
