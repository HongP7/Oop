#include "Text.h"
#include <iostream>
#include <algorithm>
#include<string>

Text_::Text_(float x, float y, std::string content, float fontSize, float fillOpacity, float strokeOpacity, float strokeWidth, 
           std::string fontFamily, float dx, float dy, std::string textAnchor, std::string fontStyle, 
           bool checkStroke, std::string fill, std::string stroke)
    : x(x), y(y), content(content), fontSize(fontSize), fillOpacity(fillOpacity), strokeOpacity(strokeOpacity), 
      strokeWidth(strokeWidth), fontFamily(fontFamily), dx(dx), dy(dy), textAnchor(textAnchor), 
      fontStyle(fontStyle), checkStroke(checkStroke), fill(fill), stroke(stroke) {}

float Text_::getX() const { return x; }
float Text_::getY() const { return y; }
std::string Text_::getContent() const { return content; }
float Text_::getFontSize() const { return fontSize; }
std::string Text_::getFontFamily() const { return fontFamily; }
std::string Text_::getFill() const { return fill; }
std::string Text_::getStroke() const { return stroke; }

void Text_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    normalizeTextContent();
    if (IsStringValidForFont()) {
        std::cout << "Drawing text at (" << x << ", " << y << ") with content: '" << content 
                  << "', font size: " << fontSize << ", font family: " << fontFamily 
                  << ", fill: " << fill << ", stroke: " << stroke << std::endl;
    } else {
        std::cout << "Invalid text content for font" << std::endl;
    }
}

void Text_::normalizeTextContent() {
    std::transform(content.begin(), content.end(), content.begin(), ::toupper);
}

bool Text_::IsStringValidForFont() const {
    return !content.empty(); 
}
