#ifndef GROUP_H
#define GROUP_H

#include "Shapes.h"
#include <vector>

class Group_ : public Shape
{
private:
    vector<Shape*> shapes;
    int fontSize;

public:
    Group_(vector<Shape*>&, float, float, RGB, RGB, float, Transform, int, string, string);
    void Draw(Graphics&, vector<Defs*>&) override;
    void AddShape(Shape* shape);

};


#endif // GROUP_H
