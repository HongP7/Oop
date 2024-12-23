#include "Viewbox.h"
#include <iostream>

ViewBox::ViewBox(float width, float height, float scale)
    : width(width), height(height), scale(scale) {}

float ViewBox::getWidth() const {
    return width;
}

float ViewBox::getHeight() const {
    return height;
}

float ViewBox::getScale() const {
    return scale;
}

void ViewBox::setWidth(float newWidth) {
    width = newWidth;
}

void ViewBox::setHeight(float newHeight) {
    height = newHeight;
}

void ViewBox::setScale(float newScale) {
    scale = newScale;
}

void ViewBox::DrawViewBox() const {
    std::cout << "Drawing ViewBox with width: " << width
              << ", height: " << height
              << ", and scale: " << scale << std::endl;
}
