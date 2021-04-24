#include "JsonLoader.hpp"
#include <stdexcept>
#include <vector>

class EntityList{
public:
    EntityList(char* filename, std::vector<std::string> sub_config_dicts);
    json list;
    json get_character(unsigned tag);

    template<class T> inline bool check_existence(unsigned tag, std::string varname){
        try{
            T var = list[std::to_string(tag)][varname];
            return true;
        }
        catch (std::out_of_range &e){
            return false;
        }
    }
    unsigned size;
private:
    std::vector<std::string> sub_config_dicts;
    unsigned get_size();
};