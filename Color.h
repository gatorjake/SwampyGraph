//
// Created by jbsha on 1/30/2021.
//

#include <iostream>
#pragma once

struct Color {
    unsigned char red, green, blue;
    explicit Color(int r = 0, int g = 0, int b = 0) {
        red = r;
        green = g;
        blue = b;
    }
    bool operator==(const Color& rhs) const {
        return red == rhs.red && green == rhs.green && blue == rhs.blue;
    }
    bool operator!=(const Color& rhs) const { return !operator==(rhs); }
    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "RGB(" << (int)color.red << ", " << (int)color.green << ", " << (int)color.blue << ")";
        return os;
    }
};
