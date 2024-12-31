#ifndef PATH_H
#define PATH_H

#include "Shapes.h"
#include "Defs.h"
#include <vector>
#include <string>

class ClassPath : public Shape {
public:
    ClassPath(const std::string& pathData, const Transform& transform);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;
    void convertPathToValue();

    void addValue(float value);
    void addType(char type);
    void clear();

private:
    std::string pathData;
    std::vector<float> values;
    std::vector<char> types;

    void AddArc(GraphicsPath& pathToDraw, PointF& lastPoint, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, PointF endPoint);
    void AddArc(GraphicsPath& pathToDraw, float cx, float cy, float rx, float ry, float startAngle, float deltaAngle, bool sweepFlag);
};

#endif // PATH_H
