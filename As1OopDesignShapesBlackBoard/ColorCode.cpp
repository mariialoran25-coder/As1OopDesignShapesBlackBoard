#pragma once
#include "string"
#include "ColorCode.h"

std::string ColorCode::GetColorCode(const std::string& colorName) {
    if (colorName == "red") return "\033[31m";
    if (colorName == "blue")return "\033[34m";
    if (colorName == "yellow") return "\033[33m";
    if (colorName == "green") return "\033[32m";
    if (colorName == "black") return "\033[30m";
    if (colorName == "pink") return "\033[38;2;255;192;203m";
    return "\033[0m";
};