#include "Group.h"

Group::Group(const Transform& transform)
    : Shape() {
    this->transform = transform;
}

void Group::Draw(Graphics& graphics, std::vector<Defs*>& defs) {
    GraphicsState state = TransformSVG(graphics, transform);
    for (auto& shape : shapes) {
        shape->Draw(graphics, defs);
    }
    graphics.Restore(state);
}

void Group::AddShape(Shape* shape) {
    shapes.push_back(shape);
}
