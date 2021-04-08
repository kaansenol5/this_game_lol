#include "JsonLoader.hpp"
#include <SDL2/SDL_render.h>
#include <vector>

class Map{
public:
    Map();
    ~Map();
    void render();
    void scroll(int x_diff, int y_diff);
private:
    int tile_size;
    json config;
    SDL_Texture* texture_set;
    std::vector<std::vector<char>> tile_map; // a vector of x locations in a big wide image
};