#ifndef PATH_H
#define PATH_H

#include "Shapes.h"
#include <vector>
#include <string>

class ClassPath : public Shape {
public:
    ClassPath(const std::string& pathData, const Transform& transform);
    void Draw(Graphics& graphics, std::vector<Defs*>& defs) override;

private:
    void convertPathToValue();
    std::string pathData;
    std::vector<float> values;
    std::vector<char> types;
};

#endif // PATH_H
