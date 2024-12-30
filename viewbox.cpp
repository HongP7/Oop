#include "ViewBox.h"
#include <iostream>

ViewBox::ViewBox(float x, float y, 
                 float width_in, float height_in, 
                 float width_out, float height_out, 
                 bool check_viewbox, float scale)
    : x(x), y(y), width_in(width_in), height_in(height_in), 
      width_out(width_out), height_out(height_out), 
      check_viewbox(check_viewbox), scale(scale) {}

float ViewBox::getScale() const { 
    return scale; 
}

float ViewBox::getWidthOut() const { 
    return width_out; 
}

float ViewBox::getHeightOut() const { 
    return height_out; 
}

float ViewBox::getWidthIn() const { 
    return width_in; 
}

float ViewBox::getHeightIn() const { 
    return height_in; 
}

bool ViewBox::getcheck() const { 
    return check_viewbox; 
}

void ViewBox::DrawViewBox() const {
    if (check_viewbox) {
        std::cout << "Drawing ViewBox at (" << x << ", " << y 
                  << ") with dimensions: " << width_in << "x" << height_in 
                  << " (input) and " << width_out << "x" << height_out 
                  << " (output), scale: " << scale << std::endl;
    } else {
        std::cout << "ViewBox is disabled." << std::endl;
    }
}