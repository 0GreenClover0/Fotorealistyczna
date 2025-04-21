#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Global.h"
#include "Plane.h"
#include "PointLight.h"
#include "Sphere.h"
#include <Windows.h>

#include "Importer.h"
#include "Material.h"
#include "Triangle.h"
#pragma comment(lib, "shell32.lib")

int main()
{
    srand(time(nullptr));

    std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(256, 256);
    Camera camera = Camera(bitmap, 200, 100);
    std::shared_ptr<HittableList> world = std::make_shared<HittableList>();
    Global::world = world;

    camera.verticalFov = 90.0f;
    camera.lookFrom = Vector(0.0f, 0.0f, 8.0f);
    camera.lookAt = Vector(0.0f, 0.0f, 2.0f);
    camera.vUp = Vector(0.0f, 1.0f, 0.0f);

    std::shared_ptr<Material> mat1 = std::make_shared<Reflective>();
    std::shared_ptr<Material> mat2 = std::make_shared<Refractive>(1.35f);
    std::shared_ptr<Material> mat3 = std::make_shared<Phong>(Vector(0.0f, 0.5f, 0.0f), Vector(0.0f, 5.0f, 0.0f), 50.0f);
    std::shared_ptr<Material> matWallWhite = std::make_shared<Phong>(Vector(0.9f, 0.9f, 0.9f), Vector(1.5f, 1.5f, 1.5f), 50.0f);
    std::shared_ptr<Material> matWallRed = std::make_shared<Phong>(Vector(0.9f, 0.0f, 0.0f), Vector(0.005f, 0.005f, 0.005f), 5.0f);
    std::shared_ptr<Material> matWallBlue = std::make_shared<Phong>(Vector(0.0f, 0.9f, 0.0f), Vector(0.005f, 0.005f, 0.005f), 5.0f);
    std::shared_ptr<Material> matDiffuseLight = std::make_shared<DiffuseLight>(Vector(2.0f, 2.0f, 2.0f));

    std::shared_ptr<Plane> plane1 = std::make_shared<Plane>(Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 1.0f), matWallWhite);
    std::shared_ptr<Plane> plane2 = std::make_shared<Plane>(Vector(0.0f, 4.0f, 0.0f), Vector(0.0f, -1.0f, 0.0f), matWallWhite);
    std::shared_ptr<Plane> plane3 = std::make_shared<Plane>(Vector(0.0f, -4.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), matWallWhite);
    std::shared_ptr<Plane> plane4 = std::make_shared<Plane>(Vector(-4.0f, 0.0f, 0.0f), Vector(1.0f, 0.0f, 0.0f), matWallRed);
    std::shared_ptr<Plane> plane5 = std::make_shared<Plane>(Vector(4.0f, 0.0f, 0.0f), Vector(-1.0f, 0.0f, 0.0f), matWallBlue);
    std::shared_ptr<Plane> plane6 = std::make_shared<Plane>(Vector(0.0f, 0.0f, 8.1f), Vector(0.0f, 0.0f, -1.0f), matWallBlue);

    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector(-1.1f, 0.0f, 2.3f), 1.4f, mat1);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector(1.0f, -3.2f, 3.15f), 0.8f, mat2);
    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector(1.5f, 0.75f, 1.0f), 0.8, mat3);
    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(Vector(-1.9f, -1.25f, 3.5f), 0.8, matWallWhite);

    std::shared_ptr<Triangle> triangle1 = std::make_shared<Triangle>(Vector(-3.0f, -1.0f, 2.0f), Vector(3.0f, -1.0f, 2.0f), Vector(0.0f, 3.0f, 2.0f), matWallRed);

    std::shared_ptr<Sphere> sphereLight = std::make_shared<Sphere>(Vector(0.0f, 4.0f, 2.0f), 1.5, matDiffuseLight);

    auto obj = import("untitled.obj", matWallRed);
    world->add(obj);

    //world->add(triangle1);
    // world->addToWorld(sphere1);
    // world->addToWorld(sphere2);
    // world->addToWorld(sphere3);
    // world->addToWorld(sphere4);
    world->add(sphereLight);
    world->add(plane1);
    world->add(plane2);
    world->add(plane3);
    world->add(plane4);
    world->add(plane5);
    world->add(plane6);

    lights.push_back(std::make_shared<PointLight>(Vector(-3.0f, 3.5f, 3.0f), Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f)));
    lights.push_back(std::make_shared<PointLight>(Vector(3.0f, 3.5f, 3.0f), Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f)));
    lights.push_back(std::make_shared<PointLight>(Vector(-3.0f, -3.5f, 3.0f), Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f)));
    lights.push_back(std::make_shared<PointLight>(Vector(3.0f, -3.5f, 3.0f), Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f)));
    camera.isOrthographic = false;
    camera.render(world);

    std::ofstream output("output.ppm");
    output << "P3\n" << bitmap->width << " " << bitmap->height << "\n255\n";

    Vector one = Vector(1.0f, 1.0f, 1.0f);

    for (int y = 0; y < bitmap->height; y++)
    {
        for (int x = 0; x < bitmap->width; x++)
        {
            // Reinhard tone mapping
            const Vector mappedColor = bitmap->data[y][x] / (bitmap->data[y][x] + one);

            // Gamma Correction
            const Vector gammaCorrected = Vector(
                std::powf(mappedColor.x, 1.0f / 2.2f),
                std::powf(mappedColor.y, 1.0f / 2.2f),
                std::powf(mappedColor.z, 1.0f / 2.2f)
            );

            output << Vector::clamp(gammaCorrected, 0.0f, 1.0f).toColorString();
        }
    }

    output.close();
    ShellExecuteW(nullptr, L"open", L"output.ppm", nullptr, L".", SW_SHOW);

    std::cout << "Done\n";
}
