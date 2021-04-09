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
    auto j = json::parse(file);
    return j;
  }
};
