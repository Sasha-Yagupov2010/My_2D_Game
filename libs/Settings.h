#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>

class Settings {
public:
    uint16_t height{ 600 };
    uint16_t width{ 400 };
    uint8_t fps{ 60 };
    uint8_t minDistToFlag{ 12 };
    uint8_t scoreForWin{ 5 };

    bool keyb_style = true;//default wasd none-default up dwn lt rt

};

#endif // SETTINGS_H