#ifndef PATH_H
#define PATH_H

#include "Shapes.h"
#include <vector>
#include <string>

class ClassPath : public Shape {
public:
    ClassPath(const std::string& pathData, const Transform& transform);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;
    void convertPathToValue();

private:
    std::string pathData;
    std::vector<float> values;
    std::vector<char> types;

    void AddArc(PointF& lastPoint, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, PointF endPoint);
    void AddArc(float cx, float cy, float rx, float ry, float startAngle, float deltaAngle, bool sweepFlag);
};

#endif // PATH_H
