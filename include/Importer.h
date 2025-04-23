#pragma once

#include "HittableList.h"
#include "Triangle.h"
#include "Global.h"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

static std::shared_ptr<HittableList> import(std::string const& path, std::shared_ptr<Material> const& material)
{
    auto model = std::make_shared<HittableList>();

    std::ifstream input_file(path);

    if (!input_file.is_open())
    {
        std::cerr << "Failed to open file " << path << "\n";
        return {};
    }

    std::string line;

    std::vector<Vector> triangles = {};
    triangles.reserve(128);

    while (std::getline(input_file, line))
    {
        if (line.size() < 2)
            continue;

        if (line[0] != 'v' || line[1] != ' ') // v 0.477241 0.205729 0.676920
        {
            if (line[0] != 'f' || line[1] != ' ') // //f 500 1257 1826
                continue;

            int face_index = 0;
            std::array<int, 3> indices = {};

            std::istringstream iss(line);
            std::string face_string;
            while (std::getline(iss, face_string, ' '))
            {
                if (face_index == 0)
                {
                    face_index += 1;
                    continue;
                }

                // indices[face_index - 1] = std::stoi(face_string) - 1;

                std::istringstream iss2(face_string);
                std::string face_index_string;
                std::getline(iss2, face_index_string, '/');

                indices[face_index - 1] = std::stoi(face_index_string) - 1;

                face_index += 1;
            }

            Global::world->add(std::make_shared<Triangle>(
                    triangles[indices[0]],
                    triangles[indices[1]],
                    triangles[indices[2]],
                    material
                )
            );
        }

        std::istringstream iss(line);
        std::string vertex_string;
        std::array<float, 3> vertices = {};

        int index = 0;
        while (std::getline(iss, vertex_string, ' '))
        {
            if (index == 0)
            {
                index += 1;
                continue;
            }

            vertices[index - 1] = std::stof(vertex_string);
            index += 1;
        }

        triangles.emplace_back(vertices[0], vertices[1], vertices[2]);
    }

    return model;
}
