#ifndef PATH_H
#define PATH_H

#include "Shapes.h"
#include <vector>
#include <string>

class ClassPath : public Shape {
public:
    ClassPath(const std::string& pathData, float fillOpacity, float strokeOpacity, RGB fillRGB, RGB strokeRGB, float strokeWidth, Transform transform, std::string fill, std::string stroke);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;
    void convertPathToValue();

private:
    std::string pathData;
    std::vector<float> values;
    std::vector<char> types;
};

#endif // PATH_H
