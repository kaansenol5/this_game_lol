#include "EntityList.hpp"
#include "JsonLoader.hpp"
#include "include/json.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

EntityList::EntityList(char* filename, std::vector<std::string> sub_config_dicts){
    json current = JsonLoader::load(filename);
    json next;
    for(std::string subcfg : sub_config_dicts){
        next = current[subcfg];
        current = next;
    }
    list = current;
    size = get_size();
   // std::cout << "Loaded EntityList with subconfig with size " << size << std::endl;  
}

unsigned EntityList::get_size(){
    int i = 0;
    try{   
        for(;;){
            std::string a = list[std::to_string(i)]["texture"];
            i++;
        }
    }
    catch(nlohmann::detail::type_error &e){
        return i + 1;
    }
    
    return i + 1; // lol
}

json EntityList::get_character(unsigned tag){
    if (tag > size){
        std::cerr <<  "[EntityList::get_character] unknown tag: \"" << tag << "\" exiting..." << std::endl;
        exit(1);    
    }
    return list[std::to_string(tag)];
}

