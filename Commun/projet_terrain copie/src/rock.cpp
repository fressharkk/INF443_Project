#include "rock.hpp"

using namespace cgp;

static buffer<uint3> connectivity_grid(size_t Nu, size_t Nv)
    {
        buffer<uint3> connectivity;
        for(size_t ku=0; ku<Nu-1; ++ku) {
            for(size_t kv=0; kv<Nv-1; ++kv) {
                unsigned int k00 = static_cast<unsigned int>(kv   + Nv* ku);
                unsigned int k10 = static_cast<unsigned int>(kv+1 + Nv* ku);
                unsigned int k01 = static_cast<unsigned int>(kv   + Nv*(ku+1));
                unsigned int k11 = static_cast<unsigned int>(kv+1 + Nv*(ku+1));

                connectivity.push_back(uint3{k00, k10, k11});
                connectivity.push_back(uint3{k00, k11, k01});
            }
        }
        return connectivity;
    }

mesh rock_with_texture(float radius, vec3 const& center, int Nu, int Nv)
    {

        mesh shape;
        for( size_t ku=0; ku<size_t(Nu); ++ku ) {
            for( size_t kv=0; kv<size_t(Nv); ++kv ) {
                float const u = ku/(Nu-1.0f);
                float const alpha = kv/(Nv-1.0f);
                float const v = 1.0f/(Nv+1.0f) * (1-alpha) + alpha* Nv/(Nv+1.0f) ;

                float const theta = 2.0f * Pi * (u-0.5f);
                float const phi   =        Pi * (v-0.5f);

                // spherical coordinates
                vec3 const n = {
                    std::cos(phi)*std::cos(theta) + 0.7f * noise_perlin({ std::cos(phi)/3.0f + 50, std::cos(theta)/3.0f +50 }, 4, 0.35, 2.0), 
                    std::cos(phi)*std::sin(theta) + 0.8f * noise_perlin({ std::cos(phi)/3.0f + 50, std::cos(theta)/3.0f +50 }, 4, 0.35, 2.0), 
                    std::sin(phi) + 0.8f * noise_perlin({ std::cos(phi)/3.0f + 50, std::cos(theta)/3.0f +50 }, 4, 0.35, 2.0)};
                vec3 const p = radius * n + center;
                vec2 const uv = {u,v};

                shape.position.push_back(p);
                shape.normal.push_back(n);
                shape.uv.push_back(uv);
            }
        }

        shape.connectivity = connectivity_grid(Nu,Nv);

        
        // poles
        for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
        {
            shape.position.push_back(center+radius*vec3{0,0,-1.0f});
            shape.normal.push_back(vec3{0,0,-1.0f});
            shape.uv.push_back({ku/(Nu-1.0f),0.0f});
        }
        for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
            shape.connectivity.push_back({Nu*Nv+ku, Nv*ku, Nv*(ku+1)});

        for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
        {
            shape.position.push_back(center+radius*vec3{0,0,1.0f});
            shape.normal.push_back(vec3{0,0,1.0f});
            shape.uv.push_back({ku/(Nu-1.0f),1.0f});
        }
        for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
            shape.connectivity.push_back({Nu*Nv+Nu-1+ku, Nv-1+Nv*(ku+1), Nv-1+Nv*ku});

        

        shape.fill_empty_field();
        shape.flip_connectivity();
        return shape;
    }





