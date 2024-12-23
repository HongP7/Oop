#include "stdafx.h"
#include "rapidxml.hpp"
#include "pugixml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;
using namespace rapidxml;   
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")

class SVGElement {
public:
    virtual void render() = 0;
};

class Circle : public SVGElement {
private:
    float centerX, centerY, radius;
    float fillOpacity, strokeOpacity, strokeWidth;
    string fillColor, strokeColor;
    int fillR, fillG, fillB;
    int strokeR, strokeG, strokeB;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }

    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

public:
    Circle(float cx, float cy, float r, float fillOp, float strokeOp, const string& fill, const string& stroke, float strokeW)
        : centerX(cx), centerY(cy), radius(r), fillOpacity(fillOp), strokeOpacity(strokeOp), fillColor(fill), strokeColor(stroke), strokeWidth(strokeW) {
        parseFillColor();
        parseStrokeColor();
    }

    void render() override {}

    void getData(float& cx, float& cy, float& r, float& fillOp, float& strokeOp, float& strokeW, int& fillR_, int& fillG_, int& fillB_, int& strokeR_, int& strokeG_, int& strokeB_) {
        cx = centerX;
        cy = centerY;
        r = radius;
        fillOp = fillOpacity;
        strokeOp = strokeOpacity;
        strokeW = strokeWidth;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
    }
};

class Rectangle_ : public SVGElement {
private:
    float posX, posY, rectWidth, rectHeight;
    float fillOpacity, strokeWidth;
    string fillColor, strokeColor;
    int fillR, fillG, fillB;
    int strokeR, strokeG, strokeB;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }

    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

public:
    Rectangle_(float x, float y, float width, float height, float fillOp, const string& fill, const string& stroke, float strokeW)
        : posX(x), posY(y), rectWidth(width), rectHeight(height), fillOpacity(fillOp), fillColor(fill), strokeColor(stroke), strokeWidth(strokeW) {
        parseFillColor();
        parseStrokeColor();
    }

    void render() override {}

    void getData(float& x, float& y, float& width, float& height, float& fillOp, int& fillR_, int& fillG_, int& fillB_, int& strokeR_, int& strokeG_, int& strokeB_, float& strokeW) {
        x = posX;
        y = posY;
        width = rectWidth;
        height = rectHeight;
        fillOp = fillOpacity;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
        strokeW = strokeWidth;
    }
};

class Line : public SVGElement {
private:
    float startX, startY, endX, endY;
    float strokeOpacity, strokeWidth;
    string strokeColor;
    int strokeR, strokeG, strokeB;

    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

public:
    Line(float x1, float y1, float x2, float y2, float strokeOp, const string& stroke, float strokeW)
        : startX(x1), startY(y1), endX(x2), endY(y2), strokeOpacity(strokeOp), strokeColor(stroke), strokeWidth(strokeW) {
        parseStrokeColor();
    }

    void render() override {}

    void getData(float& x1, float& y1, float& x2, float& y2, float& strokeOp, float& strokeW, int& strokeR_, int& strokeG_, int& strokeB_) {
        x1 = startX;
        y1 = startY;
        x2 = endX;
        y2 = endY;
        strokeOp = strokeOpacity;
        strokeW = strokeWidth;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
    }
};

class Text : public SVGElement {
private:
    float posX, posY, fontSize;
    string content, fillColor;
    int fillR, fillG, fillB;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }

public:
    Text(float x, float y, const string& text, float size, const string& fill)
        : posX(x), posY(y), content(text), fontSize(size), fillColor(fill) {
        parseFillColor();
    }

    void render() override {}

    void getData(float& x, float& y, float& size, string& text, int& fillR_, int& fillG_, int& fillB_) {
        x = posX;
        y = posY;
        size = fontSize;
        text = content;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
    }
};

class Polyline_ : public SVGElement {
private:
    string points;
    float fillOpacity, strokeOpacity, strokeWidth;
    string fillColor, strokeColor;
    int fillR, fillG, fillB;
    int strokeR, strokeG, strokeB;
    vector<pair<float, float>> allPoints;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }
    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

    void parsePoints() {
        regex pointRegex(R"(\s*([\d.]+),\s*([\d.]+)\s*)");
        smatch matches;
        string pointsCopy = points;
        while (regex_search(pointsCopy, matches, pointRegex)) {
            float x = stof(matches[1]);
            float y = stof(matches[2]);
            allPoints.push_back({ x, y });
            pointsCopy = matches.suffix();
        }
    }

