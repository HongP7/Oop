#include "Text.h"
#include <iostream>
#include <algorithm> 

Text::Text(float x, float y, std::string content, float fontSize, std::string color)
    : x(x), y(y), content(content), fontSize(fontSize), color(color) {}

float Text::getX() const { return x; }
float Text::getY() const { return y; }
std::string Text::getContent() const { return content; }
float Text::getFontSize() const { return fontSize; }
std::string Text::getColor() const { return color; }

void Text::Draw() {
    normalizeTextContent();
    if (IsStringValidForFont()) {
        std::cout << "Drawing text at (" << x << ", " << y << ") with content: '" << content 
                  << "', font size: " << fontSize << " and color: " << color << std::endl;
    } else {
        std::cout << "Invalid text content for font" << std::endl;
    }
}

void Text::normalizeTextContent() {
    std::transform(content.begin(), content.end(), content.begin(), ::toupper); // For example, converting to uppercase
}


bool Text::IsStringValidForFont() const {
    return !content.empty(); 
}
