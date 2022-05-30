#include "lake.hpp"
#include "terrain.hpp"

using namespace cgp;

mesh create_lake_mesh(int N, float terrain_length)
{

    mesh lake; // temporary terrain storage (CPU only)
    lake.position.resize(N*N);
    lake.uv.resize(N * N);

    // Fill terrain geometry
    for(int ku=0; ku<N; ++ku)
    {
        for(int kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku/(N-1.0f);
            float v = kv/(N-1.0f);

            // Compute the real coordinates (x,y) of the terrain in [-terrain_length/2, +terrain_length/2]
            float x = (u - 0.5f) * 8 - 19.5f;
            float y = (v - 0.5f) * terrain_length;
            x += 0.5f * noise_perlin({ u/3.0f + 50, v/3.0f +50 }, 4, 0.35, 2.0);
            y += 0.5f * noise_perlin({ x/3.0f + 50, y/3.0f +50 }, 4, 0.35, 2.0);

            // Compute the surface height function at the given sampled coordinate
            float z = evaluate_terrain_height(x,y)+0.6f;

            // Store vertex coordinates
            lake.position[kv+N*ku] = {x,y,z};
            lake.uv[kv + N * ku] = { u, 4*v };
        }
    }

    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    for(int ku=0; ku<N-1; ++ku)
    {
        for(int kv=0; kv<N-1; ++kv)
        {
            unsigned int idx = kv + N*ku; // current vertex offset

            uint3 triangle_1 = {idx, idx+1+N, idx+1};
            uint3 triangle_2 = {idx, idx+N, idx+1+N};

            lake.connectivity.push_back(triangle_1);
            lake.connectivity.push_back(triangle_2);
        }
    }

    // need to call this function to fill the other buffer with default values (normal, color, etc)
    lake.fill_empty_field(); 

    return lake;
}

mesh create_lake_mesh2()
{
    float r = 1.0f;

    mesh disc;
    int N = 20;

    for (int k = 0; k < N; ++k)
    {
        float u = k/(N-1.0f);
        vec3 p = r * vec3(std::cos(2* Pi *u), std::sin(2* Pi *u), 0.0f);
        disc.position.push_back(p);
        // disc.uv.push_back(...)
        
    }
    // middle point
    disc.position.push_back({0,0,0});
    // disc.uv.push_back(...)

    for (int k = 0; k < N-1; ++k)
        disc.connectivity.push_back( uint3{ N, k, k+1});

    disc.fill_empty_field();
    return disc;
}






