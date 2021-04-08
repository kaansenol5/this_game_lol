#pragma once
#include <SDL2/SDL_rect.h>
#include <string>
#include <SDL2/SDL.h>
#include "colors.hpp"
#include <functional>

class Button{
public:
  Button(char* fontdir, char* text, int ptsize, SDL_Rect location, bool filled, const std::function<void(Button& button)> fn);
  ~Button();
  void on_click();
  void render();
  void change_colors(SDL_Color text_color, SDL_Color normal_outline_color, SDL_Color selected_outline_color);
  void change_text(char* text);
  SDL_Rect location;
  bool selected = false;
  char* text;
  SDL_Color text_color = Colors::Black;
  SDL_Color normal_outline_color = Colors::Gray;
  SDL_Color selected_outline_color = Colors::White;
private:
  char* font;
  int ptsize;
  bool filled = true;
  SDL_Rect outer_rect;
  SDL_Texture* texture;
  const std::function<void(Button& button)> fn;
};
