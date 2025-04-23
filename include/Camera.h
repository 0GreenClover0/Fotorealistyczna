#pragma once

#include <memory>

#include "Bitmap.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Vector.h"

class BVHNode;

class Camera
{
public:
    float verticalFov = 20.0f;
    Vector lookFrom;
    Vector lookAt;
    Vector vUp;

    Vector backgroundColor = { 1.4f, 1.6f, 50.0f };
    Vector ambientColor = { 0.01f, 0.01f, 0.01f };
    bool isOrthographic = false;

    Camera(const std::shared_ptr<Bitmap>& bitmap, const int samples_per_pixel, const int max_depth)
        : lookFrom(Vector()), lookAt(Vector(0.0f, 0.0f, -1.0f)), vUp(Vector(0.0f, 1.0f, 0.0f)),
        bitmap(bitmap), samplesPerPixel(samples_per_pixel), maxDepth(max_depth)
    {
        imageWidth = bitmap->width;
        imageHeight = bitmap->height;
        aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
    }

    void render(const std::shared_ptr<BVHNode>& root);

private:
    void initialize();
    Vector rayGetColor(const Ray& ray, int depth, const std::shared_ptr<BVHNode>& root) const;
    Ray getRay(int x, int y) const;
    Vector sampleSquare() const;

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
