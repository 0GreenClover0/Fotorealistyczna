#pragma once

#include <memory>

#include "Bitmap.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Vector.h"

class Camera
{
public:
    float verticalFov = 20.0f;
    Vector lookFrom;
    Vector lookAt;
    Vector vUp;

    Vector backgroundColor = { 0.7f, 0.8f, 1.0f };
    bool isOrthographic = false;

    Camera(const std::shared_ptr<Bitmap>& bitmap, const int samples_per_pixel, const int max_depth)
        : lookFrom(Vector()), lookAt(Vector(0.0f, 0.0f, -1.0f)), vUp(Vector(0.0f, 1.0f, 0.0f)),
        bitmap(bitmap), samplesPerPixel(samples_per_pixel), maxDepth(max_depth)
    {
        imageWidth = bitmap->width;
        imageHeight = bitmap->height;
        aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
    }

    void render(const std::shared_ptr<Hittable>& root);
    void render(const std::shared_ptr<HittableList>& world);

private:
    void initialize();
    Vector rayGetColor(const Ray& ray, int depth, const std::shared_ptr<Hittable>& root) const;
    Vector rayGetColor(const Ray& ray, int depth, const std::shared_ptr<HittableList>& world) const;
    Ray getRay(int x, int y) const;
    // Vec3 sample_square() const;

    float aspectRatio = 0.0f;
    int imageWidth = 0;
    int imageHeight = 0;

    std::shared_ptr<Bitmap> bitmap;

    int samplesPerPixel = 50;
    int maxDepth = 50;

    float pixelSamplesScale = 1.0f;
    Vector center = {};
    Vector pixel00Location = {};
    Vector pixelDeltaU = {};
    Vector pixelDeltaV = {};
    Vector u = {}, v = {}, w = {};
};
