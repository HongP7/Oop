#include "Group.h"

Group_::Group_(vector<Shape*>& shapes, float strokeOpacity, float fillOpacity, RGB strokeRGB, RGB fillRGB, float strokeWidth, Transform transform, int fontSize, string fill, string stroke)
    : Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke), shapes(shapes), fontSize(fontSize) {}

void Group_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    for (auto& shape : shapes)
    {
        shape->Draw(graphics, defs);
    }
}

void Group_::AddShape(Shape* shape) {
    shapes.push_back(shape);
}
