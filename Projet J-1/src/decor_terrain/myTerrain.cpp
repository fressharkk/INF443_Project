#include "myTerrain.hpp"

using namespace cgp;

float myTerrain::terrain_length = 200;
float myTerrain::height_array[100][100];
float myTerrain::sec_height_array[100][100];

float getNoise(int x, int z) {
   
    std::srand(x * 49632 + z * 325176);
    float r_max = (float)RAND_MAX;
    float r_value = (float)std::rand() / r_max;
    return r_value * 2.f - 1.f;
}

float getSmoothNoise(int x, int z) {
    float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1)
        + getNoise(x + 1, z + 1)) / 16.f;
    float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1)
        + getNoise(x, z + 1)) / 8.f;
    float center = getNoise(x, z) / 4.f;
    return corners + sides + center;
}

float interpolate(float a, float b, float blend) {
    double theta = blend * Pi;
    float f = (float)(1.f - cos(theta)) * 0.5f;
    return a * (1.f - f) + b * f;
}

float getInterpolatedNoise(float x, float z) {
    int intX = (int)x;
    int intZ = (int)z;
    float fracX = x - intX;
    float fracZ = z - intZ;

    float v1 = getSmoothNoise(intX, intZ);
    float v2 = getSmoothNoise(intX + 1, intZ);
    float v3 = getSmoothNoise(intX, intZ + 1);
    float v4 = getSmoothNoise(intX + 1, intZ + 1);
    float i1 = interpolate(v1, v2, fracX);
    float i2 = interpolate(v3, v4, fracX);
    return interpolate(i1, i2, fracZ);
}

float myTerrain::noise(float x, float z)
{
    float y = 0.0;
    y = 0.2*noise_perlin({ x / 3.0f + 50, z / 3.0f + 50 }, 4, 0.35, 2.0);
    return y;
}

float myTerrain::getTerrainLength()
{
    return myTerrain::terrain_length;
}

float myTerrain::main_terrain_shape(float x, float z)
{
    float y = 0.0f;
    float z_top_hill = -50;
    //HILL
    if (z < 10)
    {
        float d = std::abs(z - z_top_hill) / 40;
        y = 7 * exp(-d * d);
    }
    if (z < -50)
    {
        float d = std::abs(z - z_top_hill)/30;
        y = 7 * exp(-d * d);
    }
    
    //LAKE
    vec2 lake_center = vec2(75, 75);
    if (norm(vec2(x, z) - lake_center) < 15 + 5*noise(x, z))
        y = -5 + 5*noise(x, z);
        

    return y;
}

