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
    Vector viewDirection = -ray.direction;
    HitResult hitResult = { .hittable = nullptr, .hitPoint = Vector::invalid(), .t = 0.0f };
    world->hit(ray, Interval(0.0f, FLT_MAX), hitResult);

    if (hitResult.hitPoint.isInvalid())
    {
        return backgroundColor;
    }

    if (depth <= 0)
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    if (hitResult.hittable->getMaterial()->materialType == MaterialType::Reflective)
    {
        Vector const normal = hitResult.hittable->getNormal(hitResult.hitPoint);
        Vector const newDirection = ray.direction - 2.0f * normal * normal.dot(ray.direction);
        Ray const reflectedRay = { hitResult.hitPoint + normal * 0.0001f, newDirection };
        return rayGetColor(reflectedRay, depth - 1, world);
    }

    if (hitResult.hittable->getMaterial()->materialType == MaterialType::Refractive)
    {
        Vector const normal = hitResult.hittable->getNormal(hitResult.hitPoint);
        Vector const unitDir = ray.direction.normalize();
        float ior = hitResult.hittable->getMaterial()->ior;
        float cos_theta = -unitDir.negative().normalize().dot(normal);
        bool entering = cos_theta < 0.0f;

        Vector n = entering ? normal : normal.negative();
        cos_theta = std::abs(cos_theta);

        float etai = entering ? 1.0f : ray.currentMaterial->ior;
        float etat = entering ? ray.currentMaterial->ior : 1.0f;
        float eta = etai / etat;

        float refrRatio = entering ? (1.0f / ior) : ior;
        float k = 1 - refrRatio * refrRatio * (1.0f - cos_theta * cos_theta);

        if (k >= 0)
        {
            Vector refractedDir = ray.direction * refrRatio + (refrRatio * cos_theta - sqrt(k)) * n;
            Ray refractedRay = Ray(hitResult.hitPoint + refractedDir * 0.0001f, refractedDir);
            return rayGetColor(refractedRay, depth - 1, world);
        }

        Vector reflectedDir = Vector::reflect(ray.direction, n);
        Ray reflectedRay = Ray(hitResult.hitPoint + reflectedDir * 0.0001f, reflectedDir);
        return rayGetColor(reflectedRay, depth - 1, world);

        // Vector r_out_perp = eta * (unitDir + cos_theta * n);
        // Vector r_out_parallel = -std::sqrt(std::fabs(1.0f - r_out_perp.lengthSquared())) * n;
        // Vector refracted = r_out_perp + r_out_parallel;
        //
        // Ray refractedRay = {
        //     hitResult.hitPoint - n * 0.0001f,
        //     refracted.normalize(),
        //     hitResult.hittable->getMaterial()
        // };
        //
        // return rayGetColor(refractedRay, depth - 1, world);
    }

    // if (hitResult.hittable->getMaterial()->materialType == MaterialType::Refractive)
    // {
    //     Vector const n = hitResult.hittable->getNormal(hitResult.hitPoint);
    //
    //     float cos_theta = -ray.direction.negative().dot(n);
    //     float refr_ratio = 1.0f / hitResult.hittable->getMaterial()->ior;
    //     float k = 1.0f - refr_ratio * refr_ratio * (1.0f - cos_theta * cos_theta);
    //
    //     Vector refractedDir = ray.direction * refr_ratio + (refr_ratio * cos_theta - sqrt(k)) * n;
    //
    //     Ray refractedRay = {
    //                 hitResult.hitPoint + refractedDir * 0.0001f,
    //                 refractedDir,
    //                 hitResult.hittable->getMaterial()
    //     };
    //
    //     return rayGetColor(refractedRay, depth - 1, world);
    // }

    Vector lightColor = { 0.0f, 0.0f, 0.0f };
    Vector normal = hitResult.hittable->getNormal(hitResult.hitPoint);

    for (auto const& light : lights)
    {
        // Send shadow ray to the light to check if it is occluded
        HitResult lightResult = { .hittable = nullptr, .hitPoint = Vector::invalid(), .t = 0.0f };

        Vector lightDirection = light->position - hitResult.hitPoint;
        float distanceSquared = lightDirection.lengthSquared();
        float distance = std::sqrt(distanceSquared);
        lightDirection = lightDirection.normalize();

        Ray shadowRay = Ray(hitResult.hitPoint + lightDirection * 0.0001f, lightDirection);
        world->hit(shadowRay, Interval(0.0f, distance), lightResult);

        if (!lightResult.hitPoint.isInvalid())
        {
            continue;
        }

        // Calculate light influence, Phong model
        float diff = std::fmax(normal.dot(lightDirection), 0.0f);
        Vector diffuse = diff * light->diffuse * hitResult.hittable->getMaterial()->diffuse;

        Vector halfwayDirection = (lightDirection + viewDirection).normalize();
        float spec = std::powf(std::fmax(normal.dot(halfwayDirection), 0.0f), hitResult.hittable->getMaterial()->shininess);
        Vector specular = spec * light->specular * hitResult.hittable->getMaterial()->specular;

        float attenuation = 1.0f / (light->constant + light->linear * distance + light->quadratic * distanceSquared);

        lightColor += (diffuse + specular) * attenuation;
    }

    Vector hitColor = lightColor + ambientColor;

    return hitColor;
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
