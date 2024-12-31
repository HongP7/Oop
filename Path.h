#ifndef PATH_H
#define PATH_H
#define _USE_MATH_DEFINES
#include "Shapes.h"
#include "Defs.h"
#include <vector>
#include <string>


class Path {
public:
    std::vector<float> values;
    std::vector<char> types;
};

class ClassPath : public Shape {
public:
    ClassPath(const std::string& pathData, const Transform& transform);
    ClassPath(float fillOpacity, float strokeOpacity, float strokeWidth, RGB fillRGB, RGB strokeRGB, Transform transform, Path path, const std::string& fill, const std::string& stroke, float strokeDasharray, float strokeDashoffset);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;
    void convertPathToValue();
    void addValue(float value);
    void addType(char type);
    void clear();

private:
    std::string pathData;
    std::vector<float> values;
    std::vector<char> types;
    Path path;
    float fillOpacity;
    float strokeOpacity;
    float strokeWidth;
    RGB fillRGB;
    RGB strokeRGB;
    Transform transform;
    std::string fill;
    std::string stroke;
    float strokeDasharray;
    float strokeDashoffset;

    void AddArc(GraphicsPath& pathToDraw, PointF& lastPoint, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, PointF endPoint);
    void AddArc(GraphicsPath& pathToDraw, float cx, float cy, float rx, float ry, float startAngle, float deltaAngle, bool sweepFlag);
};

void convertPathToValue(const std::string& pathData, Path& path);

#endif // PATH_H
