#include "Text.h"
#include <iostream>
#include <algorithm>
#include<string>

Text::Text(float x, float y, std::string content, float fontSize, float fillOpacity, float strokeOpacity, float strokeWidth, 
           std::string fontFamily, float dx, float dy, std::string textAnchor, std::string fontStyle, 
           bool checkStroke, std::string fill, std::string stroke)
    : x(x), y(y), content(content), fontSize(fontSize), fillOpacity(fillOpacity), strokeOpacity(strokeOpacity), 
      strokeWidth(strokeWidth), fontFamily(fontFamily), dx(dx), dy(dy), textAnchor(textAnchor), 
      fontStyle(fontStyle), checkStroke(checkStroke), fill(fill), stroke(stroke) {}

float Text::getX() const { return x; }
float Text::getY() const { return y; }
std::string Text::getContent() const { return content; }
float Text::getFontSize() const { return fontSize; }
std::string Text::getFontFamily() const { return fontFamily; }
std::string Text::getFill() const { return fill; }
std::string Text::getStroke() const { return stroke; }

void Text::Draw() {
    normalizeTextContent();
    if (IsStringValidForFont()) {
        std::cout << "Drawing text at (" << x << ", " << y << ") with content: '" << content 
                  << "', font size: " << fontSize << ", font family: " << fontFamily 
                  << ", fill: " << fill << ", stroke: " << stroke << std::endl;
    } else {
        std::cout << "Invalid text content for font" << std::endl;
    }
}

void Text::normalizeTextContent() {
    std::transform(content.begin(), content.end(), content.begin(), ::toupper);
}

bool Text::IsStringValidForFont() const {
    return !content.empty(); 
}
