#ifndef GameMap_H
#define GameMap_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace sf;

class GameMap {
private:
    vector< vector<int>> map;
    vector< RectangleShape> walls;
    int tileSize;
    int mapWidth, mapHeight;

public:

    GameMap(int width, int height, int tileSize = 50);

    void loadFromArray(const  vector< vector<int>>& newMap, Color color);
    void createWalls(Color color);
    void draw(RenderWindow& window);
    bool checkCollision(float x, float y, float size);
    bool loadFromFile(const string& filename, Color color);

    int getTileSize() const { return tileSize; }
    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }



};

#endif // !GameMap_H