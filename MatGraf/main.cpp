#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Sphere.h"

int main()
{
    std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(100, 100);
    Camera camera = Camera(bitmap, 50, 1);
    std::shared_ptr<HittableList> world = std::make_shared<HittableList>();

    camera.verticalFov = 40.0f;
    camera.lookFrom = Vector(13.0f, 2.0f, 3.0f);
    camera.lookAt = Vector(0.0f, 0.0f, 0.0f);
    camera.vUp = Vector(0.0f, 1.0f, 0.0f);

    std::shared_ptr<Material> mat1 = std::make_shared<Material>(Vector(1.0f, 0.0f, 0.0f));
    std::shared_ptr<Material> mat2 = std::make_shared<Material>(Vector(0.0f, 0.0f, 1.0f));

    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector(-8.0, -1.0f, 0.0f), 1.0f, mat1);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector(0.0, 0.0f, 0.0f), 1.0f, mat2);
    world->addToWorld(sphere1);
    world->addToWorld(sphere2);

    camera.isOrthographic = false;
    camera.render(world);

    std::ofstream output("output.ppm");
    output << "P3\n" << bitmap->width << " " << bitmap->height << "\n255\n";

    for (int y = 0; y < bitmap->height; y++)
    {
        for (int x = 0; x < bitmap->width; x++)
        {
            output << bitmap->data[y][x].toColorString();
        }
    }

    output.close();

    std::cout << "Done\n";
}
