#include "StartMenu.hpp"
#include "TextureManager.hpp"
StartMenu::StartMenu(SDL_Window* window, SDL_Renderer* renderer, int& current_scene_id, bool& running)
: window(window), renderer(renderer), current_scene_id(current_scene_id), running(running){
  add_text("assets/fonts/font.ttf", "Hello", 52, {0,0,100,50}, {255,255,255,255});
  add_text("assets/fonts/font.ttf", "Press x to start", 42, {0, 75, 100, 50}, {255,255,255,100});
}


StartMenu::~StartMenu(){
    for(Text text : texts){
      SDL_DestroyTexture(text.texture);
    }
    std::cout << "start_menu_scene exits" << std::endl;
    running = false;
}

void StartMenu::add_text(char* font_dir, char* text, int ptsize, SDL_Rect location, SDL_Color color){
  SDL_Texture* texture = TextureManager::load_ttf_font(font_dir, text, ptsize, color);
  texts.push_back({texture, location});
}

void StartMenu::updateFrame(){
  SDL_RenderClear(renderer);
  for(Text text : texts){
    TextureManager::render(text.texture, NULL, &text.location);
  }
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      delete this; //lol
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_x:
          current_scene_id = 1;
          break;
        default:
          break;
      }
      default:
        break;
  }
  SDL_RenderPresent(renderer);
}
