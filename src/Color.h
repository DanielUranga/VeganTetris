#pragma once

#include <random>
#include <tuple>

enum Color {
    Rojizo,
    Verdazio,
    Azulino,
    Violazeo,
    Espiritu,
    Colorido,
    Adamantio,
    Esperanza,
    ColorMax
};

namespace ColorUtil {

    static std::tuple<int, int, int> getRGB(Color color) {
        switch (color)
        {
        case Rojizo:
            return std::make_tuple(255, 128, 128);
            break;
        case Verdazio:
            return std::make_tuple(128, 255, 128);
            break;
        case Azulino:
            return std::make_tuple(128, 128, 255);
            break;
        case Violazeo:
            return std::make_tuple(255, 128, 255);
            break;
        case Espiritu:
            return std::make_tuple(200, 190, 120);
            break;
        case Colorido:
            return std::make_tuple(140, 100, 140);
            break;
        case Adamantio:
            return std::make_tuple(20, 100, 150);
            break;
        case Esperanza:
            return std::make_tuple(190, 12, 130);
            break;
        default:
            break;
        }
        return std::make_tuple(0, 0, 0);
    }

}