public:
    Polyline_(const string& pts, float fillOp, float strokeOp, float strokeW, const string& fill, const string& stroke)
        : points(pts), fillOpacity(fillOp), strokeOpacity(strokeOp), strokeWidth(strokeW), fillColor(fill), strokeColor(stroke) {
        parseFillColor();
        parseStrokeColor();
        parsePoints();
    }

    void render() override {}

    void getData(float& fillOp, float& strokeOp, float& strokeW, int& fillR_, int& fillG_, int& fillB_, int& strokeR_, int& strokeG_, int& strokeB_, vector<pair<float, float>>& pts) {
        fillOp = fillOpacity;
        strokeOp = strokeOpacity;
        strokeW = strokeWidth;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
        pts = allPoints;
    }
};

class Polygon_ : public SVGElement {
private:
    string points;
    float fillOpacity, strokeOpacity, strokeWidth;
    string fillColor, strokeColor;
    int fillR, fillG, fillB;
    int strokeR, strokeG, strokeB;
    vector<pair<float, float>> allPoints;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }

    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

    void parsePoints() {
        regex pointRegex(R"(\s*([\d.]+),\s*([\d.]+)\s*)");
        smatch matches;
        string pointsCopy = points;
        while (regex_search(pointsCopy, matches, pointRegex)) {
            float x = stof(matches[1]);
            float y = stof(matches[2]);
            allPoints.push_back({ x, y });
            pointsCopy = matches.suffix();
        }
    }

public:
    Polygon_(const string& pts, float fillOp, float strokeOp, const string& fill, const string& stroke, float strokeW)
        : points(pts), fillOpacity(fillOp), strokeOpacity(strokeOp), fillColor(fill), strokeColor(stroke), strokeWidth(strokeW) {
        parseFillColor();
        parseStrokeColor();
        parsePoints();
    }

    void render() override {}

    void getData(float& fillOp, float& strokeOp, float& strokeW, int& fillR_, int& fillG_, int& fillB_, int& strokeR_, int& strokeG_, int& strokeB_, vector<pair<float, float>>& pts) {
        fillOp = fillOpacity;
        strokeOp = strokeOpacity;
        strokeW = strokeWidth;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
        pts = allPoints;
    }
};

class Ellipse_ : public SVGElement {
private:
    float centerX, centerY, radiusX, radiusY;
    float fillOpacity, strokeOpacity, strokeWidth;
    string fillColor, strokeColor;
    int fillR, fillG, fillB;
    int strokeR, strokeG, strokeB;

    void parseFillColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(fillColor, matches, rgbRegex)) {
            fillR = stoi(matches[1]);
            fillG = stoi(matches[2]);
            fillB = stoi(matches[3]);
        } else {
            fillColor = "default_color";
            fillR = fillG = fillB = 0;
        }
    }

    void parseStrokeColor() {
        regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
        smatch matches;
        if (regex_search(strokeColor, matches, rgbRegex)) {
            strokeR = stoi(matches[1]);
            strokeG = stoi(matches[2]);
            strokeB = stoi(matches[3]);
        } else {
            strokeColor = "default_color";
            strokeR = strokeG = strokeB = 0;
        }
    }

public:
    Ellipse_(float cx, float cy, float rx, float ry, float fillOp, float strokeOp, float strokeW, string fill, string stroke)
        : centerX(cx), centerY(cy), radiusX(rx), radiusY(ry), fillOpacity(fillOp), strokeOpacity(strokeOp), fillColor(fill), strokeColor(stroke), strokeWidth(strokeW) {
        parseFillColor();
        parseStrokeColor();
    }

    void render() override {}

    void getData(float& cx, float& cy, float& rx, float& ry, float& fillOp, float& strokeOp, float& strokeW, int& fillR_, int& fillG_, int& fillB_, int& strokeR_, int& strokeG_, int& strokeB_) {
        cx = centerX;
        cy = centerY;
        rx = radiusX;
        ry = radiusY;
        fillOp = fillOpacity;
        strokeOp = strokeOpacity;
        strokeW = strokeWidth;
        fillR_ = fillR;
        fillG_ = fillG;
        fillB_ = fillB;
        strokeR_ = strokeR;
        strokeG_ = strokeG;
        strokeB_ = strokeB;
    }
};

