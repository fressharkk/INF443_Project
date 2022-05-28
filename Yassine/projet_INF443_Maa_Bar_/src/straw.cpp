#include "straw.hpp"

using namespace cgp;


mesh cylinder_with_texture(float h, float r)
{

    // Number of samples of the terrain is N x N
    int N = 20;

    mesh cylinder; // temporary terrain storage (CPU only)
    cylinder.position.resize(N*N);
    cylinder.uv.resize(N*N);

    // Fill terrain geometry
    for(int ku=0; ku<N; ++ku)
    {
        for(int kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku/(N-1.0f);
            float v = kv/(N-1.0f);

            // Compute the local surface function
            vec3 p = {r*std::cos(2* Pi *u), h * (v - 0.5f), r*std::sin(2* Pi *u) };
            vec2 uv = {u,v};

            // Store vertex coordinates
            cylinder.position[kv+N*ku] = p;
            cylinder.uv[kv+N*ku] = {u , v};
        }
    }

    // Generate triangle organization
    for(int ku=0; ku<N-1; ++ku)
    {
        for(int kv=0; kv<N-1; ++kv)
        {
            int idx = kv + N*ku;

            uint3 triangle_1 = {idx, idx+1+N, idx+1};
            uint3 triangle_2 = {idx, idx+N, idx+1+N};

            cylinder.connectivity.push_back(triangle_1);
            cylinder.connectivity.push_back(triangle_2);
        }
    }

    cylinder.fill_empty_field();
    return cylinder;
}

mesh disc_with_texture(float r)
{

    mesh disc;
    int N = 20;

    for (int k = 0; k < N; ++k)
    {
        float u = k/(N-1.0f);
        vec3 p = r * vec3(std::cos(2* Pi *u), std::sin(2* Pi *u), 0.0f);
        disc.position.push_back(p);
        disc.uv.push_back({1,u});
        
    }
    // middle point
    disc.position.push_back({0,0,0});
    disc.uv.push_back({0,0});

    for (int k = 0; k < N-1; ++k)
        disc.connectivity.push_back( uint3{ N, k, k+1});

    disc.fill_empty_field();
    return disc;
}

mesh create_straw_mesh()
{
    float h = 0.080f; // trunk height
    float r = 0.044f; // trunk radius

    // Create a brown trunk
    mesh straw = cylinder_with_texture(h,r);

    

    mesh hat_a = disc_with_texture(r);  // base-cone
    hat_a.position += vec3(0, 0, h/2);                        // place foliage at the top of the trunk
    straw.push_back(hat_a);

    mesh hat_b = disc_with_texture(r);
    hat_b.position += vec3(0, 0, -h/2);      // base-cone                       // place foliage at the top of the trunk
    straw.push_back(hat_b);

    return straw;
}


