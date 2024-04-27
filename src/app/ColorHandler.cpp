//
// Created by spoil on 04/27/2024.
//

#include "ColorHandler.hpp"

std::unordered_map<std::string, std::string> ColorHandler::colorMap = {
    {"blue", "#0000FF"},
    {"white", "#FFFFFF"},
    {"purple", "#800080"},
    {"red", "#FF0000"},
    {"green", "#008000"},
    {"yellow", "#FFFF00"},
    {"orange", "#FFA500"},
    {"pink", "#FFC0CB"},
    {"brown", "#A52A2A"},
    {"cyan", "#00FFFF"},
    {"magenta", "#FF00FF"},
    {"teal", "#008080"},
    {"gray", "#808080"},
    {"silver", "#C0C0C0"},
    {"gold", "#FFD700"},
    {"maroon", "#800000"},
    {"navy", "#000080"},
    {"olive", "#808000"},
    {"lime", "#00FF00"},
    {"aqua", "#00FFFF"},
    {"fuchsia", "#FF00FF"},
    {"violet", "#8A2BE2"},
    {"indigo", "#4B0082"}
};

std::tuple<int, int, int> ColorHandler::convertHextoRGB(std::string& hexCode) {
    if (hexCode.front() == '#') {
        hexCode.erase(0, 1);
    }

    auto red = std::stoi(hexCode.substr(0, 2), nullptr, 16);
    auto green = std::stoi(hexCode.substr(2, 2), nullptr, 16);
    auto blue = std::stoi(hexCode.substr(4, 2), nullptr, 16);

    return std::make_tuple(red, green, blue);
}
