#pragma once
#include <vector>
#include <string>

#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

class MapHandler {
    public:
        MapHandler(std::string filename);
        ~MapHandler();

    private:
        std::vector<std::vector<int>> *map;
        const std::string FILENAME;
};
#endif