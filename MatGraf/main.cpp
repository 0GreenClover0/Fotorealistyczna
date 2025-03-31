#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Sphere.h"

int main()
{
    std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(100, 100);
    Camera camera = Camera(bitmap, 1, 1);

    camera.vertical_fov = 20.0f;
    camera.look_from = Vector(13.0f, 2.0f, 3.0f);
    camera.look_at = Vector(0.0f, 0.0f, 0.0f);
    camera.v_up = Vector(0.0f, 1.0f, 0.0f);

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector(0.0f, 0.0f, 0.0f), 1.0f);

    camera.render(sphere);

    std::ofstream output("output.ppm");
    output << "P3\n" << bitmap->width << " " << bitmap->height << "\n255\n";

    for (int y = 0; y < bitmap->height; y++)
    {
        for (int x = 0; x < bitmap->width; x++)
        {
            output << bitmap->data[x][y].toColorString();
        }
    }

    output.close();

    std::cout << "Done\n";
}
