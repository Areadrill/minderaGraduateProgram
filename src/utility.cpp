#include "utility.hpp"

using json = nlohmann::json;

std::vector<std::vector<uint8_t>> readFile(char *filename){
    std::ifstream in(filename);
    if(in.good()){
        std::stringstream s;
	    s << in.rdbuf();
        
        return json::parse(s.str());
    }
	return std::vector<std::vector<uint8_t>>();
}