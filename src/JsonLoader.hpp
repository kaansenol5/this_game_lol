#include "include/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class JsonLoader{
public:
  static json inline load(char* dirname){
    std::ifstream file;
    file.open("config.json", std::ios::out);
    std::string text;
    std::string tmp;
    while (getline (file, tmp)) {
      text += tmp;
    }
    std::cout << text << std::endl;
    auto j = json::parse(text);
    return j;
  }
};