float barycentre(vec3 p1, vec3 p2, vec3 p3, vec2 pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float myTerrain::evaluate_terrain_height(float x, float z)
{
    return main_terrain_shape(x, z) + 2*noise(x, z);
}

void myTerrain::build_terrain(int N, float terrain_length)
{
    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N * N);
    terrain.uv.resize(N * N);

    // Fill terrain geometry
    for (int ku = 0; ku < N; ++ku)
    {
        for (int kv = 0; kv < N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku / (N - 1.0f);
            float v = kv / (N - 1.0f);

            // Compute the real coordinates (x,y) of the terrain in [-terrain_length/2, +terrain_length/2]
            float x = (u - 0.5f) * terrain_length;
            float y = (v - 0.5f) * terrain_length;

            // Compute the surface height function at the given sampled coordinate
            float z = evaluate_terrain_height(x, y);
            if (std::abs(x - terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(x + terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(y + terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(y - terrain_length / 2) < 0.01)
                z = 0;

            // Store vertex coordinates
            terrain.position[kv + N * ku] = { x,z,y };
            height_array[ku][kv] = z;
            terrain.uv[kv + N * ku] = { 40 * u, 40 * v };
        }
    }

    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    for (int ku = 0; ku < N - 1; ++ku)
    {
        for (int kv = 0; kv < N - 1; ++kv)
        {
            unsigned int idx = kv + N * ku; // current vertex offset

            uint3 triangle_1 = { idx, idx + 1 + N, idx + 1 };
            uint3 triangle_2 = { idx, idx + N, idx + 1 + N };

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    // need to call this function to fill the other buffer with default values (normal, color, etc)
    terrain.fill_empty_field();

    main_terrain.initialize(terrain, "Main Terrain");
}

void myTerrain::build_terrain_secondary(int N, float terrain_length)
{
    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N * N);
    terrain.uv.resize(N * N);

    // Fill terrain geometry
    for (int ku = 0; ku < N; ++ku)
    {
        for (int kv = 0; kv < N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            float u = ku / (N - 1.0f);
            float v = kv / (N - 1.0f);

            // Compute the real coordinates (x,y) of the terrain in [-terrain_length/2, +terrain_length/2]
            float x = (u - 0.5f) * terrain_length;
            float y = (v - 0.5f) * terrain_length;

            // Compute the surface height function at the given sampled coordinate
            float z = secondaryNoise((int)x, (int)y) + 0.5*noise(x,y);
            if (std::abs(x - terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(x + terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(y + terrain_length / 2) < 0.01)
                z = 0;
            if (std::abs(y - terrain_length / 2) < 0.01)
                z = 0;
            // Store vertex coordinates
            terrain.position[kv + N * ku] = { x,z,y };
            sec_height_array[ku][kv] = z;
            terrain.uv[kv + N * ku] = { 40 * u, 40 * v };
        }
    }

    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    for (int ku = 0; ku < N - 1; ++ku)
    {
        for (int kv = 0; kv < N - 1; ++kv)
        {
            unsigned int idx = kv + N * ku; // current vertex offset

            uint3 triangle_1 = { idx, idx + 1 + N, idx + 1 };
            uint3 triangle_2 = { idx, idx + N, idx + 1 + N };

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    // need to call this function to fill the other buffer with default values (normal, color, etc)
    terrain.fill_empty_field();

    secondary_terrain.initialize(terrain, "Main Terrain");
}

float myTerrain::secondaryNoise(int x, int z)
{
    float total = 0;
    float d = (float)pow(2, octaves - 1);
    for (int i = 0;i < octaves ;i++) {
        float freq = (float)(pow(2, i) / d);
        float amp = (float)pow(roughness, i) * amplitude;
        total += getInterpolatedNoise(x * freq, z * freq) * amp;
    }
    return total;
}

void myTerrain::initialize()
{
    build_terrain(100, 200);
    build_terrain_secondary(10, 200);
    

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            is_burnt(i, j) = vec3(0, 0, 0);
            empty_grid(i, j) = vec3(0, 0, 0);
        }
    }
    background_texture = opengl_load_texture_image("assets/Terrain_Texture/grass_texture.jpg", GL_REPEAT, GL_REPEAT);
    road_texture = opengl_load_texture_image("assets/Terrain_Texture/path.png", GL_REPEAT, GL_REPEAT);
    mud_texture = opengl_load_texture_image("assets/Terrain_Texture/mud.png", GL_REPEAT, GL_REPEAT);
    dirt_texture = opengl_load_texture_image("assets/Terrain_Texture/dirt_texture.jpg", GL_REPEAT, GL_REPEAT);
    burnt_texture = opengl_load_texture_image("assets/Terrain_Texture/herbe_brulee_texture.jpg", GL_REPEAT, GL_REPEAT);
    blend_maps_textures.push_back(opengl_load_texture_image("assets/Terrain_Texture/main_blend_map.png", GL_REPEAT, GL_REPEAT));

    GLuint terrain_shader = opengl_load_shader("shaders/terrain/terrain_vert.glsl", "shaders/terrain/terrain_frag.glsl");
    main_terrain.shader = terrain_shader;
    secondary_terrain.shader = terrain_shader;
    createTexture();
    empty_grid_texture = opengl_load_texture_image(empty_grid, GL_REPEAT, GL_REPEAT);
}

void myTerrain::createTexture()
{
  
    is_burnt_texture = opengl_load_texture_image(is_burnt, GL_REPEAT, GL_REPEAT);
 
}

void myTerrain::updateIsBurnt(int x, int z)
{
    is_burnt(x, z) = vec3(1, 0, 0);
    createTexture();
}

float myTerrain::getHeight(float x, float z)
{
    x = x + 100;
    z = z + 100;
    if ((std::abs(x-terrain_length/2) <= terrain_length / 2) && (std::abs(z-terrain_length/2) <= terrain_length / 2))
    {
        int x_i = (int) x / 2;
        int z_i = (int) z / 2;

        float frac_x = std::fmod(x, 1);
        float frac_z = std::fmod(z, 1);

        float res;
        if (frac_x <= 1 - frac_z)
        {
            res = barycentre(vec3(0,height_array[x_i][z_i],0), vec3(1,height_array[x_i+1][z_i], 0), vec3(0, height_array[x_i][z_i+1], 1), vec2(frac_x, frac_z));
        }
        else
        {
            res = barycentre(vec3(1, height_array[x_i+1][z_i], 0), vec3(1, height_array[x_i + 1][z_i+1], 1), vec3(0, height_array[x_i][z_i + 1], 1), vec2(frac_x, frac_z));
        }
        return res;
    }
    else
    {
        float x_m = std::fmod(std::abs(x), 200);
        float z_m = std::fmod(std::abs(z), 200);

        if (x < 0)
            x_m = 200 - x_m;
        if (z < 0)
            z_m = 200 - z_m;

        int x_i = (int)x_m / 2;
        int z_i = (int)z_m / 2;

        if (x_i > 98)
            return 0;
        if (z_i > 98)
            return 0;
        if (x_i < 0)
            return 0;
        if (z_i < 0)
            return 0;

        float frac_x = std::fmod(x_m, 1);
        float frac_z = std::fmod(z_m, 1);

        float res;
        if (frac_x <= 1 - frac_z)
        {
            res = barycentre(vec3(0, sec_height_array[x_i][z_i], 0), vec3(1, sec_height_array[x_i + 1][z_i], 0), vec3(0, sec_height_array[x_i][z_i + 1], 1), vec2(frac_x, frac_z));
        }
        else
        {
            res = barycentre(vec3(1, sec_height_array[x_i + 1][z_i], 0), vec3(1, sec_height_array[x_i + 1][z_i + 1], 1), vec3(0, sec_height_array[x_i][z_i + 1], 1), vec2(frac_x, frac_z));
        }
        return res;
    }
}

cgp::vec3 normal_vector(vec3 p1, vec3 p2, vec3 p3)
{
    vec3 res = cross((p2 - p1), p3 - p1);
    return normalize(res);
}

cgp::vec3 myTerrain::get_normal(float x, float z)
{
    x = x + 100;
    z = z + 100;
    if ((std::abs(x - terrain_length / 2) <= terrain_length / 2) && (std::abs(z - terrain_length / 2) <= terrain_length / 2))
    {
        int x_i = (int)x / 2;
        int z_i = (int)z / 2;

        float frac_x = std::fmod(x, 1);
        float frac_z = std::fmod(z, 1);

        vec3 res;
        if (frac_x <= 1 - frac_z)
        {
            res = normal_vector(vec3(x, height_array[x_i][z_i], z), vec3(x+200/99, height_array[x_i + 1][z_i], z), vec3(x, height_array[x_i][z_i + 1], z+200/99));
        }
        else
        {
            res = normal_vector(vec3(x + 200 / 99, height_array[x_i+1][z_i], z), vec3(x + 200 / 99, height_array[x_i + 1][z_i+1], z + 200 / 99), vec3(x, height_array[x_i][z_i + 1], z + 200 / 99));
        }
        return res;
    }
    else
    {
        float x_m = std::fmod(std::abs(x), 200);
        float z_m = std::fmod(std::abs(z), 200);

        if (x < 0)
            x_m = 200 - x_m;
        if (z < 0)
            z_m = 200 - z_m;

        int x_i = (int) x_m / 2;
        int z_i = (int) z_m / 2;

        if (x_i > 98)
            return vec3(0, -1, 0);
        if (z_i > 98)
            return vec3(0, -1, 0);
        if (x_i < 0)
            return vec3(0, -1, 0);
        if (z_i < 0)
            return vec3(0, -1, 0);
        float frac_x = std::fmod(x_m, 1);
        float frac_z = std::fmod(z_m, 1);
        vec3 res;
        if (frac_x <= 1 - frac_z)
        {
            res = normal_vector(vec3(x_m, sec_height_array[x_i][z_i], z_m), vec3(x_m + 200 / 99, sec_height_array[x_i + 1][z_i], z_m), vec3(x_m, sec_height_array[x_i][z_i + 1], z_m + 200 / 99));
        }
        else
        {
            res = normal_vector(vec3(x_m + 200 / 99, sec_height_array[x_i + 1][z_i], z_m), vec3(x_m + 200 / 99, sec_height_array[x_i + 1][z_i + 1], z_m + 200 / 99), vec3(x_m, sec_height_array[x_i][z_i + 1], z_m + 200 / 99));
        }
        return res;
    }
}

void myTerrain::draw_main_Terrain(scene_environment_camera_head& environment)
{
    
	if (main_terrain.number_triangles == 0) return;

	// Setup shader
	assert_cgp(main_terrain.shader != 0, "Try to draw mesh_main_terrain without shader [name:" + main_terrain.name + "]");
	assert_cgp(main_terrain.texture != 0, "Try to draw mesh_main_terrain without texture [name:" + main_terrain.name + "]");
	glUseProgram(main_terrain.shader); opengl_check;

	// Send uniforms for this shader
	opengl_uniform(main_terrain.shader, environment);
	opengl_uniform(main_terrain.shader, main_terrain.shading);
	opengl_uniform(main_terrain.shader, "model", main_terrain.model_matrix());

	// Set texture
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_2D, background_texture); opengl_check;
	opengl_uniform(main_terrain.shader, "background_texture", 0);  opengl_check;
	glActiveTexture(GL_TEXTURE1); opengl_check;
	glBindTexture(GL_TEXTURE_2D, road_texture); opengl_check;
	opengl_uniform(main_terrain.shader, "road_texture", 1);  opengl_check;
	glActiveTexture(GL_TEXTURE2); opengl_check;
	glBindTexture(GL_TEXTURE_2D, mud_texture); opengl_check;
	opengl_uniform(main_terrain.shader, "mud_texture", 2);  opengl_check;
	glActiveTexture(GL_TEXTURE3); opengl_check;
	glBindTexture(GL_TEXTURE_2D, dirt_texture); opengl_check;
	opengl_uniform(main_terrain.shader, "dirt_texture", 3);  opengl_check;
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, burnt_texture); opengl_check;
    opengl_uniform(main_terrain.shader, "burnt_texture", 4);  opengl_check;
	glActiveTexture(GL_TEXTURE5); opengl_check;
	glBindTexture(GL_TEXTURE_2D, blend_maps_textures[0]); opengl_check;
	opengl_uniform(main_terrain.shader, "blend_map", 5);  opengl_check;

    glActiveTexture(GL_TEXTURE6); opengl_check;
    glBindTexture(GL_TEXTURE_2D, is_burnt_texture); opengl_check;
    opengl_uniform(main_terrain.shader, "is_burnt_texture", 6); opengl_check;

	// Call draw function
	assert_cgp(main_terrain.number_triangles > 0, "Try to draw mesh_main_terrain with 0 triangles [name:" + main_terrain.name + "]"); opengl_check;
	glBindVertexArray(main_terrain.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main_terrain.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(main_terrain.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void myTerrain::draw_sec_Terrain_gl(scene_environment_camera_head& environment)
{
    if (secondary_terrain.number_triangles == 0) return;

    // Setup shader
    assert_cgp(secondary_terrain.shader != 0, "Try to draw mesh_main_terrain without shader [name:" + secondary_terrain.name + "]");
    assert_cgp(secondary_terrain.texture != 0, "Try to draw mesh_main_terrain without texture [name:" + secondary_terrain.name + "]");
    glUseProgram(secondary_terrain.shader); opengl_check;

    // Send uniforms for this shader
    opengl_uniform(secondary_terrain.shader, environment);
    opengl_uniform(secondary_terrain.shader, secondary_terrain.shading);
    opengl_uniform(secondary_terrain.shader, "model", secondary_terrain.model_matrix());

    // Set texture
    glActiveTexture(GL_TEXTURE0); opengl_check;
    glBindTexture(GL_TEXTURE_2D, background_texture); opengl_check;
    opengl_uniform(secondary_terrain.shader, "background_texture", 0);  opengl_check;
    glActiveTexture(GL_TEXTURE1); opengl_check;
    glBindTexture(GL_TEXTURE_2D, road_texture); opengl_check;
    opengl_uniform(secondary_terrain.shader, "road_texture", 1);  opengl_check;
    glActiveTexture(GL_TEXTURE2); opengl_check;
    glBindTexture(GL_TEXTURE_2D, mud_texture); opengl_check;
    opengl_uniform(secondary_terrain.shader, "mud_texture", 2);  opengl_check;
    glActiveTexture(GL_TEXTURE3); opengl_check;
    glBindTexture(GL_TEXTURE_2D, dirt_texture); opengl_check;
    opengl_uniform(secondary_terrain.shader, "dirt_texture", 3);  opengl_check;
    glActiveTexture(GL_TEXTURE4); opengl_check;
    glBindTexture(GL_TEXTURE_2D, blend_maps_textures[0]); opengl_check;
    opengl_uniform(secondary_terrain.shader, "blend_map", 4);  opengl_check;
    glActiveTexture(GL_TEXTURE6); opengl_check;
    glBindTexture(GL_TEXTURE_2D, empty_grid_texture); opengl_check;
    opengl_uniform(main_terrain.shader, "is_burnt_texture", 6); opengl_check;
    // Call draw function
    assert_cgp(secondary_terrain.number_triangles > 0, "Try to draw mesh_main_terrain with 0 triangles [name:" + secondary_terrain.name + "]"); opengl_check;
    glBindVertexArray(secondary_terrain.vao);   opengl_check;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, secondary_terrain.vbo.at("index")); opengl_check;
    glDrawElements(GL_TRIANGLES, GLsizei(secondary_terrain.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;

    // Clean buffers
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void myTerrain::draw_sec_Terrain(cgp::vec2 grid_position, scene_environment_camera_head& environment)
{
    int x_dep = (int)grid_position.x;
    int z_dep = (int)grid_position.y;
    
    if (grid_position.x < 0)
        x_dep--;
    
    if (grid_position.y < 0)
        z_dep--;

    if ((x_dep == 0) && (z_dep == 0))
        return;
    
    secondary_terrain.transform.translation = vec3(200 * x_dep, 0, 200 * z_dep);
    draw_sec_Terrain_gl(environment);
}
void myTerrain::draw_all_Terrains(scene_environment_camera_head& environment)
{
    vec3 pos;
    if (environment.is_camera_head_used)
        pos = environment.camera.position();
    else
        pos = environment.camera_fixe.position();

    pos = (pos+vec3(100,0,100))/200;
    if ((- 1.f <= pos.x) && (pos.x <= 2.f) && (-1.f <= pos.z) && (pos.z <= 2.f))
        draw_main_Terrain(environment);

    for (int i = -2; i < 3; i++)
    {
        for (int j = -2; j < 3; j++)
        {
           
            draw_sec_Terrain((pos.xz() + vec2(i, j)), environment);
            
        }
    }
}