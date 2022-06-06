#include "cart.hpp"


using namespace cgp;

cgp::mesh Carts::create_cart_mesh(){

    mesh m;
    m = mesh_load_file_obj("assets/cart.obj");
    return m;
}

cgp::vec3 Carts::getHitBox()
{
    return hitbox;
}

std::vector<cgp::vec3> Carts::getPos()
{
    return pos;
}

Carts::Carts(int number, float scale, cgp::vec4 bounds, float(*func)(float, float), cgp::vec3(*n_func)(float, float))
{
    cart.initialize(create_cart_mesh(), "Cart");
    straw.initialize(create_straw_mesh(), "Straw");
    straw.transform.scaling = scale;
    cart.transform.scaling = scale;
    generatePositions(number, bounds.x, bounds.y, bounds.z, bounds.w, *func, *n_func);
}

void Carts::generatePositions(int n, float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float))
{
    for (int i = 0; i < n; i++)
    {
        float x = rand_interval(min_x, max_x);
        float z = rand_interval(min_z, max_z);
        float y = func(x, z);

        bool detectCollisions = true;
        for (vec3 p : pos)
        {
            
            if (norm(p - vec3(x, y, z)) < 2 * std::max(std::max(length, height), width))
                detectCollisions = false;
        }
        if (detectCollisions)
        {
            pos.push_back(vec3(x, y, z));
            ori.push_back(n_func(x, z));
        }
    }
}

void Carts::draw_carts(scene_environment_camera_head& environment)
{
    for (int i = 0; i < pos.size(); i++)
    {
        auto r = rotation_transform::between_vector({ 0,1,0 }, ori[i]);
        cart.transform.rotation = r;
        cart.transform.translation = pos[i];
        straw.transform.rotation = r;
        straw.transform.translation = pos[i];
        draw(cart, environment);
        draw(straw, environment);
    }
}

cgp::mesh Carts::cylinder_with_texture(float h, float r)
{

    // Number of samples of the terrain is N x N
    int N = 20;

    mesh cylinder; // temporary terrain storage (CPU only)
    cylinder.position.resize(N * N);
    cylinder.uv.resize(N * N);

    // Fill terrain geometry
    for (int ku = 0; ku < N; ++ku)
    {
        for (int kv = 0; kv < N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku / (N - 1.0f);
            float v = kv / (N - 1.0f);

            // Compute the local surface function
            vec3 p = { r * std::cos(2 * Pi * u), h * (v - 0.5f), r * std::sin(2 * Pi * u) };
            vec2 uv = { u,v };

            // Store vertex coordinates
            cylinder.position[kv + N * ku] = p;
            cylinder.uv[kv + N * ku] = { u , v };
        }
    }

    // Generate triangle organization
    for (int ku = 0; ku < N - 1; ++ku)
    {
        for (int kv = 0; kv < N - 1; ++kv)
        {
            int idx = kv + N * ku;

            uint3 triangle_1 = { idx, idx + 1 + N, idx + 1 };
            uint3 triangle_2 = { idx, idx + N, idx + 1 + N };

            cylinder.connectivity.push_back(triangle_1);
            cylinder.connectivity.push_back(triangle_2);
        }
    }

    cylinder.fill_empty_field();
    return cylinder;    
}

cgp::mesh Carts::disc_with_texture(float r)
{
    mesh disc;
    int N = 20;

    for (int k = 0; k < N; ++k)
    {
        float u = k / (N - 1.0f);
        vec3 p = r * vec3(std::cos(2 * Pi * u), std::sin(2 * Pi * u), 0.0f);
        disc.position.push_back(p);
        disc.uv.push_back({ 1,u });

    }
    // middle point
    disc.position.push_back({ 0,0,0 });
    disc.uv.push_back({ 0,0 });

    for (int k = 0; k < N - 1; ++k)
        disc.connectivity.push_back(uint3{ N, k, k + 1 });

    disc.fill_empty_field();
    return disc;
}

cgp::mesh Carts::create_straw_mesh()
{
    float h = 0.080f; // trunk height
    float r = 0.044f; // trunk radius

    // Create a brown trunk
    mesh straw = cylinder_with_texture(h, r);

    mesh hat_a = disc_with_texture(r);  // base-cone
    hat_a.position += vec3(0, 0, h / 2);                        // place foliage at the top of the trunk
    straw.push_back(hat_a);

    mesh hat_b = disc_with_texture(r);
    hat_b.position += vec3(0, 0, -h / 2);      // base-cone                       // place foliage at the top of the trunk
    straw.push_back(hat_b);

    return straw;
}

