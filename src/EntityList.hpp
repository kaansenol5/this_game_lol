#include "JsonLoader.hpp"
#include "include/json.hpp"
#include <stdexcept>
#include <string>
#include <vector>

class EntityList{
public:
    EntityList(char* filename, std::vector<std::string> sub_config_dicts);
    json list;
    json get_character(unsigned tag);

    template<class T> inline bool check_existence(unsigned tag, std::string varname){
        try{
            T var = list.at(std::to_string(tag)).at(varname);
            return true;
        }
        catch (nlohmann::detail::out_of_range &e){
            return false;
        }
    }
    unsigned size;
private:
    std::vector<std::string> sub_config_dicts;
    unsigned get_size();
};