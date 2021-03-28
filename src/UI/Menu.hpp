#include "Button.hpp"
#include "Text.hpp"
#include <vector>




class Menu{
public:
  Menu(const int& Width, const int& Height);

  enum item_location{
    CENTERED, LEFT, RIGHT, DOWN, BOTTOM
  };
  void update();
  void add_button(char* fontdir, char* text, int ptsize, item_location location,  const std::function<void()> fn);
  void add_text(char* fontdir, char* text, int ptsize, item_location location,  SDL_Color color);
private:
  void set_xy(item_location, int& x, int& y);
  const int& Width; // screen dimensions
  const int& Height; // ^^^^^^^^^^^^^^^
  int selected_button = 0;
  int default_item_width = 100;
  int default_item_height = 50;
  int default_side_item_padding = 50;
  void handle_events();
  std::vector<Button> buttons;
  std::vector<Text> texts;
};