void parseAndRenderSVG(const string& filePath, vector<SVGElement*>& elements) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filePath.c_str());
    if (result) {
        pugi::xml_node svgNode = doc.child("svg");
        for (pugi::xml_node elementNode : svgNode.children()) {
            string elementName = elementNode.name();
            if (elementName == "circle") {
                float cx = elementNode.attribute("cx").as_float();
                float cy = elementNode.attribute("cy").as_float();
                float r = elementNode.attribute("r").as_float();
                float fillOpacity = elementNode.attribute("fill-opacity").as_float();
                float strokeOpacity = elementNode.attribute("stroke-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Circle* circle = new Circle(cx, cy, r, fillOpacity, strokeOpacity, fill, stroke, strokeWidth);
                elements.push_back(circle);
            } else if (elementName == "rect") {
                float x = elementNode.attribute("x").as_float();
                float y = elementNode.attribute("y").as_float();
                float width = elementNode.attribute("width").as_float();
                float height = elementNode.attribute("height").as_float();
                float fillOpacity = elementNode.attribute("fill-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Rectangle_* rect = new Rectangle_(x, y, width, height, fillOpacity, fill, stroke, strokeWidth);
                elements.push_back(rect);
            } else if (elementName == "line") {
                float x1 = elementNode.attribute("x1").as_float();
                float y1 = elementNode.attribute("y1").as_float();
                float x2 = elementNode.attribute("x2").as_float();
                float y2 = elementNode.attribute("y2").as_float();
                float strokeOpacity = elementNode.attribute("stroke-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Line* line = new Line(x1, y1, x2, y2, strokeOpacity, stroke, strokeWidth);
                elements.push_back(line);
            } else if (elementName == "text") {
                float x = elementNode.attribute("x").as_float();
                float y = elementNode.attribute("y").as_float();
                string content = elementNode.child_value();
                float fontSize = elementNode.attribute("font-size").as_float();
                string fill = elementNode.attribute("fill").value();
                Text* text = new Text(x, y, content, fontSize, fill);
                elements.push_back(text);
            } else if (elementName == "polyline") {
                string points = elementNode.attribute("points").value();
                float fillOpacity = elementNode.attribute("fill-opacity").as_float();
                float strokeOpacity = elementNode.attribute("stroke-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Polyline_* polyline = new Polyline_(points, fillOpacity, strokeOpacity, strokeWidth, fill, stroke);
                elements.push_back(polyline);
            } else if (elementName == "polygon") {
                string points = elementNode.attribute("points").value();
                float fillOpacity = elementNode.attribute("fill-opacity").as_float();
                float strokeOpacity = elementNode.attribute("stroke-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Polygon_* polygon = new Polygon_(points, fillOpacity, strokeOpacity, fill, stroke, strokeWidth);
                elements.push_back(polygon);
            } else if (elementName == "ellipse") {
                float cx = elementNode.attribute("cx").as_float();
                float cy = elementNode.attribute("cy").as_float();
                float rx = elementNode.attribute("rx").as_float();
                float ry = elementNode.attribute("ry").as_float();
                float fillOpacity = elementNode.attribute("fill-opacity").as_float();
                float strokeOpacity = elementNode.attribute("stroke-opacity").as_float();
                string fill = elementNode.attribute("fill").value();
                string stroke = elementNode.attribute("stroke").value();
                float strokeWidth = elementNode.attribute("stroke-width").as_float();
                Ellipse_* ellipse = new Ellipse_(cx, cy, rx, ry, fillOpacity, strokeOpacity, strokeWidth, fill, stroke);
                elements.push_back(ellipse);
            }
        }
    } else {
        cout << "Cannot read SVG file." << endl;
    }
}

string getClassName(SVGElement* element) {
    if (dynamic_cast<Circle*>(element) != NULL) {
        return "Circle";
    } else if (dynamic_cast<Rectangle_*>(element) != NULL) {
        return "Rectangle";
    } else if (dynamic_cast<Line*>(element) != NULL) {
        return "Line";
    } else if (dynamic_cast<Text*>(element) != NULL) {
        return "Text";
    } else if (dynamic_cast<Polyline_*>(element) != NULL) {
        return "Polyline";
    } else if (dynamic_cast<Polygon_*>(element) != NULL) {
        return "Polygon";
    } else if (dynamic_cast<Ellipse_*>(element) != NULL) {
        return "Ellipse";
    }
    return "";
}

void drawRectangle(Graphics& graphics, float x, float y, float width, float height, float fillOpacity, int fillR, int fillG, int fillB, int strokeR, int strokeG, int strokeB, int strokeWidth) {
    SolidBrush rectBrush(Color(255 * fillOpacity, fillR, fillG, fillB));
    graphics.FillRectangle(&rectBrush, x, y, width, height);
    Pen rectBorderPen(Color(strokeR, strokeG, strokeB), strokeWidth);
    graphics.DrawRectangle(&rectBorderPen, x, y, width, height);
}

void drawCircle(Graphics& graphics, float cx, float cy, float r, float fillOpacity, float strokeOpacity, float strokeWidth, int fillR, int fillG, int fillB, int strokeR, int strokeG, int strokeB) {
    SolidBrush circleBrush(Color(255 * fillOpacity, fillR, fillG, fillB));
    graphics.FillEllipse(&circleBrush, cx - r, cy - r, 2 * r, 2 * r);
    Pen circlePen(Color(255 * strokeOpacity, strokeR, strokeG, strokeB), strokeWidth);
    graphics.DrawEllipse(&circlePen, cx - (r + strokeWidth / 2), cy - (r + strokeWidth / 2), 2 * (r + strokeWidth / 2), 2 * (r + strokeWidth / 2));
}

void drawLine(Graphics& graphics, float x1, float y1, float x2, float y2, float strokeOpacity, float strokeWidth, int strokeR, int strokeG, int strokeB) {
    Pen linePen(Color(255 * strokeOpacity, strokeR, strokeG, strokeB), strokeWidth);
    graphics.DrawLine(&linePen, x1, y1, x2, y2);
}

void drawText(Graphics& graphics, float x, float y, float fontSize, string content, int fillR, int fillG, int fillB) {
    SolidBrush textBrush(Color(fillR, fillG, fillB));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, 30, FontStyleRegular, UnitPixel);
    PointF point(x - fontSize, y - fontSize);
    wstring text(content.begin(), content.end());
    graphics.DrawString(text.c_str(), -1, &font, point, &textBrush);
}

void drawPolyline(Graphics& graphics, float fillOpacity, float strokeOpacity, float strokeWidth, int fillR, int fillG, int fillB, int strokeR, int strokeG, int strokeB, vector<pair<float, float>> points) {
    Pen polylinePen(Color(strokeOpacity * 255, strokeR, strokeG, strokeB), strokeWidth);
    SolidBrush polylineBrush(Color(fillOpacity * 255, fillR, fillG, fillB));
    int numPoints = points.size();
    PointF* pointArray = new PointF[numPoints];
    for (int i = 0; i < numPoints; ++i) {
        pointArray[i] = PointF(points[i].first, points[i].second);
    }
    graphics.FillPolygon(&polylineBrush, pointArray, static_cast<int>(numPoints));
    graphics.DrawLines(&polylinePen, pointArray, static_cast<int>(numPoints));
    delete[] pointArray;
}

void drawPolygon(Graphics& graphics, float fillOpacity, float strokeOpacity, float strokeWidth, int fillR, int fillG, int fillB, int strokeR, int strokeG, int strokeB, const vector<pair<float, float>>& points) {
    SolidBrush polygonBrush(Color(255 * fillOpacity, fillR, fillG, fillB));
    Pen polygonPen(Color(255 * strokeOpacity, strokeR, strokeG, strokeB), strokeWidth);
    vector<PointF> pointsArray;
    for (const auto& point : points) {
        pointsArray.push_back(PointF(point.first, point.second));
    }
    PointF* pointsArrayPtr = pointsArray.data();
    graphics.FillPolygon(&polygonBrush, pointsArrayPtr, static_cast<int>(points.size()));
    graphics.DrawPolygon(&polygonPen, pointsArrayPtr, static_cast<int>(points.size()));
}

void drawEllipse(Graphics& graphics, float cx, float cy, float rx, float ry, float fillOpacity, float strokeOpacity, float strokeWidth, int fillR, int fillG, int fillB, int strokeR, int strokeG, int strokeB) {
    Pen ellipsePen(Color(255 * strokeOpacity, strokeR, strokeG, strokeB), strokeWidth);
    SolidBrush ellipseBrush(Color(255 * fillOpacity, fillR, fillG, fillB));
    graphics.FillEllipse(&ellipseBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&ellipsePen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}

float zoomScale = 1.0f;

void zoomGraphics(Graphics& graphics, float scale) {
    graphics.SetTransform(new Matrix(scale, 0, 0, scale, 0, 0));
}

VOID OnPaint(HDC hdc, float zoomScale) {
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    zoomGraphics(graphics, zoomScale);
    vector<SVGElement*> elements;
    parseAndRenderSVG("sample.svg", elements);
    for (const auto& element : elements) {
        string className = getClassName(element);
        if (className == "Circle") {
            Circle* circle = dynamic_cast<Circle*>(element);
            float cx, cy, r, fillOpacity, strokeOpacity, strokeWidth;
            int fillR, fillG, fillB, strokeR, strokeG, strokeB;
            circle->getData(cx, cy, r, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB);
            drawCircle(graphics, cx, cy, r, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB);
        } else if (className == "Rectangle") {
            Rectangle_* rect = dynamic_cast<Rectangle_*>(element);
            float x, y, width, height, fillOpacity, strokeWidth;
            int fillR, fillG, fillB, strokeR, strokeG, strokeB;
            rect->getData(x, y, width, height, fillOpacity, fillR, fillG, fillB, strokeR, strokeG, strokeB, strokeWidth);
            drawRectangle(graphics, x, y, width, height, fillOpacity, fillR, fillG, fillB, strokeR, strokeG, strokeB, strokeWidth);
        } else if (className == "Line") {
            Line* line = dynamic_cast<Line*>(element);
            float x1, y1, x2, y2, strokeOpacity, strokeWidth;
            int strokeR, strokeG, strokeB;
            line->getData(x1, y1, x2, y2, strokeOpacity, strokeWidth, strokeR, strokeG, strokeB);
            drawLine(graphics, x1, y1, x2, y2, strokeOpacity, strokeWidth, strokeR, strokeG, strokeB);
        } else if (className == "Text") {
            Text* text = dynamic_cast<Text*>(element);
            float x, y, fontSize;
            string content;
            int fillR, fillG, fillB;
            text->getData(x, y, fontSize, content, fillR, fillG, fillB);
            drawText(graphics, x, y, fontSize, content, fillR, fillG, fillB);
        } else if (className == "Polyline") {
            Polyline_* polyline = dynamic_cast<Polyline_*>(element);
            float fillOpacity, strokeOpacity, strokeWidth;
            int fillR, fillG, fillB, strokeR, strokeG, strokeB;
            vector<pair<float, float>> allPoints;
            polyline->getData(fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB, allPoints);
            drawPolyline(graphics, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB, allPoints);
        } else if (className == "Polygon") {
            Polygon_* polygon = dynamic_cast<Polygon_*>(element);
            float fillOpacity, strokeOpacity, strokeWidth;
            int fillR, fillG, fillB, strokeR, strokeG, strokeB;
            vector<pair<float, float>> allPoints;
            polygon->getData(fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB, allPoints);
            drawPolygon(graphics, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB, allPoints);
        } else if (className == "Ellipse") {
            Ellipse_* ellipse = dynamic_cast<Ellipse_*>(element);
            float cx, cy, rx, ry, fillOpacity, strokeOpacity, strokeWidth;
            int fillR, fillG, fillB, strokeR, strokeG, strokeB;
            ellipse->getData(cx, cy, rx, ry, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB);
            drawEllipse(graphics, cx, cy, rx, ry, fillOpacity, strokeOpacity, strokeWidth, fillR, fillG, fillB, strokeR, strokeG, strokeB);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
    HWND hWnd;
    MSG msg;
    WNDCLASS wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("SVGDemo");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("SVGDemo"), // window class name
        TEXT("SVG Demo"), // window caption
        WS_OVERLAPPEDWINDOW, // window style
        CW_USEDEFAULT, // initial x position
        CW_USEDEFAULT, // initial y position
        CW_USEDEFAULT, // initial x size
        CW_USEDEFAULT, // initial y size
        NULL, // parent window handle
        NULL, // window menu handle
        hInstance, // program instance handle
        NULL); // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc, zoomScale);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_MOUSEWHEEL: {
        short delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta > 0)
            zoomScale += 0.1f;
        else
            zoomScale -= 0.1f;
        if (zoomScale < 0.1f)
            zoomScale = 0.1f;
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
            