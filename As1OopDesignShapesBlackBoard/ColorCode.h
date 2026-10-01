#pragma once

class ColorCode {
private:
    struct ColorPair {
        std::string name;
        std::string code;
    };
public:
    static std::string GetColorCode(const std::string& colorName);
};