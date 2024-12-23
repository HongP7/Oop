#ifndef GROUP_H
#define GROUP_H

#include "Shapes.h"
#include <vector>

class Group : public Shape {
public:
    Group(std::vector<Shape*>& shapes, float strokeOpacity, float fillOpacity, RGB strokeRGB, RGB fillRGB, float strokeWidth, Transform transform, int fontSize, std::string fill, std::string stroke);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;

private:
    std::vector<Shape*> shapes;
    int fontSize;
};

#endif // GROUP_H
