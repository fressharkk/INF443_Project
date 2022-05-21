
#include "terrain.hpp"


using namespace cgp;

// Evaluate 3D position of the terrain for any (x,y)
float evaluate_terrain_height(float x, float y)
{
   
    float z = 0.0f;
    z = 68*std::exp(-(x-10)*(x-10)/(2*23))/ std::sqrt(2*3.14f*9*9)*std::exp(-(y)*(y)/(2*200)) + 36*std::exp(-(x-25)*(x-25)/(2*9))/ std::sqrt(2*3.14f*9*9) + 36*std::exp(-(x+25)*(x+25)/(2*9))/ std::sqrt(2*3.14f*9*9) + 36*std::exp(-(y-25)*(y-25)/(2*9))/ std::sqrt(2*3.14f*9*9)+ 36*std::exp(-(y+25)*(y+25)/(2*9))/ std::sqrt(2*3.14f*9*9);

    if (x>-10 || x < -11 || !(-22<x && x<-14 && -7<y && y<7)) {
        // Add perlin noise
        z += 0.20f * noise_perlin({ x/3.0f + 50, y/3.0f +50 }, 4, 0.35, 2.0);
    }

    return z;
}



mesh create_terrain_mesh(int N, float terrain_length)
{

    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N*N);
    terrain.uv.resize(N * N);

    // Fill terrain geometry
    for(int ku=0; ku<N; ++ku)
    {
        for(int kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku/(N-1.0f);
            float v = kv/(N-1.0f);

            // Compute the real coordinates (x,y) of the terrain in [-terrain_length/2, +terrain_length/2]
            float x = (u - 0.5f) * terrain_length;
            float y = (v - 0.5f) * terrain_length;

            // Compute the surface height function at the given sampled coordinate
            float z = evaluate_terrain_height(x,y);

            // Store vertex coordinates
            terrain.position[kv+N*ku] = {x,z,y};
            terrain.uv[kv + N * ku] = { 50*u, 40*v };
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

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    // need to call this function to fill the other buffer with default values (normal, color, etc)
	terrain.fill_empty_field(); 

    return terrain;
}




std::vector<vec3> generate_positions_on_terrain(int N, float terrain_length)
{
    std::vector<cgp::vec3> position;
    for (int k = 0; k < N; ++k)
    {
        float const x = rand_interval(-terrain_length / 2, terrain_length / 2);
        float const y = (rand_interval()-0.5f) * terrain_length;

        vec3 const p = { x, y, evaluate_terrain_height(x,y) };

        bool to_add = true;
        for (int k2 = 0; to_add==true && k2 < position.size(); ++k2) {
            vec3 const& p2 = position[k2];
            if(norm(p2-p)<4)
                to_add=false;
            if (x<-6 && x>-15) 
                to_add=false;
        }
        if(to_add)
            position.push_back(p);
    }
    return position;
}
