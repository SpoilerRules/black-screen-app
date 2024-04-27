//
// Created by spoil on 04/27/2024.
//

#ifndef COLORHANDLER_HPP
#define COLORHANDLER_HPP

#include <string>
#include <tuple>
#include <unordered_map>

class ColorHandler {
public:
    static std::unordered_map<std::string, std::string> colorMap;

    static std::tuple<int, int, int> convertHextoRGB(std::string& hexCode);
};


#endif //COLORHANDLER_HPP
