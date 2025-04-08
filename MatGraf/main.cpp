#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Global.h"
#include "PointLight.h"
#include "Sphere.h"

int main()
{
    std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(100, 100);
    Camera camera = Camera(bitmap, 50, 1);
    std::shared_ptr<HittableList> world = std::make_shared<HittableList>();

    camera.verticalFov = 90.0f;
    camera.lookFrom = Vector(0.0f, 0.0f, 8.0f);
    camera.lookAt = Vector(0.0f, 0.0f, 2.0f);
    camera.vUp = Vector(0.0f, 1.0f, 0.0f);

    std::shared_ptr<Material> mat1 = std::make_shared<Material>(Vector(0.0f, 0.0f, 0.2f), Vector(1.5f, 1.0f, 1.0f), 5.0f);
    std::shared_ptr<Material> mat2 = std::make_shared<Material>(Vector(0.0f, 0.0f, 0.2f), Vector(1.5f, 1.0f, 1.0f), 50.0f);

    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector(-4.0f, 0.0f, -3.0f), 4.0f, mat1);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector(2.0f, 0.0f, 0.0f), 4.0f, mat2);
    world->addToWorld(sphere1);
    world->addToWorld(sphere2);

    lights.push_back(std::make_shared<PointLight>(Vector(0.0f, 1.0f, 6.0f), Vector(4.0f, 4.0f, 4.0f), Vector(0.3f, 0.0f, 0.0f)));
    lights.push_back(std::make_shared<PointLight>(Vector(0.0f, 6.0f, 3.0f), Vector(0.0f, 2.0f, 0.0f), Vector(0.0f, 0.4f, 0.0f)));

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

    std::cout << "Done\n";
}
