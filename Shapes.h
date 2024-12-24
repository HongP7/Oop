#ifndef SHAPE_H
#define SHAPE_H
#include "Defs.h"
#include <string>
#include <vector>
class Shape
{
protected:
    float fillOpacity, strokeOpacity, strokeWidth;
    RGB fillRGB, strokeRGB;
    Transform transform;
    string fill, stroke;

public:
    Shape();
    Shape(vector<string>);
    Shape(float, RGB, float, Transform, string);

    Shape(RGB, RGB, float, float, float, Transform, string, string);
    GraphicsState TransformSVG(Graphics&, Transform);
    virtual void Draw(Graphics&, vector<Defs*>&) = 0;
};
class Ellipse : public Shape
{
protected:
    float cx, cy;
    float rx, ry;

public:
    Ellipse(float, float, float, float, float, float, float, RGB, RGB, Transform, string, string);
    void Draw(Graphics&, vector<Defs*>&) override;
};
class Circle : public Ellipse
{
private:
    float r;

public:
    Circle(float, float, float, float, float, RGB, RGB, float, Transform, string, string);

    void Draw(Graphics&, vector<Defs*>&) override;
};
class Rectangle : public Shape
{
private:
    float x, y, width, height;
public:
    Rectangle(float, float, float, float, float, float, RGB, RGB, float, Transform, string, string);
    void Draw(Graphics&, vector<Defs*>&) override;
};

class Line : public Shape
{
private:
    float x1, y1, x2, y2;

public:
    Line(float, float, float, float, float, RGB, float, Transform, string);
    void Draw(Graphics&, vector<Defs*>&) override;
};
class Polygon : public Shape
{
private:
    string points;
    vector<pair<float, float>> allPoints;

public:
    string chuanhoa1(string);
    void parsePoints1(string, vector<pair<float, float>>&);
    Polygon(const string&, float, float, RGB, RGB, float, Transform, string, string);
    void Draw(Graphics&, vector<Defs*>&) override;
};
class Polyline : public Shape
{
private:

    string points;
    vector<pair<float, float>> allPoints;

public:
    string chuanhoa2(string);
    void parsePoints2(string, vector<pair<float, float>>&);
    Polyline(const string&, float, float, float, RGB, RGB, Transform, string, string);
    void Draw(Graphics&, vector<Defs*>&) override;
};
#endif // !SHAPES_H
