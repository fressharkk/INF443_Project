#include "rock.hpp"

using namespace cgp;

static buffer<uint3> connectivity_grid(size_t Nu, size_t Nv)
{
    buffer<uint3> connectivity;
    for (size_t ku = 0; ku < Nu - 1; ++ku) {
        for (size_t kv = 0; kv < Nv - 1; ++kv) {
            unsigned int k00 = static_cast<unsigned int>(kv + Nv * ku);
            unsigned int k10 = static_cast<unsigned int>(kv + 1 + Nv * ku);
            unsigned int k01 = static_cast<unsigned int>(kv + Nv * (ku + 1));
            unsigned int k11 = static_cast<unsigned int>(kv + 1 + Nv * (ku + 1));

            connectivity.push_back(uint3{ k00, k10, k11 });
            connectivity.push_back(uint3{ k00, k11, k01 });
        }
    }
    return connectivity;
}

mesh Rocks::rock_with_texture(float radius, vec3 const& center, int Nu, int Nv)
{

    mesh shape;
    for (size_t ku = 0; ku < size_t(Nu); ++ku) {
        for (size_t kv = 0; kv < size_t(Nv); ++kv) {
            float const u = ku / (Nu - 1.0f);
            float const alpha = kv / (Nv - 1.0f);
            float const v = 1.0f / (Nv + 1.0f) * (1 - alpha) + alpha * Nv / (Nv + 1.0f);

            float const theta = 2.0f * Pi * (u - 0.5f);
            float const phi = Pi * (v - 0.5f);

            // spherical coordinates
            vec3 const n = {
                std::cos(phi) * std::cos(theta) + 0.7f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::cos(phi) * std::sin(theta) + 0.8f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::sin(phi) + 0.8f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0) };
            vec3 const p = radius * n + center;
            vec2 const uv = { u,v };

            shape.position.push_back(p);
            shape.normal.push_back(n);
            shape.uv.push_back(uv);
        }
    }

    shape.connectivity = connectivity_grid(Nu, Nv);


    // poles
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,-1.0f });
        shape.normal.push_back(vec3{ 0,0,-1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),0.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + ku, Nv * ku, Nv * (ku + 1) });

    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,1.0f });
        shape.normal.push_back(vec3{ 0,0,1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),1.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + Nu - 1 + ku, Nv - 1 + Nv * (ku + 1), Nv - 1 + Nv * ku });



    shape.fill_empty_field();
    shape.flip_connectivity();
    return shape;
}

mesh Rocks::rock_with_texture_1(float radius, vec3 const& center, int Nu, int Nv)
{

    mesh shape;
    for (size_t ku = 0; ku < size_t(Nu); ++ku) {
        for (size_t kv = 0; kv < size_t(Nv); ++kv) {
            float const u = ku / (Nu - 1.0f);
            float const alpha = kv / (Nv - 1.0f);
            float const v = 1.0f / (Nv + 1.0f) * (1 - alpha) + alpha * Nv / (Nv + 1.0f);

            float const theta = 2.0f * Pi * (u - 0.5f);
            float const phi = Pi * (v - 0.5f);

            // spherical coordinates
            vec3 const n = {
                std::cos(phi) * std::cos(theta) + 0.9f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::cos(phi) * std::sin(theta) + 0.4f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::sin(phi) + 0.6f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0) };
            vec3 const p = radius * n + center;
            vec2 const uv = { u,v };

            shape.position.push_back(p);
            shape.normal.push_back(n);
            shape.uv.push_back(uv);
        }
    }

    shape.connectivity = connectivity_grid(Nu, Nv);


    // poles
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,-1.0f });
        shape.normal.push_back(vec3{ 0,0,-1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),0.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + ku, Nv * ku, Nv * (ku + 1) });

    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,1.0f });
        shape.normal.push_back(vec3{ 0,0,1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),1.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + Nu - 1 + ku, Nv - 1 + Nv * (ku + 1), Nv - 1 + Nv * ku });



    shape.fill_empty_field();
    shape.flip_connectivity();
    return shape;
}

