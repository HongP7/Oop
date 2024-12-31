#include "Shapes.h"
// Shape
Shape::Shape() {}

Shape::Shape(vector<string> transformOrder)
    : fillOpacity(1.0f), strokeOpacity(1.0f), strokeWidth(1.0f),
    fillRGB({ 255, 255, 255 }), strokeRGB({ 0, 0, 0 }),
    transform({ 0, 0, 0, 1.0f, 1.0f, 0, 0, transformOrder }) {
}

Shape::Shape(float strokeOpacity, RGB strokeRGB, float strokeWidth, Transform transform, string stroke)
    : strokeOpacity(strokeOpacity), strokeRGB(strokeRGB), strokeWidth(strokeWidth), transform(transform), stroke(stroke) {
}

Shape::Shape(RGB fillRGB, RGB strokeRGB, float fillOpacity, float strokeOpacity, float strokeWidth, Transform transform, string fill, string stroke)
    : fillRGB(fillRGB), strokeRGB(strokeRGB), fillOpacity(fillOpacity), strokeOpacity(strokeOpacity), strokeWidth(strokeWidth), transform(transform), fill(fill), stroke(stroke) {
}


// Ellipse_
Ellipse_::Ellipse_(float cx, float cy, float rx, float ry, float fillOpacity, float strokeOpacity, float strokeWidth, RGB fillRGB, RGB strokeRGB, Transform transform, string fill, string stroke)
    : Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke), cx(cx), cy(cy), rx(rx), ry(ry) {
}

void Ellipse_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    Pen ellipsePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    SolidBrush ellipseBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    GraphicsState state = TransformSVG(graphics, transform);
    graphics.DrawEllipse(&ellipsePen, cx - rx, cy - ry, 2 * rx, 2 * ry);
    if (fill != "") {
        LinearGradient* linearGradient = nullptr;
        vector<LinearGradient*> vectorlinear = defs[0]->getlinear();
        for (LinearGradient* lin : vectorlinear) {
            if (lin->getID() == fill) {
                linearGradient = lin;
                break;
            }
        }
        if (linearGradient != nullptr) {
            vector<Stop*> StopList = linearGradient->getStopList();
            Color* colors = new Color[StopList.size()];

            for (int i = 0; i < StopList.size(); ++i) {
                if (i > 0) {
                    colors[i] = Color(255 * StopList[i]->getstopOpacity(), StopList[i]->getstopColor_red(), StopList[i]->getstopColor_green(), StopList[i]->getstopColor_blue());
                }
            }
            float* positions = new float[StopList.size()];
            for (size_t i = 0; i < StopList.size(); ++i) {
                if (i > 0) {
                    positions[i] = StopList[i]->getoffset();
                }
            }

            pointLinearGradient pointlineargradient = linearGradient->getPoint();

            LinearGradientBrush gradientBrush(PointF(pointlineargradient.x1, pointlineargradient.y1), PointF(pointlineargradient.x2, pointlineargradient.y2), colors[0], colors[StopList.size() - 1]);
            gradientBrush.SetLinearColors(colors[0], colors[StopList.size() - 1]); //  default gradientUnits = userSpaceOnUse
            gradientBrush.SetInterpolationColors(colors, positions, StopList.size());
            gradientBrush.SetGammaCorrection(TRUE);
            graphics.FillEllipse(&gradientBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);

            delete[] colors;
            delete[] positions;
        }
    }
    else
        graphics.FillEllipse(&ellipseBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.Restore(state);
}


// Circle
Circle::Circle(float cx, float cy, float r, float fillOpacity, float strokeOpacity, RGB fillRGB, RGB strokeRGB, float strokeWidth, Transform transform, string fill, string stroke)
    : Ellipse_(cx, cy, r, r, fillOpacity, strokeOpacity, strokeWidth, fillRGB, strokeRGB, transform, fill, stroke), r(r) {
}

