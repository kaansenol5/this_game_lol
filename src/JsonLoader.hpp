#pragma once
#include "include/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class JsonLoader{
public:
  static json inline load(char* file_name){
    std::cout << "LOADING JSON FILE \"" << file_name << "\"" << std::endl;
    std::ifstream file;
    file.open(file_name, std::ios::out);
    std::string text;
    std::string tmp;
    while (getline (file, tmp)) {
      text += tmp;
    }
    auto j = json::parse(text);
    return j;
  }
};