mesh Rocks::rock_with_texture_2(float radius, vec3 const& center, int Nu, int Nv)
{

    mesh shape;
    for (size_t ku = 0; ku < size_t(Nu); ++ku) {
        for (size_t kv = 0; kv < size_t(Nv); ++kv) {
            float const u = ku / (Nu - 1.0f);
            float const alpha = kv / (Nv - 1.0f);
            float const v = 1.0f / (Nv + 1.0f) * (1 - alpha) + alpha * Nv / (Nv + 1.0f);

            float const theta = 2.0f * Pi * (u - 0.5f);
            float const phi = Pi * (v - 0.5f);

            // spherical coordinates
            vec3 const n = {
                std::cos(phi) * std::cos(theta) + 0.4f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::cos(phi) * std::sin(theta) + 0.1f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0),
                std::sin(phi) + 0.5f * noise_perlin({ std::cos(phi) / 3.0f + 50, std::cos(theta) / 3.0f + 50 }, 4, 0.35, 2.0) };
            vec3 const p = radius * n + center;
            vec2 const uv = { u,v };

            shape.position.push_back(p);
            shape.normal.push_back(n);
            shape.uv.push_back(uv);
        }
    }

    shape.connectivity = connectivity_grid(Nu, Nv);


    // poles
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,-1.0f });
        shape.normal.push_back(vec3{ 0,0,-1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),0.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + ku, Nv * ku, Nv * (ku + 1) });

    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
    {
        shape.position.push_back(center + radius * vec3{ 0,0,1.0f });
        shape.normal.push_back(vec3{ 0,0,1.0f });
        shape.uv.push_back({ ku / (Nu - 1.0f),1.0f });
    }
    for (size_t ku = 0; ku < size_t(Nu - 1); ++ku)
        shape.connectivity.push_back({ Nu * Nv + Nu - 1 + ku, Nv - 1 + Nv * (ku + 1), Nv - 1 + Nv * ku });



    shape.fill_empty_field();
    shape.flip_connectivity();
    return shape;
}

cgp::vec3 Rocks::getHitBox()
{
    return vec3(2*rad, 2 * rad, 2 * rad);
}

std::vector<cgp::vec3> Rocks::getPos()
{
    return pos;
}

Rocks::Rocks(int type, int number, float radius, cgp::vec3 center, cgp::vec4 bounds, float (*func)(float, float), cgp::vec3(*n_func)(float, float))
{
    if (type == 1)
    {
        rock.initialize(rock_with_texture(radius, center, 8, 8));
        rock.texture = opengl_load_texture_image("assets/rock_2.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
        
    }
    else if (type == 2)
    {
        rock.initialize(rock_with_texture_1(radius, center, 8, 8));
        rock.texture = opengl_load_texture_image("assets/rock_4.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
    }
    else
    {
        rock.initialize(rock_with_texture_2(radius, center, 8, 8));
        rock.texture = opengl_load_texture_image("assets/rock_3.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
    }
       
    rad = radius;
    generatePositions(number, bounds.x, bounds.y, bounds.z, bounds.w, *func, *n_func);

}

float noise(float x, float y)
{   
    return noise_perlin(vec2(x, y), 5);
}
void Rocks::generatePositions(int n , float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float))
{
    for (int i = 0; i < n; i++)
    {
        float x = rand_interval(min_x, max_x);
        float z = rand_interval(min_z, max_z);
        float y = func(x, z);

        bool detectCollisions = true;
        for (vec3 p : pos)
        {
            if (norm(p - vec3(x, y, z)) < 2 * rad)
                detectCollisions = false;
        }
        if (detectCollisions)
        {
            pos.push_back(vec3(x, y+rad/2+0.1*noise(x,z), z));
            ori.push_back(n_func(x, z));
        }
    }
}

void Rocks::draw_rocks(scene_environment_camera_head& environment)
{
    for (int i = 0; i < pos.size(); i++)
    {
        auto r = rotation_transform::between_vector({ 0,1,0 }, ori[i]);
        rock.transform.rotation = r;
        rock.transform.translation = pos[i];
        draw(rock, environment);
    }
        
}






