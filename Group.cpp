#include "Group.h"

Group::Group(std::vector<Shape*>& shapes, float strokeOpacity, float fillOpacity, RGB strokeRGB, RGB fillRGB, float strokeWidth, Transform transform, int fontSize, std::string fill, std::string stroke)
    : Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke), shapes(shapes), fontSize(fontSize) {
}

void Group::Draw(Graphics& graphics, std::vector<Defs*>& defs) {
    for (auto& shape : shapes) {
        shape->Draw(graphics, defs);
    }
}