void Circle::Draw(Graphics& graphics, vector<Defs*>& defs) {
    SolidBrush circleBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    Pen circlePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    GraphicsState state = TransformSVG(graphics, transform);
    graphics.DrawEllipse(&circlePen, cx - (r + strokeWidth / 2), cy - (r + strokeWidth / 2), 2 * (r + strokeWidth / 2), 2 * (r + strokeWidth / 2));
    if (fill != "") {
        LinearGradient* linearGradient = nullptr;
        vector<LinearGradient*> vectorlinear = defs[0]->getlinear();
        for (LinearGradient* lin : vectorlinear) {
            if (lin->getID() == fill) {
                linearGradient = lin;
                break;
            }
        }
        if (linearGradient != nullptr) {
            vector<Stop*> StopList = linearGradient->getStopList();
            Color* colors = new Color[StopList.size()];
            for (int i = 0; i < StopList.size(); ++i) {
                if (i > 0) {
                    colors[i] = Color(255 * StopList[i]->getstopOpacity(), StopList[i]->getstopColor_red(), StopList[i]->getstopColor_green(), StopList[i]->getstopColor_blue());
                }
            }
            float* positions = new float[StopList.size()];
            for (size_t i = 0; i < StopList.size(); ++i) {
                if (i > 0)
                    positions[i] = StopList[i]->getoffset();
            }

            pointLinearGradient pointlineargradient = linearGradient->getPoint();

            LinearGradientBrush gradientBrush(PointF(pointlineargradient.x1, pointlineargradient.y1), PointF(pointlineargradient.x2, pointlineargradient.y2), colors[0], colors[StopList.size() - 1]);
            gradientBrush.SetInterpolationColors(colors, positions, StopList.size());
            gradientBrush.SetGammaCorrection(TRUE);
            graphics.FillEllipse(&gradientBrush, cx - r, cy - r, 2 * r, 2 * r);
            delete[] colors;
            delete[] positions;
        }
    }
    else
        graphics.FillEllipse(&circleBrush, cx - r, cy - r, 2 * r, 2 * r);
    graphics.Restore(state);
}

// Rectangle_
Rectangle_::Rectangle_(float x, float y, float width, float height, float fillOpacity, float strokeOpacity, RGB fillRGB, RGB strokeRGB, float strokeWidth, Transform transform, string fill, string stroke)
    : Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke), x(x), y(y), width(width), height(height) {
}

void Rectangle_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    SolidBrush RectBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    Pen RectBorderPen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    GraphicsState state = TransformSVG(graphics, transform);
    graphics.DrawRectangle(&RectBorderPen, x, y, width, height);
    if (fill != "") {
        LinearGradient* linearGradient = nullptr;
        vector<LinearGradient*> vectorlinear = defs[0]->getlinear();
        for (LinearGradient* lin : vectorlinear) {
            if (lin->getID() == fill) {
                linearGradient = lin;
                break;
            }
        }
        if (linearGradient != nullptr) {
            vector<Stop*> StopList = linearGradient->getStopList();
            Color* colors = new Color[StopList.size()];

            for (int i = 0; i < StopList.size(); ++i) {
                if (i > 0)
                    colors[i] = Color(255 * StopList[i]->getstopOpacity(), StopList[i]->getstopColor_red(), StopList[i]->getstopColor_green(), StopList[i]->getstopColor_blue());
            }
            float* positions = new float[StopList.size()];

            for (size_t i = 0; i < StopList.size(); ++i) {
                if (i > 0)
                    positions[i] = StopList[i]->getoffset();
            }
            pointLinearGradient pointlineargradient = linearGradient->getPoint();
            LinearGradientBrush gradientBrush(PointF(pointlineargradient.x1, pointlineargradient.y1), PointF(pointlineargradient.x2, pointlineargradient.y2), colors[0], colors[StopList.size() - 1]);
            gradientBrush.SetLinearColors(colors[0], colors[StopList.size() - 1]); //  default gradientUnits = userSpaceOnUse
            gradientBrush.SetInterpolationColors(colors, positions, StopList.size());
            gradientBrush.SetGammaCorrection(TRUE);
            graphics.FillRectangle(&gradientBrush, x, y, width, height);
            delete[] colors;
            delete[] positions;
        }
    }
    else
        graphics.FillRectangle(&RectBrush, x, y, width, height);
    graphics.Restore(state);
}


// Line
Line::Line(float x1, float y1, float x2, float y2, float strokeOpacity, RGB strokeRGB, float strokeWidth, Transform transform, string stroke)
    : Shape(strokeOpacity, strokeRGB, strokeWidth, transform, stroke), x1(x1), y1(y1), x2(x2), y2(y2) {
}

