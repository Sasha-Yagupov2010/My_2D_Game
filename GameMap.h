#ifndef GameMap_H
#define GameMap_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class GameMap {
private:
     vector< vector<int>> map;
     vector< RectangleShape> walls;
    int tileSize;
    int mapWidth, mapHeight;

public:
    GameMap(int width, int height, int tileSize = 50)
        : mapWidth(width), mapHeight(height), tileSize(tileSize) {
        
        map.resize(height,  vector<int>(width, 0));
    }

    void loadFromArray(const  vector< vector<int>>& newMap, Color color) {
        map = newMap;
        createWalls(color);
    }

    void createWalls(Color color) {
        walls.clear();
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                if (map[y][x] == 1) { 
                     RectangleShape wall( Vector2f(tileSize, tileSize));
                    wall.setPosition(x * tileSize, y * tileSize);
                    wall.setFillColor(color);
                    walls.push_back(wall);
                }
            }
        }
    }

    void draw( RenderWindow& window) {
        for (auto& wall : walls) {
            window.draw(wall);
        }
    }

    bool checkCollision(float x, float y, float size) {
        
        for (auto& wall : walls) {
            if (x + size > wall.getPosition().x &&
                x < wall.getPosition().x + tileSize &&
                y + size > wall.getPosition().y &&
                y < wall.getPosition().y + tileSize) {
                return true;
            }
        }
        return false;
    }

    int getTileSize() const { return tileSize; }
    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
};

#endif // !GameMap_H