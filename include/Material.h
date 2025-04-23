#pragma once

#include "Global.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Vector.h"

#include <algorithm>

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray_in, const HitResult& hit_result, Vector& attenuation, Ray& scattered) const = 0;

    virtual Vector emitted(float u, float v, const Vector& p) const
    {
        return {};
    }
};

class Phong final : public Material
{
public:
    Phong(const Vector& diffuse, const Vector& specular, float shininess = 0.0f) : diffuse(diffuse), specular(specular), shininess(shininess) {}

    virtual bool scatter(const Ray& ray_in, const HitResult& hit_result, Vector& attenuation, Ray& scattered) const override
    {
        Vector const normal = hit_result.normal;

        Vector scatter_direction = normal + Vector::random_unit_vector();

        if (scatter_direction.nearZero())
        {
            scatter_direction = normal;
        }

        scattered = Ray(hit_result.point, scatter_direction);

        attenuation = diffuse;

        return true;
    }

    Vector lightColor(const HitResult& hitResult) const
    {
        Vector lightColor = { 0.0f, 0.0f, 0.0f };
        Vector const normal = hitResult.normal;

        for (auto const& light : lights)
        {
            // Send shadow ray to the light to check if it is occluded
            HitResult lightResult = HitResult();

            Vector lightDirection = light->position - hitResult.point;
            float distanceSquared = lightDirection.lengthSquared();
            float distance = std::sqrt(distanceSquared);
            lightDirection = lightDirection.normalize();

            Ray shadowRay = Ray(hitResult.point + lightDirection * 0.0001f, lightDirection);
            Global::world->hit(shadowRay, Interval(0.0f, distance), lightResult);

            if (!lightResult.point.isInvalid())
            {
                continue;
            }

            // Calculate light influence, Phong model
            float diff = std::fmax(normal.dot(lightDirection), 0.0f);
            Vector diffuse = diff * light->diffuse * this->diffuse;

            // Vector halfwayDirection = (lightDirection + viewDirection).normalize();
            // float spec = std::powf(std::fmax(normal.dot(halfwayDirection), 0.0f), hitResult.hittable->getMaterial()->shininess);
            // Vector specular = spec * light->specular * hitResult.hittable->getMaterial()->specular;
            Vector specular = {};
            float attenuation = 1.0f / (light->constant + light->linear * distance + light->quadratic * distanceSquared);

            lightColor += (diffuse + specular) * attenuation;
        }

        Vector hitColor = lightColor;

        return hitColor;
    }

    Vector diffuse = {};
    Vector specular = {};
    float shininess = 1.0f;
};

class Reflective final : public Material
{
public:
    Reflective() {}

    virtual bool scatter(const Ray& ray_in, const HitResult& hit_result, Vector& attenuation, Ray& scattered) const override
    {
        attenuation = Vector(1.0f, 1.0f, 1.0f);

        Vector const normal = hit_result.normal;
        Vector const newDirection = ray_in.direction - 2.0f * normal * normal.dot(ray_in.direction);
        scattered = { hit_result.point + normal * 0.0001f, newDirection };

        return true;
    }
};

class Refractive final : public Material
{
public:
    Refractive(Vector const& absorptionColor, float ior) : absorptionColor(absorptionColor), refractionIndex(ior) {}

    virtual bool scatter(const Ray& ray_in, const HitResult& hitResult, Vector& attenuation, Ray& scattered) const override
    {
        float ri = hitResult.frontFace ? (1.0f / refractionIndex) : refractionIndex;

        Vector normal = hitResult.normal;

        Vector unit_direction = ray_in.direction.normalize();
        float cos_theta = std::fminf((-unit_direction).dot(normal), 1.0f);
        float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0f;
        Vector direction;

        if (cannot_refract || reflectance(cos_theta, ri) > randomFloat(0.0f, 1.0f))
        {
            direction = Vector::reflect(unit_direction, normal);
            attenuation = Vector(1.0f, 1.0f, 1.0f);
        }
        else
        {
            direction = Vector::refract(unit_direction, normal, ri);

            // Beer's Law attenuation
            if (!hitResult.frontFace)
            {
                float distance = hitResult.t;
                Vector absorption = Vector(
                    expf(-absorptionColor.x * distance),
                    expf(-absorptionColor.y * distance),
                    expf(-absorptionColor.z * distance)
                );

                attenuation = absorption;
            }
            else
            {
                attenuation = Vector(1.0f, 1.0f, 1.0f); // Entering the dielectric
            }
        }

        scattered = Ray(hitResult.point, direction);

        return true;
    }

    Vector absorptionColor = Vector(0.0f, 0.0f, 0.0f); // Beer's Law coefficient
    float refractionIndex = 1.0f;

private:
    static float reflectance(const float cosine, const float refraction_index)
    {
        float r0 = (1.0f - refraction_index) / (1.0f + refraction_index);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * powf((1.0f - cosine), 5.0f);
    }
};

class DiffuseLight final : public Material
{
public:
    DiffuseLight(const Vector& emit) : diffuse(emit) {}

    virtual bool scatter(const Ray& ray_in, const HitResult& hit_result, Vector& attenuation, Ray& scattered) const override
    {
        return false;
    }

    virtual Vector emitted(float u, float v, const Vector& p) const override
    {
        return diffuse;
    }

private:
    Vector diffuse;
};