void Line::Draw(Graphics& graphics, vector<Defs*>& defs) {
    GraphicsState state = TransformSVG(graphics, transform);
    Pen linePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    graphics.DrawLine(&linePen, x1, y1, x2, y2);
    graphics.Restore(state);
}

// Polygon_
string Polygon_::standardization(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',')
            input[i] = ' ';
    }
    istringstream iss(input);
    ostringstream oss;
    string word;
    bool first = true;

    while (iss >> word) {
        if (!first)
            oss << " ";
        oss << word;
        first = false;
    }
    return oss.str();
}

void Polygon_::parsePoints_(string s, vector<pair<float, float>>& allPoints) {
    int i = 0;
    s = standardization(s);
    while (i < s.length()) {

        if (isdigit(s[i]) || s[i] == '-' || s[i] == '.' || s[i] == ' ')
        {

            size_t next_pos;
            float x = stof(s.substr(i), &next_pos);
            i += next_pos + 1;

            float y = stof(s.substr(i), &next_pos);
            i += next_pos;

            allPoints.push_back(make_pair(x, y));
        }
    }
}

Polygon_::Polygon_(const string& points, float fillOpacity, float strokeOpacity, RGB fillRGB, RGB strokeRGB, float strokeWidth, Transform transform, string fill, string stroke)
    : points(points), Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke) {
    parsePoints_(points, allPoints);
}

void Polygon_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    GraphicsState state = TransformSVG(graphics, transform);
    SolidBrush polygonBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    Pen polygonPen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    vector<PointF> pointsArray;
    for (const auto& point : allPoints) {
        pointsArray.push_back(PointF(point.first, point.second));
    }
    PointF* pointsArrayPtr = pointsArray.data();
    int numPoints = static_cast<int>(pointsArray.size());

    if (numPoints > 0) {
        graphics.FillPolygon(&polygonBrush, pointsArrayPtr, numPoints, FillModeWinding);
        graphics.DrawPolygon(&polygonPen, pointsArrayPtr, numPoints);
    }
    graphics.Restore(state);
}

// Polyline_
string Polyline_::standardization_Poly(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',')
            input[i] = ' ';
    }
    istringstream iss(input);
    ostringstream oss;
    string word;
    bool first = true;
    while (iss >> word) {
        if (!first)
            oss << " ";
        oss << word;
        first = false;
    }
    return oss.str();
}

void Polyline_::parsePoints2(string s, vector<pair<float, float>>& allPoints) {

    int i = 0;
    s = standardization_Poly(s);
    while (i < s.length()) {
        if (isdigit(s[i]) || s[i] == '-' || s[i] == '.' || s[i] == ' ') {
            size_t next_pos;
            float x = stof(s.substr(i), &next_pos);
            i += next_pos + 1;
            float y = stof(s.substr(i), &next_pos);
            i += next_pos;
            allPoints.push_back(make_pair(x, y));
        }
    }
}


Polyline_::Polyline_(const string& points, float fillOpacity, float strokeOpacity, float strokeWidth, RGB fillRGB, RGB strokeRGB, Transform transform, string fill, string stroke)
    : points(points), Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke) {
    parsePoints2(points, allPoints);
}

void Polyline_::Draw(Graphics& graphics, vector<Defs*>& defs) {
    vector<PointF> pointsArray;
    for (const auto& point : allPoints) {
        pointsArray.push_back(PointF(static_cast<float>(point.first), static_cast<float>(point.second)));
    }

    PointF* pointsArrayPtr = pointsArray.data();
    int numPoints = static_cast<int>(pointsArray.size());

    Pen polylinePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);
    SolidBrush polylineBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    GraphicsState state = TransformSVG(graphics, transform);
    if (numPoints > 0) {
        if (fillRGB.r == 256 && fillRGB.b == 256 && fillRGB.g == 256)
            graphics.DrawLines(&polylinePen, pointsArrayPtr, numPoints);
        else {
            graphics.FillPolygon(&polylineBrush, pointsArrayPtr, numPoints);
            graphics.DrawLines(&polylinePen, pointsArrayPtr, numPoints);
        }
    }
    graphics.Restore(state);
}