﻿#include "Camera.h"

#include "Global.h"
#include "MathHelpers.h"

void Camera::render(const std::shared_ptr<HittableList>& world)
{
    initialize();

    for (int y = 0; y < bitmap->height; y++)
    {
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
    HitResult hitResult = {nullptr, Vector::invalid()};
    world->hit(ray, hitResult);

    if (hitResult.hitPoint.isInvalid())
    {
        return backgroundColor;
    }

    Vector lightColor = {1.0f, 1.0f, 1.0f};
    Vector normal = hitResult.hittable->getNormal(hitResult.hitPoint);

    for (auto const& light : lights)
    {
        // Send shadow ray to the light to check if it is occluded
        HitResult lightResult = {nullptr, Vector::invalid()};
        Vector lightDirection = (light->position - hitResult.hitPoint).normalize();
        Ray shadowRay = Ray(hitResult.hitPoint, lightDirection);
        world->hit(shadowRay, lightResult);

        if (!lightResult.hitPoint.isInvalid())
        {
            continue;
        }

        // Calculate light influence
        // Blinn-Phong model
        float diff = std::fmaxf(normal.dot(lightDirection), 0.0f);
        Vector diffuse = diff * light->color;
        lightColor = diffuse;
    }

    Vector const hitColor = ambientColor * lightColor * hitResult.hittable->getMaterial()->color;

    return hitColor;
}

Ray Camera::getRay(int x, int y) const
{
    if (isOrthographic)
    {
        Vector offset = sampleSquare();
        Vector pixel_sample = pixel00Location + (static_cast<float>(x) + 0.5f + offset.x) * pixelDeltaU + (static_cast<float>(y) + 0.5f  + offset.y) * pixelDeltaV;
        Vector ray_origin = pixel_sample;
        Vector ray_direction = lookAt - lookFrom;
        return Ray(ray_origin, ray_direction);
    }
    else
    {
        Vector offset = sampleSquare();
        Vector pixel_sample = pixel00Location + (static_cast<float>(x) + 0.5f + offset.x) * pixelDeltaU + (static_cast<float>(y) + 0.5f + offset.y) * pixelDeltaV;
        Vector ray_origin = center;
        Vector ray_direction = pixel_sample - ray_origin;
        return Ray(ray_origin, ray_direction);
    }
}

Vector Camera::sampleSquare() const
{
    return { randomFloat(0.0f, 1.0f) - 0.5f, randomFloat(0.0f, 1.0f) - 0.5f, 0.0f };
}
