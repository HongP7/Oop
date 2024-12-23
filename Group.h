#ifndef GROUP_H
#define GROUP_H

#include "Shapes.h"
#include <vector>

class Group : public Shape {
public:
    Group(const Transform& transform);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;
    void AddShape(Shape* shape);

private:
    std::vector<Shape*> shapes;
};

#endif // GROUP_H
