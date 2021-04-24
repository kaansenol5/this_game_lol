#include <string>
struct AdvancedCharacterComponent{
    int base_movement_speed;
    int current_movement_speed = base_movement_speed;
    std::string character_type;
};